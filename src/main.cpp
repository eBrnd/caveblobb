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

  int sdlopts = SDL_SWSURFACE;

  for(int i = 1; i < argc; i++)
  {
    std::string fullscreen ("--fullscreen");
    std::string f ("-f");
    if(!fullscreen.compare(argv[i]) || !f.compare(argv[i]))
      // sdlopts = SDL_SWSURFACE | SDL_FULLSCREEN;
      std::cout << "Fullscreen is broken. Sorry!" << endl;
    std::string help ("--help");
    std::string h ("-h");
    if(!help.compare(argv[i]) || !h.compare(argv[i]))
    {
      std::cout << "~cavebl0bb~\n\nCommand line options:\n\t--fullscreen, -f\t\tStart in full screen mode." << std::endl;
      exit(0);
    }
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
