#include "game.hpp"

Game::Game(SDL_Surface* display)
{
  // init private variables
  mode = MENU;
  this->display = display;
  globalStore = new GlobalStore();
  storage = new PermanentStorage();

  // init game modes
  playMode = new PlayMode(display, globalStore, storage);
  menuMode = new MenuMode(display, globalStore);
  gameOverMode = new GameOverMode(display, globalStore, storage);
}

Game::~Game()
{
  delete (PlayMode*)playMode;
  delete (MenuMode*)menuMode;
  delete (GameOverMode*)gameOverMode;
  delete globalStore;
  delete storage;
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
