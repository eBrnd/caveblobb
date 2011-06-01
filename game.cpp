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
      switch(menuMode->frame())
      {
        case 0:
          break;
        case 1:
          playMode->reset();
          mode = PLAY;
          break;
      }
      break;

    case PLAY:
      switch(playMode->frame())
      {
        case 0:
          break;
        case 1:
          mode = MENU;
          break;
        case 2:
          mode = GAMEOVER;
          break;
      }
      break;

    case GAMEOVER:
      switch(gameOverMode->frame())
      {
        case 0:
          break;
        case 1:
          mode = MENU;
          break;
      }
      break;

    default:
      break;
  }

  SDL_Flip(display);
}
