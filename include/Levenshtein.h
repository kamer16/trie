#ifndef LEVENSHTEIN_H_
# define LEVENSHTEIN_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct bits
{
  // The index of the brother
  unsigned brother : 24;
  // Has at least one child
  unsigned sun : 1;
  // 2^6 = 64, we have 41 letters
  unsigned letter : 6;
  unsigned is_terminal : 1;
  unsigned freq;
};

struct trie_bin
{
  unsigned dfs_iter();

  // Should always be 41 as there are 41 characters
  unsigned start_pos[41];
  // Maps each char to a value between 0 and 41
  unsigned char map[256];
  bits nodes[];
};

class levenshtein
{
public:
  void remap_word();
  std::vector<std::pair<unsigned, std::string>> compute();
  void update();
  void update_matrix(std::vector<unsigned char>& matrix, unsigned char letter,
                     unsigned char old_let);
  void dump_matrix(std::vector<unsigned char>& matrix);
  std::string other;
  char to_char[41];
  unsigned dist;
  unsigned w;
  std::vector<unsigned char> buff;
  trie_bin* trie;
};

#endif /* !LEVENSHTEIN_H_ */
