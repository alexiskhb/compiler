#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ostream>
#include "scanner.h"
#include <algorithm>
#include <stack>
#include <map>
#include "node.h"
#include "token.h"
#include "symboltable.h"
#include "exceptions.h"

struct Symtables : public std::vector<PSymTable> {
	PSymbol operator[](const std::string& s);
	Symtables& operator<<(const PSymbol& symbol);
};

class Parser {
public:
	Parser(const std::string& filename, const bool strict = true);
	PNodeProgram parse_program();
	PNode parse();
	bool is_open() const;
	std::ostream& output_syntax_tree(std::ostream&);
	std::ostream& output_symbols(std::ostream&);
	std::string get_line(int);
	Parser& set_strictness(const bool);
	PNode tree();

private:
	int output_subtree(PNode,       int, int&, std::ostream&, bool silent = false);
	int output_subtree(std::string, int, int&, std::ostream&, bool silent = false);
	void require(const std::initializer_list<Token::Operator>&, Pos, const std::string&, const std::string&);
	void require(const std::initializer_list<Token::Separator>&,Pos, const std::string&, const std::string&);
	void require(const std::initializer_list<Token::Category>&, Pos, const std::string&, const std::string&);
	void require(const std::initializer_list<Token::Reserved>&, Pos, const std::string&, const std::string&);
	void require(const std::initializer_list<Token::Literal>&,  Pos, const std::string&, const std::string&);
	void require(const std::initializer_list<Token::Operator>&, const std::string&);
	void require(const std::initializer_list<Token::Separator>&,const std::string&);
	void require(const std::initializer_list<Token::Category>&, const std::string&);
	void require(const std::initializer_list<Token::Reserved>&, const std::string&);
	void require(const std::initializer_list<Token::Literal>&, const std::string&);
	PNodeExpression parse_factor();
	PNodeExpression parse_expression(int);
	PNodeExpression new_literal_factor(const Token&);
	PNodeStmt parse_stmt();
	PNodeStmtIf parse_if();
	PNodeStmtWhile parse_while();
	PNodeStmtRepeat parse_repeat();
	PNodeStmtBlock parse_repeat_block();
	PNodeStmtConst parse_const();
	PNodeStmtVar parse_var();
	PNodeStmtFor parse_for();
	PNodeStmtProcedure parse_procedure();
	PNodeStmtType parse_type_part();
	PNodeStmtFunction parse_function();
	PNodeStmtBlock parse_block();
	PNodeIdentifier parse_identifier();
	PNodeTypeRecord parse_type_record();
	PNodeTypeArray parse_type_array();
	PNodeTypeProc parse_type_procedure();
	PNodeTypeFunc parse_type_function();
	PNodeType parse_type();
	std::vector<PNodeFormalParameterSection> parse_formal_parameters();
	std::vector<PNodeStmt> parse_procedure_body();
	PNodeFormalParameterSection parse_formal_parameter_section();
	PNodeActualParameters parse_actual_parameters();
	std::vector<PNodeIdentifier> parse_comma_separated_identifiers();
	PNodeVarDeclarationUnit parse_var_declaration_unit(PSymTable, bool with_initialization);
	PNodeInitializer parse_initializer();
	PNodeConstant evaluate(PNodeExpression);
	void parse_procedure_header(PNodeIdentifier&, std::vector<PNodeFormalParameterSection>&, bool skip_identifier = false);
	void parse_function_header(PNodeIdentifier&, std::vector<PNodeFormalParameterSection>&, PNodeType&, bool skip_identifier = false);

	Scanner scanner;
	PNode m_syntax_tree = nullptr;
	Symtables m_symtables;
	std::vector<SymTable> m_current_scope;
	std::stack<PNodeStmt> m_current_cycle;
	std::map<std::string, bool> m_forwarded_funcs;
};

template <class T>
void check(Node* ptr, Pos pos, const std::string& msg) {
	if (!dynamic_cast<T*>(ptr)) {
		throw ParseError(pos, msg);
	}
}


#endif // PARSER_H
