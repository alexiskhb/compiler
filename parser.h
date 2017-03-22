#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ostream>
#include "scanner.h"
#include <algorithm>
#include "node.h"
#include "token.h"

class Parser {
public:
    Parser(const std::string& filename);
    NodePtr parse_program();
    NodePtr parse_simple_expressions();
    bool is_open() const;
    std::ostream& output_syntax_tree(std::ostream&);
    std::string get_line(int);
private:
//    void output_subtree(BinaryOperatorNode, int&, std::ostream&);
    void output_subtree(NodePtr, int&, std::ostream&);
    void require(std::initializer_list<Token::Operator>, Pos, const std::string&, const std::string&);
    void require(std::initializer_list<Token::Category>, Pos, const std::string&, const std::string&);
    ExpressionNodePtr parse_factor();
    ExpressionNodePtr parse_expression(int);
    ExpressionNodePtr new_literal_factor(const Token&);
    CommaSeparatedArgsNodePtr parse_args();
    Scanner scanner;
    NodePtr syntax_tree = nullptr;
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
