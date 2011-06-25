#include <iostream>
#include <ctime>
#include <SDL.h>
#include <SDL_framerate.h>
#include <boost/random.hpp>

#include "game.hpp"

int main(int argc, char** argv)
{

  typedef boost::mt19937 RNGType; 
  RNGType rng;                
  rng.seed(static_cast<unsigned int>(std::time(0)));
  boost::uniform_real<> zero2one( 0, 1);
  boost::variate_generator< RNGType, boost::uniform_real<> > random(rng, zero2one);          
  for ( int i = 1; i < 6; i++ ) {
    double n  = random();
    std::cout << "OMG Zufall! " << n << std::endl;
  }

  // Start up SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  SDL_Surface *display;
  display = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE); // HWSURFACE?
  if(display == NULL)
  {
    std::cout << "Could not initialize video: " << SDL_GetError() << std::endl;
    exit(1);
  }

  Game* game = new Game(display);

  FPSmanager* fpsmanager = new FPSmanager();
  SDL_initFramerate(fpsmanager);
  SDL_setFramerate(fpsmanager, 60);
  
  while(true)
  {
    SDL_framerateDelay(fpsmanager);
    game->frame();
  }

  delete game;
  atexit(SDL_Quit);
}
