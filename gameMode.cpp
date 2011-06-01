#include "gameMode.hpp"

GameMode::GameMode(SDL_Surface* display, GlobalStore* globalStore)
{
  this->display = display;
  this->globalStore = globalStore;
}

int GameMode::frame()
{
  return 0;
}
