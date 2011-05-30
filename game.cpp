#include "SDL/SDL_ttf.h"

class Game
{
  private:
      enum Mode { MENU, PLAY };
      Mode mode;
      SDL_Surface* display;

      TTF_Font* menuFont;
      SDL_Color clrWhite;
      SDL_Color clrBlack;
  public:
    Game(SDL_Surface* display)
    {
      // init private variables
      mode = MENU;
      this->display = display;

      // init fonts + colors
      TTF_Init();
      menuFont = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
      clrWhite = { 255,255,255, 0 };
      clrBlack = { 0,0,0, 0 };
    }

    void frame()
    {
      switch(mode)
      {
        case MENU:
            drawMenu();
          break;

        case PLAY:

          break;
        default:
          break;
      }

      SDL_Flip(display);
    }

    void drawMenu()
    {
      SDL_Surface* text = TTF_RenderText_Shaded(menuFont, "Click to start.", clrWhite, clrBlack);
      SDL_Rect textLocation = { 100,100, 0,0 };
      SDL_BlitSurface(text, NULL, display, &textLocation);
    }
};
