#include "Node.h"

Node::Node()
  : sons_(41), freq_(0)
{
}

Node::~Node()
{
}

int Node::getFreq()
{
    return freq_;
}

void Node::setFreq(int freq)
{
    freq_ = freq;
}
