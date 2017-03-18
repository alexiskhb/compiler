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
    NodePtr parse_comma_separated();
    NodePtr parse_statements();
    NodePtr parse_identifier();
    NodePtr parse_recursive(int);
    NodePtr new_node(Token::Operator, NodePtr, NodePtr);
    NodePtr new_node(Token::Operator, NodePtr);
    NodePtr new_node(Token::Separator, NodePtr, NodePtr);
    NodePtr new_literal_factor(const Token&);
    Scanner scanner;
    Token stored_token;
    NodePtr syntax_tree = nullptr;
    bool new_node_created = false;
};

#endif // PARSER_H
