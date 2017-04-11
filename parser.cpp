#include "parser.h"

using namespace std;

int precedence_lst[Token::SIZEOF_OPERATORS];
int precedence_sep_lst[Token::SIZEOF_SEPARATORS];

vector<PSymTable> symtables;

int PREC_MAX;
bool init_precedence() {
	fill(precedence_lst, precedence_lst + Token::SIZEOF_OPERATORS, 0);
	fill(precedence_sep_lst, precedence_sep_lst + Token::SIZEOF_SEPARATORS, 0);

	precedence_lst[Token::OP_DOT] = 10;

	precedence_lst[Token::OP_DEREFERENCE]  = 9;
	precedence_lst[Token::OP_LEFT_BRACKET] = 9;
	precedence_lst[Token::OP_LEFT_PAREN] = 9;

	precedence_lst[Token::OP_AT]  = 8;
	precedence_lst[Token::OP_NOT] = 8;

	precedence_lst[Token::OP_AND]       = 7;
	precedence_lst[Token::OP_MULT]      = 7;
	precedence_lst[Token::OP_SLASH_DIV] = 7;
	precedence_lst[Token::OP_DIV]       = 7;
	precedence_lst[Token::OP_MOD]       = 7;
	precedence_lst[Token::OP_SHL]       = 7;
	precedence_lst[Token::OP_SHR]       = 7;
	
	precedence_lst[Token::OP_PLUS]  = 6;
	precedence_lst[Token::OP_MINUS] = 6;
	precedence_lst[Token::OP_OR]    = 6;
	precedence_lst[Token::OP_XOR]   = 6;
	
	precedence_lst[Token::OP_IN]      = 5;
	precedence_lst[Token::OP_LEQ]     = 5;
	precedence_lst[Token::OP_GEQ]     = 5;
	precedence_lst[Token::OP_NEQ]     = 5;
	precedence_lst[Token::OP_EQUAL]   = 5;
	precedence_lst[Token::OP_GREATER] = 5;
	precedence_lst[Token::OP_LESS]    = 5;
	
	precedence_lst[Token::OP_ASSIGN]       = 4;
	precedence_lst[Token::OP_PLUS_ASSIGN]  = 4;
	precedence_lst[Token::OP_MINUS_ASSIGN] = 4;
	precedence_lst[Token::OP_DIV_ASSIGN]   = 4;
	precedence_lst[Token::OP_MULT_ASSIGN]  = 4;

	precedence_sep_lst[Token::S_COMMA] = 3;

	precedence_sep_lst[Token::S_COLON] = 2;

	precedence_lst[Token::OP_RIGHT_BRACKET] = 2;
	precedence_lst[Token::OP_RIGHT_PAREN] = 2;


	precedence_sep_lst[Token::S_SEMICOLON] = 1;

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

Parser::Parser(const string& filename, const bool strict) {
	static bool init = init_precedence();
	scanner.open(filename);
	set_strictness(strict);
}

bool Parser::is_open() const {
	return scanner.is_open();
}

PNodeProgram Parser::parse_program() {
	NodeProgram* program = new NodeProgram;
	while (scanner == Token::C_RESERVED) {
		Token token = scanner;
		switch((Token::Reserved)token) {
		case Token::R_CONST: {
			program->parts.push_back(parse_const());
		} break;
		case Token::R_VAR: {
			program->parts.push_back(parse_var());
//            symtables[1]->add(dynamic_pointer_cast<NodeStmtVar>(program->parts.back()));
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
		default: throw ParseError(token, "unexpected \"" + token.raw_value + "\"");
		}
		require({Token::S_SEMICOLON}, ";");
		++scanner;
	}
	if (require_main_block) {
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
	case Token::R_FOR: return parse_for ();
	case Token::R_BEGIN: return parse_block();
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
				PNodeBinaryOperator div_res = make_shared<NodeBinaryOperator>(Token::OP_SLASH_DIV, op->left, op->right);
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

PNodeStmtIf Parser::parse_if () {
	NodeStmtIf* node = new NodeStmtIf;
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
	return PNodeStmtIf(node);
}

PNodeStmtWhile Parser::parse_while () {
	NodeStmtWhile* node = new NodeStmtWhile;
	++scanner;
	node->cond = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_DO}, "keyword DO");
	++scanner;
	node->stmt = parse_stmt();
	return PNodeStmtWhile(node);
}

PNodeStmtRepeat Parser::parse_repeat() {
	NodeStmtRepeat* node = new NodeStmtRepeat;
	++scanner;
	node->stmt = parse_stmt();
	require({Token::R_UNTIL}, "keyword UNTIL");
	++scanner;
	node->cond = parse_expression(precedence(Token::OP_EQUAL));
	return PNodeStmtRepeat(node);
}

PNodeStmtConst Parser::parse_const() {
	//!TODO
	NodeStmtConst* node = new NodeStmtConst;
	++scanner;
	return PNodeStmtConst(node);
}

PNodeStmtVar Parser::parse_var() {
	//!TODO
	NodeStmtVar* node = new NodeStmtVar;
	++scanner;
	while (scanner == Token::C_IDENTIFIER) {
		node->var_units.push_back(parse_var_declaration_unit(Initializer::on));
		if (scanner == Token::C_RESERVED) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
	}
	for (PNodeVarDeclarationUnit& vunit: node->var_units) {
		for (PNodeIdentifier& var: vunit->vars) {
			symtables.back()->add(var);
		}
	}
	return PNodeStmtVar(node);
}

PNodeStmtFor Parser::parse_for () {
	NodeStmtFor* node = new NodeStmtFor;
	++scanner;
	require({Token::C_IDENTIFIER}, "identifier");
	node->iter_var = make_shared<NodeIdentifier>(scanner++);
	require({Token::OP_ASSIGN}, ":=");
	++scanner;
	node->low = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_TO, Token::R_DOWNTO}, "keyword TO or DOWNTO");
	node->is_inc = scanner++ == Token::R_TO;
	node->high = parse_expression(precedence(Token::OP_EQUAL));
	require({Token::R_DO}, "keyword DO");
	++scanner;
	node->stmt = parse_stmt();
	return PNodeStmtFor(node);
}

