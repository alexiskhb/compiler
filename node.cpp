#include "node.h"
#include "symboltable.h"
#include "scanner.h"
#include <sstream>

using namespace std;

PSymbolTypeInt NodeInteger::type_sym_ptr = nullptr;
PSymbolTypeFloat NodeFloat::type_sym_ptr = nullptr;
PSymbolTypeChar NodeString::char_type_sym_ptr = nullptr;
PSymbolTypeString NodeString::str_type_sym_ptr = nullptr;

uint NodeString::strcounter = 0;
string NodeString::str_prefix = ".str";
string fmt_newline = "._fmt_newline_";

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
	m_exprtype = NodeInteger::type_sym_ptr;
}

NodeFloat::NodeFloat(const Token& token) {
	value = Token::float_values[token.value_id];
	m_exprtype = NodeFloat::type_sym_ptr;
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
	m_exprtype = this->exprtype();
}

NodeBinaryOperator::NodeBinaryOperator(Token::Operator operation, PNodeExpression left, PNodeExpression right) :
	operation(operation), left(left), right(right) {
	m_exprtype = this->exprtype();
}

NodeVariable::NodeVariable(PNodeIdentifier identifier, PSymbolVariable s_var) :
    NodeExpression(s_var->type), identifier(identifier), symbol(s_var) {
	m_exprtype = this->exprtype();
}

NodeActualParameters::NodeActualParameters(PNodeExpression expr) {
	arglist.push_back(expr);
}

//NodeExprStmtFunctionCall::NodeExprStmtFunctionCall(PNodeIdentifier func_id, PNodeActualParameters args) :
//	function_identifier(func_id), args(args) {
//	//!
//}

NodeExprStmtFunctionCall::NodeExprStmtFunctionCall(PSymbolProcedure sym, PNodeActualParameters args) :
    proc(sym), args(args) {
	if (sym->name == "WRITE") {
		m_predefined = Predefined::WRITE;
	}
	if (sym->name == "WRITELN") {
		m_predefined = Predefined::WRITELN;
	}
	if (sym->name == "ORD") {
		m_predefined = Predefined::ORD;
	}
	if (sym->name == "CHR") {
		m_predefined = Predefined::CHR;
	}
	if (sym->name == "EXIT") {
		m_predefined = Predefined::EXIT;
	}
	m_exprtype = this->exprtype();
}

NodeUnaryOperator::NodeUnaryOperator(Token::Operator operation, PNodeExpression node) :
	operation(operation), node(node) {
	m_exprtype = this->exprtype();
}

NodeRecordAccess::NodeRecordAccess(PNodeExpression expr, PSymbolVariable var) :
    record(expr), field(var) {
	m_exprtype = this->exprtype();
}

NodeStmtAssign::NodeStmtAssign(PNodeExpression left, PNodeExpression right) :
	NodeBinaryOperator(Token::OP_ASSIGN, left, right) {
	m_exprtype = this->exprtype();
}

NodeConstant::NodeConstant(PSymbolConst sym) :
    symbol(sym) {
}

NodeConstantInt::NodeConstantInt(PSymbolConstInt sym) :
    NodeConstant(sym) {
}

NodeConstantFloat::NodeConstantFloat(PSymbolConstFloat sym) :
    NodeConstant(sym) {
}

NodeStmtBreak::NodeStmtBreak(PNodeStmt a_cycle) :
    cycle(a_cycle) {
}

