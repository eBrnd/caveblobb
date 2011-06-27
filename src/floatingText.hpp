#ifndef FLOATINGTEXT
#define FLOATINGTEXT

#include <vector>
#include <SDL.h>
#include "fontManager.hpp"

class FloatingText
{
  private:
    struct line { char* text; int x,y,ttl; };
    std::vector<line> lines;
    SDL_Surface* display;
    FontManager* fontm;
  public:
    FloatingText(SDL_Surface* display);
    void draw();
    void update();
    void add(const char* text, int x, int y, int ttl);
};

#endif
