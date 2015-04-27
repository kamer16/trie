#include "Dictionnary.h"

// Constructor
Dictionnary::Dictionnary(char *words)
{
    words_ = words;
}

// Destructor
Dictionnary::~Dictionnary()
{
}

// Extracts words from the file words.txt
void Dictionnary::extractWords()
{
    ifstream file(words_);

    if (file.is_open())
    {
        string word;
        while (getline(file, word))
        {
            boost::char_separator<char> sep(" ");
            boost::tokenizer<boost::char_separator<char>> tok(word, sep);
            for (const auto& t: tok)
                cout << t << " ";
            cout << endl;
        }
    }
    else
        cout << "Unable to open " << words_ << endl;
}
