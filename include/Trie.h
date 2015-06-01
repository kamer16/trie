#pragma once

#include "Node.h"

class Trie
{
public:
    void add_word(std::string& s);
    void print();
    void load(char* input);
    unsigned num_sets();

    Trie();
    // Map a letter to it's id.
    vector<unsigned char> map_;
    vector<unsigned> nodes_;
};
