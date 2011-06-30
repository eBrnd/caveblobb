#ifndef MENUMODE
#define MENUMODE

#include <string>

#include "gameMode.hpp"
#include "mode.hpp"
#include "font.hpp"

class MenuMode : public GameMode
{
  private:
    Font* font;
  public:
    MenuMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
};

#endif
