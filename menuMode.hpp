#ifndef MENUMODE
#define MENUMODE

#include "gameMode.hpp"
#include "SDL/SDL_ttf.h"
#include "mode.hpp"

class MenuMode : public GameMode
{
  private:
    TTF_Font* menuFont, * titleFont;
    SDL_Color clrWhite, clrBlack;
  public:
    MenuMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
};

#endif
