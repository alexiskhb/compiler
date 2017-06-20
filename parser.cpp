#include "parser.h"

using namespace std;

int precedence_lst[Token::SIZEOF_OPERATORS];
int precedence_sep_lst[Token::SIZEOF_SEPARATORS];
map<string, bool> for_checker;

PSymbol Symtables::operator[](const std::string& s) {
	if (!Symbol::use_strict) {
		return nullptr;
	}
	for (auto t = this->rbegin(); t != this->rend(); t++) {
		SymTable& st = **t;
		PSymbol r = st[s];
		if (r) {
			return r;
		}
	}
	if (Symbol::use_strict) {
		throw SymbolNotFound(Scanner::current_position(), s);
	}
	return nullptr;
}

Symtables& Symtables::operator<<(const PSymbol& symbol) {
	this->back() << symbol;
	return *this;
}

int PREC_MAX;
bool init_precedence() {
	fill(precedence_lst, precedence_lst + Token::SIZEOF_OPERATORS, 0);
	fill(precedence_sep_lst, precedence_sep_lst + Token::SIZEOF_SEPARATORS, 0);
	precedence_lst[Token::OP_DOT] = 10;///
	precedence_lst[Token::OP_DEREFERENCE]  = 9;
	precedence_lst[Token::OP_LEFT_BRACKET] = 9;
	precedence_lst[Token::OP_LEFT_PAREN]   = 9;///
	precedence_lst[Token::OP_AT]  = 8;
	precedence_lst[Token::OP_NOT] = 8;///
	precedence_lst[Token::OP_AND]       = 7;
	precedence_lst[Token::OP_MULT]      = 7;
	precedence_lst[Token::OP_DIV_SLASH] = 7;
	precedence_lst[Token::OP_DIV]       = 7;
	precedence_lst[Token::OP_MOD]       = 7;
	precedence_lst[Token::OP_SHL]       = 7;
	precedence_lst[Token::OP_SHR]       = 7;///
	precedence_lst[Token::OP_PLUS]  = 6;
	precedence_lst[Token::OP_MINUS] = 6;
	precedence_lst[Token::OP_OR]    = 6;
	precedence_lst[Token::OP_XOR]   = 6;///
	precedence_lst[Token::OP_IN]      = 5;
	precedence_lst[Token::OP_LEQ]     = 5;
	precedence_lst[Token::OP_GEQ]     = 5;
	precedence_lst[Token::OP_NEQ]     = 5;
	precedence_lst[Token::OP_EQUAL]   = 5;
	precedence_lst[Token::OP_GREATER] = 5;
	precedence_lst[Token::OP_LESS]    = 5;///
	precedence_lst[Token::OP_ASSIGN]       = 4;
	precedence_lst[Token::OP_PLUS_ASSIGN]  = 4;
	precedence_lst[Token::OP_MINUS_ASSIGN] = 4;
	precedence_lst[Token::OP_DIV_ASSIGN]   = 4;
	precedence_lst[Token::OP_MULT_ASSIGN]  = 4;///
	precedence_sep_lst[Token::S_COMMA] = 3;
	precedence_sep_lst[Token::S_COLON] = 2;///
	precedence_lst[Token::OP_RIGHT_BRACKET] = 2;
	precedence_lst[Token::OP_RIGHT_PAREN]   = 2;///
	precedence_sep_lst[Token::S_SEMICOLON] = 1;///
	PREC_MAX = 0;
	for (auto t: precedence_lst) {
		PREC_MAX = max(PREC_MAX, t);
	}
	for (auto t: precedence_sep_lst) {
		PREC_MAX = max(PREC_MAX, t);
	}
	return true;
}

int precedence(const Token& token) {
	switch (token.category) {
	case Token::C_OPERATOR: return precedence_lst[token.subcategory];
	case Token::C_SEPARATOR: return precedence_sep_lst[token.subcategory];
	default: return PREC_MAX;
	}
}

int precedence(Token::Separator sep) {
	return precedence_sep_lst[sep];
}

int precedence(Token::Operator op) {
	return precedence_lst[op];
}

Parser::Parser(const string& filename, const bool is_strict) {
	static bool init = init_precedence();
	scanner.open(filename);
	set_strictness(is_strict);
	m_symtables.clear();
	m_symtables.emplace_back(new SymTable);
	m_symtables <<
	             make_shared<SymbolTypeChar>("CHAR") <<
	             make_shared<SymbolTypeFloat>("FLOAT") <<
	             make_shared<SymbolTypeString>("STRING") <<
	             make_shared<SymbolTypeInt>("INTEGER") <<
	             make_shared<SymbolProcedure>("WRITE") <<
	             make_shared<SymbolProcedure>("WRITELN") <<
	             make_shared<SymbolProcedure>("EXIT");
	m_symtables["CHAR"] >> NodeString::char_type_sym_ptr;
	m_symtables["FLOAT"] >> NodeFloat::type_sym_ptr;
	m_symtables["STRING"] >> NodeString::str_type_sym_ptr;
	m_symtables["INTEGER"] >> NodeInteger::type_sym_ptr;
}

bool Parser::is_open() const {
	return scanner.is_open();
}

