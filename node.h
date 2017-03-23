#ifndef NODE_H
#define NODE_H

#include <string>
#include "token.h"
#include <map>
#include <memory>
#include "symbol.h"
#include "symboltable.h"

class Node;
class NodeSeparated;
class NodeExpression;
class NodeInteger;
class NodeEof;
class NodeFloat;
class NodeString;
class NodeIdentifier;
class NodeBinaryOperator;
class NodeCommaSeparatedArgs;
class NodeFunctionCall;
class NodeCommaSeparatedIdentifiers;
class NodeUnaryOperator;
class NodeArrayAccess;
class NodeRecordAccess;

typedef std::shared_ptr<Node> PNode;
typedef std::shared_ptr<NodeSeparated> PNodeSeparated;
typedef std::shared_ptr<NodeExpression> PNodeExpression;
typedef std::shared_ptr<NodeInteger> PNodeInteger;
typedef std::shared_ptr<NodeEof> PNodeEof;
typedef std::shared_ptr<NodeFloat> PNodeFloat;
typedef std::shared_ptr<NodeString> PNodeString;
typedef std::shared_ptr<NodeIdentifier> PNodeIdentifier;
typedef std::shared_ptr<NodeBinaryOperator> PNodeBinaryOperator;
typedef std::shared_ptr<NodeCommaSeparatedArgs> PNodeCommaSeparatedArgs;
typedef std::shared_ptr<NodeFunctionCall> PNodeFunctionCall;
typedef std::shared_ptr<NodeCommaSeparatedIdentifiers> PNodeCommaSeparatedIdentifiers;
typedef std::shared_ptr<NodeUnaryOperator> PNodeUnaryOperator;
typedef std::shared_ptr<NodeArrayAccess> PNodeArrayAccess;
typedef std::shared_ptr<NodeRecordAccess> PNodeRecordAccess;

class NodeProgram;
class NodeStmt;
class NodeStmtIf;
class NodeStmtWhile;
class NodeStmtAssign;
class NodeStmtConst;
class NodeStmtRepeat;
class NodeStmtVar;
class NodeStmtFor;
class NodeStmtProcedure;
class NodeStmtFunction;
class NodeStmtRecord;
class NodeStmtType;
class NodeStmtBlock;
class NodeVarDeclarationUnit;

typedef std::shared_ptr<NodeProgram> PNodeProgram;
typedef std::shared_ptr<NodeStmt> PNodeStmt;
typedef std::shared_ptr<NodeStmtIf> PNodeStmtIf;
typedef std::shared_ptr<NodeStmtWhile> PNodeStmtWhile;
typedef std::shared_ptr<NodeStmtAssign> PNodeStmtAssign;
typedef std::shared_ptr<NodeStmtConst> PNodeStmtConst;
typedef std::shared_ptr<NodeStmtRepeat> PNodeStmtRepeat;
typedef std::shared_ptr<NodeStmtVar> PNodeStmtVar;
typedef std::shared_ptr<NodeStmtFor> PNodeStmtFor;
typedef std::shared_ptr<NodeStmtProcedure> PNodeStmtProcedure;
typedef std::shared_ptr<NodeStmtFunction> PNodeStmtFunction;
typedef std::shared_ptr<NodeStmtRecord> PNodeStmtRecord;
typedef std::shared_ptr<NodeStmtType> PNodeStmtType;
typedef std::shared_ptr<NodeStmtBlock> PNodeStmtBlock;
typedef std::shared_ptr<NodeVarDeclarationUnit> PNodeVarDeclarationUnit;


class Node {
public:
    virtual std::string str();
    virtual bool empty() const;
};

class NodeProgram : public Node {
public:
    std::vector<PNodeStmt> parts;
};

class NodeSeparated : public Node {
public:
};

class NodeExpression : public Node {
public:
};

class NodeEof : public NodeExpression {
public:
    NodeEof(const Token& token);
    std::string str() override;
};

class NodeInteger : public NodeExpression {
public:
    NodeInteger(const Token& token);
    std::string str() override;
    int value;
};

class NodeFloat : public NodeExpression {
public:
    NodeFloat(const Token& token);
    std::string str() override;
    long double value;
};

class NodeString : public NodeExpression {
public:
    NodeString(const Token& token);
    std::string str() override;
    std::string value;
};

class NodeIdentifier : public NodeExpression {
public:
    NodeIdentifier(const Token& token);
    bool empty() const override;
    std::string str() override;
    std::string name;
    SymbolVariable var;
};

class NodeBinaryOperator : public NodeExpression {
public:
    NodeBinaryOperator(Token::Operator, PNodeExpression, PNodeExpression);
    std::string str() override;
    Token::Operator operation;
    PNodeExpression left = nullptr;
    PNodeExpression right = nullptr;
};

class NodeCommaSeparatedArgs : public NodeSeparated {
public:
    NodeCommaSeparatedArgs(PNodeExpression);
    std::string str() override;
    std::vector<PNodeExpression> args;
};

class NodeCommaSeparatedIdentifiers : public NodeSeparated {
public:
    std::string str() override;
    std::vector<PNodeIdentifier> args;
};

class NodeFunctionCall : public NodeExpression {
public:
    NodeFunctionCall(PNodeIdentifier, PNodeCommaSeparatedArgs);
    std::string str() override;
    PNodeIdentifier function_identifier;
    PNodeCommaSeparatedArgs args;
};

class NodeUnaryOperator : public NodeExpression {
public:
    NodeUnaryOperator(Token::Operator, PNodeExpression);
    std::string str() override;
    Token::Operator operation;
    PNodeExpression node;
};

class NodeArrayAccess : public NodeExpression {
public:
    NodeArrayAccess(PNodeExpression, PNodeCommaSeparatedArgs);
    std::string str() override;
    PNodeExpression array;
    PNodeCommaSeparatedArgs index;
};

class NodeRecordAccess : public NodeExpression {
public:
    NodeRecordAccess(PNodeExpression, PNodeIdentifier);
    std::string str() override;
    PNodeExpression record;
    PNodeIdentifier field;
};


class NodeStmt : public Node {

};

class NodeStmtIf : public NodeStmt {
public:
    std::string str() override;
    NodeExpression cond;
    NodeStmt then_stmt;
    NodeStmt else_stmt;
};

class NodeStmtWhile : public NodeStmt {
public:
    std::string str() override;
    NodeExpression cond;
    NodeStmt stmt;
};

class NodeStmtAssign : public NodeStmt {
public:
    std::string str() override;
    NodeExpression left;
    NodeExpression right;
};

class NodeStmtConst : public NodeStmt {
public:
    std::string str() override;
};

class NodeStmtRepeat : public NodeStmt {
public:
    std::string str() override;
    NodeExpression cond;
    NodeStmt stmt;
};

class NodeVarDeclarationUnit : public Node {
public:
    PNodeCommaSeparatedIdentifiers vars;
    PSymbolType type;
};

class NodeStmtVar : public NodeStmt {
public:
    std::string str() override;
    std::vector<PNodeVarDeclarationUnit> vars;
};

class NodeStmtFor : public NodeStmt {
    std::string str() override;
};

class NodeStmtProcedure : public NodeStmt {
    std::string str() override;
};

class NodeStmtFunction : public NodeStmt {
    std::string str() override;
};

class NodeStmtRecord : public NodeStmt {
    std::string str() override;
};

class NodeStmtType : public NodeStmt {
    std::string str() override;
};

class NodeStmtBlock : public NodeStmt {
    std::string str() override;
};


#endif // NODE_H
