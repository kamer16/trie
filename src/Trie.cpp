#include <iostream>
#include <fstream>
#include <set>
#include <cassert>

#include "Trie.h"

// Sorted by highest frequency
static const char g_letters[] =
{
'e', 'a', 'i', '1', '2', '3', 'r', 'o', 'n', '4', 's', '5', 't', '0', '6', 'l',
'7', '8', '9', 'u', 'c', 'm', 'd', 'p', 'h', 'b', 'g', 'f', 'k', 'v', 'y', 'z',
'x', 'w', 'j', '_', 'q', '.', '+', '&', '#',
};

static const size_t g_nb_letters = sizeof (g_letters) / sizeof (char);

node::node(unsigned letter)
  : value(0)
{
  bits.letter = letter;
}

void Trie::add_word(std::string& s)
{
  static const unsigned mask = 1 << (sizeof(unsigned) * 8 - 1);
  static const unsigned not_mask = ~mask;
  // offset corresponds to index of first sun of previous node with letter s[i]
  unsigned offset = start_pos_[map_[s[0]]];
  if (!offset)
    {
      // l corresponds to value of remapped letter
      unsigned l = map_[s[0]];
      offset = nodes_.size();
      start_pos_[l] = offset;
      nodes_.emplace_back(l);
    }
  unsigned tmp = 0;
  for (unsigned i = 1; i < s.size(); ++i)
    {
      unsigned l = map_[s[i]];
      if (!nodes_[offset].bits.sun)
        {
          // If no sun, create one with the correct letter
          assert(offset + 1 == nodes_.size());
          nodes_[offset].bits.sun = 1;
          ++offset;
          nodes_.emplace_back(l);
        }
      else
        {
          // Go to first sun position
          ++offset;
          // Sun exists, we need to find correct label
          while (nodes_[offset].bits.letter != l && nodes_[offset].bits.brother)
            offset = nodes_[offset].bits.brother;
          if (nodes_[offset].bits.letter != l)
            {
              assert(nodes_[offset].bits.brother == 0);
              // We must create new brother
              nodes_[offset].bits.brother = nodes_.size();
              offset = nodes_.size();
              nodes_.emplace_back(l);
            }
        }
    }
  // Set high bit to indicate end of word.
  // Note that top 10 bits are free
  nodes_[offset].bits.is_terminal = 1;
}


Trie::Trie(Dictionnary& dict)
  : map_(256, -1), start_pos_(g_nb_letters, 0)
{
  unsigned cnt = 0;
  for (unsigned i = 0; i < g_nb_letters; ++i)
    map_[g_letters[i]] = cnt++;
  for (auto& p: dict.words)
    {
      add_word(p.first);
    }
}
