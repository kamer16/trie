#include "Levenshtein.h"

// TODO handle swap of letters
void levenshtein::update_matrix(std::vector<unsigned char>& matrix,
                                unsigned char letter)
{
  unsigned back = matrix.size();
  matrix.resize(back + w);
  matrix[back] = matrix[back - w] + 1;
  for (unsigned i = 1; i < w; ++i)
    {
      if (letter == other[i - 1])
        matrix[back + i] = matrix[back + i - w - 1];
      else
        {
          unsigned char m = std::min(matrix[back + i - w], matrix[back + i - 1]);
          m = std::min(matrix[back + i - w - 1], m);
          matrix[back + i] = m + 1;
        }
    }
}

std::vector<std::pair<unsigned, std::string>> levenshtein::compute()
{
  std::vector<std::pair<unsigned, std::string>> res;
  std::string s;
  std::vector<std::pair<unsigned, unsigned>> stack;
  for (unsigned i = 0; i < 41; ++i)
    {
      unsigned idx = trie->start_pos[i];
      if (idx == -1U)
        continue;
      // INIT MATRIX //////////
      std::vector<unsigned char> matrix(w, 0);
      unsigned val = 0;
      for (auto& c: matrix)
        c = val++;
      // END INIT MATRIX ///////
      // First element is a sentinelle as it will never be iterated on
      unsigned size = 0;
      stack.emplace_back(idx, size);
      do {
        bits n = trie->nodes[idx];
        s.push_back(to_char[n.letter]);
        update_matrix(matrix, n.letter);
        if (n.brother)
          {
            unsigned b = n.brother;
            stack.emplace_back(b, size);
          }
        if (n.is_terminal && matrix.back() <= dist)
          {
            res.emplace_back(n.freq, s);
          }
        if (n.sun)
          {
            ++idx;
            ++size;
          }
        else
          {
            auto p = stack.back();
            idx = p.first;
            size = p.second;
            // keep first sentinell row, and all following letters
            matrix.resize((1 + size) * w);
            s.resize(size);
            stack.pop_back();
          }
      } while (!stack.empty());
    }
  return res;
}

void levenshtein::remap_word()
{
  for (auto& c: other)
    c = trie->map[c];
  std::cerr << "New word:";
  for (auto& c: other)
    std::cerr << static_cast<unsigned>(c) << ' ';
  std::cerr << std::endl;
}

unsigned trie_bin::dfs_iter()
{
  unsigned res = 0;
  std::vector<unsigned> stack;
  for (unsigned i = 0; i < 41; ++i)
    {
      unsigned idx = start_pos[i];
      if (idx == -1U)
        continue;
      // First element is a sentinelle as it will never be iterated on
      stack.push_back(idx);
      do {
        bits n = nodes[idx];
        res += n.is_terminal;
        if (n.brother)
          stack.push_back(n.brother);
        if (n.sun)
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

void levenshtein::update()
{
  for (unsigned i = 0; i < 256; ++i)
    {
      if (trie->map[i] != -1)
        {
          to_char[trie->map[i]] = i;
        }
    }
}

void levenshtein::dump_matrix(std::vector<unsigned char>& matrix)
{
  for (unsigned j = 0; j < matrix.size() / w; ++j)
    {
      for (unsigned i = 0; i < w; ++i)
        {
          std::cerr << (unsigned) matrix[j * w + i] << ' ';
        }
      std::cerr << std::endl;
    }
  std::cerr << std::endl;
}
