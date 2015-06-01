#include <string>

#include "Dictionnary.h"
#include "Node.h"
#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    //Dictionnary D(argv[1], argv[2]);
    //D.extractWords();
    Trie t;
    t.load(argv[1]);
    std::cerr << t.nodes_.size() << std::endl;
    unsigned sum = 0;
    for (auto c: t.nodes_)
      {
        sum += c == 0;
      }
    std::cout << sum << std::endl;
    //t.print();
    std::cout << t.num_sets() << std::endl;
}
