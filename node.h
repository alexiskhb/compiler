#ifndef NODE_H
#define NODE_H

#include <string>
#include "token.h"
#include <map>
#include <fstream>
#include <iostream>
#include <memory>
#include "symbol.h"
#include "types.h"
#include "asmcode.h"

enum Initializer : bool {
	on = true,
	off = false
};

class Node {
public:
	virtual AsmCode& generate(AsmCode&);
	virtual std::string str() const;
	virtual bool empty() const;
};

class NodeProgram : public Node {
public:
	AsmCode& generate(AsmCode&) override;
	std::vector<PNodeStmt> parts;
};

class NodeExpression : public Node {
public:
	NodeExpression() {}
	NodeExpression(PSymbolType);
	virtual PSymbolType exprtype();
	virtual void write(AsmCode&);
protected:
	PSymbolType m_exprtype;
};

class NodeEof : public NodeExpression {
public:
	NodeEof(const Token& token);
	std::string str() const override;
};

class NodeInteger : public NodeExpression {
public:
	NodeInteger(const Token& token);
	std::string str() const override;
	PSymbolType exprtype() override;
	AsmCode& generate(AsmCode&) override;
	void write(AsmCode&) override;
	int64_t value;
	static PSymbolTypeInt type_sym_ptr;
};

class NodeFloat : public NodeExpression {
public:
	NodeFloat(const Token& token);
	std::string str() const override;
	PSymbolType exprtype() override;
	AsmCode& generate(AsmCode&) override;
	void write(AsmCode&) override;
	long double value;
	static PSymbolTypeFloat type_sym_ptr;
};

class NodeString : public NodeExpression {
public:
	NodeString(const Token& token);
	PSymbolType exprtype() override;
	std::string str() const override;
	AsmCode& generate(AsmCode&) override;
	std::string value;
	void write(AsmCode&) override;
	static PSymbolTypeChar char_type_sym_ptr;
	static PSymbolTypeString str_type_sym_ptr;
	const uint strlabel_id;
	static std::string str_prefix;
private:
	static uint strcounter;
	PAsmLabel m_label = nullptr;
};

class NodeIdentifier : public NodeExpression {
public:
	/// toupper in constructor
	NodeIdentifier(const Token& token);
	bool empty() const override;
	std::string str() const override;
	std::string name;
};

class NodeVariable : public NodeExpression {
public:
	NodeVariable(PNodeIdentifier, PSymbolVariable);
	std::string str() const override;
	PNodeIdentifier identifier;
	AsmCode& generate(AsmCode&) override;
	PSymbolVariable symbol;
};

class NodeBinaryOperator : public NodeExpression {
public:
	NodeBinaryOperator(Token::Operator, PNodeExpression, PNodeExpression);
	PSymbolType exprtype() override;
	std::string str() const override;
	AsmCode& generate(AsmCode&) override;
	Token::Operator operation;
	PNodeExpression left = nullptr;
	PNodeExpression right = nullptr;
};

class NodeActualParameters : public Node {
public:
	NodeActualParameters(PNodeExpression);
	std::string str() const override;
	std::vector<PNodeExpression> arglist;
	size_t size() const {
		return arglist.size();
	}
	PNodeExpression at(size_t n) {
		return arglist.at(n);
	}
};

class NodeUnaryOperator : public NodeExpression {
public:
	NodeUnaryOperator(Token::Operator, PNodeExpression);
	PSymbolType exprtype() override;
	std::string str() const override;
	AsmCode& generate(AsmCode&) override;
	Token::Operator operation;
	PNodeExpression node;
};

class NodeArrayAccess : public NodeExpression {
public:
	NodeArrayAccess(PNodeExpression, PNodeActualParameters);
	std::string str() const override;
	PNodeExpression array;
	AsmCode& generate(AsmCode&) override;
	PNodeActualParameters index;
};

class NodeRecordAccess : public NodeExpression {
public:
	NodeRecordAccess(PNodeExpression, PSymbolVariable);
	std::string str() const override;
	PNodeExpression record;
	AsmCode& generate(AsmCode&) override;
	PSymbolVariable field;
};

class NodeStmt : public Node {

};

class NodeStmtIf : public NodeStmt {
public:
	std::string str() const override;
	PNodeExpression cond;
	PNodeStmt then_stmt;
	PNodeStmt else_stmt;
};

class NodeStmtWhile : public NodeStmt {
public:
	std::string str() const override;
	PNodeExpression cond;
	PNodeStmt stmt;
};

class NodeStmtAssign : public NodeStmt, public NodeBinaryOperator {
public:
	NodeStmtAssign(PNodeExpression, PNodeExpression);
	AsmCode& generate(AsmCode&) override;
	std::string str() const override;
};

class NodeStmtConst : public NodeStmt {
public:
	std::string str() const override;
};

class NodeStmtRepeat : public NodeStmt {
public:
	std::string str() const override;
	PNodeExpression cond;
	PNodeStmt stmt;
};

class NodeType : public Node {
public:
	std::string str() const override;
	PSymbolType symtype;
};

class NodeInitializer : public Node {
public:

};

class NodeVarDeclarationUnit : public Node {
public:
	std::string str() const override;
	std::vector<PNodeVariable> vars;
	PNodeType nodetype;
	PNodeInitializer initializer = nullptr;
};

class NodeTypeDeclarationUnit : public Node {
public:
	std::string str() const override;
	PSymbolType alias;
	PNodeType nodetype;
};


class NodeStmtVar : public NodeStmt {
public:
	std::string str() const override;
	AsmCode& generate(AsmCode&) override;
	std::vector<PNodeVarDeclarationUnit> units;
};

class NodeStmtFor : public NodeStmt {
public:
	std::string str() const override;
	PNodeIdentifier iter_var;
	PNodeExpression low;
	PNodeExpression high;
	bool is_inc = true;
	PNodeStmt stmt;
};

class NodeFormalParameterSection : public Node {
public:
	std::string str() const override;
	std::vector<PNodeVariable> identifiers;
	PNodeType type;
	bool is_var = false;
};

class NodeStmtProcedure : public NodeStmt {
public:
	std::string str() const override;
	PNodeIdentifier name;
	std::vector<PNodeFormalParameterSection> params;
	std::vector<PNodeStmt> parts;
	PSymbolProcedure symbol;
};

class NodeStmtFunction : public NodeStmtProcedure {
public:
	std::string str() const override;
	PNodeType result_type;
};

class NodeTypeRecord : public NodeType {
public:
	std::string str() const override;
	std::vector<PNodeVarDeclarationUnit> units;
};

class NodeStmtType : public NodeStmt {
public:
	std::string str() const override;
	std::vector<PNodeTypeDeclarationUnit> units;
};

class NodeStmtBlock : public NodeStmt {
public:
	std::string str() const override;
	AsmCode& generate(AsmCode&) override;
	std::vector<PNodeStmt> stmts;
};

class NodeExprStmtFunctionCall : public NodeStmt, public NodeExpression {
public:
	NodeExprStmtFunctionCall(PNodeIdentifier, PSymbolProcedure, PNodeActualParameters args = nullptr);
	bool check_parameters();
	std::string str() const override;
	AsmCode& generate(AsmCode&) override;
	PNodeIdentifier function_identifier;
	PSymbolProcedure symbol;
	PNodeActualParameters args;
private:
	enum Predefined {
		NONE = 0,
		WRITE = 1
	};
	Predefined m_predefined = NONE;
	void m_write(AsmCode& ac, PNodeExpression);
};


#endif // NODE_H




