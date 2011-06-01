#ifndef GAME
#define GAME

#include "SDL/SDL_ttf.h"
#include "gameMode.hpp"

class Game
{
  private:
    enum Mode { MENU, PLAY, GAMEOVER };
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
