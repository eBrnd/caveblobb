#include "updateTimer.hpp"

UpdateTimer::UpdateTimer()
{
  manager = new FPSmanager();
  SDL_initFramerate(manager);
  SDL_setFramerate(manager, 60);
}

bool UpdateTimer::timeToUpdate()
{
  SDL_framerateDelay(manager);
  return true;
}
