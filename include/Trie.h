#pragma once

#include "Dictionnary.h"
#include "Node.h"

union node
{
  node(unsigned letter);
  struct
  {
    // Has at least one child
    unsigned sun : 1;
    // The index of the brother
    unsigned brother : 24;
    // 2^6 = 64, we have 41 letters
    unsigned letter : 6;
    unsigned is_terminal : 1;
  } bits;
  unsigned value;
};

class Trie
{
public:
    Trie(Dictionnary& dict);
    void add_word(std::string& s);
    void print();
    void load(char* input);
    unsigned num_sets();

    Trie();
    // Map a letter to it's id.
    vector<unsigned char> map_;
    vector<unsigned> start_pos_;
    vector<node> nodes_;
};
