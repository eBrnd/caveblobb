#ifndef GAMEMODE
#define GAMEMODE

#include "globalStore.cpp"

class GameMode
{
  private:
    SDL_Surface* display;

    int walls_top[160], walls_bottom[160], obstacles[160], player_tail[29];
    float player_pos, player_vel;
    bool up;
    int frames_to_corner, corner_at, level_height, frames_to_obstacle, passed;
    int obstacle_distance, decrease_height_frames;
    unsigned long int playtime;
    float slope;
    TTF_Font* scoreFont;
    SDL_Color clrWhite;
    SDL_Color clrBlack;
    GlobalStore* globalStore;
  public:
    GameMode(SDL_Surface* display, GlobalStore* globalStore);
    void reset();
    inline void FillRect(int x, int y, int w, int h, int color);
    int frame();
};

#endif
