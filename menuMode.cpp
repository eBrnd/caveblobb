#include "menuMode.hpp"
#include "colors.hpp"

#include <string>

MenuMode::MenuMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  menuFont = Colors::getInstance()->sans18;
  clrWhite = Colors::getInstance()->white;
  clrBlack = Colors::getInstance()->black;
}

Mode MenuMode::frame()
{
  SDL_Surface* text = TTF_RenderText_Shaded(menuFont, "Click to start. Esc to quit.", clrWhite, clrBlack);
  SDL_Rect textLocation = { 100,100, 0,0 };
  SDL_BlitSurface(text, NULL, display, &textLocation);
  SDL_FreeSurface(text);

  SDL_Event event;
  if(SDL_PollEvent(&event))
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
