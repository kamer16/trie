#include <string>

#include "Dictionnary.h"
#include "Node.h"
#include "Trie.h"

#include <sys/time.h>

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

    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    t.bfs();
    gettimeofday(&end, NULL);
    std::cerr << "Number of words: " << t.count_words() << std::endl;
    std::cerr << "BFS executed in: " << end.tv_usec - start.tv_usec
              << " micro-seconds" << std::endl;
    gettimeofday(&start, NULL);
    t.count_words();
    gettimeofday(&end, NULL);
    std::cerr << "Number of words: " << t.bfs() << std::endl;
    std::cerr << "DFS executed in: " << end.tv_usec - start.tv_usec
              << " micro-seconds" << std::endl;
}
