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

    void frame()
    {
      // TODO move all objects

      // TODO draw the walls
      for(int i = 0; i < 800; i++)
      {
        FillRect(5 * i, 0, 5, walls_top[i], 0x80FF80);
        FillRect(5 * i, walls_bottom[i], 5, 599 - walls_bottom[i], 0x80FF80);
      }

      // TODO draw the obstacles

      // TODO draw the player

      // TODO collision detection

    }
};
