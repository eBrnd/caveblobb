#include "game.hpp"
#include "playMode.hpp"
#include "menuMode.hpp"
#include "gameOverMode.hpp"

#include <iostream>
#include <string>
#include <sstream>

Game::Game(SDL_Surface* display)
{
  // init private variables
  mode = MENU;
  this->display = display;

  // init fonts + colors for menu
  TTF_Init();
  menuFont = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
  clrWhite = { 255,255,255, 0 };
  clrBlack = { 0,0,0, 0 };

  globalStore = new GlobalStore();

  // init game mode
  playMode = new PlayMode(display, globalStore);
  menuMode = new MenuMode(display, globalStore);
  gameOverMode = new GameOverMode(display, globalStore);
}

Game::~Game()
{
  delete globalStore;
  delete playMode;
  delete menuMode;
  delete gameOverMode;
}

void Game::frame()
{
  SDL_FillRect(display, NULL, 0); // clear the buffer

  switch(mode)
  {
    case MENU:
      mode = menuMode->frame();
      break;
    case START:
      playMode->reset();
      mode = PLAY;
    case PLAY:
      mode = playMode->frame();
      break;
    case GAMEOVER:
      mode = gameOverMode->frame();
      break;
    case QUIT:
      SDL_Quit();
      exit(0);      // still not sure whether here is the right play to do this
    default:
      break;
  }

  SDL_Flip(display);
}
