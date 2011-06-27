#include "floatingText.hpp"

FloatingText::FloatingText(SDL_Surface* display)
{
  this->display = display;
  fontm = FontManager::getInstance();
}

void FloatingText::draw()
{
  for(unsigned int i = 0; i < lines.size(); i++)
  {
    if(lines[i].ttl > 25 || lines[i].ttl % 4 <= 1) // make it flash before disappearing
    fontm->write(display, lines[i].x, lines[i].y, 0, lines[i].text);
  }
}

void FloatingText::update()
{
  for(unsigned int i = 0; i < lines.size(); i++)
  {
    lines[i].y--;
    if(!lines[i].ttl--)
    {
      delete lines[i].text;
      lines.erase(lines.begin() + i--);
    }
  }
}

void FloatingText::add(const char* text, int x, int y, int ttl)
{
  char* content = new char[32];
  strncpy(content, text, 32);
  line myLine;
  myLine.text = content;
  myLine.x = x;
  myLine.y = y;
  myLine.ttl = ttl;

  lines.push_back(myLine);
}
