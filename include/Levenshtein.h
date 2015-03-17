#ifndef LEVENSHTEIN_H_
# define LEVENSHTEIN_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Levenshtein
{
    public:
        Levenshtein(bool isFile, char* argv[]);
        virtual ~Levenshtein();

    private:
        std::vector<std::string> word1;
        std::vector<std::string> word2;
};

#endif /* !LEVENSHTEIN_H_ */
