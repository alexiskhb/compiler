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
#include "exceptions.h"

enum Initializer : bool {
	on = true,
	off = false
};

class Node {
public:
	virtual void generate(AsmCode&);
	virtual std::string str() const;
	virtual bool empty() const;
};

class NodeProgram : public Node {
public:
	void generate(AsmCode&) override;
	std::vector<PNodeStmt> parts;
};

class NodeExpression : public Node {
public:
	NodeExpression() {}
	NodeExpression(PSymbolType);
	virtual PSymbolType exprtype();
	virtual void write(AsmCode&);
	virtual void generate_lvalue(AsmCode&);
protected:
	PSymbolType m_exprtype = nullptr;
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
	void generate(AsmCode&) override;
	void write(AsmCode&) override;
	int64_t value;
	static PSymbolTypeInt type_sym_ptr;
};

class NodeFloat : public NodeExpression {
public:
	NodeFloat(const Token& token);
	std::string str() const override;
	PSymbolType exprtype() override;
	void generate(AsmCode&) override;
	void write(AsmCode&) override;
	double value;
	static PSymbolTypeFloat type_sym_ptr;
};

class NodeString : public NodeExpression {
public:
	NodeString(const Token& token);
	PSymbolType exprtype() override;
	std::string str() const override;
	void generate(AsmCode&) override;
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
	PSymbolType exprtype() override;
	PNodeIdentifier identifier;
	void generate(AsmCode&) override;
	void generate_lvalue(AsmCode&) override;
	void declare(AsmCode&);
	PSymbolVariable symbol;
};

class NodeBinaryOperator : public NodeExpression {
public:
	NodeBinaryOperator(Token::Operator, PNodeExpression, PNodeExpression);
	PSymbolType exprtype() override;
	std::string str() const override;
	void generate(AsmCode&) override;
	Token::Operator operation;
	PNodeExpression left = nullptr;
	PNodeExpression right = nullptr;
private:
	void m_gen_arithm(AsmCode& ac);
	void m_gen_cmp(AsmCode& ac);
	void m_gen_bin(AsmCode& ac);
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
	void generate(AsmCode&) override;
	void generate_lvalue(AsmCode&) override;
	Token::Operator operation;
	PNodeExpression node;
};

class NodeArrayAccess : public NodeExpression {
public:
	NodeArrayAccess(PNodeExpression, PNodeActualParameters);
	std::string str() const override;
	PSymbolType exprtype() override;
	void generate(AsmCode&) override;
	void generate_lvalue(AsmCode&) override;
	PNodeExpression array;
	PNodeActualParameters index;
};

class NodeRecordAccess : public NodeExpression {
public:
	NodeRecordAccess(PNodeExpression, PSymbolVariable);
	std::string str() const override;
	PSymbolType exprtype() override;
	void generate(AsmCode&) override;
	void generate_lvalue(AsmCode&) override;
	PNodeExpression record;
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
	void generate(AsmCode&) override;
	std::string str() const override;
};

class NodeConstant : public Node {
public:
	NodeConstant(PSymbolConst);
	PSymbolConst symbol;
};

class NodeConstantInt : public NodeConstant {
public:
	NodeConstantInt(PSymbolConstInt);
};

class NodeConstantFloat : public NodeConstant {
public:
	NodeConstantFloat(PSymbolConstFloat);
};


class NodeStmtConst : public NodeStmt {
public:
	std::string str() const override;
	std::vector<PNodeConstant> vars;
};

class NodeStmtRepeat : public NodeStmt {
public:
	std::string str() const override;
	PNodeExpression cond;
	PNodeStmt stmt;
};

class NodeStmtBreak : public NodeStmt {
public:
	NodeStmtBreak(PNodeStmt);
	std::string str() const override;
	PNodeStmt cycle;
};

class NodeStmtContinue : public NodeStmt {
public:
	NodeStmtContinue(PNodeStmt);
	std::string str() const override;
	PNodeStmt cycle;
};

class NodeType : public Node {
public:
	std::string str() const override;
	PSymbolType symtype;
};

class NodeInitializer : public Node {
public:
	PNodeExpression expr;
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
	void generate(AsmCode&) override;
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

class NodeTypeArray : public NodeType {
public:
	std::string str() const override;
	PNodeType type;
};

class NodeTypeProc : public NodeType {
public:
};

class NodeTypeFunc : public NodeType {
public:
};

class NodeStmtType : public NodeStmt {
public:
	std::string str() const override;
	std::vector<PNodeTypeDeclarationUnit> units;
};

class NodeStmtBlock : public NodeStmt {
public:
	std::string str() const override;
	void generate(AsmCode&) override;
	std::vector<PNodeStmt> stmts;
};

class NodeExprStmtFunctionCall : public NodeStmt, public NodeExpression {
public:
	NodeExprStmtFunctionCall(PSymbolProcedure, PNodeActualParameters args = nullptr);
	bool check_parameters(Pos);
	PSymbolType exprtype() override;
	PSymbolType proctype();
	std::string str() const override;
	void generate(AsmCode&) override;
	void generate_lvalue(AsmCode&) override;
	PSymbolProcedure proc;
	PNodeActualParameters args;
private:
	PSymbolType m_proctype = nullptr;
	enum Predefined {
		NONE,
		WRITE,
		WRITELN,
		ORD,
		CHR,
		EXIT
	};
	Predefined m_predefined = NONE;
	void m_write(AsmCode& ac, PNodeExpression);
};


#endif // NODE_H




