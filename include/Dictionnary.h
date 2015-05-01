#ifndef DICTIONNARY_H_
# define DICTIONNARY_H_

#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>

using namespace std;

class Dictionnary
{
    public:
        Dictionnary(char *words, char *output_dict);
        virtual ~Dictionnary();

        void extractWords();

    private:
        char *words_;
		char *dict_;
};

#endif /* !DICTIONNARY_H_ */
