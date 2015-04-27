#include "Node.h"

Node::Node()
{
}

Node::~Node()
{
}

string Node::getLetters()
{
    return letters_;
}

int Node::getFreq()
{
    return freq_;
}

void Node::setLetters(string letters)
{
    letters_ = letters;
}

void Node::setFreq(int freq)
{
    freq_ = freq;
}
