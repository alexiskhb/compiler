#ifndef NODE_H
#define NODE_H

#include <string>
#include "token.h"
#include <map>
#include <memory>

class Node;
class SeparatedNode;
class ExpressionNode;
class IntegerNode;
class EofNode;
class FloatNode;
class StringNode;
class IdentifierNode;
class BinaryOperatorNode;
class CommaSeparatedArgsNode;
class FunctionCallNode;
class CommaSeparatedIdentifiersNode;
class UnaryOperatorNode;
class ArrayAccessNode;
class RecordAccessNode;

typedef std::shared_ptr<Node> NodePtr;
typedef std::shared_ptr<SeparatedNode> SeparatedNodePtr;
typedef std::shared_ptr<ExpressionNode> ExpressionNodePtr;
typedef std::shared_ptr<IntegerNode> IntegerNodePtr;
typedef std::shared_ptr<EofNode> EofNodePtr;
typedef std::shared_ptr<FloatNode> FloatNodePtr;
typedef std::shared_ptr<StringNode> StringNodePtr;
typedef std::shared_ptr<IdentifierNode> IdentifierNodePtr;
typedef std::shared_ptr<BinaryOperatorNode> BinaryOperatorNodePtr;
typedef std::shared_ptr<CommaSeparatedArgsNode> CommaSeparatedArgsNodePtr;
typedef std::shared_ptr<FunctionCallNode> FunctionCallNodePtr;
typedef std::shared_ptr<CommaSeparatedIdentifiersNode> CommaSeparatedIdentifiersNodePtr;
typedef std::shared_ptr<UnaryOperatorNode> UnaryOperatorNodePtr;
typedef std::shared_ptr<ArrayAccessNode> ArrayAccessNodePtr;
typedef std::shared_ptr<RecordAccessNode> RecordAccessNodePtr;

class Node {
public:
    virtual std::string str();
    virtual bool empty() const;
};

class SeparatedNode : public Node {
public:
};

class ExpressionNode : public Node {
public:
};

class EofNode : public ExpressionNode {
public:
    EofNode(const Token& token);
    std::string str() override;
};

class IntegerNode : public ExpressionNode {
public:
    IntegerNode(const Token& token);
    std::string str() override;
    int value;
};

class FloatNode : public ExpressionNode {
public:
    FloatNode(const Token& token);
    std::string str() override;
    long double value;
};

class StringNode : public ExpressionNode {
public:
    StringNode(const Token& token);
    std::string str() override;
    std::string value;
};

class IdentifierNode : public ExpressionNode {
public:
    IdentifierNode(const Token& token);
    bool empty() const override;
    std::string str() override;
    std::string name;
};

class BinaryOperatorNode : public ExpressionNode {
public:
    BinaryOperatorNode(Token::Operator, ExpressionNodePtr, ExpressionNodePtr);
    std::string str() override;
    Token::Operator operation;
    ExpressionNodePtr left = nullptr;
    ExpressionNodePtr right = nullptr;
};

//class ColonSeparated
//class SemicolonSeparated

class CommaSeparatedArgsNode : public SeparatedNode {
public:
    CommaSeparatedArgsNode(ExpressionNodePtr);
    std::string str() override;
    std::vector<ExpressionNodePtr> args;
};

class CommaSeparatedIdentifiersNode : public SeparatedNode {
public:
    std::string str() override;
    std::vector<IdentifierNodePtr> args;
};

class FunctionCallNode : public ExpressionNode {
public:
    FunctionCallNode(IdentifierNodePtr, CommaSeparatedArgsNodePtr);
    std::string str() override;
    IdentifierNodePtr function_identifier;
    CommaSeparatedArgsNodePtr args;
};

class UnaryOperatorNode : public ExpressionNode {
public:
    UnaryOperatorNode(Token::Operator, ExpressionNodePtr);
    std::string str() override;
    Token::Operator operation;
    ExpressionNodePtr node;
};

class ArrayAccessNode : public ExpressionNode {
public:
    ArrayAccessNode(ExpressionNodePtr, CommaSeparatedArgsNodePtr);
    std::string str() override;
    ExpressionNodePtr array;
    CommaSeparatedArgsNodePtr index;
};

class RecordAccessNode : public ExpressionNode {
public:
    RecordAccessNode(ExpressionNodePtr, IdentifierNodePtr);
    std::string str() override;
    ExpressionNodePtr record;
    IdentifierNodePtr field;
};




#endif // NODE_H
