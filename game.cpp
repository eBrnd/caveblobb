class Game
{
  private:
      enum Mode { MENU, PLAY };
      Mode mode;

  public:
    Game()
    {
      mode = MENU;
    }

    void frame()
    {
      switch(mode)
      {
        case MENU:

          break;
        case PLAY:

          break;
        default:
          break;
      }
    }
};
