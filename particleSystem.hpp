#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

class ParticleSystem {
  public:
    enum Type { CIRCLE, SQUARE };
  private:
    struct particle { float x,y, vx,vy; int ttl, size, group; Type type; Uint32 color; };

    SDL_Surface* display;
    std::vector<particle> particles;
  public:
    ParticleSystem(SDL_Surface* display);
    void clear();
    void clear(int group);
    void add(float x, float y, float vx, float vy, int ttl, int size, int group, Type type, Uint32 color);
    void draw(int group);
    void update();
};

#endif
