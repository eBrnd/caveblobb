#ifndef COLORS
#define COLORS

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Colors
{
  private:
    Colors();
    static Colors* pointer;
  public:
    TTF_Font* sans18;
    SDL_Color white, black;
    static Colors* getInstance();
};

#endif
