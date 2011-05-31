#include <string>

class GameMode
{
  private:
    SDL_Surface* display;

    int walls_top[160], walls_bottom[160], obstacles[160], player_tail[29];
    float player_pos, player_vel;
    bool up;
    int frames_to_corner, corner_at, level_height, frames_to_obstacle;
    float slope;
  public:
    GameMode(SDL_Surface* display)
    {
      this->display = display;
      reset();
    }

    void reset()
    {
      player_pos = 300;
      player_vel = 0;

      frames_to_corner = 1;
      corner_at = 80;
      level_height = 340;
      up = true; // since mouse button is still pressed from the click in the menu when the game starts
      slope = 0;

      // for testing purposes, init with constant values
      for(int i = 0; i < 160; i++)
      {
        walls_top[i] = 80;
        walls_bottom[i] = walls_top[i] + level_height;
        obstacles[i] = 0;
      }
      for(int i = 0; i < 29; i++)
      {
        player_tail[i] = 300;
      }
    }

    inline void FillRect(int x, int y, int w, int h, int color)
    {
      SDL_Rect rect = {x,y,w,h};
      SDL_FillRect(display, &rect, color);
    }

    int frame()
    {
      // move all objects
      for(int i = 0; i < 159; i++) // move the walls and obstacles
      {
        walls_top[i] = walls_top[i+1];
        walls_bottom[i] = walls_bottom[i+1];
        obstacles[i] = obstacles[i+1];
      }
      for(int i = 0; i < 28; i++)
        player_tail[i] = player_tail[i+1];

      //draw new wall bits
      walls_top[159] = corner_at + (slope * frames_to_corner);
      walls_bottom[159] = walls_top[159] + level_height;

      // draw the walls and obstacles and the player tail
      for(int i = 0; i < 160; i++)
      {
        FillRect(5 * i, 0, 5, walls_top[i], 0x309930);
        FillRect(5 * i, walls_bottom[i], 5, 599 - walls_bottom[i], 0x309930);
        if(obstacles[i])
          FillRect(5 * i, obstacles[i], 5, 50, 0x309930);
        if(i < 29)
          FillRect(5 * i, player_tail[i], 5, 10, 0xFF0000);
      }

      // generate walls
      if(!frames_to_corner--)
      {
        int last_corner = corner_at;
        frames_to_corner = 10 + (rand() % 160);
        corner_at = rand() % (600 - level_height);
        slope = ((float)last_corner - (float)corner_at) / frames_to_corner;
      }

      // generate obstacles
      obstacles[159] = 0;
      if(!frames_to_obstacle--)
      {
        obstacles[157] = obstacles[158] = obstacles[159] = walls_top[159] + (rand() % (level_height - 50));
        frames_to_obstacle = 10 + rand() % 160;
      }

      // Grab the input
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
            if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
              return 1;
        }
      }

      // physics
      if(up)
        player_vel -= .1f;
      else
        player_vel += .1f;
      player_pos += player_vel;

      // draw the player
      FillRect(140,(int)player_pos, 10,10, 0xFF0000);
      player_tail[28] = (int)player_pos;

      // collision detection
      if( (int)player_pos < walls_top[28] ||
          (int)player_pos + 10 > walls_bottom[28] ||
          ((int)player_pos + 10 > obstacles[28] && (int)player_pos < obstacles[28] + 50))
        return 2;

      return 0;
    }
};