PNodeProgram Parser::parse_program() {
	NodeProgram* program = new NodeProgram;
	m_symtables.emplace_back(new SymTable);
	while (scanner == Token::C_RESERVED) {
		Token token = scanner;
		switch((Token::Reserved)token) {
		case Token::R_CONST: {
			program->parts.push_back(parse_const());
		} break;
		case Token::R_VAR: {
			program->parts.push_back(parse_var());
		} break;
		case Token::R_PROCEDURE: {
			program->parts.push_back(parse_procedure());
		} break;
		case Token::R_FUNCTION: {
			program->parts.push_back(parse_function());
		} break;
		case Token::R_TYPE: {
			program->parts.push_back(parse_type_part());
		} break;
		case Token::R_BEGIN: {
			program->parts.push_back(parse_block());
			require({Token::OP_DOT}, ".");
			return PNodeProgram(program);
		}
		default: throw ParseError(token, "unexpected \"" + token.raw_value + "\": BEGIN expected");
		}
	}
	if (Symbol::use_strict) {
		require({Token::R_BEGIN}, "keyword BEGIN");
	}
	return PNodeProgram(program);
}

PNodeStmt Parser::parse_stmt() {
	Token token = scanner;
	switch((Token::Reserved)token) {
	case Token::R_IF: return parse_if ();
	case Token::R_WHILE: return parse_while ();
	case Token::R_REPEAT: return parse_repeat();
	case Token::R_FOR: {
		return parse_for();
	}
	case Token::R_BEGIN: return parse_block();
	case Token::R_BREAK: {
		++scanner;
		if (m_current_cycle.size() > 0) {
			PNodeStmtBreak node = make_shared<NodeStmtBreak>(m_current_cycle.top());
			return node;
		} else {
			throw ParseError(scanner.top(), "BREAK not allowed");
		}
	} break;
	case Token::R_CONTINUE: {
		++scanner;
		if (m_current_cycle.size() > 0) {
			PNodeStmtContinue node = make_shared<NodeStmtContinue>(m_current_cycle.top());
			return node;
		} else {
			throw ParseError(scanner.top(), "CONTINUE not allowed");
		}
	} break;
	default: {
		PNodeExpression expr = parse_expression(precedence(Token::OP_ASSIGN));
		if (dynamic_pointer_cast<NodeExprStmtFunctionCall>(expr)) {
			return dynamic_pointer_cast<NodeExprStmtFunctionCall>(expr);
		} else if (dynamic_pointer_cast<NodeBinaryOperator>(expr)) {
			PNodeBinaryOperator op = dynamic_pointer_cast<NodeBinaryOperator>(expr);
			switch (op->operation) {
			case Token::OP_ASSIGN:
				return make_shared<NodeStmtAssign>(op->left, op->right);
			case Token::OP_MULT_ASSIGN: {
				PNodeBinaryOperator mult_res = make_shared<NodeBinaryOperator>(Token::OP_MULT, op->left, op->right);
				return make_shared<NodeStmtAssign>(op->left, mult_res);
			}
			case Token::OP_PLUS_ASSIGN: {
				PNodeBinaryOperator plus_res = make_shared<NodeBinaryOperator>(Token::OP_PLUS, op->left, op->right);
				return make_shared<NodeStmtAssign>(op->left, plus_res);
			}
			case Token::OP_DIV_ASSIGN: {
				PNodeBinaryOperator div_res = make_shared<NodeBinaryOperator>(Token::OP_DIV_SLASH, op->left, op->right);
				return make_shared<NodeStmtAssign>(op->left, div_res);
			}
			case Token::OP_MINUS_ASSIGN: {
				PNodeBinaryOperator minus_res = make_shared<NodeBinaryOperator>(Token::OP_MINUS, op->left, op->right);
				return make_shared<NodeStmtAssign>(op->left, minus_res);
			}
			default:/*throw*/;
			}
		} else {
//            throw
		}
	}
	}
	throw ParseError(scanner.top().position, scanner.top().strvalue());
}

PNodeStmtIf Parser::parse_if() {
	PNodeStmtIf node = make_shared<NodeStmtIf>();
	++scanner;
	node->cond = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_THEN}, "keyword THEN");
	++scanner;
	node->then_stmt = parse_stmt();
	if (scanner == Token::R_ELSE) {
		++scanner;
		node->else_stmt = parse_stmt();
	} else {
		node->else_stmt = nullptr;
	}
	return node;
}

PNodeStmtWhile Parser::parse_while() {
	PNodeStmtWhile node = make_shared<NodeStmtWhile>();
	++scanner;
	node->cond = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_DO}, "keyword DO");
	++scanner;
	m_current_cycle.push(node);
	node->stmt = parse_stmt();
	m_current_cycle.pop();
	return node;
}

PNodeStmtRepeat Parser::parse_repeat() {
	PNodeStmtRepeat node = make_shared<NodeStmtRepeat>();
	m_current_cycle.push(node);
	node->stmt = parse_repeat_block();
	m_current_cycle.pop();
	node->cond = parse_expression(precedence(Token::OP_EQUAL));
	return node;
}

PNodeStmtConst Parser::parse_const() {
	PNodeStmtConst node = make_shared<NodeStmtConst>();
	PSymTable st = m_symtables.back();
	++scanner;
	while (scanner == Token::C_IDENTIFIER) {
		string name = parse_identifier()->name;
		PNodeExpression expr;
		if (scanner == Token::OP_EQUAL) {
			++scanner;
			expr = parse_expression(Token::OP_PLUS);
			PSymbolConst sym;
			if (dynamic_pointer_cast<NodeInteger>(expr)) {
				sym = make_shared<SymbolConstInt>(name, NodeInteger::type_sym_ptr, dynamic_pointer_cast<NodeInteger>(expr)->value);
			} else if (dynamic_pointer_cast<NodeFloat>(expr)) {
				sym = make_shared<SymbolConstFloat>(name, NodeFloat::type_sym_ptr, dynamic_pointer_cast<NodeFloat>(expr)->value);
			} else {
				throw ParseError(scanner.top(), "only integer and float literals allowed");
			}
			st << sym;
		} else if (scanner == Token::S_COLON) {
			++scanner;
			require({Token::C_IDENTIFIER}, "plain type identifier");
			PNodeType type = parse_type();
			expr = parse_expression(Token::OP_PLUS);
		} else {// throw in other case
			require({Token::OP_EQUAL}, "=");
		}
		if (scanner == Token::C_RESERVED) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
		++scanner;
	}
	return node;
}

