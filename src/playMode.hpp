#ifndef PLAYMODE
#define PLAYMODE

#include <string>
#include <sstream>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "globalStore.hpp"
#include "permanentStorage.hpp"
#include "gameMode.hpp"
#include "mode.hpp"
#include "particleSystem.hpp"
#include "randomNumberGenerator.hpp"
#include "floatingText.hpp"
#include "backgroundGenerator.hpp"

class PlayMode : public GameMode
{
  private:
    int walls_top[160], walls_bottom[160], obstacles[160], shot[131], items[160];
    float player_pos, player_vel;
    bool up;
    int frames_to_corner, corner_at, level_height, frames_to_obstacle, passed, frames_to_item, collected;
    int obstacle_distance, decrease_height_frames;
    unsigned long int playtime;
    unsigned long int score;
    float slope;
    RandomNumberGenerator* rng;
    int special;
    bool crashed;
    bool paused;
    int justHit;
    int comboTime;
    int hitDuringCombo;
    int gameOverExplosionTime;
    int superShotActive;
    ParticleSystem* particles;
    FloatingText* floating;
    BackgroundGenerator* background;
    PermanentStorage* storage;
    int last_hit_x, last_hit_y;

    inline void FillRect(int x, int y, int w, int h, Uint32 color);
    void drawBackground();
    void moveField();
    void updatePlayerTail();
    void drawStuff();
    void drawPlayer();
    void generateWalls();
    void generateObstacles();
    void generateItems();
    bool handleInput();
    void updatePlayer();
    void collisionDetect();
    void obstacleCounter();
    void drawScorePanel();
    void addExplosion(int x, int y);
    void crashExplosion();
    void drawPauseScreen();

    Uint32 hue2rgb(float h);

  public:
    PlayMode(SDL_Surface* display, GlobalStore* globalStore, PermanentStorage* storage);
    void reset();
    Mode frame();
};

#endif
