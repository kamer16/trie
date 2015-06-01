#ifndef NODE_H_
# define NODE_H_

#include <string>
#include <vector>

using namespace std;

class Node
{
    public:
        Node();
        virtual ~Node();

        int getFreq();
        void setFreq(int freq);


    private:
        std::vector<unsigned char> sons_;
        int freq_;
};

#endif /* !NODE_H_ */
