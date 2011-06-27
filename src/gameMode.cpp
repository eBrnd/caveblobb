#include "gameMode.hpp"

#include <iostream>

GameMode::GameMode(SDL_Surface* display, GlobalStore* globalStore)
{
  this->display = display;
  this->globalStore = globalStore;
  this->fontm = FontManager::getInstance();
}
