#include "Levenshtein.h"

Levenshtein::Levenshtein(bool isFile, char* argv[])
{
    std::string arg1(argv[1]);
    std::string arg2(argv[2]);

    if (isFile == false)
    {
        word1.push_back(argv[1]);
        word2.push_back(argv[2]);

        std::cout << word1[0] << " " << word2[0] << std::endl; /* DEBUG */
    }
    else
    {
        std::ifstream file;
        file.open(arg2, std::ios::out);


        std::cout << file << std::endl;
    }
}

Levenshtein::~Levenshtein()
{
}
