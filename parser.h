#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ostream>
#include "scanner.h"
#include <algorithm>
#include "node.h"
#include "token.h"
#include "symboltable.h"

class Parser {
public:
	Parser(const std::string& filename, const bool strict = true);
	PNodeProgram parse_program();
	PNode parse();
	bool is_open() const;
	std::ostream& output_syntax_tree(std::ostream&);
	std::ostream& output_symbols(std::ostream&);
	std::string get_line(int);
	void set_strictness(const bool);
private:
	int output_subtree(PNode, int, int&, std::ostream&, bool silent = false);
	int output_subtree(std::string, int, int&, std::ostream&, bool silent = false);
	void require(std::initializer_list<Token::Operator>, Pos, const std::string&, const std::string&);
	void require(std::initializer_list<Token::Separator>,Pos, const std::string&, const std::string&);
	void require(std::initializer_list<Token::Category>, Pos, const std::string&, const std::string&);
	void require(std::initializer_list<Token::Reserved>, Pos, const std::string&, const std::string&);
	void require(std::initializer_list<Token::Operator>, const std::string&);
	void require(std::initializer_list<Token::Separator>,const std::string&);
	void require(std::initializer_list<Token::Category>, const std::string&);
	void require(std::initializer_list<Token::Reserved>, const std::string&);
	PNodeExpression parse_factor();
	PNodeExpression parse_expression(int);
	PNodeExpression new_literal_factor(const Token&);
	PNodeStmt parse_stmt();
	PNodeStmtIf parse_if();
	PNodeStmtWhile parse_while();
	PNodeStmtRepeat parse_repeat();
	PNodeStmtConst parse_const();
	PNodeStmtVar parse_var();
	PNodeStmtFor parse_for();
	PNodeStmtProcedure parse_procedure();
	PNodeStmtType parse_type_part();
	PNodeStmtFunction parse_function();
	PNodeTypeRecord parse_record();
	PNodeStmtBlock parse_block();
	PNodeIdentifier parse_identifier();

	std::vector<PNodeFormalParameterSection> parse_formal_parameters();
	std::vector<PNodeStmt> parse_procedure_body();
	PNodeFormalParameterSection parse_formal_parameter_section();
	PNodeActualParameters parse_actual_parameters();
	std::vector<PNodeIdentifier> parse_comma_separated_identifiers();
	PNodeVarDeclarationUnit parse_var_declaration_unit(PSymTable, bool with_initialization);
	PNodeInitializer parse_initializer();
	PNodeType parse_type();

	Scanner scanner;
	PNode syntax_tree = nullptr;
	std::vector<SymTable> m_current_scope;
};

class ParseError : public std::runtime_error {
public:
	ParseError(const Pos& pos, const std::string& msg) :
		std::runtime_error("parse error at " + (std::string)pos + ": " + msg), m_msg("at " + (std::string)pos + ": " + msg), m_pos(pos) {
	}
	const char* what() const noexcept override {
		std::string message = ("parse error at " + (std::string)pos() + ": " + m_msg).c_str();
		return message.c_str();
	}
	std::string msg() const {
		return m_msg;
	}
	Pos pos() const {
		return m_pos;
	}
private:
	std::string m_msg;
	Pos m_pos;
};

template <class T>
void check(Node* ptr, Pos pos, const std::string& msg) {
	if (!dynamic_cast<T*>(ptr)) {
		throw ParseError(pos, msg);
	}
}


#endif // PARSER_H