NodeStmtContinue::NodeStmtContinue(PNodeStmt a_cycle) :
    cycle(a_cycle) {
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

string NodeStmtBreak::str() const {
	return "BREAK";
}

string NodeStmtContinue::str() const {
	return "CONTINUE";
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

string NodeTypeArray::str() const {
	return "ARRAY";
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
	PSymbolType ltype = left->exprtype(), rtype = right->exprtype();
	PSymbolType int_type = NodeInteger::type_sym_ptr, float_type = NodeFloat::type_sym_ptr;
	if (m_exprtype) {
		return m_exprtype;
	}
	switch (operation) {
	case Token::OP_PLUS:
	case Token::OP_MINUS:
	case Token::OP_MULT:{
		if (SymbolType::is_arithmetic({ltype, rtype})) {
			m_exprtype = SymbolType::max(ltype, rtype);
			break;
		}
		throw ParseError(Scanner::current_position(),
		                 "both operands of \""+operator_lst[operation]+"\" must be arithmetic: got \"" +
		                 left->exprtype()->name + "\" and \"" + right->exprtype()->name + "\"");
	}
	case Token::OP_DIV_SLASH: {
		if (SymbolType::is_arithmetic({ltype, rtype})) {
			m_exprtype = int_type;
			break;
		}
		throw ParseError(Scanner::current_position(),
		                 "both operands of \"\\\" must be arithmetic: got \"" +
		                 left->exprtype()->name + "\" and \"" + right->exprtype()->name + "\"");
	}
	case Token::OP_EQUAL:
	case Token::OP_GREATER:
	case Token::OP_LESS:
	case Token::OP_LEQ:
	case Token::OP_GEQ:
	case Token::OP_NEQ: {
		if (SymbolType::is_arithmetic({ltype, rtype})) {
			m_exprtype = int_type;
			break;
		}
		throw ParseError(Scanner::current_position(),
		                 "both operands of \""+operator_lst[operation]+"\" must be arithmetic: got \"" +
		                 left->exprtype()->name + "\" and \"" + right->exprtype()->name + "\"");
	}
	case Token::OP_AND:
	case Token::OP_OR:
	case Token::OP_XOR:
	case Token::OP_SHL:
	case Token::OP_SHR:
	case Token::OP_DIV:
	case Token::OP_MOD: {
		if (ltype == int_type && rtype == int_type) {
			m_exprtype = int_type;
			break;
		}
		throw ParseError(Scanner::current_position(),
		                 "both operands of \""+operator_lst[operation]+"\" must be integer: got \"" +
		                 left->exprtype()->name + "\" and \"" + right->exprtype()->name + "\"");
	}
	case Token::OP_ASSIGN: {
		PNodeUnaryOperator l = dynamic_pointer_cast<NodeUnaryOperator>(left);
		m_exprtype = SymbolType::notype();
		if (SymbolType::is_arithmetic({ltype, rtype}) || ltype == rtype) {
//			m_exprtype = ltype;
		} else if (l && l->operation == Token::OP_DEREFERENCE) {
//			m_exprtype = l->exprtype();
		} else {
			throw ParseError(Scanner::current_position(),
			                 "Incompatible types : got \"" + rtype->name + "\", expected \"" + ltype->name + "\"");
		}
		break;
	}
	case Token::OP_DIV_ASSIGN:
	case Token::OP_PLUS_ASSIGN:
	case Token::OP_MINUS_ASSIGN:
	case Token::OP_MULT_ASSIGN: {
		m_exprtype = SymbolType::notype();
		break;
	}
	default: throw runtime_error("Internal error: unknown binary operator");
	}
	return m_exprtype;
}

PSymbolType NodeUnaryOperator::exprtype() {
	switch (this->operation) {
	case Token::OP_MINUS: {
		m_exprtype = this->node->exprtype();
		if (!SymbolType::is_arithmetic({m_exprtype})) {
			throw ParseError(Scanner::current_position(),
			                 "Incompatible type for unary operator \"-\": got \"" +
			                 m_exprtype->name + "\", expected float or integer");
		}
		break;
	}
	case Token::OP_DEREFERENCE: {
		m_exprtype = this->node->exprtype();
		if (!dynamic_pointer_cast<SymbolTypePointer>(m_exprtype)) {
			throw ParseError(Scanner::current_position(),
			                 "Incompatible type for dereference operator: got \"" +
			                 m_exprtype->name + "\", expected pointer");
		}
		break;
	}
	case Token::OP_AT: {
		if ((dynamic_pointer_cast<NodeArrayAccess>(node) ||
		    dynamic_pointer_cast<NodeVariable>(node) ||
		    (dynamic_pointer_cast<NodeUnaryOperator>(node) && dynamic_pointer_cast<NodeUnaryOperator>(node)->operation == Token::OP_DEREFERENCE)
		    ))
		{
			m_exprtype = make_shared<SymbolTypePointer>(node->exprtype());
		} else {
			throw ParseError(Scanner::current_position(),
			                 "Invalid operand for unary operator \"@\": must be lvalue");
		}
		break;
	}
	default: throw runtime_error("Internal error: unknown unary operator");
	}
	return m_exprtype;
}

PSymbolType NodeArrayAccess::exprtype() {
	if (m_exprtype) return m_exprtype;
	PSymbolTypeArray s = dynamic_pointer_cast<SymbolTypeArray>(this->array->exprtype());
	if (s) {
		m_exprtype = s->type;
	} else {
		throw ParseError(Scanner::current_position(),
		                 "left operand of [] must be an array");
	}
	for (int i = 0; i < this->index->arglist.size(); i++) {
		PNodeExpression expr = this->index->arglist[i];
		if (expr->exprtype() != NodeInteger::type_sym_ptr) {
			throw ParseError(Scanner::current_position(),
			                 "Incompatible type for arg no. " + to_string(i+1) +
			                 ": Got \"" + expr->exprtype()->name + "\", expected \"INTEGER\"");
		}
	}
	return m_exprtype;
}

PSymbolType NodeRecordAccess::exprtype() {
	return m_exprtype = this->field->type;
}

PSymbolType NodeExprStmtFunctionCall::exprtype() {
	if (m_exprtype) return m_exprtype;
	PSymbolFunction f = dynamic_pointer_cast<SymbolFunction>(this->proc);
	m_exprtype = f ? f->type : SymbolType::notype();
	return m_exprtype;
}

PSymbolType NodeVariable::exprtype() {
	return m_exprtype = symbol->type;
}

bool NodeExprStmtFunctionCall::check_parameters(Pos pos) {
	if (proc->params->size() == 0 && !args) {
		return true;
	}
	if (m_predefined) {
		return true;
	}
	if (proc->params->size() != args->size()) {
		throw ParseError(pos,
		                 "Wrong number of parameters specified for call to \"" + proc->name +
		                 "\": Got " + to_string(args->size()) + ", expected " + to_string(proc->params->size()));
		return false;
	}
	SymTable& st = *proc->params;
	for (size_t i = 0; i < args->size(); i++) {
		PSymbolType formal, actual = args->at(i)->exprtype();
		PSymbolVariable formal_var;
		st[i] >> formal_var;
		formal = formal_var->type;
		if (formal != actual && !SymbolType::is_arithmetic({formal, actual})) {
			throw ParseError(pos,
			                 "Incompatible type for arg no. " + to_string(i+1) +
			                 ": Got \"" + actual->name + "\", expected \"" + formal->name + "\"");
			return false;
		}
	}
	return true;
}

void Node::generate(AsmCode& ac) {
}

void NodeInteger::generate(AsmCode& ac) {
	ac << AsmCmd1{PUSHQ, value};
}

void NodeFloat::generate(AsmCode& ac) {
	ac << AsmCmd2{MOVQ, value, RAX}
	   << AsmCmd1{PUSHQ, RAX};
}

void NodeString::generate(AsmCode& ac) {
	if (!m_label) {
		m_label = ac.add_data(make_shared<AsmVarString>(str_prefix + to_string(strlabel_id), value));
	}
}

void NodeVariable::generate(AsmCode& ac) {
	ac << AsmComment{"variable access"};
}

void NodeVariable::generate_assign(AsmCode& ac) {

}

void NodeExprStmtFunctionCall::generate_assign(AsmCode& ac) {

}

void NodeRecordAccess::generate_assign(AsmCode& ac) {

}

void NodeArrayAccess::generate_assign(AsmCode& ac) {

}

void NodeVariable::declare(AsmCode& ac) {
	this->exprtype()->declare(ac, this->identifier->name);
}

void NodeBinaryOperator::generate(AsmCode& ac) {
	left->generate(ac);
	right->generate(ac);
	ac << AsmCmd1{POPQ, RBX}
	   << AsmCmd1{POPQ, RAX};
	switch (this->operation) {
	case Token::OP_PLUS:
		ac << AsmCmd2{ADDQ, RBX, RAX}; break;
	case Token::OP_MINUS:
		ac << AsmCmd2{SUBQ, RBX, RAX}; break;
	case Token::OP_MULT:
		ac << AsmCmd2{IMULQ, RBX, RAX}; break;
	case Token::OP_DIV:
		ac << AsmCmd0{CQO}
		   << AsmCmd1{IDIVQ, RBX}; break;
	default:;
	}
	ac << AsmCmd1{PUSHQ, RAX};
}

void NodeUnaryOperator::generate(AsmCode& ac) {
	ac << AsmComment{"unary operator"};
}

void NodeArrayAccess::generate(AsmCode& ac) {
	ac << AsmComment{"array access"};
}

void NodeRecordAccess::generate(AsmCode& ac) {
	ac << AsmComment{"record access"};
}

void NodeStmtAssign::generate(AsmCode& ac) {

	ac << AsmComment{"stmt assign"};
}

void NodeStmtVar::generate(AsmCode& ac) {
	for (PNodeVarDeclarationUnit unit: this->units) {
		for (PNodeVariable var: unit->vars) {
			var->declare(ac);
		}
	}
}

void NodeExprStmtFunctionCall::generate(AsmCode& ac) {
	if (m_predefined == Predefined::WRITE || m_predefined == Predefined::WRITELN) {
		for (PNodeExpression expr: this->args->arglist) {
			m_write(ac, expr);
		}
		if (m_predefined == Predefined::WRITELN) {
			ac << AsmCmd2{LEAQ, AsmVar{fmt_newline}, RDI}
			   << AsmCmd1{CALL, PRINTF};
		}
	}
}

void NodeExprStmtFunctionCall::m_write(AsmCode& ac, PNodeExpression expr) {
	expr->generate(ac);
	expr->write(ac);
}

void NodeStmtBlock::generate(AsmCode& ac) {
	ac << AsmComment{"start block"};
	for (PNode stmt: this->stmts) {
		stmt->generate(ac);
	}
	ac << AsmComment{"end block"};
}

void NodeProgram::generate(AsmCode& ac) {
	ac.add_data(make_shared<AsmVarString>(SymbolTypeInt::fml_label, "%Ld"));
	ac.add_data(make_shared<AsmVarString>(SymbolTypeFloat::fml_label, "%lf"));
	ac.add_data(make_shared<AsmVarString>(fmt_newline, "\n"));
	ac << *ac.add_data(make_shared<AsmGlobl>("main"));
	ac << AsmCmd1{PUSHQ, RBP}
	   << AsmCmd2{MOVQ, RSP, RBP};
	for (PNode part: this->parts) {
		part->generate(ac);
	}
	ac << AsmCmd1{POPQ, RBP}
	   << AsmCmd2{XORQ, RAX, RAX}
	   << AsmCmd0{RET};
}

void NodeExpression::write(AsmCode& ac) {
	this->exprtype()->write(ac);
}

void NodeExpression::generate_assign(AsmCode& ac) {
	ac << AsmComment("TODO: define assign for this kind of expr (or compiler must throw here)");
}

void NodeInteger::write(AsmCode& ac) {
	NodeInteger::type_sym_ptr->write(ac);
}

void NodeFloat::write(AsmCode& ac) {
	NodeFloat::type_sym_ptr->write(ac);
}

void NodeString::write(AsmCode& ac) {
	ac << AsmCmd2{LEAQ, dynamic_pointer_cast<AsmVar>(m_label), RDI}
	   << AsmCmd1{CALL, PRINTF};
}






















