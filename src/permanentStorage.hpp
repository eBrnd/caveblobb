#ifndef PERMANENTSTORAGE
#define PERMANENTSTORAGE

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

class PermanentStorage
{
  private:
    unsigned long int highscores[5];
    std::string browser;
  public:
    PermanentStorage();
    void read();
    void write();
    unsigned long int getHighscore(int index);
    void insert(unsigned long int score);
    std::string getBrowser();
};

#endif