PNodeFormalParameterSection Parser::parse_formal_parameter_section() {
	NodeFormalParameterSection* node = new NodeFormalParameterSection;
	if (scanner == Token::R_VAR) {
		node->is_var = true;
		++scanner;
	}
	while (scanner == Token::C_IDENTIFIER && scanner != Token::S_COLON) {
		node->identifiers.push_back(make_shared<NodeIdentifier>(scanner++));
		if (scanner == Token::S_COLON) {
			break;
		}
		require({Token::S_COMMA}, ",");
		++scanner;
	}
	require({Token::S_COLON}, ":");
	++scanner;
	require({Token::C_IDENTIFIER}, "type identifier");
	node->type = make_shared<NodeIdentifier>(scanner++);
	return PNodeFormalParameterSection(node);
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
		default: throw ParseError(scanner.top(), "unexpected token \"" + scanner.top().raw_value + "\"");
		}
	}
	require({Token::R_BEGIN}, "keyword BEGIN");
	return body;
}

PNodeStmtType Parser::parse_type_part() {
	//!TODO
	NodeStmtType* node = new NodeStmtType;
}

PNodeStmtProcedure Parser::parse_procedure() {
	NodeStmtProcedure* node = new NodeStmtProcedure;
	++scanner;
	require({Token::C_IDENTIFIER}, "procedure identifier");
	node->name = make_shared<NodeIdentifier>(scanner++);
	if (scanner == Token::OP_LEFT_PAREN) {
		node->params = parse_formal_parameters();
	}
	require({Token::S_SEMICOLON}, ";");
	++scanner;
	node->parts = parse_procedure_body();
	return PNodeStmtProcedure(node);
}

PNodeStmtFunction Parser::parse_function() {
	NodeStmtFunction* node = new NodeStmtFunction;
	++scanner;
	require({Token::C_IDENTIFIER}, "function identifier");
	node->name = make_shared<NodeIdentifier>(scanner++);
	if (scanner == Token::OP_LEFT_PAREN) {
		node->params = parse_formal_parameters();
	}
	require({Token::S_COLON}, ":");
	++scanner;
	require({Token::C_IDENTIFIER}, "simple function type");
	node->result_type = make_shared<NodeIdentifier>(scanner++);
	require({Token::S_SEMICOLON}, ";");
	++scanner;
	node->parts = parse_procedure_body();
	return PNodeStmtFunction(node);
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
	NodeInitializer* node = new NodeInitializer;
	//!TODO
	return PNodeInitializer(node);
}

