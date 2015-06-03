#include <iostream>
#include <fstream>
#include <set>
#include <cassert>
#include <deque>

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

unsigned Trie::bfs()
{
  std::deque<unsigned> todo;
  for (auto& idx: start_pos_)
    {
      if (idx != -1U)
        todo.push_back(idx);
    }
  unsigned res = 0;
  while(!todo.empty())
  {
    unsigned i = todo.front();
    todo.pop_front();
    res += nodes_[i].bits.is_terminal;
    if (nodes_[i].bits.sun)
      {
        ++i;
        todo.push_back(i);
      while (nodes_[i].bits.brother)
        {
          todo.push_back(nodes_[i].bits.brother);
          i = nodes_[i].bits.brother;
        }
      }
  }
  return res;
}

unsigned Trie::dfs_iter()
{
  unsigned res = 0;
  std::vector<unsigned> stack;
  for (auto idx: start_pos_)
    {
      if (idx == -1U)
        continue;
      // First element is a sentinelle as it will never be iterated on
      stack.push_back(idx);
      do {
        node n = nodes_[idx];
        res += n.bits.is_terminal;
        if (n.bits.brother)
          stack.push_back(n.bits.brother);
        if (n.bits.sun)
          ++idx;
        else
          {
            idx = stack.back();
            stack.pop_back();
          }
      } while (!stack.empty());
    }
  return res;
}

unsigned Trie::dfs(unsigned idx)
{
  unsigned res = 0;
  do {
      res += nodes_[idx].bits.is_terminal;
      if (nodes_[idx].bits.sun)
        res += dfs(idx + 1);
      idx = nodes_[idx].bits.brother;
    } while (idx);
  return res;
}

unsigned Trie::count_words()
{
  unsigned res = 0;
  for (auto idx: start_pos_)
    {
      if (idx != -1U)
      {
        res += dfs(idx);
      }
    }
  return res;
}

void Trie::add_word(std::string& s)
{
  // offset corresponds to index of first sun of previous node with letter s[i]
  unsigned offset = start_pos_[map_[s[0]]];
  if (offset == -1U)
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
      assert(offset < 1 << 24);
    }
  // Set high bit to indicate end of word.
  // Note that top 10 bits are free
  nodes_[offset].bits.is_terminal = 1;
}


void Trie::print()
{
  unsigned mod = 0;
  std::vector<char> inv(g_nb_letters);
  for (unsigned i = 0; i < g_nb_letters; ++i)
    {
      inv[i] = g_letters[i];
      if (start_pos_[i] != -1U)
        std::cout << g_letters[i] << ": " << start_pos_[i] << ", ";
    }
  std::cout << '\n';
  for (auto n: nodes_)
    {
      if (mod == 8)
        std::cout << n.bits.sun << ',' << n.bits.brother << ','
                  << inv[n.bits.letter] << ',' << n.bits.is_terminal << '\n';
      else
        std::cout << n.bits.sun << ',' << n.bits.brother << ','
                  << inv[n.bits.letter] << ',' << n.bits.is_terminal << "  ";

      mod = (mod + 1) % 9;
    }
  std::cout << '\n';
}

Trie::Trie(Dictionnary& dict)
  : map_(256, -1), start_pos_(g_nb_letters, -1U)
{
  unsigned cnt = 0;
  for (unsigned i = 0; i < g_nb_letters; ++i)
    map_[g_letters[i]] = cnt++;
  for (auto& p: dict.words)
    {
      add_word(p.first);
    }
}
