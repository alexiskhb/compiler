#include "node.h"

using namespace std;

std::map<Token::Operator, std::string> operator_lst =
{
{Token::OP_EQUAL, "="},
{Token::OP_GREATER, ">"},
{Token::OP_LESS, "<"},
{Token::OP_PLUS, "+"},
{Token::OP_MINUS, "-"},
{Token::OP_SLASH_DIV, "/"},
{Token::OP_MULT, "*"},
{Token::OP_LEFT_BRACE, "{"},
{Token::OP_LEFT_PAREN, "("},
{Token::OP_ASSIGN, ":="},
{Token::OP_PLUS_ASSIGN, "+="},
{Token::OP_MINUS_ASSIGN, "-="},
{Token::OP_DIV_ASSIGN, "/="},
{Token::OP_MULT_ASSIGN, "*="},
{Token::OP_LEQ, "<="},
{Token::OP_GEQ, ">="},
{Token::OP_NEQ, "<>"},
{Token::OP_DOT, "."},
{Token::OP_AT, "@"},
{Token::OP_DOTDOT, ".."},
{Token::OP_RIGHT_PAREN, ")"},
{Token::OP_LEFT_BRACKET, "[]"},
{Token::OP_RIGHT_BRACKET, "]"},
{Token::OP_RIGHT_BRACE, ")"},
{Token::OP_DEREFERENCE, "^"},
{Token::OP_SHL, "SHL"},
{Token::OP_SHR, "SHR"},
{Token::OP_AND, "AND"},
{Token::OP_OR, "OR"},
{Token::OP_NOT, "NOT"},
{Token::OP_XOR, "XOR"},
{Token::OP_IN, "IN"},
{Token::OP_DIV, "DIV"},
{Token::OP_MOD, "MOD"},
};

std::map<Token::Separator, std::string> separator_lst =
{
{Token::S_COLON, ":"},
{Token::S_SCOLON, ";"},
{Token::S_COMMA, ","},
};

EofNode::EofNode(const Token&) {

}

IntegerNode::IntegerNode(const Token& token) {
    value = Token::int_values[token.value_id];
}

FloatNode::FloatNode(const Token& token) {
    value = Token::float_values[token.value_id];
}

StringNode::StringNode(const Token& token) {
    value = Token::string_values[token.value_id];
}

IdentifierNode::IdentifierNode(const Token& token) {
    name = token.raw_value;
}

BinaryOperator::BinaryOperator(Token::Operator a_operation, NodePtr a_left, NodePtr a_right) {
    operation = a_operation;
    left = a_left;
    right = a_right;
}

SeparatedPair::SeparatedPair(Token::Separator a_separator, NodePtr a_left, NodePtr a_right) {
    separator = a_separator;
    left = a_left;
    right = a_right;
}

UnaryOperator::UnaryOperator(Token::Operator operation, NodePtr node) : BinaryOperator(operation, node, nullptr) {

}

string Node::str() {
    return "";
}

string EofNode::str() {
    return "";
}

string IntegerNode::str() {
    return to_string(value);
}

string FloatNode::str() {
    return to_string(value);
}

string StringNode::str() {
    return "\"" + value + "\"";
}

string IdentifierNode::str() {
    return name;
}

string BinaryOperator::str() {
    return operator_lst[operation];
}

string SeparatedPair::str() {
    return separator_lst[separator];
}

string UnaryOperator::str() {
    return operator_lst[operation];
}

bool Node::empty() const {
    return false;
}

bool IdentifierNode::empty() const {
    return name.empty();
}








