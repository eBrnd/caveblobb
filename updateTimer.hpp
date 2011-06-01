#ifndef UPDATETIMER
#define UPDATETIMER

class UpdateTimer
{
  private:
    float lastUpdate;

  public:
    UpdateTimer();
    bool timeToUpdate();
};

#endif
