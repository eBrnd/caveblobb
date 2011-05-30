#include <stdlib.h>
#include "SDL/SDL.h"

#include "game.cpp"

int main()
{
  // Start up SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Surface *display;
  display = SDL_SetVideoMode(800, 600, 16, SDL_SWSURFACE); // HWSURFACE?
  if(display == NULL)
  {
    fprintf(stderr, "Could not initialize video: %s\n", SDL_GetError());
    exit(1);
  }

  Game* game = new Game(display);
  game->frame();

  atexit(SDL_Quit);
}
