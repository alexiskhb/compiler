#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "scanner.h"
#include "node.h"
#include "token.h"

class Parser {
public:
    Parser(const std::string& filename);
    NodePtr parse();
    NodePtr parse_expression();
    NodePtr parse_term();
    NodePtr parse_factor();
    NodePtr new_operator_node(Token::Operator, NodePtr, NodePtr);
    NodePtr new_literal_factor(const Token&);
    bool is_open() const;
private:
    Scanner scanner;
};

#endif // PARSER_H