PNodeStmtVar Parser::parse_var() {
	PNodeStmtVar node = make_shared<NodeStmtVar>();
	++scanner;
	while (scanner == Token::C_IDENTIFIER) {
		node->units.push_back(parse_var_declaration_unit(m_symtables.back(), Initializer::on));
		if (scanner == Token::C_RESERVED) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
		++scanner;
	}
	return node;
}

PNodeStmtFor Parser::parse_for () {
	PNodeStmtFor node = make_shared<NodeStmtFor>();
	++scanner;
	require({Token::C_IDENTIFIER}, "identifier");
	node->iter_var = make_shared<NodeIdentifier>(scanner++);
	if (for_checker[node->iter_var->name]) {
		throw ParseError(scanner.top(),
		                 "Illegal assignment to for-loop variable \"" + node->iter_var->name + "\"");
	}
	for_checker[node->iter_var->name] = true;
	require({Token::OP_ASSIGN}, ":=");
	++scanner;
	node->low = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_TO, Token::R_DOWNTO}, "keyword TO or DOWNTO");
	node->is_inc = scanner++ == Token::R_TO;
	node->high = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_DO}, "keyword DO");
	++scanner;
	m_current_cycle.push(node);
	node->stmt = parse_stmt();
	m_current_cycle.pop();
	for_checker.erase(for_checker.find(node->iter_var->name));
	return node;
}

PNodeFormalParameterSection Parser::parse_formal_parameter_section() {
	PNodeFormalParameterSection node = make_shared<NodeFormalParameterSection>();
	if (scanner == Token::R_VAR) {
		node->is_var = true;
		++scanner;
	}
	vector<PNodeIdentifier> vars;
	while (scanner == Token::C_IDENTIFIER && scanner != Token::S_COLON) {
		vars.push_back(make_shared<NodeIdentifier>(scanner++));
		if (scanner == Token::S_COLON) {
			break;
		}
		require({Token::S_COMMA}, ",");
		++scanner;
	}
	require({Token::S_COLON}, ":");
	++scanner;
	node->type = parse_type();
	for (PNodeIdentifier var: vars) {
		PSymbolVariable pv = make_shared<SymbolVariable>(var->name, node->type->symtype);
		node->identifiers.push_back(make_shared<NodeVariable>(var, pv));
	}
	return node;
}

std::vector<PNodeFormalParameterSection> Parser::parse_formal_parameters() {
	std::vector<PNodeFormalParameterSection> params;
	while (++scanner != Token::OP_RIGHT_PAREN) {
		params.push_back(parse_formal_parameter_section());
		if (scanner == Token::OP_RIGHT_PAREN) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
	}
	++scanner;
	return params;
}

std::vector<PNodeStmt> Parser::parse_procedure_body() {
	std::vector<PNodeStmt> body;
	while (scanner == Token::C_RESERVED) {
		switch((Token::Reserved)scanner) {
		case Token::R_CONST: {
			body.push_back(parse_const());
		} break;
		case Token::R_VAR: {
			body.push_back(parse_var());
		} break;
		case Token::R_TYPE: {
			body.push_back(parse_type_part());
		} break;
		case Token::R_BEGIN: {
			body.push_back(parse_block());
			return body;
		}
		case Token::R_FORWARD: {
			++scanner;			if (body.size() == 0) {
				return body;
			} else {
				throw ParseError(scanner.top(), "invalid definition of forwarded function");
			}
		}
		default: throw ParseError(scanner.top(), "unexpected token \"" + scanner.top().raw_value + "\"");
		}
	}
	require({Token::R_BEGIN}, "keyword BEGIN");
	return body;
}

PNodeStmtType Parser::parse_type_part() {
	PNodeStmtType node = make_shared<NodeStmtType>();
	++scanner;
	require({Token::C_IDENTIFIER}, "identifier");
	while (scanner == Token::C_IDENTIFIER) {
		NodeTypeDeclarationUnit* tdu = new NodeTypeDeclarationUnit;
		PNodeIdentifier identifier = parse_identifier();
		require({Token::OP_EQUAL}, "=");
		++scanner;
		tdu->nodetype = parse_type();
		require({Token::S_SEMICOLON}, ";");
		++scanner;
		if (dynamic_pointer_cast<SymbolTypeArray>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeArray>(identifier->name, *dynamic_pointer_cast<SymbolTypeArray>(tdu->nodetype->symtype));
		} else if (dynamic_pointer_cast<SymbolTypeChar>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeChar>(identifier->name);				
		} else if (dynamic_pointer_cast<SymbolTypeFloat>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeFloat>(identifier->name);	
		} else if (dynamic_pointer_cast<SymbolTypeInt>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeInt>(identifier->name);	
		} else if (dynamic_pointer_cast<SymbolTypePointer>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypePointer>(identifier->name, dynamic_pointer_cast<SymbolTypePointer>(tdu->nodetype->symtype)->type);
		} else if (dynamic_pointer_cast<SymbolTypeRecord>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeRecord>(identifier->name);	
			dynamic_pointer_cast<SymbolTypeRecord>(tdu->alias)->symtable = dynamic_pointer_cast<SymbolTypeRecord>(tdu->nodetype->symtype)->symtable;
		} else if (dynamic_pointer_cast<SymbolTypeString>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeString>(identifier->name);	
		} else if (dynamic_pointer_cast<SymbolTypeProc>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeProc>(identifier->name, dynamic_pointer_cast<SymbolTypeProc>(tdu->nodetype->symtype)->proc);
		} else if (dynamic_pointer_cast<SymbolTypeFunc>(tdu->nodetype->symtype)) {
			tdu->alias = make_shared<SymbolTypeFunc>(identifier->name, dynamic_pointer_cast<SymbolTypeFunc>(tdu->nodetype->symtype)->func);
		}
		m_symtables << tdu->alias;
		node->units.push_back(PNodeTypeDeclarationUnit(tdu));
	}
	return node;
}

