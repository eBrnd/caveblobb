#ifndef GAMEMODE
#define GAMEMODE

#include <SDL.h>

#include "globalStore.hpp"
#include "mode.hpp"
#include "colorsAndFonts.hpp"

class GameMode
{
  protected:
    SDL_Surface* display;
    GlobalStore* globalStore;
    ColorsAndFonts* caf;
  public:
    GameMode(SDL_Surface* display, GlobalStore* globalStore);
    virtual void reset() = 0;
    virtual Mode frame() = 0;
};

#endif
