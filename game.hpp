#ifndef GAME
#define GAME

#include "SDL/SDL_ttf.h"
#include "gameMode.hpp"
#include "mode.hpp"

class Game
{
  private:
    Mode mode;
    SDL_Surface* display;

    TTF_Font* menuFont;
    SDL_Color clrWhite;
    SDL_Color clrBlack;

    GlobalStore* globalStore;
    GameMode* playMode;
    GameMode* menuMode;
    GameMode* gameOverMode;
  public:
    Game(SDL_Surface* display);
    ~Game();
    void frame();
};

#endif