void Parser::parse_procedure_header(PNodeIdentifier& name, std::vector<PNodeFormalParameterSection>& params, bool skip_identifier) {
	if (!skip_identifier) {
		require({Token::C_IDENTIFIER}, "procedure/function identifier");
		name = make_shared<NodeIdentifier>(scanner++);
	}
	if (scanner == Token::OP_LEFT_PAREN) {
		params = parse_formal_parameters();
	}
}

void Parser::parse_function_header(PNodeIdentifier& name, std::vector<PNodeFormalParameterSection>& params, PNodeType& result_type, bool skip_identifier) {
	parse_procedure_header(name, params, skip_identifier);
	require({Token::S_COLON}, ":");
	++scanner;
	result_type = parse_type();
}

PNodeStmtProcedure Parser::parse_procedure() {
	PNodeStmtProcedure procedure = make_shared<NodeStmtProcedure>();
	++scanner;
	parse_procedure_header(procedure->name, procedure->params);
	require({Token::S_SEMICOLON}, ";");
	++scanner;
	procedure->symbol = make_shared<SymbolProcedure>(procedure->name->name);
	for (PNodeFormalParameterSection psection: procedure->params) {
		for (PNodeVariable var: psection->identifiers) {
			procedure->symbol->is_nth_var.push_back(psection->is_var);
			procedure->symbol->params << var->symbol;
			procedure->symbol->locals << var->symbol;
		}
	}
	if (m_forwarded_funcs[procedure->name->name]) {
		PSymbolProcedure p;
		m_symtables[procedure->name->name] >> p;
		if (p && make_shared<SymbolTypeProc>(p) == make_shared<SymbolTypeProc>(procedure->symbol)) {

		} else {
			throw ParseError(scanner.top(), "invalid definition of forwarded procedure \"" + procedure->name->name + "\"");
		}
	} else {
		m_symtables << procedure->symbol;
	}
	m_forwarded_funcs.erase(m_forwarded_funcs.find(procedure->name->name));

	m_symtables.push_back(procedure->symbol->locals);
	procedure->parts = parse_procedure_body();
	m_symtables.pop_back();

	require({Token::S_SEMICOLON}, ";");
	++scanner;
	if (procedure->parts.size() == 0) {//forward case
		m_forwarded_funcs[procedure->name->name] = true;
	}
	return procedure;
}

PNodeStmtFunction Parser::parse_function() {
	PNodeStmtFunction function = make_shared<NodeStmtFunction>();
	++scanner;
	parse_function_header(function->name, function->params, function->result_type);
	require({Token::S_SEMICOLON}, ";");
	++scanner;
	PSymbolFunction sf = make_shared<SymbolFunction>(function->name->name);
	sf->type = function->result_type->symtype;
	function->symbol = sf;
	for (PNodeFormalParameterSection psection: function->params) {
		for (PNodeVariable var: psection->identifiers) {
			function->symbol->is_nth_var.push_back(psection->is_var);
			function->symbol->params << var->symbol;
			function->symbol->locals << var->symbol;
		}
	}
	if (m_forwarded_funcs[function->name->name]) {
		PSymbolFunction ff = dynamic_pointer_cast<SymbolFunction>(function->symbol);
		PSymbolFunction f;
		m_symtables[function->name->name] >> f;
		if (f && ff && PSymbolType(make_shared<SymbolTypeFunc>(f)) == PSymbolType(make_shared<SymbolTypeFunc>(ff))) {

		} else {
			throw ParseError(scanner.top(), "invalid definition of forwarded function \"" + function->name->name + "\"");
		}
	} else {
		m_symtables << function->symbol;
	}
	m_forwarded_funcs.erase(m_forwarded_funcs.find(function->name->name));

	m_symtables.push_back(function->symbol->locals);
	function->parts = parse_procedure_body();
	m_symtables.pop_back();

	require({Token::S_SEMICOLON}, ";");
	++scanner;
	if (function->parts.size() == 0) {//forward case
		m_forwarded_funcs[function->name->name] = true;
	}
	return function;
}

std::vector<PNodeIdentifier> Parser::parse_comma_separated_identifiers() {
	PNodeIdentifier first = make_shared<NodeIdentifier>(scanner++);
	std::vector<PNodeIdentifier> result = {first};
	while (scanner == Token::S_COMMA) {
		++scanner;
		result.push_back(make_shared<NodeIdentifier>(scanner++));
	}
	return result;
}

PNodeInitializer Parser::parse_initializer() {
	PNodeInitializer node = make_shared<NodeInitializer>();
	node->expr = parse_expression(Token::OP_PLUS);
	return node;
}

