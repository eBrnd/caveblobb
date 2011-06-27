#include "gameOverMode.hpp"


GameOverMode::GameOverMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
}

Mode GameOverMode::frame()
{
  std::ostringstream s;
  s << globalStore->seconds << " seconds, " << globalStore->obstacles << " obstacles, " << globalStore->stars << " stars.";
  char* sc = (char*)s.str().c_str();
  fontm->write(display, 400 - fontm->textWidth(1, sc) / 2, 400, 1, sc);

  char* ps = (char*)"Press space to continue.";
  fontm->write(display, 400 - fontm->textWidth(1, ps) / 2, 440, 1, ps);

  std::ostringstream p;
  p << "Score: " << globalStore->score;
  char* pc = (char*)p.str().c_str();
  fontm->write(display, 400 - fontm->textWidth(2, pc) / 2, 200, 2, pc);

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_KEYDOWN:
        std::string space ("space");
        if(!space.compare(SDL_GetKeyName(event.key.keysym.sym)))
          return MENU;
    }
  }

  return GAMEOVER;
}

void GameOverMode::reset()
{}
