#include "gameOverMode.hpp"

#include <string>
#include <sstream>

GameOverMode::GameOverMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  gameOverFont = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
  clrWhite = { 255,255,255, 0 };
  clrBlack = { 0,0,0, 0 };
}

Mode GameOverMode::frame()
{
  std::ostringstream s;
  s << globalStore->seconds << " seconds, " << globalStore->obstacles << " obstacles. Click for Menu.";
  SDL_Surface* text = TTF_RenderText_Shaded(gameOverFont, s.str().c_str(), clrWhite, clrBlack);
  SDL_Rect textLocation = { 100,100, 0,0 };
  SDL_BlitSurface(text, NULL, display, &textLocation);
  SDL_FreeSurface(text);

  SDL_Event event;
  if(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_MOUSEBUTTONDOWN:
        return MENU;
    }
  }

  return GAMEOVER;
}

void GameOverMode::reset()
{}