PNodeConstant Parser::evaluate(PNodeExpression expr) {
	if (dynamic_pointer_cast<NodeInteger>(expr)) {
		return make_shared<NodeConstantInt>(
		            make_shared<SymbolConstInt>("",
		                                        NodeInteger::type_sym_ptr,
		                                        dynamic_pointer_cast<NodeInteger>(expr)->value));
	}
	if (dynamic_pointer_cast<NodeFloat>(expr)) {
		return make_shared<NodeConstantFloat>(
		            make_shared<SymbolConstFloat>("",
		                                        NodeFloat::type_sym_ptr,
		                                        dynamic_pointer_cast<NodeFloat>(expr)->value));
	}
	require({Token::L_INTEGER}, "float or integer literal");
	return nullptr;
}

PNodeVarDeclarationUnit Parser::parse_var_declaration_unit(PSymTable st, bool with_initialization) {
	PNodeVarDeclarationUnit node = make_shared<NodeVarDeclarationUnit>();
	vector<PNodeIdentifier> vars = parse_comma_separated_identifiers();
	require({Token::S_COLON}, ":");
	++scanner;
	node->nodetype = parse_type();
	node->initializer = nullptr;
	if (with_initialization) {
		if (scanner == Token::OP_EQUAL) {
			if (vars.size() > 1) {
				throw ParseError(scanner.current_position(), "only one variable can be initialized");
			}
			++scanner;
			node->initializer = parse_initializer();
			if (!SymbolType::is_arithmetic({node->initializer->expr->exprtype(), node->nodetype->symtype})) {
				throw ParseError(scanner.current_position(), "only arithmetic variables can be initialized");
			}
		}
	} else {
		if (scanner == Token::OP_EQUAL) {
			throw ParseError(scanner.current_position(), "unexpected initializer");
		}
	}
	for (PNodeIdentifier var: vars) {
		PSymbolVariable sv = make_shared<SymbolVariable>(var->name, node->nodetype->symtype);
		st << sv;
		node->vars.push_back(make_shared<NodeVariable>(var, sv));
	}
	return node;
}

PNodeTypeRecord Parser::parse_type_record() {
	PNodeTypeRecord node = make_shared<NodeTypeRecord>();
	++scanner;
	SymbolTypeRecord* stype = new SymbolTypeRecord;
	while (scanner == Token::C_IDENTIFIER) {
		node->units.push_back(parse_var_declaration_unit(stype->symtable, Initializer::off));
		if (scanner == Token::R_END) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
		++scanner;
	}
	require({Token::R_END}, "END");
	++scanner;
	node->symtype = PSymbolTypeRecord(stype);
	return node;
}

PNodeTypeArray Parser::parse_type_array() {
	PNodeTypeArray node = make_shared<NodeTypeArray>();
	++scanner;
	SymbolTypeArray* stype = new SymbolTypeArray;
	require({Token::OP_LEFT_BRACKET}, "[");
	do {
		int low, high;
		++scanner;
		require({Token::L_INTEGER}, "integer literal");
		low = dynamic_pointer_cast<NodeInteger>(parse_factor())->value;
		require({Token::OP_DOTDOT}, "..");
		++scanner;
		require({Token::L_INTEGER}, "integer literal");
		high = dynamic_pointer_cast<NodeInteger>(parse_factor())->value;
		stype->bounds.push_back({low, high});
	} while (scanner == Token::S_COMMA);
	require({Token::OP_RIGHT_BRACKET}, "]");
	++scanner;
	require({Token::R_OF}, "of");
	++scanner;
	node->type = parse_type();
	stype->type = node->type->symtype;
	node->symtype = PSymbolTypeArray(stype);
	return node;
}

PNodeTypeProc Parser::parse_type_procedure() {
	PNodeTypeProc proc = make_shared<NodeTypeProc>();
	++scanner;
	PNodeIdentifier name;
	std::vector<PNodeFormalParameterSection> params;
	parse_procedure_header(name, params, true);
	proc->symtype = make_shared<SymbolTypeProc>();
	for (PNodeFormalParameterSection psection: params) {
		for (PNodeVariable var: psection->identifiers) {
			dynamic_pointer_cast<SymbolTypeProc>(proc->symtype)->proc->is_nth_var.push_back(psection->is_var);
			dynamic_pointer_cast<SymbolTypeProc>(proc->symtype)->proc->params << var->symbol;
			dynamic_pointer_cast<SymbolTypeProc>(proc->symtype)->proc->locals << var->symbol;
		}
	}
	return proc;
}

PNodeTypeFunc Parser::parse_type_function() {
	PNodeTypeFunc func = make_shared<NodeTypeFunc>();
	++scanner;
	PNodeIdentifier name;
	std::vector<PNodeFormalParameterSection> params;
	PNodeType nt;
	parse_function_header(name, params, nt, true);
	func->symtype = make_shared<SymbolTypeFunc>();
	dynamic_pointer_cast<SymbolTypeFunc>(func->symtype)->func->type = nt->symtype;
	for (PNodeFormalParameterSection psection: params) {
		for (PNodeVariable var: psection->identifiers) {
			dynamic_pointer_cast<SymbolTypeFunc>(func->symtype)->func->is_nth_var.push_back(psection->is_var);
			dynamic_pointer_cast<SymbolTypeFunc>(func->symtype)->func->params << var->symbol;
			dynamic_pointer_cast<SymbolTypeFunc>(func->symtype)->func->locals << var->symbol;
		}
	}
	return func;
}

