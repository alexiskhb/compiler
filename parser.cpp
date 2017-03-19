#include "parser.h"

using namespace std;

int precedence_lst[Token::SIZEOF_OPERATORS];
int precedence_sep_lst[Token::SIZEOF_SEPARATORS];

const int PREC_MAX = 9;
bool init_precedence() {
    fill(precedence_lst, precedence_lst + Token::SIZEOF_OPERATORS, 0);
    fill(precedence_sep_lst, precedence_sep_lst + Token::SIZEOF_SEPARATORS, 0);

    precedence_lst[Token::OP_DOT] = 9;

    precedence_lst[Token::OP_CARET]   = 8;
    precedence_lst[Token::OP_LSQBRAC] = 8;

    precedence_lst[Token::OP_AT]  = 7;
    precedence_lst[Token::OP_NOT] = 7;

    precedence_lst[Token::OP_AND]   = 6;
    precedence_lst[Token::OP_ASTER] = 6;
    precedence_lst[Token::OP_SLASH] = 6;
    precedence_lst[Token::OP_DIV]   = 6;
    precedence_lst[Token::OP_MOD]   = 6;
    precedence_lst[Token::OP_SHL]   = 6;
    precedence_lst[Token::OP_SHR]   = 6;
    
    precedence_lst[Token::OP_PLUS]  = 5;
    precedence_lst[Token::OP_MINUS] = 5;
    precedence_lst[Token::OP_OR]    = 5;
    precedence_lst[Token::OP_XOR]   = 5;
    
    precedence_lst[Token::OP_IN]    = 4;
    precedence_lst[Token::OP_LEQ]   = 4;
    precedence_lst[Token::OP_GEQ]   = 4;
    precedence_lst[Token::OP_NEQ]   = 4;
    precedence_lst[Token::OP_EQUAL] = 4;
    precedence_lst[Token::OP_GTHAN] = 4;
    precedence_lst[Token::OP_LTHAN] = 4;
    
    precedence_lst[Token::OP_ASSIGN]   = 3;
    precedence_lst[Token::OP_PLUSAGN]  = 3;
    precedence_lst[Token::OP_MINUSAGN] = 3;
    precedence_lst[Token::OP_FACAGN]   = 3;
    precedence_lst[Token::OP_MULAGN]   = 3;

    precedence_sep_lst[Token::S_COMMA] = 2;

    precedence_sep_lst[Token::S_SCOLON] = 1;
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

NodePtr Parser::parse() {
    return syntax_tree = parse_recursive(1);
}

NodePtr Parser::parse_recursive(int prec) {
    NodePtr left = prec < PREC_MAX? parse_recursive(prec + 1) : parse_factor();
    if (precedence(scanner) >= prec) {
        Token token = scanner++;
        NodePtr right;
        switch (token.category) {
        case Token::C_OPERATOR: {
            switch (token.subcategory) {
            case Token::OP_LSQBRAC: {
                right = parse_recursive(precedence(Token::S_COMMA));
                scanner.require({Token::OP_RSQBRAC});
                ++scanner;
            } break;
            case Token::OP_DOT: {
                scanner.require({Token::C_IDENTIFIER});
                right = parse_recursive(prec);
            } break;
            case Token::OP_MINUS: {
                right = parse_recursive(prec);
                if (!dynamic_cast<BinaryOperator*>(right.get())) {
                    break;
                }
                if (dynamic_cast<UnaryOperator*>(right.get())) {
                    break;
                }
                Token::Operator op = dynamic_cast<BinaryOperator*>(right.get())->operation;
                if (precedence(op) > precedence(Token::OP_MINUS)) {
                    break;
                }
                NodePtr right_op = right;
                right = right_op->left;
                left = new_node(Token::OP_MINUS, left, right);
                right = right_op->right;
                return new_node(op, left, right);
            } break;
            default: right = parse_recursive(prec);
            }
            left = new_node((Token::Operator)token, left, right);
        } break;
        case Token::C_SEPARATOR: {
            right = parse_recursive(prec);
            left = new_node((Token::Separator)token, left, right);
        } break;
        default: throw ParseError(token, "parse_recursive: unexpected token");
        }
    }
    return left;
}

NodePtr Parser::parse_factor() {
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
        case Token::OP_LPAREN: {
            NodePtr node = parse_recursive(precedence(Token::S_COMMA));
            scanner.require({Token::OP_RPAREN});
            ++scanner;
            return node;
        } break;
        case Token::OP_MINUS:
        case Token::OP_NOT:
        case Token::OP_AT: {
            NodePtr node = parse_factor();
            return new_node((Token::Operator)token, node);
        } break;
        default: throw ParseError(token, "illegal factor operator");
        }
    }
    default: throw ParseError(token, "illegal factor category");
    }
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
        throw ParseError(token, "illegal literal type");
    }
}

NodePtr Parser::new_node(Token::Separator separator, NodePtr left, NodePtr right) {
    return make_shared<SeparatedPair>(separator, left, right);
}

NodePtr Parser::new_node(Token::Operator operation, NodePtr node) {
    return make_shared<UnaryOperator>(operation, node);
}

NodePtr Parser::new_node(Token::Operator operation, NodePtr left, NodePtr right) {
    if (!right) {
        if (!left) {
            throw runtime_error("both operands are null");
        }
        return new_node(operation, left);
    }
    return make_shared<BinaryOperator>(operation, left, right);
}






