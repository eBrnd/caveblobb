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

    GameMode* playMode;
    GameMode* menuMode;
    GlobalStore* globalStore;
  public:
    Game(SDL_Surface* display);
    ~Game();
    void frame();
    void drawGameOver(); // TODO as should GameOver! - And make it inherit from the same superclass for great Objektorientierung!
};

#endif
