#include <iostream>

#include "Levenshtein.h"

static int check_arguments(int argc)
{
    if (argc < 3)
    {
        std::cout << "Not enough arguments" << std::endl;
        return 1;
    }
    else if (argc > 3)
    {
        std::cout << "Too much arguments" << std::endl;
        return 1;
    }

    return 0;
}

static bool parse_commandline(char* argv[])
{
    std::string arg1(argv[1]);

    if (arg1.compare("-file") == 0)
        return true;
    else
        return false;
}

int main(int argc, char* argv[])
{
    // check number of arguments
    int error = check_arguments(argc);
    if (error == 1)
        return 1;

    // check if input = file
    bool isFile = parse_commandline(argv);

    // compute Damerau-Levenshtein distance
    Levenshtein L(isFile, argv);
    L.compute();

    return 0;
}
