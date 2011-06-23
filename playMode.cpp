#include "playMode.hpp"


PlayMode::PlayMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  scoreFont = ColorsAndFonts::getInstance()->sans18;
  clrWhite = ColorsAndFonts::getInstance()->white;
  clrBlack = ColorsAndFonts::getInstance()->black;
  reset();
}

void PlayMode::reset()
{
  srand(time(NULL));

  player_pos = 300;
  player_vel = 0;

  frames_to_corner = 1;
  frames_to_obstacle = 60;
  corner_at = 80;
  level_height = 340;
  up = true; // since mouse button is still pressed from the click in the menu when the game starts
  slope = 0;
  playtime = 0;
  passed = 0;
  special = 0;

  obstacle_distance = 160;

  explosion_x = explosion_y = explosion_size = 0;

  crashed = false;

  // init with constant values
  for(int i = 0; i < 160; i++)
  {
    walls_top[i] = 80;
    walls_bottom[i] = walls_top[i] + level_height;
    obstacles[i] = 0;
  }
  for(int i = 0; i < 131; i++)
  {
    shot[i] = 0;
  }
  for(int i = 0; i < 300; i++)
  {
    tail[i].x = 0;
  }
}

inline void PlayMode::FillRect(int x, int y, int w, int h, int color)
{
  SDL_Rect rect = {x,y,w,h};
  SDL_FillRect(display, &rect, color);
}

Mode PlayMode::frame()
{
  if(!crashed)
  {
    if(!handleInput())
      return MENU;
    moveField();
    updatePlayer();
    generateWalls();
    generateObstacles();
  }
  updatePlayerTail();
  drawPlayerTail();
  drawStuff();
  collisionDetect();
  obstacleCounter();
  drawScorePanel();
  if(crashed && !explosion_size)
  {
    globalStore->seconds = playtime / 60;
    globalStore->score = playtime;
    globalStore->obstacles = passed;
    return GAMEOVER;
  }

  return PLAY;
}

void PlayMode::moveField()
{
  for(int i = 0; i < 159; i++) // move the walls and obstacles
  {
    walls_top[i] = walls_top[i+1];
    walls_bottom[i] = walls_bottom[i+1];
    obstacles[i] = obstacles[i+1];
  }

  // add new wall bits
  walls_top[159] = corner_at + (slope * frames_to_corner);
  walls_bottom[159] = walls_top[159] + level_height;

  // make level smaller
  if(playtime % 30 == 0 && level_height > 51)
    level_height--;

  // move shot (to the right!)
  for(int i = 130; i > 0; i--)
  {
    shot[i] = shot[i-1];
  }
  shot[0] = 0;

  // move explosion
  explosion_x -= 4;
}

void PlayMode::updatePlayerTail()
{
  // move player tail
  for(int i = 0; i < 293; i++)
  {
    tail[i] = tail[i+6];
    tail[i+1] = tail[i+7];
    tail[i+2] = tail[i+8];
    tail[i+3] = tail[i+9];
    tail[i+4] = tail[i+10];
    tail[i+5] = tail[i+11];
  }

  // add six new player tail particles
  if(!crashed)
  {
    for(int i = 299; i >= 294; i--)
    {
      tail[i].x = 140.f;
      tail[i].y = player_pos + 5;

      float angle = ((float)rand() / (float)RAND_MAX) * 360;
      float speed = ((float)rand() / (float)RAND_MAX) + 5;
      tail[i].color = hue2rgb(angle - 60);

      angle = angle / 12 - 195;
      angle = angle * (3.14159265 / 180); // radian
      tail[i].vx = cos(angle) * speed;
      tail[i].vy = sin(angle) * speed;
    }
  } else
  {
    tail[294].x = tail[295].x = tail[296].x = tail[297].x = tail[298].x = tail[299].x = 0;
  }
}

void PlayMode::drawStuff()
{
  // draw the walls and obstacles and the shot
  for(int i = 0; i < 160; i++)
  {
    FillRect(5 * i, 0, 5, walls_top[i], 0x309930);
    FillRect(5 * i, walls_bottom[i], 5, 599 - walls_bottom[i], 0x309930);
    if(obstacles[i])
      FillRect(5 * i, obstacles[i], 5, 50, 0x309930);
    if(i < 131 && shot[i])
      FillRect(5 * i + 140, shot[i], 5, 5, 0xFFFFFF);
  }

  if(!crashed)
  {
    // draw the player
    filledCircleColor(display, 145,(int)(player_pos + 4.5f), 5, 0x9DD8F6FF);
  }

  // draw explosion
  if(explosion_size)
  {
    filledCircleColor(display, explosion_x, explosion_y, explosion_size-=2, 0xFFFF00FF);
  }
}

void PlayMode::generateWalls()
{
  if(!frames_to_corner--)
  {
    int last_corner = corner_at;
    frames_to_corner = 10 + (rand() % 160);
    corner_at = rand() % (600 - level_height);
    slope = ((float)last_corner - (float)corner_at) / frames_to_corner;
    while(abs(slope) > level_height / 45) // infinite loop if height is smaller than 0 - but who would do that?
    {
      frames_to_corner += 10;
      slope = ((float)last_corner - (float)corner_at) / frames_to_corner;
    }
  }
}

void PlayMode::generateObstacles()
{
  obstacles[159] = 0;
  if(!frames_to_obstacle--)
  {
    obstacles[157] = obstacles[158] = obstacles[159] = walls_top[159] + (rand() % (level_height - 50));
    frames_to_obstacle = 10 + rand() % obstacle_distance;
  }
}

