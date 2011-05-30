#include <string>

class GameMode
{
  private:
    SDL_Surface* display;

    int walls_top[160], walls_bottom[160];

  public:
    GameMode(SDL_Surface* display)
    {
      this->display = display;

      // for testing purposes, init with constant values
      for(int i = 0; i < 160; i++)
      {
        walls_top[i] = 80;
        walls_bottom[i] = 440;
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
      for(int i = 0; i < 159; i++) // move the walls
      {
        walls_top[i] = walls_top[i+1];
        walls_bottom[i] = walls_bottom[i+1];
      }
      walls_top[159] = 90;
      walls_bottom[159] = 420;

      // draw the walls
      for(int i = 0; i < 800; i++)
      {
        FillRect(5 * i, 0, 5, walls_top[i], 0x80FF80);
        FillRect(5 * i, walls_bottom[i], 5, 599 - walls_bottom[i], 0x80FF80);
      }

      // TODO draw the obstacles

      // Grab the input
      SDL_Event event;
      if(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          case SDL_KEYDOWN:
              std::string esc ("escape");
              if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
                return 1;
        }
      }

      // TODO draw the player

      // TODO collision detection

      return 0;
    }
};
