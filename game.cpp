#include "game.hpp"
#include "playMode.hpp"
#include "menuMode.hpp"

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
}

Game::~Game()
{
  delete globalStore;
  delete playMode;
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
      drawGameOver();
      break;

    default:
      break;
  }

  SDL_Flip(display);
}

void Game::drawGameOver()
{
  std::ostringstream s;
  s << globalStore->seconds << " seconds " << globalStore->obstacles << " obstacles.";
  SDL_Surface* text = TTF_RenderText_Shaded(menuFont, s.str().c_str(), clrWhite, clrBlack);
  SDL_Rect textLocation = { 100,100, 0,0 };
  SDL_BlitSurface(text, NULL, display, &textLocation);
  SDL_FreeSurface(text);

  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_MOUSEBUTTONDOWN:
        mode = MENU;
    }
  }
}
