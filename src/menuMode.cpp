#include "menuMode.hpp"

MenuMode::MenuMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{}

Mode MenuMode::frame()
{
  char* title = (char*)"~cavEbl0bb~";
  fontm->write(display, 400 - fontm->textWidth(3, title) / 2, 100, 3, title);

  char* clicktostart = (char*)"Click to start! Esc to quit.";
  fontm->write(display, 400 - fontm->textWidth(1, clicktostart) / 2, 280, 1, clicktostart);

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
