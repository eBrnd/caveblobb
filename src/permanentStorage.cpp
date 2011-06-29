#include "permanentStorage.hpp"

PermanentStorage::PermanentStorage()
{}

void PermanentStorage::read()
{
  for(int i = 0; i < 5; i++)
    highscores[i] = 0;
  browser = "false";
  std::string path = getenv("HOME");
  path += "/.caveblobb";
  std::ifstream ifs;
  ifs.open(path.c_str(), std::ifstream::in);
  if(ifs.fail())
    std::cout << "failed to open " << path << " - attempting to create new file later" << std::endl;
  else
  {
    std::string line;
    while(ifs.good())
    {
      ifs >> line;
      if(line == "browser")
        ifs >> browser;
      if(line == "highsc1")
        ifs >> highscores[0];
      if(line == "highsc2")
        ifs >> highscores[1];
      if(line == "highsc3")
        ifs >> highscores[2];
      if(line == "highsc4")
        ifs >> highscores[3];
      if(line == "highsc5")
        ifs >> highscores[4];
    }
  }
  ifs.close();
}

void PermanentStorage::write()
{
  std::ofstream ofs;
  std::string path = getenv("HOME");
  path += "/.caveblobb";
  ofs.open(path.c_str(), std::ofstream::out);
  if(ofs.is_open())
  {
    ofs << "browser " << browser << std::endl;
    ofs << "highsc1 " << highscores[0] << std::endl;
    ofs << "highsc2 " << highscores[1] << std::endl;
    ofs << "highsc3 " << highscores[2] << std::endl;
    ofs << "highsc4 " << highscores[3] << std::endl;
    ofs << "highsc5 " << highscores[4] << std::endl;
    ofs.close();
  }
  else
    std::cout << "failed to open " << path << " for writing.";
}

unsigned long int PermanentStorage::getHighscore(int index)
{
  if(index >= 0 && index < 5)
    return highscores[index];
  else
    return 0;
}

void PermanentStorage::insert(unsigned long int score)
{
  int i = 0;
  while(highscores[i] > score)
    i++;
  for(int j = 3; j >= i; j--)
    highscores[j+1] = highscores[j];
  highscores[i] = score;
  
  
}

std::string PermanentStorage::getBrowser()
{
  return browser;
}
