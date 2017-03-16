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
public:
    IntegerNode(const Token& token);
    int value;
};

class FloatNode : public Node {
public:
    FloatNode(const Token& token);
    long double value;
};

class StringNode : public Node {
public:
    StringNode(const Token& token);
    std::string value;
};

class IdentifierNode : public Node {
public:
    IdentifierNode(const Token& token);
    std::string name;
};

class BinaryOperator : public Node {
public:
    BinaryOperator(Token::Operator, NodePtr, NodePtr);
    NodePtr left;
    NodePtr right;
};

class UnaryOperator : public BinaryOperator {
public:
    UnaryOperator(Token::Operator, NodePtr);
};




#endif // NODE_H
