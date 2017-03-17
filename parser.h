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
    NodePtr parse_expression();
    NodePtr parse_term();
    NodePtr parse_factor();
    NodePtr new_operator_node(Token::Operator, NodePtr, NodePtr);
    NodePtr new_literal_factor(const Token&);
    Scanner scanner;
    NodePtr syntax_tree = nullptr;
};

#endif // PARSER_H