PNodeType Parser::parse_type() {
	PNodeType node = make_shared<NodeType>();
	if (scanner == Token::R_ARRAY) {
		return parse_type_array();
	} else if (scanner == Token::R_RECORD) {
		return parse_type_record();
	} else if (scanner == Token::R_PROCEDURE) {
		return parse_type_procedure();
	} else if (scanner == Token::R_FUNCTION) {
		return parse_type_function();
	} else if (scanner == Token::OP_DEREFERENCE) {
		++scanner;
		require({Token::C_IDENTIFIER}, "identifier");
		string name = NodeIdentifier(scanner++).name;
		PSymbolType pointer_type;
		if (!(m_symtables[name] >> pointer_type) && Symbol::use_strict) {
			throw SymbolNotFound(scanner.current_position(), name);
		}
		node->symtype = make_shared<SymbolTypePointer>(name, pointer_type);
	} else {
		require({Token::C_IDENTIFIER}, "identifier");
		string name = NodeIdentifier(scanner++).name;
		if (!(m_symtables[name] >> node->symtype) && Symbol::use_strict) {
			throw SymbolNotFound(scanner.current_position(), name);
		}
	}
	return node;
}

PNodeStmtBlock Parser::parse_block() {
	PNodeStmtBlock node = make_shared<NodeStmtBlock>();
	while (++scanner != Token::R_END) {
		node->stmts.push_back(parse_stmt());
		if (scanner == Token::R_END) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
	}
	require({Token::R_END}, "keyword END");
	++scanner;
	return node;
}

PNodeStmtBlock Parser::parse_repeat_block() {
	PNodeStmtBlock node = make_shared<NodeStmtBlock>();
	while (++scanner != Token::R_UNTIL) {
		node->stmts.push_back(parse_stmt());
		if (scanner == Token::R_UNTIL) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
	}
	require({Token::R_UNTIL}, "keyword UNTIL");
	++scanner;
	return node;
}

PNode Parser::parse() {
	m_syntax_tree = Symbol::use_strict ?
	                  dynamic_pointer_cast<Node>(parse_program()) :
	                  parse_expression(2);
	return m_syntax_tree;
}

PNodeActualParameters Parser::parse_actual_parameters() {
	if (scanner == Token::OP_RIGHT_PAREN) {
		return nullptr;
	}
	PNodeExpression first = parse_expression(precedence(Token::OP_EQUAL));
	PNodeActualParameters result = make_shared<NodeActualParameters>(first);
	while (scanner == Token::S_COMMA) {
		++scanner;
		result->arglist.push_back(parse_expression(precedence(Token::OP_EQUAL)));
	}
	return result;
}

PNodeExpression Parser::parse_expression(int prec) {
	PNodeExpression left = prec < PREC_MAX? parse_expression(prec + 1) : parse_factor();
	while (precedence(scanner) >= prec && scanner != Token::C_RESERVED) {
		require({Token::C_OPERATOR, Token::C_EOF}, "operator");
		Token token = scanner++;
		PNodeExpression right;
		switch ((Token::Operator)token) {
		case Token::OP_LEFT_BRACKET: {
			PNodeActualParameters index = parse_actual_parameters();
			require({Token::OP_RIGHT_BRACKET}, "]");
			++scanner;
			left = make_shared<NodeArrayAccess>(left, index);
		} break;
		case Token::OP_DOT: {
			PSymbolTypeRecord rec;
			left->exprtype() >> rec;
			if (!rec) {
				throw ParseError(token, "left operand of '.' must be a record");
			}
			PNodeIdentifier field = parse_identifier();
			PSymbolVariable r;
			(*rec->symtable)[field->name] >> r;
			if (!r) {
				throw ParseError(token, "no such field " + field->name + " of " + rec->str());
			}
			left = make_shared<NodeRecordAccess>(left, r);
		} break;
		case Token::OP_RIGHT_BRACKET: {
			throw ParseError(token, "unexpected ']', need '[' before");
		} break;
		case Token::OP_RIGHT_PAREN: {
			throw ParseError(token, "unexpected ')', need '(' before");
		} break;
		case Token::NOT_OPERATOR: {
			require({Token::C_EOF}, "end of file");
			return left;
		} break;
		case Token::OP_DEREFERENCE: {
			return make_shared<NodeUnaryOperator>(Token::OP_DEREFERENCE, left);
		} break;
		case Token::OP_LEFT_PAREN: {
			PNodeExprStmtFunctionCall f;
			if (dynamic_pointer_cast<SymbolTypeProc>(left->exprtype())) {
				PSymbolTypeProc stp = dynamic_pointer_cast<SymbolTypeProc>(left->exprtype());
				f = make_shared<NodeExprStmtFunctionCall>(stp->proc);
			} else if (dynamic_pointer_cast<SymbolTypeFunc>(left->exprtype())) {
				PSymbolTypeFunc stp = dynamic_pointer_cast<SymbolTypeFunc>(left->exprtype());
				f = make_shared<NodeExprStmtFunctionCall>(stp->func);
			}else if (dynamic_pointer_cast<NodeExprStmtFunctionCall>(left)) {
				f = dynamic_pointer_cast<NodeExprStmtFunctionCall>(left);
			} else {
				throw ParseError(token, "need procedure or function identifier");
			}
			f->args = parse_actual_parameters();
			require({Token::OP_RIGHT_PAREN}, ")");
			f->check_parameters(scanner.current_position());
			++scanner;
			return f;
		} break;
		default: {
			right = parse_expression(prec + 1);
			if (token == Token::OP_ASSIGN || token == Token::OP_MULT_ASSIGN || token == Token::OP_PLUS_ASSIGN || token == Token::OP_MINUS_ASSIGN|| token == Token::OP_DIV_ASSIGN) {
				PNodeVariable var = dynamic_pointer_cast<NodeVariable>(left);
				if (var) {
					if (for_checker[var->identifier->name]) {
						throw ParseError(scanner.top(),
						                 "Illegal assignment to for-loop variable \"" + var->identifier->name + "\"");
					} else {
						for_checker.erase(for_checker.find(var->identifier->name));
					}
				}
			}
			left = make_shared<NodeBinaryOperator>((Token::Operator)token, left, right);
		}
		}
	}
	return left;
}

