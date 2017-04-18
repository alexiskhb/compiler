#include "node.h"
#include "symboltable.h"

using namespace std;

PSymbolTypeInt NodeInteger::type_sym_ptr = nullptr;
PSymbolTypeFloat NodeFloat::type_sym_ptr = nullptr;
PSymbolTypeChar NodeString::char_type_sym_ptr = nullptr;
PSymbolTypeString NodeString::str_type_sym_ptr = nullptr;

std::map<Token::Operator, std::string> operator_lst =
{
{Token::OP_EQUAL, "="},
{Token::OP_GREATER, ">"},
{Token::OP_LESS, "<"},
{Token::OP_PLUS, "+"},
{Token::OP_MINUS, "-"},
{Token::OP_DIV_SLASH, "/"},
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

NodeExpression::NodeExpression(PSymbolType type) :
    m_exprtype(type) {
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

NodeIdentifier::NodeIdentifier(const Token& token) {
	name.resize(token.raw_value.size());
	std::transform(token.raw_value.begin(), token.raw_value.end(), name.begin(), (int (*)(int))toupper);
	m_exprtype = nullptr;
}

NodeArrayAccess::NodeArrayAccess(PNodeExpression array, PNodeActualParameters index) :
	array(array), index(index) {
}

NodeBinaryOperator::NodeBinaryOperator(Token::Operator operation, PNodeExpression left, PNodeExpression right) :
	operation(operation), left(left), right(right) {
	m_exprtype = nullptr;
}

NodeVariable::NodeVariable(PNodeIdentifier identifier, PSymbolVariable s_var) :
    NodeExpression(s_var->type), identifier(identifier), symbol(s_var) {
}

NodeActualParameters::NodeActualParameters(PNodeExpression expr) {
	args.push_back(expr);
}

//NodeExprStmtFunctionCall::NodeExprStmtFunctionCall(PNodeIdentifier func_id, PNodeActualParameters args) :
//	function_identifier(func_id), args(args) {
//	//!
//}

NodeExprStmtFunctionCall::NodeExprStmtFunctionCall(PNodeIdentifier func_id, PSymbolProcedure sym, PNodeActualParameters args) :
    function_identifier(func_id), symbol(sym), args(args) {
	if (!dynamic_pointer_cast<SymbolFunction>(sym)) {
		m_exprtype = nullptr;
	} else {
		SymbolFunction& f = *dynamic_pointer_cast<SymbolFunction>(sym);
		m_exprtype = f.type;
	}
}

NodeUnaryOperator::NodeUnaryOperator(Token::Operator operation, PNodeExpression node) :
	operation(operation), node(node) {
}

NodeRecordAccess::NodeRecordAccess(PNodeExpression expr, PSymbolVariable var) :
    record(expr), field(var) {
	m_exprtype = field->type;
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

string NodeVarDeclarationUnit::str() {
	return nodetype->symtype->str();
}

string NodeTypeDeclarationUnit::str() {
	return "ALIAS " + alias->name;
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

string NodeVariable::str() {
	return identifier->name;
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
	return (is_var ? "VAR " : "") + type->str() + " FORMAL PARAMETERS:";
}

string NodeStmtFunction::str() {
	return "FUNCTION " + name->str();
}

string NodeTypeRecord::str() {
	return "RECORD";
}

string NodeType::str() {
	return symtype->str();
}

string NodeStmtType::str() {
	return "TYPE";
}

string NodeStmtBlock::str() {
	return "BLOCK";
}

PSymbolType NodeExpression::exprtype() {
	return m_exprtype;
}

PSymbolType NodeInteger::exprtype() {
	return NodeInteger::type_sym_ptr;
}

PSymbolType NodeFloat::exprtype() {
	return NodeFloat::type_sym_ptr;
}

PSymbolType NodeString::exprtype() {
	return value.size() == 1 ?
	            dynamic_pointer_cast<SymbolType>(NodeString::char_type_sym_ptr) :
	            dynamic_pointer_cast<SymbolType>(NodeString::str_type_sym_ptr);
}

PSymbolType NodeBinaryOperator::exprtype() {
	if (m_exprtype) {
		return m_exprtype;
	}
	if (Symbol::use_strict)
	switch (operation) {
	case Token::OP_PLUS:
	case Token::OP_MINUS:
	case Token::OP_MULT:
	case Token::OP_DIV_SLASH: {
		/// float > integer
		/// throws if types are incompatible
		m_exprtype = SymbolType::max(left->exprtype(), right->exprtype());
		break;
	}
	case Token::OP_EQUAL:
	case Token::OP_GREATER:
	case Token::OP_LESS:
	case Token::OP_LEQ:
	case Token::OP_GEQ:
	case Token::OP_NEQ: {
		if (SymbolType::is_arithmetic({left->exprtype(), right->exprtype()})) {
			m_exprtype = NodeInteger::type_sym_ptr;
			break;
		}
		if (Symbol::use_strict) {
			throw runtime_error("compare non-arithmetic expressions");
		}
	}
	case Token::OP_AND:
	case Token::OP_OR:
	case Token::OP_XOR:
	case Token::OP_SHL:
	case Token::OP_SHR:
	case Token::OP_DIV:
	case Token::OP_MOD: {
		if (SymbolType::equals({left->exprtype(), right->exprtype()}, NodeInteger::type_sym_ptr)) {
			m_exprtype = NodeInteger::type_sym_ptr;
			break;
		}
		if (Symbol::use_strict) {
			throw runtime_error("illegal expression");
		}
	}
	case Token::OP_ASSIGN: {
		break;
	}
	default: {
		if (Symbol::use_strict) {
			throw runtime_error("something wrong with binary operation");
		}
	}
	}
	return m_exprtype;
}

PSymbolType NodeUnaryOperator::exprtype() {

}

bool NodeExprStmtFunctionCall::check_parameters() {
	if (symbol->params->size() == 0 && !args) {
		return true;
	}
	if (symbol->params->size() != args->size()) {
		throw runtime_error("bad actual parameters");
	}
	SymTable& st = *symbol->params;
	for (size_t i = 0; i < args->size(); i++) {
		PSymbolType formal, actual = args->at(i)->exprtype();
		st[i] >> formal;
	}
	return true;
}








