#include "colors.hpp"

Colors* Colors::pointer = NULL;

Colors::Colors()
{
  TTF_Init();
  sans18 = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
  white.r = white.b = white.g = 255;
  black.r = black.b = black.g = 0;
}

Colors* Colors::getInstance()
{
  if(pointer == NULL)
  {
    pointer = new Colors();
  }
  return pointer;
}
