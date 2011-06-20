#include "game.hpp"

Game::Game(SDL_Surface* display)
{
  // init private variables
  mode = MENU;
  this->display = display;
  globalStore = new GlobalStore();

  // init game modes
  playMode = new PlayMode(display, globalStore);
  menuMode = new MenuMode(display, globalStore);
  gameOverMode = new GameOverMode(display, globalStore);
}

Game::~Game()
{
  delete playMode;
  delete menuMode;
  delete gameOverMode;
  delete globalStore;
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
      exit(0);      // still not sure whether here is the right place to do this
    default:
      break;
  }

  SDL_Flip(display);
}
