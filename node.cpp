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

IdentifierNode::IdentifierNode(const Token& token) :
    name(token.raw_value) {
}

ArrayAccessNode::ArrayAccessNode(ExpressionNodePtr array, CommaSeparatedArgsNodePtr index) :
    array(array), index(index) {
}

BinaryOperatorNode::BinaryOperatorNode(Token::Operator operation, ExpressionNodePtr left, ExpressionNodePtr right) :
    operation(operation), left(left), right(right) {
}

CommaSeparatedArgsNode::CommaSeparatedArgsNode(ExpressionNodePtr expr) {
    args.push_back(expr);
}

FunctionCallNode::FunctionCallNode(IdentifierNodePtr func_id, CommaSeparatedArgsNodePtr args) :
    function_identifier(func_id), args(args) {
}

UnaryOperatorNode::UnaryOperatorNode(Token::Operator operation, ExpressionNodePtr node) :
    operation(operation), node(node) {
}

RecordAccessNode::RecordAccessNode(ExpressionNodePtr record, IdentifierNodePtr field) :
    record(record), field(field) {
}

string Node::str() {
    return "";
}

string EofNode::str() {
    return "end of file";
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

string BinaryOperatorNode::str() {
    return operator_lst[operation];
}

string ArrayAccessNode::str() {
    return "[]";
}

string CommaSeparatedArgsNode::str() {
    return ",";
}

string CommaSeparatedIdentifiersNode::str() {
    return ",";
}

string RecordAccessNode::str() {
    return ".";
}

string FunctionCallNode::str() {
    return "FUNCTION CALL";
}

string UnaryOperatorNode::str() {
    return operator_lst[operation];
}

bool Node::empty() const {
    return false;
}

bool IdentifierNode::empty() const {
    return name.empty();
}








