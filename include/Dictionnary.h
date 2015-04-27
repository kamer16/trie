#ifndef DICTIONNARY_H_
# define DICTIONNARY_H_

#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>

using namespace std;

class Dictionnary
{
    public:
        Dictionnary(char *words);
        virtual ~Dictionnary();

        void extractWords();

    private:
        char *words_;
};

#endif /* !DICTIONNARY_H_ */
