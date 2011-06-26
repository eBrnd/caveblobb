#include "particleSystem.hpp"

ParticleSystem::ParticleSystem(SDL_Surface* display)
{
  this->display = display;
}

void ParticleSystem::clear()
{
  particles.clear();
}

void ParticleSystem::clear(int group)
{
  for(unsigned int i = 0; i < particles.size(); i++) // is there a more elegant / efficient way to do this?
    if(particles[i].group == group)
      particles.erase(particles.begin()+ i--); // decrement index because the next one will move back one position
      // TODO I think I should use an iterator here, because erase wants one anyway
}

void ParticleSystem::add(float x, float y, float vx, float vy, int ttl, int size, int group, Type type, Uint32 color)
{
  if(ttl > 0) // ttl has to be greater than zero, otherwise it will get negative in update().
  {
    particle p;
    p.x = x; p.y = y; p.vx = vx; p.vy = vy;
    p.ttl = ttl; p.size = size; p.group = group;
    p.type = type, p.color = color;
    particles.push_back(p);
  }
}

void ParticleSystem::draw(int group)
{
  for(unsigned int i = 0; i < particles.size(); i++)
    if(particles[i].group == group)
      switch(particles[i].type)
      {
        case PIXEL:
          pixelColor(display, (int)particles[i].x, (int)particles[i].y, particles[i].color);
          break;
        case CIRCLE:
          circleColor(display, (int)particles[i].x, (int)particles[i].y, particles[i].size, particles[i].color);
          break;
        case SQUARE:
          FillRect(particles[i].x, particles[i].y, particles[i].size, particles[i].size, particles[i].color >> 8);
          break;
      }
}

void ParticleSystem::update()
{
  for(unsigned int i = 0; i < particles.size(); i++)
  {
    if(!--particles[i].ttl)
      particles.erase(particles.begin()+ i--);
    else
    {
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
    }
  }
}

inline void ParticleSystem::FillRect(int x, int y, int w, int h, Uint32 color)
{
  SDL_Rect rect = {x,y,w,h};
  SDL_FillRect(display, &rect, color);
}
