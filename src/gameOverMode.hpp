#ifndef GAMEOVERMODE
#define GAMEOVERMODE

#include <string>
#include <sstream>

#include <SDL_ttf.h>

#include "gameMode.hpp"
#include "mode.hpp"
#include "colorsAndFonts.hpp"

class GameOverMode : public GameMode
{
  public:
    GameOverMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
};

#endif
