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
    PNode parse_simple_expressions();
    bool is_open() const;
    std::ostream& output_syntax_tree(std::ostream&);
    std::string get_line(int);
    void set_strict(const bool);
private:
//    void output_subtree(BinaryOperatorNode, int&, std::ostream&);
    void output_subtree(PNode, int&, std::ostream&);
    void require(std::initializer_list<Token::Operator>, Pos, const std::string&, const std::string&);
    void require(std::initializer_list<Token::Category>, Pos, const std::string&, const std::string&);
    void require(std::initializer_list<Token::Reserved>, Pos, const std::string&, const std::string&);
    PNodeExpression parse_factor();
    PNodeExpression parse_expression(int);
    PNodeExpression new_literal_factor(const Token&);
    PNodeStmtIf parse_if();
    PNodeStmtWhile parse_while();
    PNodeStmtRepeat parse_repeat();
    PNodeStmtConst parse_const();
    PNodeStmtVar parse_var();
    PNodeStmtFor parse_for();
    PNodeStmtProcedure parse_procedure();
    PNodeStmtFunction parse_function();
    PNodeStmtRecord parse_record();
    PNodeStmtType parse_type();
    PNodeStmtBlock parse_block();

    PNodeCommaSeparatedArgs parse_args();
    Scanner scanner;
    PNode syntax_tree = nullptr;
    bool require_main_block = true;
    bool require_type_declared = true;
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
