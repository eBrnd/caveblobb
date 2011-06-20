#ifndef MENUMODE
#define MENUMODE

#include <string>

#include "SDL/SDL_ttf.h"

#include "gameMode.hpp"
#include "mode.hpp"
#include "colorsAndFonts.hpp"

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
