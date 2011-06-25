#ifndef COLORSANDFONTS
#define COLORSANDFONTS

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

class ColorsAndFonts
{
  private:
    ColorsAndFonts();
    static ColorsAndFonts* pointer;
  public:
    TTF_Font* sans18;
    TTF_Font* sans43;
    SDL_Color white, black;
    static ColorsAndFonts* getInstance();
};

#endif
