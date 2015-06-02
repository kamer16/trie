#include <string>

#include "Dictionnary.h"

// Constructor
Dictionnary::Dictionnary(const char *file)
{
  fstream f(file);
  string c;
  unsigned freq;
  f >> c >> freq;
  while (!f.eof())
    {
      words.emplace_back(move(c), freq);
      f >> c >> freq;
    }
  sort(words.begin(), words.end());
}
