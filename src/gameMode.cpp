#include "gameMode.hpp"

#include <iostream>

GameMode::GameMode(SDL_Surface* display, GlobalStore* globalStore)
{
  this->display = display;
  this->globalStore = globalStore;
  this->font1 = new Font();
  if(!font1->loadImg("/usr/local/share/caveblobb/font.png"))
    font1->loadImg("/usr/share/caveblobb/font.png");
  this->font2 = new Font();
  if(!font2->loadImg("/usr/local/share/caveblobb/font2x.png"))
    font2->loadImg("/usr/share/caveblobb/font2x.png");
  this->font4 = new Font();
  if(!font4->loadImg("/usr/local/share/caveblobb/font4x.png"))
    font4->loadImg("/usr/share/caveblobb/font4x.png");
  this->font8 = new Font();
  if(!font8->loadImg("/usr/local/share/caveblobb/font8x.png"))
    font8->loadImg("/usr/share/caveblobb/font8x.png");
}
