#include "colorsAndFonts.hpp"

ColorsAndFonts* ColorsAndFonts::pointer = NULL;

ColorsAndFonts::ColorsAndFonts()
{
  font_surface = IMG_Load("/usr/local/share/caveblobb/font.png");
  font2x_surface = IMG_Load("/usr/local/share/caveblobb/font2x.png");
  font4x_surface = IMG_Load("/usr/local/share/caveblobb/font4x.png");
  font8x_surface = IMG_Load("/usr/local/share/caveblobb/font8x.png");
  
  fonts[0] = SFont_InitFont(font_surface);
  fonts[1] = SFont_InitFont(font2x_surface);
  fonts[2] = SFont_InitFont(font4x_surface);
  fonts[3] = SFont_InitFont(font8x_surface);

  for(int i = 0; i < 4; i++)
  {
    if(fonts[i] == NULL)
      std::cout << "Error loading font - text may not be renderes correctly." << std::endl;
  }
}

ColorsAndFonts* ColorsAndFonts::getInstance()
{
  if(pointer == NULL)
  {
    pointer = new ColorsAndFonts();
  }
  return pointer;
}

void ColorsAndFonts::write(SDL_Surface* display, int x, int y, int size, char* text)
{
  if(size < 4 && size >= 0 && fonts[size] != NULL)
    SFont_Write(display, fonts[size], x, y, text);
}

int ColorsAndFonts::textWidth(int size, char* text)
{
  if(size < 4 && size >= 0 && fonts[size] != NULL)
    return SFont_TextWidth(fonts[size], text);
  else
    return 0;
}

int ColorsAndFonts::textHeight(int size)
{
  if(size < 4 && size >= 0 && fonts[size] != NULL)
    return SFont_TextHeight(fonts[size]);
  else
    return 0;
}
