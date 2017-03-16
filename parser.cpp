#include "parser.h"

using namespace std;

int precedence_lst[Token::SIZEOF_OPERATORS];

bool init_precedence() {
    fill(precedence_lst, precedence_lst + Token::SIZEOF_OPERATORS, 0);

    precedence_lst[Token::OP_CARET] = 4096;

    precedence_lst[Token::OP_DOT] = 2048;

    precedence_lst[Token::OP_AT] = 1024;
    precedence_lst[Token::OP_NOT] = 1024;

    precedence_lst[Token::OP_AND] = 512;
    precedence_lst[Token::OP_ASTER] = 512;
    precedence_lst[Token::OP_SLASH] = 512;
    precedence_lst[Token::OP_DIV] = 512;
    precedence_lst[Token::OP_MOD] = 512;
    precedence_lst[Token::OP_SHL] = 512;
    precedence_lst[Token::OP_SHR] = 512;
    
    precedence_lst[Token::OP_PLUS] = 256;
    precedence_lst[Token::OP_MINUS] = 256;
    precedence_lst[Token::OP_OR] = 256;
    precedence_lst[Token::OP_XOR] = 256;
    
    precedence_lst[Token::OP_IN] = 128;
    precedence_lst[Token::OP_LEQ] = 128;
    precedence_lst[Token::OP_GEQ] = 128;
    precedence_lst[Token::OP_NEQ] = 128;
    precedence_lst[Token::OP_EQUAL] = 128;
    precedence_lst[Token::OP_GTHAN] = 128;
    precedence_lst[Token::OP_LTHAN] = 128;
    
    precedence_lst[Token::OP_ASSIGN] = 64;
    precedence_lst[Token::OP_PLUSAGN] = 64;
    precedence_lst[Token::OP_MINUSAGN] = 64;
    precedence_lst[Token::OP_FACAGN] = 64;
    precedence_lst[Token::OP_MULAGN] = 64;

    precedence_lst[Token::NOT_OPERATOR] = 0;
    return true;
}

int precedence(Token::Operator op) {
    static bool init = init_precedence();
    return precedence_lst[op];
}

int precedence(const Token& token) {
    return precedence((Token::Operator)token);
}

Parser::Parser(const string& filename) {
    scanner.open(filename);
}

bool Parser::is_open() const {
    return scanner.is_open();
}

NodePtr Parser::parse() {
    return nullptr;
}

NodePtr Parser::parse_expression() {
    NodePtr left = parse_term();
    Token token = ++scanner;
    if (precedence(scanner) == precedence(Token::OP_OR)) {
        ++scanner;
        NodePtr right = parse_expression();
        left = new_operator_node((Token::Operator)token, left, right);
    }
    return left;
}

NodePtr Parser::parse_term() {
    NodePtr left = parse_factor();
    if (precedence(scanner) == precedence(Token::OP_AND)) {
        Token token = scanner++;
        NodePtr right = parse_term();
        left = new_operator_node((Token::Operator)token, left, right);
    }
    return left;
}

NodePtr Parser::parse_factor() {
    Token token = scanner.top();
    switch ((Token::Category)token) {
    case Token::C_IDENTIFIER:
        return make_shared<IdentifierNode>(token);
    case Token::C_LITERAL:
        return new_literal_factor(token);
    case Token::C_OPERATOR: {
        if (token != Token::OP_LPAREN) {
            throw runtime_error("illegal factor operator");
        }
        ++scanner;
        NodePtr node = parse_expression();
        scanner.require(Token::OP_RPAREN);
        ++scanner;
        return node;
    }
    default: throw runtime_error("illegal factor category");
    }
    return nullptr;
}

NodePtr Parser::new_literal_factor(const Token& token) {
    switch (token.subcategory) {
    case Token::L_FLOAT:
        return make_shared<FloatNode>(token);
    case Token::L_INTEGER:
        return make_shared<IntegerNode>(token);
    case Token::L_STRING:
        return make_shared<StringNode>(token);
    default:
        throw runtime_error("illegal literal type");
    }
}

NodePtr Parser::new_operator_node(Token::Operator operation, NodePtr left, NodePtr right) {
    return make_shared<BinaryOperator>(operation, left, right);
}

