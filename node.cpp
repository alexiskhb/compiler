#include "node.h"

Node::Node() {

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

BinaryOperator::BinaryOperator(Token::Operator operation, NodePtr left, NodePtr right) {

}

UnaryOperator::UnaryOperator(Token::Operator operation, NodePtr node) : BinaryOperator(operation, node, node) {

}
