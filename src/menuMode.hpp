#ifndef MENUMODE
#define MENUMODE

#include <string>

#include <SDL_ttf.h>

#include "gameMode.hpp"
#include "mode.hpp"

class MenuMode : public GameMode
{
  private:
  public:
    MenuMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
};

#endif
