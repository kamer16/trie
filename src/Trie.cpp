#include <iostream>
#include <fstream>
#include <set>

#include "Trie.h"

// Sorted by highest frequency
static const char g_letters[] =
{
'e', 'a', 'i', '1', '2', '3', 'r', 'o', 'n', '4', 's', '5', 't', '0', '6', 'l',
'7', '8', '9', 'u', 'c', 'm', 'd', 'p', 'h', 'b', 'g', 'f', 'k', 'v', 'y', 'z',
'x', 'w', 'j', '_', 'q', '.', '+', '&', '#', 
};

static const size_t g_nb_letters = sizeof (g_letters) / sizeof (char);

Trie::Trie()
  : map_(256, -1), nodes_(g_nb_letters, 0)
{
    unsigned cnt = 0;
    for (unsigned i = 0; i < g_nb_letters; ++i)
       map_[g_letters[i]] = cnt++;

}

void Trie::add_word(std::string& s)
{
  static const unsigned mask = 1 << (sizeof(unsigned) * 8 - 1);
  static const unsigned not_mask = ~mask;
  unsigned offset = 0;
  unsigned tmp = 0;
  for (unsigned i = 0; i < s.size() - 1; ++i)
    {
      char c = s[i];
      // Pointer to child map_[c]
      tmp = offset + map_[c];
      // Pointer to beginning of successor
      offset = nodes_[tmp];
      // offset = 0 means that correpsonding letter does not hove any successor
      if (!(offset & not_mask))
        {
          offset = nodes_.size();
          nodes_.insert(nodes_.end(), g_nb_letters, 0);
          // if old offset was terminal char leave it by |= the result
          nodes_[tmp] |= offset;
        }
      else
        offset &= not_mask;
    }
  // Set high bit to indicate end of word.
  // Note that top 10 bits are free
  char c = s[s.size() - 1];
  tmp = offset + map_[c];
  nodes_[tmp] |= mask;
}

unsigned Trie::num_sets()
{
  std::set<unsigned> power;
  for (unsigned j = 0; j < nodes_.size() / g_nb_letters; ++j)
    {
      unsigned bit = 0;
      for (unsigned i = 0; i < g_nb_letters; ++i)
        {
          if (nodes_[i + j * g_nb_letters])
            bit |= 1 << i;

        }
      power.insert(bit);
    }
  return power.size();
}

void Trie::print()
{
  static const unsigned mask = 1 << (sizeof(unsigned) * 8 - 1);
  static const unsigned not_mask = ~mask;
  for (unsigned j = 0; j < nodes_.size() / g_nb_letters; ++j)
    {
      for (unsigned i = 0; i < g_nb_letters; ++i)
        {
          std::cout << (not_mask & nodes_[i + j * g_nb_letters]) << ' ';
        }
      std::cout << std::endl;
    }
}

void Trie::load(char* input)
{
  fstream fs;
  fs.open(input);
  std::string s;
  unsigned freq;
  fs >> s >> freq;
  while (!fs.eof())
    {
      add_word(s);
      fs >> s >> freq;
    }
}
