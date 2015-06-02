#ifndef DICTIONNARY_H_
# define DICTIONNARY_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;

class Dictionnary
{
public:
  Dictionnary(const char *file);
  vector<pair<string, unsigned>> words;
};

#endif /* !DICTIONNARY_H_ */
