#pragma once

#include "Dictionnary.h"
#include "Node.h"

struct node
{
  node(unsigned letter);
  struct
  {
    // The index of the brother
    unsigned brother : 24;
    // Has at least one child
    unsigned sun : 1;
    // 2^6 = 64, we have 41 letters
    unsigned letter : 6;
    unsigned is_terminal : 1;
  } bits;
  unsigned freq;
};

class Trie
{
public:
    Trie(Dictionnary& dict);
    void dump(const char* file);
    void add_word(std::string& s, unsigned freq);
    void print();
    void load(char* input);
    unsigned bfs();
    unsigned dfs(unsigned idx);
    unsigned dfs_iter();
    unsigned count_words();

    Trie();
    // Map a letter to it's id.
    vector<unsigned char> map_;
    // Gives position of mapped char (range 0..n)
    vector<unsigned> start_pos_;
    vector<node> nodes_;
};
