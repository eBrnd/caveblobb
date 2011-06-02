#ifndef UPDATETIMER
#define UPDATETIMER

#include "SDL/SDL.h"
#include "SDL/SDL_framerate.h"

class UpdateTimer
{
  private:
    FPSmanager* manager;

  public:
    UpdateTimer();
    bool timeToUpdate();
};

#endif
