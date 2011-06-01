#ifndef COLORSANDFONTS
#define COLORSANDFONTS

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class ColorsAndFonts
{
  private:
    ColorsAndFonts();
    static ColorsAndFonts* pointer;
  public:
    TTF_Font* sans18;
    SDL_Color white, black;
    static ColorsAndFonts* getInstance();
};

#endif
