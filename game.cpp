// TODO Probably menu should also be its own class, like GameMode

#include "SDL/SDL_ttf.h"
#include "gameMode.cpp"

class Game
{
  private:
    enum Mode { MENU, PLAY, GAMEOVER };
    Mode mode;
    SDL_Surface* display;

    TTF_Font* menuFont;
    SDL_Color clrWhite;
    SDL_Color clrBlack;

    GameMode* gameMode;
    GlobalStore* globalStore;
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

      globalStore = new GlobalStore();

      // init game mode
      gameMode = new GameMode(display, globalStore);
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
          switch(gameMode->frame())
          {
            case 0:
              break;
            case 1:
              mode = MENU;
              break;
            case 2:
              mode = GAMEOVER;
              break;
          }
          break;

        case GAMEOVER:
          drawGameOver();
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
            gameMode->reset();
          case SDL_KEYDOWN:
            std::string esc ("escape");
            if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
              exit(0);
        }
      }
    }

    void drawGameOver()
    {
      std::ostringstream s;
      s << globalStore->seconds << " seconds " << globalStore->obstacles << " obstacles.";
      SDL_Surface* text = TTF_RenderText_Shaded(menuFont, s.str().c_str(), clrWhite, clrBlack);
      SDL_Rect textLocation = { 100,100, 0,0 };
      SDL_BlitSurface(text, NULL, display, &textLocation);

      SDL_Event event;
      if(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          case SDL_MOUSEBUTTONDOWN:
            mode = MENU;
            gameMode->reset();
          case SDL_KEYDOWN:
            std::string esc ("escape");
            if(!esc.compare(SDL_GetKeyName(event.key.keysym.sym)))
              exit(0);
        }
      }
    }
};
