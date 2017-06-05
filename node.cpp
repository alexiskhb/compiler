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

NodeString::NodeString(const Token& token) :
    strlabel_id(NodeString::strcounter++)
{
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
	arglist.push_back(expr);
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
	if (func_id->name == "WRITE") {
		m_predefined = Predefined::WRITE;
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

string Node::str() const {
	return "";
}

string NodeEof::str() const {
	return "END OF FILE";
}

string NodeInteger::str() const {
	return to_string(value);
}

string NodeFloat::str() const {
	return to_string(value);
}

string NodeVarDeclarationUnit::str() const {
	return nodetype->symtype->str();
}

string NodeTypeDeclarationUnit::str() const {
	return "ALIAS " + alias->name;
}

string NodeString::str() const {
	return "\"" + value + "\"";
}

string NodeIdentifier::str() const {
	return name;
}

string NodeBinaryOperator::str() const {
	return operator_lst[operation];
}

string NodeArrayAccess::str() const {
	return "[]";
}

string NodeActualParameters::str() const {
	return ",";
}

//string NodeCommaSeparatedIdentifiers::str() const {
//    return ",";
//}

string NodeRecordAccess::str() const {
	return ".";
}

string NodeExprStmtFunctionCall::str() const {
	return "FUNCTION CALL";
}

string NodeUnaryOperator::str() const {
	return operator_lst[operation];
}

string NodeVariable::str() const {
	return identifier->name;
}

bool Node::empty() const {
	return false;
}

bool NodeIdentifier::empty() const {
	return name.empty();
}

string NodeStmtIf::str() const {
	return "IF";
}

string NodeStmtWhile::str() const {
	return "WHILE";
}

string NodeStmtAssign::str() const {
	return "ASSIGN";
}

string NodeStmtConst::str() const {
	return "CONST";
}

string NodeStmtRepeat::str() const {
	return "REPEAT";
}

string NodeStmtVar::str() const {
	return "VAR";
}

string NodeStmtFor::str() const {
	return "FOR";
}

string NodeStmtProcedure::str() const {
	return "PROCEDURE " + name->str();
}

string NodeFormalParameterSection::str() const {
	return (is_var ? "VAR " : "") + type->str() + " FORMAL PARAMETERS:";
}

string NodeStmtFunction::str() const {
	return "FUNCTION " + name->str();
}

string NodeTypeRecord::str() const {
	return "RECORD";
}

string NodeType::str() const {
	return symtype->str();
}

string NodeStmtType::str() const {
	return "TYPE";
}

string NodeStmtBlock::str() const {
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
	return nullptr;
}

bool NodeExprStmtFunctionCall::check_parameters() {
	if (symbol->params->size() == 0 && !args) {
		return true;
	}
	if (m_predefined) {
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

AsmCode& Node::generate(AsmCode& ac) {
	return ac;
}

AsmCode& NodeInteger::generate(AsmCode& ac) {
	return ac;
}

AsmCode& NodeFloat::generate(AsmCode& ac) {
	return ac;
}

uint NodeString::strcounter = 0;
string NodeString::str_prefix = ".str";

//std::string NodeString::label() const {
//	return NodeString::str_prefix + to_string(this->strlabel_id);
//}

AsmCode& NodeString::generate(AsmCode& ac) {
	PAsmLabel str = ac.add_data(make_shared<AsmVarString>(str_prefix + to_string(strlabel_id), value));
	ac << AsmCmd2{LEAQ, dynamic_pointer_cast<AsmVar>(str), RDI};
	ac << AsmCmd1{CALL, PRINTF};
	return ac;
}

AsmCode& NodeVariable::generate(AsmCode& ac) {
	ac << AsmComment{"variable access"};
	return ac;
}

AsmCode& NodeBinaryOperator::generate(AsmCode& ac) {
	ac << AsmComment{"binary operator"};
	return ac;
}

AsmCode& NodeUnaryOperator::generate(AsmCode& ac) {
	ac << AsmComment{"unary operator"};
	return ac;
}

AsmCode& NodeArrayAccess::generate(AsmCode& ac) {
	ac << AsmComment{"array access"};
	return ac;
}

AsmCode& NodeRecordAccess::generate(AsmCode& ac) {
	ac << AsmComment{"record access"};
	return ac;
}

AsmCode& NodeStmtAssign::generate(AsmCode& ac) {
	ac << AsmComment{"stmt assign"};
	return ac;
}

AsmCode& NodeStmtVar::generate(AsmCode& ac) {
	ac << AsmComment{"variables part"};
	return ac;
}

AsmCode& NodeExprStmtFunctionCall::generate(AsmCode& ac) {
	if (m_predefined == Predefined::WRITE) {
		for (PNodeExpression expr: this->args->arglist) {
			m_write(ac, expr);
		}
	}
	return ac;
}

void NodeExprStmtFunctionCall::m_write(AsmCode& ac, PNodeExpression expr) {
	expr->generate(ac);
//	expr->write(ac);
}

AsmCode& NodeStmtBlock::generate(AsmCode& ac) {
	ac << AsmComment{"start block"};
	for (PNode stmt: this->stmts) {
		stmt->generate(ac);
	}
	ac << AsmComment{"end block"};
	return ac;
}

AsmCode& NodeProgram::generate(AsmCode& ac) {
	ac.add_data(make_shared<AsmGlobl>("main"));
	ac << AsmLabel{"main"};
	ac << AsmCmd1{PUSHQ, RBP}
	   << AsmCmd2{MOVQ, RSP, RBP};
	for (PNode part: this->parts) {
		part->generate(ac);
	}
	ac << AsmCmd1{POPQ, RBP}
	   << AsmCmd2{XORQ, RAX, RAX}
	   << AsmCmd0{RET};
	return ac;
}

void NodeExpression::write() {
//	this->exprtype()->write();
}























