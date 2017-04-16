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
	NodeExpression(){}
	NodeExpression(PSymbolType);
	virtual PSymbolType exprtype();
protected:
	PSymbolType m_exprtype;
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
	PSymbolType exprtype() override;
	int value;
	static PSymbolTypeInt type_sym_ptr;
};

class NodeFloat : public NodeExpression {
public:
	NodeFloat(const Token& token);
	std::string str() override;
	PSymbolType exprtype() override;
	long double value;
	static PSymbolTypeFloat type_sym_ptr;
};

class NodeString : public NodeExpression {
public:
	NodeString(const Token& token);
	PSymbolType exprtype() override;
	std::string str() override;
	std::string value;
	static PSymbolTypeChar char_type_sym_ptr;
	static PSymbolTypeString str_type_sym_ptr;
};

class NodeIdentifier : public NodeExpression {
public:
	/// toupper in constructor
	NodeIdentifier(const Token& token);
	bool empty() const override;
	std::string str() override;
	std::string name;
};

class NodeVariable : public NodeExpression {
public:
	NodeVariable(PNodeIdentifier, PSymbolType);
	std::string str() override;
	PNodeIdentifier identifier;
};

class NodeBinaryOperator : public NodeExpression {
public:
	NodeBinaryOperator(Token::Operator, PNodeExpression, PNodeExpression);
	PSymbolType exprtype() override;
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
	size_t size() const {
		return args.size();
	}
	PNodeExpression at(size_t n) {
		return args.at(n);
	}
};

class NodeUnaryOperator : public NodeExpression {
public:
	NodeUnaryOperator(Token::Operator, PNodeExpression);
	PSymbolType exprtype() override;
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
//	SymbolType type;
};

class NodeStmtRepeat : public NodeStmt {
public:
	std::string str() override;
	PNodeExpression cond;
	PNodeStmt stmt;
};

class NodeType : public Node {
public:
	std::string str() override;
	PSymbolType symtype;
};

class NodeInitializer : public Node {
public:

};

class NodeVarDeclarationUnit : public Node {
public:
	std::vector<PNodeIdentifier> vars;
	PNodeType nodetype;
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
	PNodeType type;
	bool is_var = false;
};

class NodeStmtProcedure : public NodeStmt {
public:
	std::string str() override;
	PNodeIdentifier name;
	std::vector<PNodeFormalParameterSection> params;
	std::vector<PNodeStmt> parts;
	PSymbolProcedure symbol;
};

class NodeStmtFunction : public NodeStmtProcedure {
public:
	std::string str() override;
	PNodeType result_type;
};

class NodeTypeRecord : public NodeType {
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
	NodeExprStmtFunctionCall(PNodeIdentifier, PSymbolProcedure, PNodeActualParameters args = nullptr);
	NodeExprStmtFunctionCall(PNodeIdentifier, PNodeActualParameters args = nullptr);
	bool check_parameters();
	std::string str() override;
	PNodeIdentifier function_identifier;
	PSymbolProcedure symbol;
	PNodeActualParameters args;
};


#endif // NODE_H




