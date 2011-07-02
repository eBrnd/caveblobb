#include <iostream>
#include <SDL.h>
#include <SDL_framerate.h>

#include "game.hpp"
#include <config/config.h>

#include "font.hpp"

int main(int argc, char** argv)
{
  std::cout << "Caveblobb version " << VERSION_MAJOR << "." 
    << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
  if(HAS_MACOS)
    std::cout << "Running on MacOS" << std::endl;

  // Start up SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  int sdlopts = SDL_SWSURFACE | SDL_DOUBLEBUF;

  for(int i = 1; i < argc; i++)
  {
    std::string fullscreen ("--fullscreen");
    std::string f ("-f");
    if(!fullscreen.compare(argv[i]) || !f.compare(argv[i]))
      sdlopts = SDL_SWSURFACE | SDL_FULLSCREEN;
    std::string help ("--help");
    std::string h ("-h");
    if(!help.compare(argv[i]) || !h.compare(argv[i]))
    {
      std::cout << "~cavebl0bb~\n\nCommand line options:\n\t--fullscreen, -f\t\tStart in full screen mode." << std::endl;
      exit(0);
    }
  }

  // TODO add a command line switch to override the color depth setting manually
  int colordepth = 32;
#ifdef HAS_MACOS
  if(HAS_MACOS & !(sdlopts & SDL_FULLSCREEN))
    colordepth = 24; // somehow the colors look odd on a mac if you choose 32 or 0 in windowes mode. Fullscreen works though.
#endif

  SDL_Surface *display;
  display = SDL_SetVideoMode(800, 600, colordepth, sdlopts); // HWSURFACE?
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
