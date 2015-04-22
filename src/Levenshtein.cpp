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

		std::vector<std::vector<int> matrix;
		unsigned int i = 0;
		unsigned int j = 0;
		int dist = 0;

		// Initialization
		for (i = 0; i < w1.size(); ++i)
			matrix[i][0] = i;
		for (j = 1; j < w2.size(); ++j)
			matrix[0][j] = j;

		
		for (i = 1; i < w1.size(); ++i)
		{
			for (j = 1; j < w2.size(); ++j)
			{
				if (w1[i] == w2[j])
					dist = 0;
				else
					dist = 1;

				int minSupIns = std::min(matrix[i - 1][j] + 1,
											matrix[i][j - 1] + 1);
				matrix[i][j] = std::min(minSupIns, matrix[i - 1][j - 1] + dist);

				if (i > 1 && j > 1 && w1[i] == w2[j - 1] && w1[i - 1] == w2[j])
					matrix[i][j] = std::min(matrix[i][j],
											matrix[i - 2][j - 2] + dist);
			}
		}

		dist.push_back(matrix[w1.size()][w2.size()]);
	}

	for (int d: dist)
		std::cout << d << std::endl;
}

