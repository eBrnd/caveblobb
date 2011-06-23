#ifndef PLAYMODE
#define PLAYMODE

#include <string>
#include <sstream>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"

#include "globalStore.hpp"
#include "gameMode.hpp"
#include "mode.hpp"
#include "colorsAndFonts.hpp"
#include "particleSystem.hpp"

class PlayMode : public GameMode
{
  private:
    int walls_top[160], walls_bottom[160], obstacles[160], shot[131];
    float player_pos, player_vel;
    bool up;
    int frames_to_corner, corner_at, level_height, frames_to_obstacle, passed;
    int obstacle_distance, decrease_height_frames;
    unsigned long int playtime;
    float slope;
    TTF_Font* scoreFont;
    SDL_Color clrWhite;
    SDL_Color clrBlack;
    int special;
    bool crashed;
    ParticleSystem* particles;

    void moveField();
    void updatePlayerTail();
    void drawStuff();
    void generateWalls();
    void generateObstacles();
    bool handleInput();
    void updatePlayer();
    void collisionDetect();
    void obstacleCounter();
    void drawScorePanel();
    void addExplosion(int x, int y);

    Uint32 hue2rgb(float h);

  public:
    PlayMode(SDL_Surface* display, GlobalStore* globalStore);
    void reset();
    inline void FillRect(int x, int y, int w, int h, int color);
    Mode frame();
};

#endif
