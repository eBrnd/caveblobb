#include "font.hpp"

Font::Font()
{
  font_surf = NULL;  
}

Font::~Font()
{ 
  if(font_surf != NULL)
    SDL_FreeSurface(font_surf); 
}

bool Font::loadImg(std::string filename)
{
  if(font_surf != NULL)
    SDL_FreeSurface(font_surf);
  if((font_surf = IMG_Load(filename.c_str())) != NULL)
  {
    readPositions();
    return true;
  } else
  {
    return false;
  }
}

void Font::readPositions()
{
  // initialize everything with 'zero' letters
  for(unsigned int i = 0; i < 95; i++)
    letters[i].x = 0;

  h = font_surf->h - 1;
  unsigned char current = 0;
  for(int i = 1; i < font_surf->w; i++)
  {
    Uint8 r,g,b,a,nr,ng,nb,na;
    SDL_GetRGBA(*((Uint32*)font_surf->pixels + i-1), font_surf->format, &r, &g, &b, &a);
    SDL_GetRGBA(*((Uint32*)font_surf->pixels + i), font_surf->format, &nr, &ng, &nb, &na);
    if(r == 255 && g == 0 && b >= 200 && na == 0)
    {
      letter l;
      l.x = i;
      l.w = 0;

      while(na == 0 && i < font_surf->w - 1)
      {
        SDL_GetRGBA(*((Uint32*)font_surf->pixels + ++i), font_surf->format, &nr, &ng, &nb, &na);
        l.w++;
      }
      letters[current++] = l;
    }
  }
}

void Font::write(SDL_Surface* display, int x, int y, std::string text)
{
  unsigned int offset = 0;
  for(unsigned int i = 0; i < text.size(); i++)
  {
    unsigned char c = (unsigned int)text[i] - 0x20;
    if(c < 95)
    {
      SDL_Rect char_pos = { letters[c].x, 1, letters[c].w, h };
      SDL_Rect dest_pos = { x + offset, y, letters[c].w, h };
      SDL_BlitSurface(font_surf, &char_pos, display, &dest_pos);
      offset += dest_pos.w;
    }
  }
}

unsigned int Font::width(std::string text)
{
  unsigned int offset = 0;
  for(unsigned int i = 0; i < text.size(); i++)
  {
    unsigned char c = (unsigned int)text[i] - 0x20;
    if(c < 95)
      offset += letters[i].w;
  }
  return offset;
}

void Font::writeCentered(SDL_Surface* display, int x, int y, std::string text)
{
  int xpos = x - width(text) / 2;
  if(xpos < 0)
    xpos = 0;
  write(display, xpos, y, text);
}
