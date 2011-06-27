#ifndef COLORSANDFONTS
#define COLORSANDFONTS

#include <iostream>

#include <SDL.h>
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
    static ColorsAndFonts* getInstance();
    void write(SDL_Surface* display, int x, int y, int size, char* text);
    int textWidth(int size, char* text);
    int textHeight(int size);
};

#endif
