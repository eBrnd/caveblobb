#ifndef GAMEMODE
#define GAMEMODE

#include <SDL.h>

#include "globalStore.hpp"
#include "mode.hpp"
#include "font.hpp"

class GameMode
{
  protected:
    SDL_Surface* display;
    GlobalStore* globalStore;
    Font* font1, *font2, *font4, *font8;
  public:
    GameMode(SDL_Surface* display, GlobalStore* globalStore);
    virtual ~GameMode() { }
    virtual void reset() = 0;
    virtual Mode frame() = 0;
};

#endif
