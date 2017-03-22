#include "parser.h"

using namespace std;

int precedence_lst[Token::SIZEOF_OPERATORS];
int precedence_sep_lst[Token::SIZEOF_SEPARATORS];

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
    precedence_sep_lst[Token::S_SCOLON] = 1;

    PREC_MAX = 0;
    for(auto t: precedence_lst) {
        PREC_MAX = max(PREC_MAX, t);
    }
    for(auto t: precedence_sep_lst) {
        PREC_MAX = max(PREC_MAX, t);
    }
    return true;
}

int precedence(const Token& token) {
    switch (token.category) {
    case Token::C_OPERATOR: return precedence_lst[token.subcategory];
    case Token::C_SEPARATOR: return precedence_sep_lst[token.subcategory];
    default: return 0;
    }
}

int precedence(Token::Separator sep) {
    return precedence_sep_lst[sep];
}

int precedence(Token::Operator op) {
    return precedence_lst[op];
}

Parser::Parser(const string& filename) {
    static bool init = init_precedence();
    scanner.open(filename);
}

bool Parser::is_open() const {
    return scanner.is_open();
}

NodePtr Parser::parse_program() {

}

NodePtr Parser::parse_simple_expressions() {
    return syntax_tree = parse_expression(1);
}

void Parser::require(initializer_list<Token::Operator> ops, Pos pos, const string& expected, const string& found) {
    if (!scanner.require(ops)) {
        throw ParseError(pos, expected + " expected, but \"" + found + "\" found");
    }
}

void Parser::require(initializer_list<Token::Category> cats, Pos pos, const string& expected, const string& found) {
    if (!scanner.require(cats)) {
        throw ParseError(pos, expected + " expected, but \"" + found + "\" found");
    }
}

CommaSeparatedArgsNodePtr Parser::parse_args() {
    ExpressionNodePtr first = parse_expression(precedence(Token::OP_EQUAL));
    CommaSeparatedArgsNodePtr result = make_shared<CommaSeparatedArgsNode>(first);
    while(scanner == Token::S_COMMA) {
        ++scanner;
        result->args.push_back(parse_expression(precedence(Token::OP_EQUAL)));
    }
    return result;
}

ExpressionNodePtr Parser::parse_expression(int prec) {
    ExpressionNodePtr left = prec < PREC_MAX? parse_expression(prec + 1) : parse_factor();
    while (precedence(scanner) >= prec) {
        Token token = scanner++;
        ExpressionNodePtr right;
        if (token != Token::C_OPERATOR) {
            throw ParseError(token, "parse_recursive: unexpected token");
        }
        switch ((Token::Operator)token) {
        case Token::OP_LEFT_BRACKET: {
            CommaSeparatedArgsNodePtr index = parse_args();
            require({Token::OP_RIGHT_BRACKET}, token, "\"]\"", scanner.top().strvalue());
            ++scanner;
//            check<IdentifierNode>(left.get(), token, "need array identifier to access");
            left = make_shared<ArrayAccessNode>(left, index);
        } break;
        case Token::OP_DOT: {
            require({Token::C_IDENTIFIER}, token, "indentifier", scanner.top().strvalue());
            right = parse_factor();
            left = make_shared<RecordAccessNode>(left, dynamic_pointer_cast<IdentifierNode>(right));
        } break;
        case Token::OP_RIGHT_BRACKET: {
            throw ParseError(token, "unexpected ']', need '[' before");
        } break;
        case Token::OP_RIGHT_PAREN: {
            throw ParseError(token, "unexpected ')', need '(' before");
        } break;
        case Token::OP_DEREFERENCE: {
            return make_shared<UnaryOperatorNode>(Token::OP_DEREFERENCE, left);
        } break;
        case Token::OP_LEFT_PAREN: {
            CommaSeparatedArgsNodePtr args = parse_args();
            require({Token::OP_RIGHT_PAREN}, token, "\")\"", scanner.top().strvalue());
            check<IdentifierNode>(left.get(), token, "need identifier to function call from");
            ++scanner;
            return make_shared<FunctionCallNode>(dynamic_pointer_cast<IdentifierNode>(left), args);
        } break;
        default: {
            right = parse_expression(prec + 1);
            left = make_shared<BinaryOperatorNode>((Token::Operator)token, left, right);
        }
        }
    }
    return left;
}

ExpressionNodePtr Parser::parse_factor() {
    Token token = scanner++;
    switch ((Token::Category)token) {
    case Token::C_IDENTIFIER:
        return make_shared<IdentifierNode>(token);
    case Token::C_LITERAL:
        return new_literal_factor(token);
    case Token::C_EOF:
        return make_shared<EofNode>(token);
    case Token::C_OPERATOR: {
        switch ((Token::Operator)token) {
        case Token::OP_LEFT_PAREN: {
            ExpressionNodePtr node = parse_expression(precedence(Token::OP_EQUAL));
            require({Token::OP_RIGHT_PAREN}, token, "\")\"", scanner.top().strvalue());
            ++scanner;
            return node;
        } break;
        case Token::OP_MINUS:
        case Token::OP_NOT:
        case Token::OP_AT: {
            ExpressionNodePtr node = parse_expression(precedence(Token::OP_DEREFERENCE));
            return make_shared<UnaryOperatorNode>((Token::Operator)token, node);
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

ostream& Parser::output_syntax_tree(ostream& os) {
    if (syntax_tree) {
        int node_id = 1;
        output_subtree(syntax_tree, node_id, os);
        os << '.' << endl;
    }
    return os;
}

void Parser::output_subtree(NodePtr node, int& id, ostream& os) {
    int this_node = id;
    os << "+ " << this_node << ' ' << node->str() << '\n';
    if (dynamic_pointer_cast<BinaryOperatorNode>(node)) {
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<BinaryOperatorNode>(node)->left, id, os);
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<BinaryOperatorNode>(node)->right, id, os);
    } else if (dynamic_pointer_cast<UnaryOperatorNode>(node)) {
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<UnaryOperatorNode>(node)->node, id, os);
    } else if (dynamic_pointer_cast<CommaSeparatedArgsNode>(node)) {
        for(auto child: dynamic_pointer_cast<CommaSeparatedArgsNode>(node)->args) {
            os << "- " << this_node << ' ' << ++id << '\n';
            output_subtree(child, id, os);
        }
    } else if (dynamic_pointer_cast<CommaSeparatedIdentifiersNode>(node)) {
        for(auto child: dynamic_pointer_cast<CommaSeparatedIdentifiersNode>(node)->args) {
            os << "- " << this_node << ' ' << ++id << '\n';
            output_subtree(child, id, os);
        }
    } else if (dynamic_pointer_cast<ArrayAccessNode>(node)) {
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<ArrayAccessNode>(node)->array, id, os);
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<ArrayAccessNode>(node)->index, id, os);
    } else if (dynamic_pointer_cast<FunctionCallNode>(node)) {
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<FunctionCallNode>(node)->function_identifier, id, os);
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<FunctionCallNode>(node)->args, id, os);
    } else if (dynamic_pointer_cast<RecordAccessNode>(node)) {
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<RecordAccessNode>(node)->record, id, os);
        os << "- " << this_node << ' ' << ++id << '\n';
        output_subtree(dynamic_pointer_cast<RecordAccessNode>(node)->field, id, os);
    }
}

ExpressionNodePtr Parser::new_literal_factor(const Token& token) {
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
