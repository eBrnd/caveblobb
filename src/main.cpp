#include <iostream>
#include <SDL.h>
#include <SDL_framerate.h>

#include "game.hpp"

int main(int argc, char** argv)
{
  // Start up SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  int sdlopts = 0;
  if(argc > 1)
  {
    std::string fullscreen ("--fullscreen");
    if(!fullscreen.compare(argv[1]))
      sdlopts = SDL_SWSURFACE | SDL_FULLSCREEN;
    else
      sdlopts = SDL_SWSURFACE;
  }

  SDL_Surface *display;
  display = SDL_SetVideoMode(800, 600, 32, sdlopts); // HWSURFACE?
  if(display == NULL)
  {
    std::cout << "Could not initialize video: " << SDL_GetError() << std::endl;
    exit(1);
  }

  Game* game = new Game(display);

  FPSmanager* fpsmanager = new FPSmanager();
  SDL_initFramerate(fpsmanager);
  SDL_setFramerate(fpsmanager, 60);
  
  atexit(SDL_Quit);

  while(true)
  {
    SDL_framerateDelay(fpsmanager);
    game->frame();
  }
}
