#include "fontManager.hpp"

FontManager* FontManager::pointer = NULL;

FontManager::FontManager()
{
  font_surface = IMG_Load("/usr/local/share/caveblobb/font.png");
  if(font_surface == NULL)
    font_surface = IMG_Load("/usr/share/caveblobb/font.png");
  font2x_surface = IMG_Load("/usr/local/share/caveblobb/font2x.png");
  if(font2x_surface == NULL)
    font2x_surface = IMG_Load("/usr/share/caveblobb/font2x.png");
  font4x_surface = IMG_Load("/usr/local/share/caveblobb/font4x.png");
  if(font4x_surface == NULL)
    font4x_surface = IMG_Load("/usr/share/caveblobb/font4x.png");
  font8x_surface = IMG_Load("/usr/local/share/caveblobb/font8x.png");
  if(font8x_surface == NULL)
    font8x_surface = IMG_Load("/usr/share/caveblobb/font8x.png");
  
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

FontManager* FontManager::getInstance()
{
  if(pointer == NULL)
  {
    pointer = new FontManager();
  }
  return pointer;
}

void FontManager::write(SDL_Surface* display, int x, int y, int size, char* text)
{
  if(size < 4 && size >= 0 && fonts[size] != NULL)
    SFont_Write(display, fonts[size], x, y, text);
}

int FontManager::textWidth(int size, char* text)
{
  if(size < 4 && size >= 0 && fonts[size] != NULL)
    return SFont_TextWidth(fonts[size], text);
  else
    return 0;
}

int FontManager::textHeight(int size)
{
  if(size < 4 && size >= 0 && fonts[size] != NULL)
    return SFont_TextHeight(fonts[size]);
  else
    return 0;
}
