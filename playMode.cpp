#include "playMode.hpp"

#include "colorsAndFonts.hpp"

#include <string>
#include <sstream>

PlayMode::PlayMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  scoreFont = ColorsAndFonts::getInstance()->sans18;
  clrWhite = ColorsAndFonts::getInstance()->white;
  clrBlack = ColorsAndFonts::getInstance()->black;
  // TODO Initialize random generator
  reset();
}

void PlayMode::reset()
{
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
  special = false;

  obstacle_distance = 160;

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
  moveField();
  drawStuff();
  generateWalls();
  generateObstacles();
  if(!handleInput())
    return MENU;
  updatePlayer();
  drawPlayerTail();
  if(collisionDetect())
  {
    globalStore->seconds = playtime / 60;
    globalStore->score = playtime;
    globalStore->obstacles = passed;
    return GAMEOVER;
  }
  obstacleCounter();
  drawScorePanel();

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

  // move player tail
  for(int i = 0; i < 299; i++)
    tail[i] = tail[i+1];

  
  // add new player tail particle
  tail[299].x = 140.f;
  tail[299].y = player_pos;
  tail[299].vx = ((float)rand() / (float)RAND_MAX) - 5;
  tail[299].vy = ((float)rand() / (float)RAND_MAX) - .5f;
  tail[299].r = rand() % 128 + 128;
  tail[299].g = rand() % 128 + 128;
  tail[299].b = rand() % 128 + 128;
  // Idee: Die Dinger mit wenig Geschwindigkeit starten, dann
  // konstant nach links beschleunigen ^^
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
        if(special && !space.compare(SDL_GetKeyName(event.key.keysym.sym)))  // fire shot
        {
          shot[0] = player_pos;
          shot[1] = player_pos; // shot needs to be 2 columns long because the shot moves to the right and the level to the left, and we have to make sure it overlaps with every column at least once
          special = false;
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

  // draw the player
  circleColor(display, 140,(int)player_pos, 5, 0xFF0000FF);
  // TODO atm the player is not drawn where it is supposed to be. player_pos refers to the upper left corner of the sprite if its 10 pixels large.
}

void PlayMode::drawPlayerTail()
{
  for(int i = 0; i < 300; i++)
  {
    aacircleColor(display, (int)tail[i].x, (int)tail[i].y, 0, tail[i].r << 24 | tail[i].g << 16 | tail[i].b << 8 | 255);
    tail[i].x += tail[i].vx;
    tail[i].y += tail[i].vy;
  }
}

bool PlayMode::collisionDetect()
{
  if( (int)player_pos < walls_top[28] )
  {
    // crashed into top wall
    return true;
  }
  if( (int)player_pos + 10 > walls_bottom[28] )
  {
    // crashed into bottom wall
    return true;
  }
  if( obstacles[28] && (int)player_pos + 10 > obstacles[28] && (int)player_pos < obstacles[28] + 50 )
  {
    // crashed into obstacle
    return true;
  }

  // detect near-crashes for special power
  if((int)player_pos < walls_top[28] + 10 ||
     (int)player_pos + 10 > walls_bottom[28] - 10 ||
     (obstacles[28] && (int)player_pos + 10 > obstacles[28] - 10 && (int)player_pos < obstacles[28] + 60) )
    special = true;

  // collision of shots with obstacles
  // TODO Collision of shots with walls
  for(int i = 0; i < 131; i++)
  {
    if(shot[i] + 5 > obstacles[i+28] && shot[i] < obstacles[i+28] + 50)
      obstacles[i+28] = 0;
  }

  return false;
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
    s << " Score: " << playtime << " ";
    if(special)
      s << "++SPECIAL++";
    SDL_Surface* text = TTF_RenderText_Shaded(scoreFont, s.str().c_str(), clrWhite, clrBlack);
    SDL_Rect textLocation = { 17,17, 0,0 };

    FillRect(16,16, text->w + 2,text->h + 2, 0x0000FF);

    SDL_BlitSurface(text, NULL, display, &textLocation);
    SDL_FreeSurface(text);
  }
}