bool PlayMode::handleInput()
{
  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_MOUSEBUTTONDOWN:
        up = true;
        break;
      case SDL_MOUSEBUTTONUP:
        up = false;
        break;
      case SDL_KEYDOWN:
        std::string esc ("escape");
        std::string space ("space");
        if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
          return false;
        if(special > 25 && !space.compare(SDL_GetKeyName(event.key.keysym.sym)))  // fire shot
        {
          shot[0] = player_pos;
          shot[1] = player_pos; // shot needs to be 2 columns long because the shot moves to the right and the level to the left, and we have to make sure it overlaps with every column at least once
          special -= 25;
        }
    }
  }
  return true;
}

void PlayMode::updatePlayer()
{
  // move Player
  if(up)
    player_vel -= .1f;
  else
    player_vel += .1f;
  player_pos += player_vel;
}

void PlayMode::drawPlayerTail()
{
  for(int i = 0; i < 300; i++)
  {
    if(tail[i].x)
    {
      circleColor(display, (int)tail[i].x, (int)tail[i].y, 3, tail[i].color);
      tail[i].x += tail[i].vx;
      tail[i].y += tail[i].vy;
    }
  }
}

void PlayMode::collisionDetect()
{
  if( (int)player_pos < walls_top[28] && !crashed )
  {
    // crashed into top wall
    explosion_x = 140;
    explosion_y = player_pos + 5;
    explosion_size = 56;
    crashed = true;
  }
  if( (int)player_pos + 10 > walls_bottom[28] && !crashed )
  {
    // crashed into bottom wall
    explosion_x = 140;
    explosion_y = player_pos + 5;
    explosion_size = 56;
    crashed = true;
  }
  if( obstacles[28] && (int)player_pos + 10 > obstacles[28] && (int)player_pos < obstacles[28] + 50 && !crashed )
  {
    // crashed into obstacle
    explosion_x = 140;
    explosion_y = player_pos + 5;
    explosion_size = 56;
    crashed = true;
  }

  // detect near-crashes for special power
  if( !crashed && special < 100 && (
     (int)player_pos < walls_top[28] + 10 ||
     (int)player_pos + 10 > walls_bottom[28] - 10 ||
     (obstacles[28] && (int)player_pos + 10 > obstacles[28] - 10 && (int)player_pos < obstacles[28] + 60) ) )
    special++;

  // collision of shots with obstacles
  for(int i = 0; i < 131; i++)
  {
    if(shot[i] && shot[i] + 5 > obstacles[i+28] && shot[i] < obstacles[i+28] + 50)
    {
      obstacles[i+28] = 0;
      explosion_x = 5*(28+i);
      explosion_y = shot[i] + 3;
      explosion_size = 36;
    }
  }
  // ...and with walls
  for(int i = 1; i < 130; i++) // only from 1..130 because we have to delete 3 elements in the shots array to make sure the shot is erased completely
    if(shot[i] && (shot[i] + 5 > walls_bottom[i+28] || shot[i] < walls_top[i+28]))
    {
      explosion_x = 5*(28+i);
      explosion_y = shot[i] + 3;
      explosion_size = 36;
      shot[i-1] = shot[i] = shot[i+1] = 0;
    }
}

void PlayMode::obstacleCounter()
{
  if(obstacles[28] && !obstacles[29])
  {
    passed++;
    if((passed % 5) == 0 && obstacle_distance > 10)
      obstacle_distance--;
  }
}

void PlayMode::drawScorePanel()
{
  playtime++;
  if((int)player_pos > 60)
  {
    std::ostringstream s;
    s << " Score: " << playtime; // TODO Some more useful score counting - collect items or something

    int barHeight = 10; // if text is rendered, replace this with the height of the text
    if(scoreFont != NULL)
    {
      // Score text
      SDL_Surface* text = TTF_RenderText_Shaded(scoreFont, s.str().c_str(), clrWhite, clrBlack);
      SDL_Rect textLocation = { 17,17, 0,0 };

      FillRect(16,16, text->w + 2,text->h + 2, 0x0000FF);

      SDL_BlitSurface(text, NULL, display, &textLocation);
      SDL_FreeSurface(text);

      // "Special" bar
      text = TTF_RenderText_Shaded(scoreFont, "Special", clrWhite, clrBlack);

      FillRect(297 - text->w, 16, text->w + 204, text->h + 2, 0x0000FF);
      SDL_Rect specialLocation = { 299 - text->w,17, 0,0 };
      SDL_BlitSurface(text, NULL, display, &specialLocation);
      barHeight = text->h;
    }

    FillRect(300,17, 200, barHeight, 0x000000);
    FillRect(300,17, 2 * special, barHeight, 0xFFFF00);
    FillRect(350,17, 1, barHeight, 0x808080);
    FillRect(400,17, 1, barHeight, 0x808080);
    FillRect(450,17, 1, barHeight, 0x808080);
  }
}

Uint32 PlayMode::hue2rgb(float h)
{
  while(h > 360) h -= 360; // normalize to 360 degrees
  while(h < 0) h += 360;
  h = h / 60;
  float x = 1 - abs(fmod(h, 2)); // see Wikipedia - and in our case, C = 1.
  if(0 <= h && h < 1)
    return 0xFF0000FF | (Uint8)(x * 255) << 16; // r = 255, g = (x*255), b = 0, a = 255
  if(1 <= h && h < 2)
    return 0x00FF00FF | (Uint8)(x * 255) << 24;
  if(2 <= h && h < 3)
    return 0x00FF00FF | (Uint8)(x * 255) << 8;
  if(3 <= h && h < 4)
    return 0x0000FFFF | (Uint8)(x * 255) << 16;
  if(4 <= h && h < 5)
    return 0x0000FFFF | (Uint8)(x * 255) << 24;
  if(5 <= h && h < 6)
    return 0xFF0000FF | (Uint8)(x * 255) << 8;
  return 0;
}
