#include "gameOverMode.hpp"


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
  s << globalStore->seconds << " seconds, " << globalStore->obstacles << " obstacles, " << globalStore->stars << " stars. Press space to continue.";
  if(gameOverFont != NULL)
  {
    SDL_Surface* text = TTF_RenderText_Shaded(gameOverFont, s.str().c_str(), clrWhite, clrBlack);
    SDL_Rect textLocation = { 400 - text->w / 2, 400, 0,0 };
    SDL_BlitSurface(text, NULL, display, &textLocation);
    SDL_FreeSurface(text);
  }

  std::ostringstream p;
  p << "Score: " << globalStore->score;
  if(bigFont != NULL)
  {
    SDL_Surface* points = TTF_RenderText_Shaded(bigFont, p.str().c_str(), clrWhite, clrBlack);
    SDL_Rect pointsLocation = { 400 - points->w / 2, 200, 0,0 };
    SDL_BlitSurface(points, NULL, display, &pointsLocation);
    SDL_FreeSurface(points);
  }
  

  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_KEYDOWN:
        std::string space ("space");
        if(!space.compare(SDL_GetKeyName(event.key.keysym.sym)))
          return MENU;
    }
  }

  return GAMEOVER;
}

void GameOverMode::reset()
{}
