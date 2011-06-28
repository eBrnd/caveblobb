#include "permanentStorage.hpp"

PermanentStorage::PermanentStorage()
{}

void PermanentStorage::read()
{
  for(int i = 0; i < 5; i++)
    highscores[i] = 0;
  strcpy(browser, "");
  std::string path = getenv("HOME");
  path += "/.caveblobb";
  std::ifstream ifs;
  ifs.open(path.c_str(), std::ifstream::in);
  if(ifs.fail())
    std::cout << "failed to open " << path << " - attempting to create new file later" << std::endl;
  else
  {
    char line[128];
    while(ifs.good())
    {
      ifs.getline(line, 128);
      if(!strncmp(line, "browser ", 8))
        strncpy(browser, line+8, 120);
      if(!strncmp(line, "highsc1 ", 8))
        highscores[0] = atol(line+8);
      if(!strncmp(line, "highsc2 ", 8))
        highscores[1] = atol(line+8);
      if(!strncmp(line, "highsc3 ", 8))
        highscores[2] = atol(line+8);
      if(!strncmp(line, "highsc4 ", 8))
        highscores[3] = atol(line+8);
      if(!strncmp(line, "highsc5 ", 8))
        highscores[4] = atol(line+8);
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
