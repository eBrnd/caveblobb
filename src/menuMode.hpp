#ifndef MENUMODE
#define MENUMODE

#include <string>
#include <sstream>

#include <config/config.h>
#include "gameMode.hpp"
#include "mode.hpp"

class MenuMode : public GameMode
{
  private:
  public:
    MenuMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
    virtual ~MenuMode() { }
};

#endif
