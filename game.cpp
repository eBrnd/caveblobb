// TODO Probably menu should also be its own class, like GameMode

#include "SDL/SDL_ttf.h"
#include "gameMode.cpp"

class Game
{
  private:
    enum Mode { MENU, PLAY };
    Mode mode;
    SDL_Surface* display;

    TTF_Font* menuFont;
    SDL_Color clrWhite;
    SDL_Color clrBlack;

    GameMode* gameMode;
  public:
    Game(SDL_Surface* display)
    {
      // init private variables
      mode = MENU;
      this->display = display;

      // init fonts + colors for menu
      TTF_Init();
      menuFont = TTF_OpenFont("/usr/share/fonts/TTF/FreeSans.ttf", 18);
      clrWhite = { 255,255,255, 0 };
      clrBlack = { 0,0,0, 0 };

      // init game mode
      gameMode = new GameMode(display);
    }

    void frame()
    {
      SDL_FillRect(display, NULL, 0); // clear the buffer

      switch(mode)
      {
        case MENU:
            drawMenu();
          break;

        case PLAY:
            if(gameMode->frame())
              mode = MENU;
          break;

        default:
          break;
      }

      SDL_Flip(display);
    }

    void drawMenu()
    {
      SDL_Surface* text = TTF_RenderText_Shaded(menuFont, "Click to start. Esc to quit.", clrWhite, clrBlack);
      SDL_Rect textLocation = { 100,100, 0,0 };
      SDL_BlitSurface(text, NULL, display, &textLocation);

      SDL_Event event;
      if(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          case SDL_MOUSEBUTTONDOWN:
            mode = PLAY;
          case SDL_KEYDOWN:
              std::string esc ("escape");
              if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
                exit(0);
        }
      }
    }
};
