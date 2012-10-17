#include "backgroundGenerator.hpp"

BackgroundGenerator::BackgroundGenerator(SDL_Surface* display)
{
  this->display = display;
  rng = RandomNumberGenerator::getInstance();
}

void BackgroundGenerator::clear()
{
  counter = 0;
  stars.clear();
}

void BackgroundGenerator::draw()
{
  for(unsigned int i = 0; i < stars.size(); i++)
    FillRect(stars[i].x, stars[i].y, stars[i].size, stars[i].size, 0xFFFFFFFF);
}

void BackgroundGenerator::update()
{
  // generate new stars
  if(!(counter++ % 10))
  {
    star myStar;
    myStar.x = 799;
    myStar.y = rng->rand() % 600;
    myStar.vx = -4.f * ((float)rng->rand() / (float)RAND_MAX);
    myStar.size = 1 - (int)myStar.vx;
    stars.push_back(myStar);
  }
  // move existing stars, erase old ones
  for(unsigned int i = 0; i < stars.size(); i++)
  {
    stars[i].x += stars[i].vx;
    if(stars[i].x < 0)
      stars.erase(stars.begin() + i--);
  }
}

inline void BackgroundGenerator::FillRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint32 color)
{
  SDL_Rect rect = {x,y,w,h};
  SDL_FillRect(display, &rect, color);
}
