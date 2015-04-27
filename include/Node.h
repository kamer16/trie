#ifndef NODE_H_
# define NODE_H_

#include <string>

using namespace std;

class Node
{
    public:
        Node();
        virtual ~Node();

        string getLetters();
        int getFreq();

        void setLetters(string letters);
        void setFreq(int freq);

    private:
        string letters_;
        int freq_;
        Node *leftNode_;
        Node *rightNode_;
};

#endif /* !NODE_H_ */
