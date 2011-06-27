#ifndef FONTMANAGER
#define FONTMANAGER

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include "SFont.h"

class FontManager
{
  private:
    FontManager();
    static FontManager* pointer;
    SDL_Surface* font_surface, *font2x_surface, *font4x_surface, *font8x_surface;
    SFont_Font* fonts[4];
  public:
    static FontManager* getInstance();
    void write(SDL_Surface* display, int x, int y, int size, char* text);
    int textWidth(int size, char* text);
    int textHeight(int size);
};

#endif
