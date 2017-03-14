#ifndef NODE_H
#define NODE_H

#include <string>
#include "token.h"
#include <memory>

class Node;

typedef std::shared_ptr<Node> NodePtr;

class Node {
public:
    Node();
};

class IntegerNode : public Node {

};

class BinaryOperation : public Node {
    NodePtr left;
    NodePtr right;
};




#endif // NODE_H
