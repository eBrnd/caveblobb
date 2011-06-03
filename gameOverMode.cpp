#include "gameOverMode.hpp"

#include "colorsAndFonts.hpp"

#include <string>
#include <sstream>

GameOverMode::GameOverMode(SDL_Surface* display, GlobalStore* globalStore)
  : GameMode(display, globalStore)
{
  gameOverFont = ColorsAndFonts::getInstance()->sans18;
  bigFont = ColorsAndFonts::getInstance()->sans43;
  clrWhite = ColorsAndFonts::getInstance()->white;
  clrBlack = ColorsAndFonts::getInstance()->black;
}

Mode GameOverMode::frame()
{
  std::ostringstream s;
  s << globalStore->seconds << " seconds, " << globalStore->obstacles << " obstacles. Click for Menu.";
  SDL_Surface* text = TTF_RenderText_Shaded(gameOverFont, s.str().c_str(), clrWhite, clrBlack);
  SDL_Rect textLocation = { 400 - text->w / 2, 400, 0,0 };
  SDL_BlitSurface(text, NULL, display, &textLocation);
  SDL_FreeSurface(text);

  std::ostringstream p;
  p << "Score: " << globalStore->score;
  SDL_Surface* points = TTF_RenderText_Shaded(bigFont, p.str().c_str(), clrWhite, clrBlack);
  SDL_Rect pointsLocation = { 400 - points->w / 2, 200, 0,0 };
  SDL_BlitSurface(points, NULL, display, &pointsLocation);
  SDL_FreeSurface(points);
  

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
