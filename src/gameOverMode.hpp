#ifndef GAMEOVERMODE
#define GAMEOVERMODE

#include <string>
#include <sstream>

#include "gameMode.hpp"
#include "mode.hpp"
#include "permanentStorage.hpp"

class GameOverMode : public GameMode
{
  private:
    PermanentStorage* storage;
  public:
    GameOverMode(SDL_Surface* display, GlobalStore* globalStore, PermanentStorage* storage);
    Mode frame();
    void prepare();
    void reset();
    virtual ~GameOverMode() { }
};

#endif
