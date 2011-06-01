#ifndef GAMEMODE
#define GAMEMODE

#include "SDL/SDL.h"
#include "globalStore.hpp"

class GameMode
{
  protected:
    SDL_Surface* display;
    GlobalStore* globalStore;
  public:
    GameMode(SDL_Surface* display, GlobalStore* globalStore);
    virtual void reset() = 0;
    virtual int frame() = 0;
};

#endif
