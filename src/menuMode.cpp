#include "menuMode.hpp"

MenuMode::MenuMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  menuFont = ColorsAndFonts::getInstance()->sans18;
  titleFont = ColorsAndFonts::getInstance()->sans43;
  clrWhite = ColorsAndFonts::getInstance()->white;
  clrBlack = ColorsAndFonts::getInstance()->black;
}

Mode MenuMode::frame()
{
  char* title = (char*)"~cavEbl0bb~";
  caf->write(display, 400 - caf->textWidth(3, title) / 2, 100, 3, title);

  char* clicktostart = (char*)"Click to start! Esc to quit.";
  caf->write(display, 400 - caf->textWidth(1, clicktostart) / 2, 280, 1, clicktostart);

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
