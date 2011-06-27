#ifndef GAME
#define GAME

#include <string>
#include <sstream>

#include "gameMode.hpp"
#include "mode.hpp"
#include "playMode.hpp"
#include "menuMode.hpp"
#include "gameOverMode.hpp"

class Game
{
  private:
    Mode mode;
    SDL_Surface* display;

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