PNodeIdentifier Parser::parse_identifier() {
	require({Token::C_IDENTIFIER}, "indentifier");
	return make_shared<NodeIdentifier>(scanner++);
}

PNodeExpression Parser::parse_factor() {
	Token token = scanner++;
	switch ((Token::Category)token) {
	case Token::C_IDENTIFIER: {
		NodeIdentifier *node = new NodeIdentifier(token);
		PSymbolVariable s_var;
		m_symtables[node->name] >> s_var;
		if (s_var) {
			return make_shared<NodeVariable>(PNodeIdentifier(node), s_var);
		}
		PSymbolProcedure s_f;
		m_symtables[node->name] >> s_f;
		if (s_f) {
			return make_shared<NodeExprStmtFunctionCall>(s_f);
		}
		return make_shared<NodeIdentifier>(token);
	}
	case Token::C_LITERAL:
		return new_literal_factor(token);
	case Token::C_EOF:
		return make_shared<NodeEof>(token);
	case Token::C_OPERATOR: {
		switch ((Token::Operator)token) {
		case Token::OP_LEFT_PAREN: {
			PNodeExpression node = parse_expression(precedence(Token::OP_EQUAL));
			require({Token::OP_RIGHT_PAREN}, ")");
			++scanner;
			return node;
		} break;
		case Token::OP_MINUS:
		case Token::OP_NOT:
		case Token::OP_AT: {
			PNodeExpression node = parse_expression(precedence(Token::OP_DEREFERENCE));
			return make_shared<NodeUnaryOperator>((Token::Operator)token, node);
		} break;
		default: throw ParseError(token, "unexpected operator \"" + token.raw_value + "\"");
		}
	}
	default: throw ParseError(token, "unexpected token \"" + token.raw_value + "\"");
	}
}

string Parser::get_line(int id) {
	return scanner.get_line(id);
}

Parser& Parser::set_strictness(const bool strict) {
	Symbol::use_strict = strict;
	return *this;
}

ostream& Parser::output_symbols(ostream& os) {
	for (PSymTable pst: m_symtables) {
		SymTable& st = *pst;
		for (PSymbol p: st) {
			os << p->output_str() << endl;
		}
	}
	return os;
}

ostream& Parser::output_syntax_tree(ostream& os) {
	if (m_syntax_tree) {
		int node_id = 1;
		output_subtree(m_syntax_tree, 0, node_id, os);
		os << '.' << endl;
	}
	return os;
}

int Parser::output_subtree(string str, int parent, int& id, ostream& os, bool silent) {
	int this_node = silent ? parent : id++;
	if (!silent) {
		if (parent) {
			os << "- " << parent << ' ' << this_node << '\n';
		}
		os << "+ " << this_node << ' ' << str << '\n';
	}
	return this_node;
}

