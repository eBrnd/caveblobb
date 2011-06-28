#ifndef BACKGROUNDGENERATOR
#define BACKGROUNDGENERATOR

#include <vector>
#include <SDL.h>

#include "randomNumberGenerator.hpp"

class BackgroundGenerator {
  private:
    struct star { float x,vx; int y, size; };
    SDL_Surface* display;
    std::vector<star> stars;
    RandomNumberGenerator* rng;
    int counter;

    inline void FillRect(int x, int y, int w, int h, Uint32 color);
  public:
    BackgroundGenerator(SDL_Surface* display);
    void clear();
    void draw();
    void update();
};

#endif