PNodeVarDeclarationUnit Parser::parse_var_declaration_unit(bool with_initialization) {
	NodeVarDeclarationUnit* node = new NodeVarDeclarationUnit;
	node->vars = parse_comma_separated_identifiers();
	require({Token::S_COLON}, ":");
	++scanner;
	node->type = parse_type();
	node->initializer = nullptr;
	if (with_initialization) {
		if (scanner == Token::OP_EQUAL) {
			++scanner;
			node->initializer = parse_initializer();
		}
	} else {
		if (scanner == Token::OP_EQUAL) {
			// throw
		}
	}
	return PNodeVarDeclarationUnit(node);
}

PNodeStmtRecord Parser::parse_record() {
	NodeStmtRecord* node = new NodeStmtRecord;
	++scanner;
///TODO
	return PNodeStmtRecord(node);
}

PNodeType Parser::parse_type() {
///TODO
	NodeType* node = new NodeType;
	if (scanner == Token::R_ARRAY) {

	} else if (scanner == Token::R_RECORD) {

	} else if (scanner == Token::OP_DEREFERENCE) {

	}
	return PNodeType(node);
}

PNodeStmtBlock Parser::parse_block() {
	NodeStmtBlock* node = new NodeStmtBlock;
	while (++scanner != Token::R_END) {
		node->stmts.push_back(parse_stmt());
		if (scanner == Token::R_END) {
			break;
		}
		require({Token::S_SEMICOLON}, ";");
	}
	require({Token::R_END}, "keyword END");
	++scanner;
	return PNodeStmtBlock(node);
}

PNode Parser::parse() {
	syntax_tree = require_main_block ?
				dynamic_pointer_cast<Node>(parse_program()) :
				parse_expression(1);
	return syntax_tree;
}

PNodeActualParameters Parser::parse_actual_parameters() {
	PNodeExpression first = parse_expression(precedence(Token::OP_EQUAL));
	PNodeActualParameters result = make_shared<NodeActualParameters>(first);
	while (scanner == Token::S_COMMA) {
		++scanner;
		result->args.push_back(parse_expression(precedence(Token::OP_EQUAL)));
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
			require({Token::OP_RIGHT_BRACKET}, token, "\"]\"", scanner.top().strvalue());
			++scanner;
			// check<IdentifierNode>(left.get(), token, "need array identifier to access");
			left = make_shared<NodeArrayAccess>(left, index);
		} break;
		case Token::OP_DOT: {
			require({Token::C_IDENTIFIER}, token, "indentifier", scanner.top().strvalue());
			right = parse_factor();
			left = make_shared<NodeRecordAccess>(left, dynamic_pointer_cast<NodeIdentifier>(right));
		} break;
		case Token::OP_RIGHT_BRACKET: {
			throw ParseError(token, "unexpected ']', need '[' before");
		} break;
		case Token::OP_RIGHT_PAREN: {
			throw ParseError(token, "unexpected ')', need '(' before");
		} break;
		case Token::NOT_OPERATOR: {
			if (token != Token::C_EOF) {
				throw ParseError(token, "unexpected token");
			} else {
				return left;
			}
		} break;
		case Token::OP_DEREFERENCE: {
			return make_shared<NodeUnaryOperator>(Token::OP_DEREFERENCE, left);
		} break;
		case Token::OP_LEFT_PAREN: {
			PNodeActualParameters args = parse_actual_parameters();
			require({Token::OP_RIGHT_PAREN}, token, "\")\"", scanner.top().strvalue());
			check<NodeIdentifier>(left.get(), token, "need identifier to function call from");
			++scanner;
			return make_shared<NodeExprStmtFunctionCall>(dynamic_pointer_cast<NodeIdentifier>(left), args);
		} break;
		default: {
			right = parse_expression(prec + 1);
			left = make_shared<NodeBinaryOperator>((Token::Operator)token, left, right);
		}
		}
	}
	return left;
}

