#include <stdlib.h>
#include "SDL/SDL.h"

#include "updateTimer.hpp"
#include "game.hpp"

int main()
{
  // Start up SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Surface *display;
  display = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE); // HWSURFACE?
  if(display == NULL)
  {
    fprintf(stderr, "Could not initialize video: %s\n", SDL_GetError());
    exit(1);
  }

  UpdateTimer* updateTimer = new UpdateTimer();
  Game* game = new Game(display);
  
  while(true)
    if(updateTimer->timeToUpdate())
      game->frame();

  delete game;
  atexit(SDL_Quit);
}
