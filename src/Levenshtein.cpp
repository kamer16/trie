#include "Levenshtein.h"

Levenshtein::Levenshtein(bool isFile, char* argv[])
{
    std::string arg1(argv[1]);
    std::string arg2(argv[2]);

    if (isFile == false)
    {
        word1.push_back(argv[1]);
        word2.push_back(argv[2]);

        std::cerr << word1[0] << " " << word2[0] << std::endl; /* DEBUG */
    }
    else
    {
        std::ifstream file;
        file.open(arg2, std::ios::out);

        std::string line;
        while (getline(file, line))
        {
            boost::char_separator<char> sep(" ");
            boost::tokenizer<boost::char_separator<char>> tok(line, sep);
            bool first = true;
            for (const auto& t: tok)
            {
                if (first == true)
                {
                    word1.push_back(t);
                    first = false;
                }
                else
                    word2.push_back(t);
            }
        }

        file.close();
    }
}

Levenshtein::~Levenshtein()
{
}

void Levenshtein::compute()
{
    for (unsigned int l = 0; l < word1.size(); ++l)
    {
        std::string w1 = word1[l];
        std::string w2 = word2[l];
        std::cerr << "WORDS: " << w1 << " " << w2 << std::endl;

        int** matrix = new int*[w1.size() + 1];
        for (size_t i = 0; i < w1.size() + 1; ++i)
            matrix[i] = new int[w2.size() + 1];

        for (size_t i = 0; i < w1.size() + 1; ++i)
            for (size_t j = 0; j < w2.size() + 1; ++j)
                matrix[i][j] = 0;


        unsigned int i = 0;
        unsigned int j = 0;
        int d = 0;

        // Initialization
        for (i = 0; i < w1.size() + 1; ++i)
            matrix[i][0] = i;
        for (j = 1; j < w2.size() + 1; ++j)
            matrix[0][j] = j;

        for (i = 1; i < w1.size() + 1; ++i)
        {
            for (j = 1; j < w2.size() + 1; ++j)
            {
                if (w1[i - 1] == w2[j - 1])
                    d = 0;
                else
                    d = 1;

                int minSupIns = std::min(matrix[i - 1][j] + 1,
                        matrix[i][j - 1] + 1);
                matrix[i][j] = std::min(minSupIns, matrix[i - 1][j - 1] + d);

                if (i > 1 && j > 1 && w1[i - 1] == w2[j - 2]
                        && w1[i - 2] == w2[j - 1])
                    matrix[i][j] = std::min(matrix[i][j],
                            matrix[i - 2][j - 2] + d);

            }
        }

        dist.push_back(matrix[w1.size()][w2.size()]);
    }

    std::cerr << "distance:" << std::endl;
    for (int d: dist)
        std::cerr << d << std::endl;
}

