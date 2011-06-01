#ifndef MENUMODE
#define MENUMODE

#include "gameMode.hpp"
#include "SDL/SDL_ttf.h"

class MenuMode : public GameMode
{
  private:
    TTF_Font* menuFont;
    SDL_Color clrWhite, clrBlack;
  public:
    MenuMode(SDL_Surface* display, GlobalStore* globalStore);
    int frame();
    void reset();
};

#endif