PNodeExpression Parser::parse_factor() {
	Token token = scanner++;
	switch ((Token::Category)token) {
	case Token::C_IDENTIFIER:
		return make_shared<NodeIdentifier>(token);
	case Token::C_LITERAL:
		return new_literal_factor(token);
	case Token::C_EOF:
		return make_shared<NodeEof>(token);
	case Token::C_OPERATOR: {
		switch ((Token::Operator)token) {
		case Token::OP_LEFT_PAREN: {
			PNodeExpression node = parse_expression(precedence(Token::OP_EQUAL));
			require({Token::OP_RIGHT_PAREN}, token, "\")\"", scanner.top().strvalue());
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

void Parser::set_strictness(const bool strict) {
	require_main_block = strict;
	require_symbol_declared = strict;
}

ostream& Parser::output_syntax_tree(ostream& os) {
	if (syntax_tree) {
		int node_id = 1;
		output_subtree(syntax_tree, 0, node_id, os);
		os << '.' << endl;
	}
	return os;
}

int Parser::output_subtree(PNode node, int parent, int& id, ostream& os) {
	int this_node = id++;
	if (parent) {
		os << "- " << parent << ' ' << this_node << '\n';
	}
	os << "+ " << this_node << ' ' << node->str() << '\n';
	if (dynamic_pointer_cast<NodeBinaryOperator>(node)) {
		output_subtree(dynamic_pointer_cast<NodeBinaryOperator>(node)->left, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeBinaryOperator>(node)->right, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeUnaryOperator>(node)) {
		output_subtree(dynamic_pointer_cast<NodeUnaryOperator>(node)->node, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeActualParameters>(node)) {
		for (auto child: dynamic_pointer_cast<NodeActualParameters>(node)->args) {
			output_subtree(child, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeArrayAccess>(node)) {
		output_subtree(dynamic_pointer_cast<NodeArrayAccess>(node)->array, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeArrayAccess>(node)->index, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)) {
		output_subtree(dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)->function_identifier, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeExprStmtFunctionCall>(node)->args,this_node,  id, os);
	} else if (dynamic_pointer_cast<NodeRecordAccess>(node)) {
		output_subtree(dynamic_pointer_cast<NodeRecordAccess>(node)->record, this_node, id, os);
		output_subtree(dynamic_pointer_cast<NodeRecordAccess>(node)->field, this_node, id, os);
	} else if (dynamic_pointer_cast<NodeStmtBlock>(node)) {
		for (auto stmt: dynamic_pointer_cast<NodeStmtBlock>(node)->stmts) {
			output_subtree(stmt, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeProgram>(node)) {
		for (auto part: dynamic_pointer_cast<NodeProgram>(node)->parts) {
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
		if (dynamic_pointer_cast<NodeStmtFunction>(node)) {
			output_subtree(dynamic_pointer_cast<NodeStmtFunction>(node)->result_type, this_node, id, os);
		}
		for (auto param: dynamic_pointer_cast<NodeStmtProcedure>(node)->params) {
			output_subtree(param, this_node, id, os);
		}
		for (auto part: dynamic_pointer_cast<NodeStmtProcedure>(node)->parts) {
			output_subtree(part, this_node, id, os);
		}
	} else if (dynamic_pointer_cast<NodeFormalParameterSection>(node)) {
		for (auto param: dynamic_pointer_cast<NodeFormalParameterSection>(node)->identifiers) {
			output_subtree(param, this_node, id, os);
		}
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
		throw runtime_error("illegal literal type");
	}
}

void Parser::require(initializer_list<Token::Operator> ops, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(ops)) {
		throw ParseError(pos, expected + " expected, but \"" + found + "\" found");
	}
}

void Parser::require(initializer_list<Token::Operator> ops, const string& expected) {
	require(ops, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(initializer_list<Token::Category> cats, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(cats)) {
		throw ParseError(pos, expected + " expected, but \"" + found + "\" found");
	}
}

void Parser::require(initializer_list<Token::Category> cats, const string& expected) {
	require(cats, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(initializer_list<Token::Reserved> rs, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(rs)) {
		throw ParseError(pos, expected + " expected, but \"" + found + "\" found");
	}
}

void Parser::require(initializer_list<Token::Reserved> rs, const string& expected) {
	require(rs, scanner.top().position, expected, scanner.top().strvalue());
}

void Parser::require(initializer_list<Token::Separator> seps, Pos pos, const string& expected, const string& found) {
	if (!scanner.require(seps)) {
		throw ParseError(pos, expected + " expected, but \"" + found + "\" found");
	}
}

void Parser::require(initializer_list<Token::Separator> seps, const string& expected) {
	require(seps, scanner.top().position, expected, scanner.top().strvalue());
}
