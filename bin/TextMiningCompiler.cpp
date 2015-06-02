#include <string>

#include "Dictionnary.h"
#include "Node.h"
#include "Trie.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;

    std::cerr << "Loading dictionary\n";
    Dictionnary dict(argv[1]);
    std::cerr << "Loading trie\n";
    Trie t(dict);
    std::cerr << "Number of nodes: " << t.nodes_.size() << std::endl;
}
