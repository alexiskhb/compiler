#include "parser.h"

using namespace std;

int precedence_lst[Token::SIZEOF_OPERATORS];

const int MAX_PREC = 7;
bool init_precedence() {
    fill(precedence_lst, precedence_lst + Token::SIZEOF_OPERATORS, 0);

    precedence_lst[Token::OP_DOT] = 7;

    precedence_lst[Token::OP_CARET] = 6;
    precedence_lst[Token::OP_LSQBRAC] = 6;

    precedence_lst[Token::OP_AT] = 5;
    precedence_lst[Token::OP_NOT] = 5;

    precedence_lst[Token::OP_AND] = 4;
    precedence_lst[Token::OP_ASTER] = 4;
    precedence_lst[Token::OP_SLASH] = 4;
    precedence_lst[Token::OP_DIV] = 4;
    precedence_lst[Token::OP_MOD] = 4;
    precedence_lst[Token::OP_SHL] = 4;
    precedence_lst[Token::OP_SHR] = 4;
    
    precedence_lst[Token::OP_PLUS] = 3;
    precedence_lst[Token::OP_MINUS] = 3;
    precedence_lst[Token::OP_OR] = 3;
    precedence_lst[Token::OP_XOR] = 3;
    
    precedence_lst[Token::OP_IN] = 2;
    precedence_lst[Token::OP_LEQ] = 2;
    precedence_lst[Token::OP_GEQ] = 2;
    precedence_lst[Token::OP_NEQ] = 2;
    precedence_lst[Token::OP_EQUAL] = 2;
    precedence_lst[Token::OP_GTHAN] = 2;
    precedence_lst[Token::OP_LTHAN] = 2;
    
    precedence_lst[Token::OP_ASSIGN] = 1;
    precedence_lst[Token::OP_PLUSAGN] = 1;
    precedence_lst[Token::OP_MINUSAGN] = 1;
    precedence_lst[Token::OP_FACAGN] = 1;
    precedence_lst[Token::OP_MULAGN] = 1;

    precedence_lst[Token::NOT_OPERATOR] = 0;
    return true;
}

int precedence(Token::Operator op) {
    static bool init = init_precedence();
    return precedence_lst[op];
}

int precedence(const Token& token) {
    return precedence((Token::Operator)token);
}

Parser::Parser(const string& filename) {
    scanner.open(filename);
}

bool Parser::is_open() const {
    return scanner.is_open();
}

NodePtr Parser::parse() {
    return syntax_tree = parse_statements();
}

NodePtr Parser::parse_statements() {
    NodePtr left = parse_comma_separated();
    if (scanner == Token::S_SCOLON) {
        Token token = scanner++;
        NodePtr right = parse_statements();
        left = new_node((Token::Separator)token, left, right);
    }
    return left;
}


NodePtr Parser::parse_comma_separated() {
    NodePtr left = parse_expression();
    if (scanner == Token::S_COMMA) {
        Token token = scanner++;
        NodePtr right = parse_comma_separated();
        left = new_node((Token::Separator)token, left, right);
    }
    return left;
}

NodePtr Parser::parse_recursive(int prec) {
    NodePtr left = prec ? parse_recursive(prec - 1) : parse_factor();
    if (precedence(scanner) == prec) {
        Token token = scanner++;
        NodePtr right = parse_recursive(prec);
        switch (token.category) {
        case Token::C_OPERATOR: left = new_node((Token::Operator)token, left, right);
        case Token::C_SEPARATOR: left = new_node((Token::Separator)token, left, right);
        default: throw runtime_error("unexpected token");
        }
    }
    return left;
}

NodePtr Parser::parse_expression() {
    NodePtr left = parse_term();
    if (precedence(scanner) == precedence(Token::OP_OR)) {
        Token token = scanner++;
        NodePtr right = parse_expression();
//        ++scanner;
        left = new_node((Token::Operator)token, left, right);
    }
    return left;
}

NodePtr Parser::parse_term() {
    NodePtr left = parse_factor();
    if (precedence(scanner) == precedence(Token::OP_AND)) {
        Token token = scanner++;
        NodePtr right = parse_term();
        left = new_node((Token::Operator)token, left, right);
    }
    return left;
}

//NodePtr Parser::parse_left_unary() {
//    NodePtr left = parse_factor();
//    if (precedence(scanner) == precedence(Token::OP_NOT)) {
//        Token token = scanner++;
//        left = new_node((Token::Operator)token, left);
//    }
//    return left;
//}

NodePtr Parser::parse_identifier() {
    NodePtr left = make_shared<IdentifierNode>(stored_token);
    if (scanner == Token::OP_DOT) {
        Token token = scanner++;
        scanner.require({Token::C_IDENTIFIER});
        NodePtr right = parse_factor();
        left = new_node((Token::Operator)token, left, right);
    }
    /*
    case Token::OP_CARET: {
        Token token = scanner++;
        stored_token = Token();
        left = new_node((Token::Operator)token, left);
        NodePtr node = parse_identifier();
        if (!node->empty()) {
            node->left = left;
            left = node;
        }
    } break;
    case Token::OP_LSQBRAC: {
        Token token = scanner++;
        NodePtr right = parse_comma_separated();
        scanner.require({Token::OP_RSQBRAC});
        ++scanner;
        left = new_node((Token::Operator)token, left, right);
    } break;
    default:;
    }
    */
    return left;
}

NodePtr Parser::parse_factor() {
    Token token = scanner++;
    stored_token = token;
//    cerr << token << endl;
    switch ((Token::Category)token) {
    case Token::C_IDENTIFIER:
        return parse_identifier();
//        return make_shared<IdentifierNode>(token);
    case Token::C_LITERAL:
        return new_literal_factor(token);
    case Token::C_EOF:
        return make_shared<EofNode>(token);
    case Token::C_OPERATOR: {
        switch ((Token::Operator)token) {
        case Token::OP_LPAREN: {
            NodePtr node = parse_expression();
            scanner.require({Token::OP_RPAREN});
            ++scanner;
            return node;
        } break;
        case Token::OP_MINUS: {
            NodePtr node = parse_factor();
            return new_node(Token::OP_MINUS, node);
        } break;
        case Token::OP_NOT: {
            NodePtr node = parse_factor();
            return new_node(Token::OP_NOT, node);
        } break;
        default: throw runtime_error("illegal factor operator");
        }
    }
    default: throw runtime_error("illegal factor category");
    }
    return nullptr;
}

ostream& Parser::output_syntax_tree(ostream& os) {
    int node_id = 1;
    walk_tree(syntax_tree, node_id, os);
    os << '.' << endl;
    return os;
}

void Parser::walk_tree(NodePtr node, int& id, ostream& os) {
    int this_node = id;
    os << "+ " << this_node << ' ' << node->str() << '\n';
    if (node->left) {
        os << "- " << this_node << ' ' << ++id << '\n';
        walk_tree(node->left, id, os);
    }
    if (node->right) {
        os << "- " << this_node << ' ' << ++id << '\n';
        walk_tree(node->right, id, os);
    }
}

NodePtr Parser::new_literal_factor(const Token& token) {
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

NodePtr Parser::new_node(Token::Separator separator, NodePtr left, NodePtr right) {
    return make_shared<SeparatedPair>(separator, left, right);
}

NodePtr Parser::new_node(Token::Operator operation, NodePtr node) {
    return make_shared<UnaryOperator>(operation, node);
}

NodePtr Parser::new_node(Token::Operator operation, NodePtr left, NodePtr right) {
    return make_shared<BinaryOperator>(operation, left, right);
}






