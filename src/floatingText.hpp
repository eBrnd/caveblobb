#ifndef FLOATINGTEXT
#define FLOATINGTEXT

#include <vector>
#include <SDL.h>
#include "font.hpp"

class FloatingText
{
  private:
    struct line { std::string text; int x,y,ttl; };
    std::vector<line> lines;
    SDL_Surface* display;
    Font* font;
  public:
    FloatingText(SDL_Surface* display, Font* font);
    void draw();
    void update();
    void add(const char* text, int x, int y, int ttl);
};

#endif
