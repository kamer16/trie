#include "Dictionnary.h"

int main(int argc, char* argv[])
{
    if (argc == 0)
        return 1;
    Dictionnary D(argv[1]);
    D.extractWords();
}
