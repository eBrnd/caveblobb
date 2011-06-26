#ifndef COLORSANDFONTS
#define COLORSANDFONTS

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "SFont.h"

class ColorsAndFonts
{
  private:
    ColorsAndFonts();
    static ColorsAndFonts* pointer;
    SDL_Surface* font_surface, *font2x_surface, *font4x_surface, *font8x_surface;
    SFont_Font* fonts[4];
  public:
    TTF_Font* sans18;
    TTF_Font* sans43;
    SDL_Color white, black;
    static ColorsAndFonts* getInstance();
    void write(SDL_Surface* display, int x, int y, int size, char* text);
};

#endif
