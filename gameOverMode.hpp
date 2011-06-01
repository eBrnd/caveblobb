#ifndef GAMEOVERMODE
#define GAMEOVERMODE

#include "gameMode.hpp"
#include "SDL/SDL_ttf.h"
#include "mode.hpp"

class GameOverMode : public GameMode
{
  private:
    TTF_Font* gameOverFont;
    SDL_Color clrWhite, clrBlack;
  public:
    GameOverMode(SDL_Surface* display, GlobalStore* globalStore);
    Mode frame();
    void reset();
};

#endif
