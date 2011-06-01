#include "updateTimer.hpp"

#include "SDL/SDL.h"

UpdateTimer::UpdateTimer()
{
  lastUpdate = 0;
}
bool UpdateTimer::timeToUpdate()
{
  Uint32 time = SDL_GetTicks();
  if(lastUpdate + 17 < time)
  {
    lastUpdate = time;
    return true;
  } else
    return false;
}
