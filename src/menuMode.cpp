#include "menuMode.hpp"

MenuMode::MenuMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{}

Mode MenuMode::frame()
{
  font8->writeCentered(display, 400, 100, "~cavEbl0bb~");
  font2->writeCentered(display, 400, 280, "Click to start! Esc to quit.");

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_MOUSEBUTTONDOWN:
        return START;
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            return QUIT;
            break;
          default:
            break;
        }
          break;
      case SDL_QUIT:
        exit(0);
    }
  }

  return MENU;
}

void MenuMode::reset()
{}
