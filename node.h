#ifndef NODE_H
#define NODE_H

#include <string>
#include "token.h"
#include <map>
#include <memory>
#include "symbol.h"
#include "types.h"

enum Initializer : bool {
    on = true,
    off = false
};

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
    PSymbolVariable var;
    PSymbolType type;
};

class NodeBinaryOperator : public NodeExpression {
public:
    NodeBinaryOperator(Token::Operator, PNodeExpression, PNodeExpression);
    std::string str() override;
    Token::Operator operation;
    PNodeExpression left = nullptr;
    PNodeExpression right = nullptr;
};

class NodeActualParameters : public NodeSeparated {
public:
    NodeActualParameters(PNodeExpression);
    std::string str() override;
    std::vector<PNodeExpression> args;
};

//class NodeCommaSeparatedIdentifiers : public NodeSeparated {
//public:
//    std::string str() override;
//    std::vector<PNodeIdentifier> args;
//};

class NodeUnaryOperator : public NodeExpression {
public:
    NodeUnaryOperator(Token::Operator, PNodeExpression);
    std::string str() override;
    Token::Operator operation;
    PNodeExpression node;
};

class NodeArrayAccess : public NodeExpression {
public:
    NodeArrayAccess(PNodeExpression, PNodeActualParameters);
    std::string str() override;
    PNodeExpression array;
    PNodeActualParameters index;
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
    PNodeExpression cond;
    PNodeStmt then_stmt;
    PNodeStmt else_stmt;
};

class NodeStmtWhile : public NodeStmt {
public:
    std::string str() override;
    PNodeExpression cond;
    PNodeStmt stmt;
};

class NodeStmtAssign : public NodeStmt, public NodeBinaryOperator {
public:
    NodeStmtAssign(PNodeExpression, PNodeExpression);
    std::string str() override;
};

class NodeStmtConst : public NodeStmt {
public:
    std::string str() override;
    SymbolType type;
};

class NodeStmtRepeat : public NodeStmt {
public:
    std::string str() override;
    PNodeExpression cond;
    PNodeStmt stmt;
};

class NodeType : public Node {
public:
    PSymbolType type;
};

class NodeInitializer : public Node {
public:

};

class NodeVarDeclarationUnit : public Node {
public:
    std::vector<PNodeIdentifier> vars;
    PNodeType type;
    PNodeInitializer initializer = nullptr;
};

class NodeStmtVar : public NodeStmt {
public:
    std::string str() override;
    std::vector<PNodeVarDeclarationUnit> var_units;
};

class NodeStmtFor : public NodeStmt {
public:
    std::string str() override;
    PNodeIdentifier iter_var;
    PNodeExpression low;
    PNodeExpression high;
    bool is_inc = true;
    PNodeStmt stmt;
};

class NodeFormalParameterSection : public Node {
public:
    std::string str() override;
    std::vector<PNodeIdentifier> identifiers;
    PNodeIdentifier type;
    bool is_var = false;
};

class NodeStmtProcedure : public NodeStmt {
public:
    std::string str() override;
    PNodeIdentifier name;
    std::vector<PNodeFormalParameterSection> params;
    std::vector<PNodeStmt> parts;
};

class NodeStmtFunction : public NodeStmtProcedure {
public:
    std::string str() override;
    PNodeIdentifier result_type;
};



class NodeStmtRecord : public NodeStmt {
public:
    std::string str() override;
    std::vector<PNodeVarDeclarationUnit> fields;
};

class NodeStmtType : public NodeStmt {
public:
    std::string str() override;
};

class NodeStmtBlock : public NodeStmt {
public:
    std::string str() override;
    std::vector<PNodeStmt> stmts;
};

class NodeExprStmtFunctionCall : public NodeStmt, public NodeExpression {
public:
    NodeExprStmtFunctionCall(PNodeIdentifier, PNodeActualParameters);
    std::string str() override;
    PNodeIdentifier function_identifier;
    PNodeActualParameters args;
};


#endif // NODE_H























