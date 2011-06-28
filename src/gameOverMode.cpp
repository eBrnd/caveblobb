#include "gameOverMode.hpp"


GameOverMode::GameOverMode(SDL_Surface* display, GlobalStore* globalStore, PermanentStorage* storage)
  : GameMode(display, globalStore)
{
  this->storage = storage;
}

Mode GameOverMode::frame()
{
  std::ostringstream s;
  s << globalStore->seconds << " seconds, " << globalStore->obstacles << " obstacles passed, " << globalStore->stars << " stars collected.";
  char* sc = (char*)s.str().c_str();
  fontm->write(display, 400 - fontm->textWidth(1, sc) / 2, 180, 1, sc);

  char* ps = (char*)"Press space to continue.";
  fontm->write(display, 400 - fontm->textWidth(1, ps) / 2, 520, 1, ps);

  std::ostringstream p;
  p << "Score: " << globalStore->score;
  char* pc = (char*)p.str().c_str();
  fontm->write(display, 400 - fontm->textWidth(3, pc) / 2, 80, 3, pc);

  fontm->write(display, 100, 240, 1, (char*)"Highscores:");
  for(int i = 0; i < 5; i++)
  {
    std::ostringstream h;
    h << i+1 << ". -  " << storage->getHighscore(i);
    fontm->write(display, 290, 270 + 30 * i, 1, (char*)h.str().c_str());
  }

  char* t = (char*)"Press T to tweet your score!";
  fontm->write(display, 400 - fontm->textWidth(1,t) / 2, 460, 1, t);

  if(!storage->getBrowser().length())
  {
    char* n = (char*)">>> Browser not set. Please edit ~/.caveblobb <<<";
    fontm->write(display, 400 - fontm->textWidth(0,n) / 2, 490, 0, n);
  }

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_KEYDOWN:
        std::string space ("space");
        if(!space.compare(SDL_GetKeyName(event.key.keysym.sym)))
        {
          storage->write();
          return MENU;
        }
        std::ostringstream s;
        switch(event.key.keysym.sym)
        {
          case ' ':
            storage->write();
            return MENU;
            break;
          case 't':
            s << storage->getBrowser() << " \"https://twitter.com/intent/tweet?text=I+just+got+" << globalStore->score << "+points+playing&hashtags=caveblobb\"";
            system(s.str().c_str());
            break;
          default:
            break;
        }
    }
  }

  return GAMEOVER;
}

void GameOverMode::reset()
{}
