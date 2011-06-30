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
      case SDL_KEYDOWN:
        std::string esc ("escape");
        if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
        {
          return QUIT;
        }
    }
  }

  return MENU;
}

void MenuMode::reset()
{}
