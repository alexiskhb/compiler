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
{Token::S_SEMICOLON, ";"},
{Token::S_COMMA, ","},
};

NodeEof::NodeEof(const Token&) {
}

NodeInteger::NodeInteger(const Token& token) {
    value = Token::int_values[token.value_id];
}

NodeFloat::NodeFloat(const Token& token) {
    value = Token::float_values[token.value_id];
}

NodeString::NodeString(const Token& token) {
    value = Token::string_values[token.value_id];
}

NodeIdentifier::NodeIdentifier(const Token& token) :
    name(token.raw_value) {
}

NodeArrayAccess::NodeArrayAccess(PNodeExpression array, PNodeActualParameters index) :
    array(array), index(index) {
}

NodeBinaryOperator::NodeBinaryOperator(Token::Operator operation, PNodeExpression left, PNodeExpression right) :
    operation(operation), left(left), right(right) {
}

NodeActualParameters::NodeActualParameters(PNodeExpression expr) {
    args.push_back(expr);
}

NodeExprStmtFunctionCall::NodeExprStmtFunctionCall(PNodeIdentifier func_id, PNodeActualParameters args) :
    function_identifier(func_id), args(args) {
}

NodeUnaryOperator::NodeUnaryOperator(Token::Operator operation, PNodeExpression node) :
    operation(operation), node(node) {
}

NodeRecordAccess::NodeRecordAccess(PNodeExpression record, PNodeIdentifier field) :
    record(record), field(field) {
}

NodeStmtAssign::NodeStmtAssign(PNodeExpression left, PNodeExpression right) :
    NodeBinaryOperator(Token::OP_ASSIGN, left, right) {
}

string Node::str() {
    return "";
}

string NodeEof::str() {
    return "END OF FILE";
}

string NodeInteger::str() {
    return to_string(value);
}

string NodeFloat::str() {
    return to_string(value);
}

string NodeString::str() {
    return "\"" + value + "\"";
}

string NodeIdentifier::str() {
    return name;
}

string NodeBinaryOperator::str() {
    return operator_lst[operation];
}

string NodeArrayAccess::str() {
    return "[]";
}

string NodeActualParameters::str() {
    return ",";
}

//string NodeCommaSeparatedIdentifiers::str() {
//    return ",";
//}

string NodeRecordAccess::str() {
    return ".";
}

string NodeExprStmtFunctionCall::str() {
    return "FUNCTION CALL";
}

string NodeUnaryOperator::str() {
    return operator_lst[operation];
}

bool Node::empty() const {
    return false;
}

bool NodeIdentifier::empty() const {
    return name.empty();
}

string NodeStmtIf::str() {
    return "IF";
}
string NodeStmtWhile::str() {
    return "WHILE";
}
string NodeStmtAssign::str() {
    return "ASSIGN";
}
string NodeStmtConst::str() {
    return "CONST";
}
string NodeStmtRepeat::str() {
    return "REPEAT";
}
string NodeStmtVar::str() {
    return "VAR";
}
string NodeStmtFor::str() {
    return "FOR";
}
string NodeStmtProcedure::str() {
    return "PROCEDURE " + name->str();
}
string NodeFormalParameterSection::str() {
    return (is_var ? "var " : "") + type->str() + " FORMAL PARAMETERS:";
}
string NodeStmtFunction::str() {
    return "FUNCTION " + name->str();
}
string NodeStmtRecord::str() {
    return "RECORD";
}
string NodeStmtType::str() {
    return "TYPE";
}
string NodeStmtBlock::str() {
    return "BLOCK";
}





