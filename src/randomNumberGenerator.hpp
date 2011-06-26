#ifndef RANDOMNUMBERGENERATOR
#define RANDOMNUMBERGENERATOR

#include <ctime>
#include <boost/random.hpp>

class RandomNumberGenerator
{
  private:
    RandomNumberGenerator();
    boost::mt19937* rng;
    static RandomNumberGenerator* pointer;
  public:
    static RandomNumberGenerator* getInstance();
    int rand();
};

#endif
