#ifndef GAMEOVERMODE
#define GAMEOVERMODE

#include <string>
#include <sstream>

#include "SDL/SDL_ttf.h"

#include "gameMode.hpp"
#include "mode.hpp"
#include "colorsAndFonts.hpp"

class GameOverMode : public GameMode
{
  private:
    TTF_Font* gameOverFont, * bigFont;
    SDL_Color clrWhite, clrBlack;
  public:
    GameOverMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
};

#endif