int Parser::output_subtree(PNode node, int parent, int& id, ostream& os, bool silent) {
	if (!node) {
		return id;
	}
	int this_node = silent ? parent : id++;
	if (!silent) {
		if (parent) {
			os << "- " << parent << ' ' << this_node << '\n';
		}
		os << "+ " << this_node << ' ' << node->str() << '\n';
	}
	if (dynamic_pointer_cast<NodeVariable>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeVariable>(node)->symbol.get() << '\n';
	} else if (dynamic_pointer_cast<NodeBinaryOperator>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeBinaryOperator>(node)->exprtype().get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeBinaryOperator>(node)->left, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeBinaryOperator>(node)->right, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeUnaryOperator>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeUnaryOperator>(node)->exprtype().get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeUnaryOperator>(node)->node, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeActualParameters>(node)) {
		for (PNodeExpression child: dynamic_pointer_cast<NodeActualParameters>(node)->arglist) {
			output_subtree(child, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeArrayAccess>(node)) {
		output_subtree(dynamic_pointer_cast<NodeArrayAccess>(node)->array, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeArrayAccess>(node)->index, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)->proc.get() << '\n';
		int fid = output_subtree(dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)->proc->name, this_node, id, os);
		os << "> " << fid << ' ' << (uint64_t)dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)->proc.get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)->args,this_node, id, os);
	} else if (dynamic_pointer_cast<NodeRecordAccess>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeRecordAccess>(node)->field->type.get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeRecordAccess>(node)->record, this_node, id, os);
		int rf = output_subtree(dynamic_pointer_cast<NodeRecordAccess>(node)->field->name, this_node, id, os);
		os << "> " << rf << ' ' << (uint64_t)dynamic_pointer_cast<NodeRecordAccess>(node)->field.get() << '\n';
	} else if (dynamic_pointer_cast<NodeStmtBlock>(node)) {
		for (PNodeStmt stmt: dynamic_pointer_cast<NodeStmtBlock>(node)->stmts) {
			output_subtree(stmt, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeProgram>(node)) {
		for (PNodeStmt part: dynamic_pointer_cast<NodeProgram>(node)->parts) {
			output_subtree(part, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeStmtIf>(node)) {
		output_subtree(dynamic_pointer_cast<NodeStmtIf>(node)->cond, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeStmtIf>(node)->then_stmt, this_node, id, os);
		if (dynamic_pointer_cast<NodeStmtIf>(node)->else_stmt) {
			output_subtree(dynamic_pointer_cast<NodeStmtIf>(node)->else_stmt, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeStmtWhile>(node)) {
		output_subtree(dynamic_pointer_cast<NodeStmtWhile>(node)->cond, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeStmtWhile>(node)->stmt, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeStmtRepeat>(node)) {
		output_subtree(dynamic_pointer_cast<NodeStmtRepeat>(node)->stmt, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeStmtRepeat>(node)->cond, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeStmtFor>(node)) {
		int iter_var = output_subtree(dynamic_pointer_cast<NodeStmtFor>(node)->iter_var, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeStmtFor>(node)->low, iter_var, id, os);
		output_subtree(dynamic_pointer_cast<NodeStmtFor>(node)->high, iter_var, id, os);
		output_subtree(dynamic_pointer_cast<NodeStmtFor>(node)->stmt, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeStmtProcedure>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeStmtProcedure>(node)->symbol.get() << '\n';
		if (dynamic_pointer_cast<NodeStmtFunction>(node)) {
			output_subtree(dynamic_pointer_cast<NodeStmtFunction>(node)->result_type, this_node, id, os);
		}
		for (PNodeFormalParameterSection param: dynamic_pointer_cast<NodeStmtProcedure>(node)->params) {
			output_subtree(param, this_node, id, os);
		}
		for (PNodeStmt part: dynamic_pointer_cast<NodeStmtProcedure>(node)->parts) {
			output_subtree(part, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeFormalParameterSection>(node)) {
		for (PNodeVariable param: dynamic_pointer_cast<NodeFormalParameterSection>(node)->identifiers) {
			output_subtree(param, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeTypeRecord>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeTypeRecord>(node)->symtype.get() << '\n';
		for (PNodeVarDeclarationUnit f: dynamic_pointer_cast<NodeTypeRecord>(node)->units) {
			output_subtree(f, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeStmtVar>(node)) {
		for (PNodeVarDeclarationUnit vu: dynamic_pointer_cast<NodeStmtVar>(node)->units) {
			output_subtree(vu, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeVarDeclarationUnit>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeVarDeclarationUnit>(node)->nodetype->symtype.get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeVarDeclarationUnit>(node)->nodetype, this_node, id, os, true);
		for (PNodeVariable v: dynamic_pointer_cast<NodeVarDeclarationUnit>(node)->vars) {
			int par = output_subtree(v, this_node, id, os);
			if (dynamic_pointer_cast<NodeVarDeclarationUnit>(node)->initializer) {
				output_subtree(dynamic_pointer_cast<NodeVarDeclarationUnit>(node)->initializer->expr, par, id, os);
			}
		}
	} else if (dynamic_pointer_cast<NodeStmtType>(node)) {
		for (PNodeTypeDeclarationUnit tdu: dynamic_pointer_cast<NodeStmtType>(node)->units) {
			output_subtree(tdu, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeTypeDeclarationUnit>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeTypeDeclarationUnit>(node)->alias.get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeTypeDeclarationUnit>(node)->nodetype, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeTypeArray>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeTypeArray>(node)->symtype.get() << '\n';
		output_subtree(dynamic_pointer_cast<NodeTypeArray>(node)->type, this_node, id, os);
	}
	else if (dynamic_pointer_cast<NodeType>(node)) {
		os << "> " << this_node << ' ' << (uint64_t)dynamic_pointer_cast<NodeType>(node)->symtype.get() << '\n';
	}
	return this_node;
}

PNodeExpression Parser::new_literal_factor(const Token& token) {
	switch (token.subcategory) {
	case Token::L_FLOAT:
		return make_shared<NodeFloat>(token);
	case Token::L_INTEGER:
		return make_shared<NodeInteger>(token);
	case Token::L_STRING:
		return make_shared<NodeString>(token);
	default:
		throw runtime_error("Internal error: unknown literal type");
	}
}

void Parser::require(const initializer_list<Token::Operator>& ops, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(ops)) {
		throw ParseError(pos, "\"" + expected + "\" expected, but \"" + found + "\" found");
	}
}

void Parser::require(const initializer_list<Token::Operator>& ops, const string& expected) {
	require(ops, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(const initializer_list<Token::Category>& cats, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(cats)) {
		throw ParseError(pos, "\"" + expected + "\" expected, but \"" + found + "\" found");
	}
}

void Parser::require(const initializer_list<Token::Category>& cats, const string& expected) {
	require(cats, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(const initializer_list<Token::Reserved>& rs, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(rs)) {
		throw ParseError(pos, "\"" + expected + "\" expected, but \"" + found + "\" found");
	}
}

void Parser::require(const initializer_list<Token::Reserved>& rs, const string& expected) {
	require(rs, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(const initializer_list<Token::Separator>& seps, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(seps)) {
		throw ParseError(pos, "\"" + expected + "\" expected, but \"" + found + "\" found");
	}
}

void Parser::require(const initializer_list<Token::Separator>& seps, const string& expected) {
	require(seps, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(const initializer_list<Token::Literal>& lits, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(lits)) {
		throw ParseError(pos, "\"" + expected + "\" expected, but \"" + found + "\" found");
	}
}

void Parser::require(const initializer_list<Token::Literal>& lits, const string& expected) {
	require(lits, scanner.top().position, expected, scanner.top().strvalue());
}

PNode Parser::tree() {
	return m_syntax_tree;
}
