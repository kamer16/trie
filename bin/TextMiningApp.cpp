#include <iostream>
#include <cassert>
#include <algorithm>

#include "Levenshtein.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


bool compare(std::pair<unsigned, std::string> lhs,
             std::pair<unsigned, std::string> rhs)
{
  if (lhs.first == rhs.first)
    return lhs.second < rhs.second;
  else
    return lhs.first > rhs.first;
}

void test(char* test, std::string res)
{
  levenshtein lev;
  lev.other = std::string(test);
  lev.w = lev.other.size() + 1;
  std::vector<unsigned char> matrix(lev.w, 0);
  unsigned val = 0;
  for (auto& c: matrix)
    c = val++;
  for (unsigned i = 0; i < res.size(); ++i)
    {
      if (i > 0)
        lev.update_matrix(matrix, res[i], res[i - 1]);
      else
        lev.update_matrix(matrix, res[i], 0);
      lev.dump_matrix(matrix);
    }
}

int main(int argc, char* argv[])
{
  test("kries", std::string("crise"));
  if (argc < 2)
    return 1;
  struct stat sb;
  int fd = open(argv[1], O_RDONLY);
  if (fstat(fd, &sb) == -1)
    return -1;

  void* addr = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  levenshtein lev;
  lev.trie = static_cast<trie_bin*>(addr);
  lev.update();
  std::string approx;
  std::cin >> approx >> lev.dist >> lev.other;
  lev.w = 1 + lev.other.size();
  assert(!approx.compare("approx"));
  while (!std::cin.eof())
    {
      assert(!approx.compare("approx"));
      // map letters to [0, 41]
      lev.remap_word();
      std::vector<std::pair<unsigned, std::string>> res = lev.compute();
      stable_sort(res.begin(), res.end(), compare);
      for (auto p: res)
        {
          std::cout << p.second << ' ' << p.first << std::endl;
        }
      std::cin >> approx >> lev.dist >> lev.other;
      lev.w = 1 + lev.other.size();
    }
  std::cerr << sb.st_size << " is file size\n";
  std::cerr << lev.trie->dfs_iter() << " is number of words size\n";
  munmap(addr, sb.st_size);
  return 0;
}
