#include "colorsAndFonts.hpp"

ColorsAndFonts* ColorsAndFonts::pointer = NULL;

ColorsAndFonts::ColorsAndFonts()
{
  TTF_Init();
  sans18 = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
  sans43 = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 43);
  if(sans18 == NULL || sans43 == NULL)
    std::cout << "Error loading Font: /usr/share/fonts/TTF/FreeSans.ttf - Text may not be rendered properly." << std::endl;
  white.r = white.b = white.g = 255;
  black.r = black.b = black.g = 0;
}

ColorsAndFonts* ColorsAndFonts::getInstance()
{
  if(pointer == NULL)
  {
    pointer = new ColorsAndFonts();
  }
  return pointer;
}
