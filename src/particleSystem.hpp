#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include <vector>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>

class ParticleSystem {
  public:
    enum Type { PIXEL, CIRCLE, SQUARE };
  private:
    struct particle { float x,y, vx,vy; int ttl, size, group; Type type; Uint32 color; };

    SDL_Surface* display;
    std::vector<particle> particles;

    inline void FillRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint32 color);
  public:
    ParticleSystem(SDL_Surface* display);
    void clear();
    void clear(int group);
    void add(float x, float y, float vx, float vy, int ttl, int size, int group, Type type, Uint32 color);
    void draw(int group);
    void update();
};

#endif
