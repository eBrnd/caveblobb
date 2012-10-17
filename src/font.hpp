#ifndef FONT
#define FONT

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

class Font
{
  private:
    SDL_Surface *font_surf;
    struct letter { Sint16 x; Uint16 w; };
    Uint16 h;
    void readPositions();
    letter letters[95];
  public:
    Font();
    ~Font();
    bool loadImg(std::string filename);
    void write(SDL_Surface* display, Sint16 x, Sint16 y, std::string text);
    void writeCentered(SDL_Surface* display, int x, int y, std::string text);
    unsigned int width(std::string text);
};

#endif
