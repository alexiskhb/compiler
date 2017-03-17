#ifndef NODE_H
#define NODE_H

#include <string>
#include "token.h"
#include <map>
#include <memory>

class Node;

typedef std::shared_ptr<Node> NodePtr;

class Node {
public:
    virtual std::string str();
    NodePtr left = nullptr;
    NodePtr right = nullptr;
};


class IntegerNode : public Node {
public:
    IntegerNode(const Token& token);
    std::string str() override;
    int value;
};

class FloatNode : public Node {
public:
    FloatNode(const Token& token);
    std::string str() override;
    long double value;
};

class StringNode : public Node {
public:
    StringNode(const Token& token);
    std::string str() override;
    std::string value;
};

class IdentifierNode : public Node {
public:
    IdentifierNode(const Token& token);
    std::string str() override;
    std::string name;
};

class BinaryOperator : public Node {
public:
    BinaryOperator(Token::Operator, NodePtr, NodePtr);
    std::string str() override;
    Token::Operator operation;
};

class UnaryOperator : public BinaryOperator {
public:
    UnaryOperator(Token::Operator, NodePtr);
    std::string str() override;
};




#endif // NODE_H
