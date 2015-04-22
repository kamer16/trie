#ifndef LEVENSHTEIN_H_
# define LEVENSHTEIN_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <boost/tokenizer.hpp>

class Levenshtein
{
    public:
        Levenshtein(bool isFile, char* argv[]);
        virtual ~Levenshtein();

		void compute();

    private:
        std::vector<std::string> word1;
        std::vector<std::string> word2;
		std::vector<int> dist;
};

#endif /* !LEVENSHTEIN_H_ */
