#include "menuMode.hpp"

#include <string>

MenuMode::MenuMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  menuFont = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
  clrWhite = { 255,255,255, 0 };
  clrBlack = { 0,0,0, 0 };
}

int MenuMode::frame()
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
        return 1;
      case SDL_KEYDOWN:
        std::string esc ("escape");
        if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
        {
          SDL_Quit();
          exit(0); // TODO this should not be done down here...
        }
    }
  }

  return 0;
}

void MenuMode::reset()
{}
