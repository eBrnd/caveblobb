#include "randomNumberGenerator.hpp"

RandomNumberGenerator* RandomNumberGenerator::pointer = NULL;

RandomNumberGenerator::RandomNumberGenerator()
{
  // start up random generator
  rng = new boost::mt19937;
  rng->seed(static_cast<unsigned int>(std::time(NULL)));
}

RandomNumberGenerator* RandomNumberGenerator::getInstance()
{
  if(pointer == NULL)
  {
    pointer = new RandomNumberGenerator();
  }
  return pointer;
}

int RandomNumberGenerator::rand()
{
  boost::uniform_int<> randrange(0, RAND_MAX-1); // TODO Use different generators for different things
  boost::variate_generator< boost::mt19937&, boost::uniform_int<> > random(*rng, randrange);
  return random();
}
