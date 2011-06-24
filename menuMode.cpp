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
  if(titleFont != NULL)
  {
    SDL_Surface* title = TTF_RenderText_Shaded(titleFont, "~cavEbl0bb~", clrWhite, clrBlack);
    SDL_Rect titleLocation;
    titleLocation.x = 400 - title->w / 2;
    titleLocation.y = 100;
    SDL_BlitSurface(title, NULL, display, &titleLocation);
    SDL_FreeSurface(title);
  }

  if(menuFont != NULL)
  {
    SDL_Surface* text = TTF_RenderText_Shaded(menuFont, "Click to start! Esc to quit.", clrWhite, clrBlack);
    SDL_Rect textLocation;
    textLocation.x = 400 - text->w / 2;
    textLocation.y = 200;
    SDL_BlitSurface(text, NULL, display, &textLocation);
    SDL_FreeSurface(text);
  }

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
