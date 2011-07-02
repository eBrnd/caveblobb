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
  font2->writeCentered(display, 400, 180, s.str());

  font2->writeCentered(display, 400, 520, "Press space to continue.");

  std::ostringstream p;
  p << "Score: " << globalStore->score;
  font8->writeCentered(display, 400, 80, p.str());

  font2->write(display, 100, 240, "Highscores:");
  for(int i = 0; i < 5; i++)
  {
    std::ostringstream h;
    h << i+1 << ". -  " << storage->getHighscore(i);
    font2->write(display, 290, 270 + 30 * i, h.str());
  }

  font2->writeCentered(display, 400, 460, "Press T to tweet your score!");

  if(storage->getBrowser() == "false")
  {
    font1->writeCentered(display, 400, 490, ">>> Browser not set. Please edit ~/.caveblobb <<<");
  }

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    std::ostringstream s;
    switch(event.type)
    {
      case SDL_KEYDOWN:
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
        break;
      case SDL_QUIT:
        storage->write();
        exit(0);
    }
  }

  return GAMEOVER;
}

void GameOverMode::reset()
{}
