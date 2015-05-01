#include "Dictionnary.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
        return 1;


    Dictionnary D(argv[1], argv[2]);
    D.extractWords();
}
