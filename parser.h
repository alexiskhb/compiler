#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <ostream>
#include "scanner.h"
#include "node.h"
#include "token.h"

class Parser {
public:
    Parser(const std::string& filename);
    NodePtr parse();
    bool is_open() const;
    std::ostream& output_syntax_tree(std::ostream&);
private:
    void walk_tree(NodePtr, int&, std::ostream&);
    NodePtr parse_factor();
    NodePtr parse_recursive(int);
    NodePtr new_node(Token::Operator, NodePtr, NodePtr);
    NodePtr new_node(Token::Operator, NodePtr);
    NodePtr new_node(Token::Separator, NodePtr, NodePtr);
    NodePtr new_literal_factor(const Token&);
    Scanner scanner;
    NodePtr syntax_tree = nullptr;
};

class ParseError : public std::runtime_error {
public:
    ParseError(const Pos& pos, const std::string& msg) :
        std::runtime_error("parse error: " + msg + " at " + (std::string)pos), m_msg(msg), m_pos(pos) {
    }
    const char* what() const noexcept override {
        std::string message = ("parse error: " + m_msg + " at " + (std::string)pos()).c_str();
        std::cerr << message << std::endl;
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

#endif // PARSER_H
