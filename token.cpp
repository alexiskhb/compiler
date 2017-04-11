#include "token.h"

using namespace std;

vector<int> Token::int_values;
vector<long double> Token::float_values;
vector<std::string> Token::string_values;
std::map<Token::Reserved, std::string> Token::reversed_reserved_lst;
std::map<std::string, Token::Reserved> Token::reserved_lst =
{
{"AND", R_AND},
{"ASM", R_ASM},
{"ARRAY", R_ARRAY},
{"BEGIN", R_BEGIN},
{"CASE", R_CASE},
{"CONST", R_CONST},
{"CONSTRUCTOR", R_CONSTRUCTOR},
{"DESTRUCTOR", R_DESTRUCTOR},
{"DIV", R_DIV},
{"DO", R_DO},
{"DOWNTO", R_DOWNTO},
{"ELSE", R_ELSE},
{"END", R_END},
{"EXPORTS", R_EXPORTS},
{"FILE", R_FILE},
{"FOR", R_FOR},
{"FUNCTION", R_FUNCTION},
{"GOTO", R_GOTO},
{"IF", R_IF},
{"IMPLEMENTATION", R_IMPLEMENTATION},
{"IN", R_IN},
{"INHERITED", R_INHERITED},
{"INLINE", R_INLINE},
{"INTERFACE", R_INTERFACE},
{"LABEL", R_LABEL},
{"LIBRARY", R_LIBRARY},
{"MOD", R_MOD},
{"NIL", R_NIL},
{"NOT", R_NOT},
{"OBJECT", R_OBJECT},
{"OF", R_OF},
{"OR", R_OR},
{"PACKED", R_PACKED},
{"PROCEDURE", R_PROCEDURE},
{"PROGRAM", R_PROGRAM},
{"RECORD", R_RECORD},
{"REPEAT", R_REPEAT},
{"SET", R_SET},
{"SHL", R_SHL},
{"SHR", R_SHR},
{"STRING", R_STRING},
{"THEN", R_THEN},
{"TO", R_TO},
{"TYPE", R_TYPE},
{"UNIT", R_UNIT},
{"UNTIL", R_UNTIL},
{"USES", R_USES},
{"VAR", R_VAR},
{"WHILE", R_WHILE},
{"WITH", R_WITH},
{"XOR", R_XOR}};
std::map<Token::Operator, std::string> Token::operator_lst =
{
{Token::OP_EQUAL, "="},
{Token::OP_GREATER, ">"},
{Token::OP_LESS, "<"},
{Token::OP_PLUS, "+"},
{Token::OP_MINUS, "-"},
{Token::OP_SLASH_DIV, "/"},
{Token::OP_MULT, "*"},
{Token::OP_LEFT_BRACE, "["},
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
{Token::OP_DIRECTIVE, "{$"},
{Token::OP_RIGHT_PAREN, ")"},
{Token::OP_LEFT_BRACKET, "["},
{Token::OP_RIGHT_BRACKET, "]"},
{Token::OP_RIGHT_BRACE, "}"},
{Token::OP_DEREFERENCE, "^"},
{Token::OP_SHL, "SHL"},
{Token::OP_SHR, "SHR"},
{Token::OP_AND, "AND"},
{Token::OP_OR, "OR"},
{Token::OP_NOT, "NOT"},
{Token::OP_XOR, "XOR"},
{Token::OP_IN, "IN"},
{Token::OP_DIV, "DIV"},
{Token::OP_MOD, "MOD"}
};
std::map<Token::Separator, std::string> Token::separator_lst = {
{Token::S_COMMA, ","},
{Token::S_COLON, ":"},
{Token::S_SEMICOLON, ";"}
};
std::map<Token::Reserved, Token::Operator> Token::reserved_operator_lst = {
{Token::R_SHL, Token::OP_SHL},
{Token::R_SHR, Token::OP_SHR},
{Token::R_AND, Token::OP_AND},
{Token::R_OR,  Token::OP_OR},
{Token::R_NOT, Token::OP_NOT},
{Token::R_XOR, Token::OP_XOR},
{Token::R_IN,  Token::OP_IN},
{Token::R_DIV, Token::OP_DIV},
{Token::R_MOD, Token::OP_MOD}
};

Token::Token() {
    position = {0, 0, 0};
    raw_value = "";
}

Token::Token(Pos _position, Category _category, const std::string& _raw_value, int _subcategory) {
    position = _position;
    category = _category;
    raw_value = _raw_value;
    subcategory = _subcategory;
}

void Token::clear() {
    raw_value.clear();
    position = {0, 0, 0};
    subcategory = 0;
}

int Token::eval_int_literal(string s) {
    switch(s[0]){
    case '$':
        s[0] = '0';
        return stoi(s, 0, 16);
    case '%':
        s[0] = '0';
        return stoi(s, 0, 2);
    default: return stoi(s);
    }
}

string Token::eval_str_literal(const string& s) {
    vector<string> parts = {""};
    for(char c: s) {
        if (c == ETX) {
            parts.push_back("");
            continue;
        }
        parts.back().push_back(c);
    }
    for(size_t i = 0; i < parts.size(); i++) {
        if (parts[i][0] == '#') {
            parts[i][0] = '0';
            int ord = stoi(parts[i]);
            if (ord > 127) {
                err_msg = "character ord is too big";
//                throw BadToken(*this, "character ord is too big");
            }
            parts[i] = string(1, ord);
            continue;
        }
        if (i < parts.size() - 1 && parts[i + 1][0] == '\'') {
            parts[i].push_back('\'');
        }
        parts[i] = string(parts[i].begin() + 1, parts[i].end() - 1);
    }
    for(int i = raw_value.size() - 1; i >= 0; i--) {
        if (raw_value[i] == ETX) {
            raw_value.erase(i, 1);
        }
    }
    return accumulate(parts.begin(), parts.end(), string(""), plus<string>());
}


Token& Token::evaluate() {
    switch (category) {
    case C_OPERATOR:
    case C_SEPARATOR:
    case C_IDENTIFIER:
    case C_RESERVED:{
        value_id = -1;
        return *this;
    }
    default: break;
    }

    switch (subcategory) {
    case L_INTEGER:{
        value_id = int_values.size();
        int_values.push_back(eval_int_literal(raw_value));
    } break;
    case L_FLOAT: {
        value_id = float_values.size();
        float_values.push_back(stold(raw_value));
    } break;
    case L_STRING: {
        value_id = string_values.size();
        string_values.push_back(eval_str_literal(raw_value));
    } break;
    default: break;
    }
    return *this;
}

bool Token::empty() const {
    return raw_value.empty();
}

bool Token::is_broken() const {
    return !err_msg.empty();
}

int Token::is_reserved(string s) {
    static bool init_rr = init_reversed_reserved();
    transform(s.begin(), s.end(), s.begin(), (int (*)(int))toupper);
    auto result = Token::reserved_lst.find(s);
    return result == Token::reserved_lst.end() ? 0 : result->second;
}

int Token::is_reserved_operator(Reserved r) {
    auto result = Token::reserved_operator_lst.find(r);
    return result == Token::reserved_operator_lst.end() ? 0 : result->second;
}

string Token::strvalue() const {
    switch(category) {
    case C_OPERATOR: return operator_lst[(Operator)subcategory];
    case C_RESERVED: return reversed_reserved_lst[(Reserved)subcategory];
    case C_SEPARATOR: return separator_lst[(Separator)subcategory];
    case C_IDENTIFIER: return raw_value;
    case C_EOF: return "end of file";
    case C_COMMENT: return "";
    default:;
    }

    if (subcategory == -1) {
        return "";
    }
    switch (subcategory) {
    case L_INTEGER: {
        return to_string(int_values[value_id]);
    }
    case L_FLOAT: {
        return to_string(float_values[value_id]);
    }
    case L_STRING: {
        return string_values[value_id];
    }
    default: return "";
    }
}

bool Token::init_reversed_reserved() {
    for(auto& p: reserved_lst) {
        reversed_reserved_lst.insert({p.second, p.first});
    }
    return true;
}

string Token::strcategory() const {
    static string cat[] = {"operator", "separator", "reserved", "literal", "identifier", "comment", "EOF"};
    static string lit[] = {"string ", "integer ", "float ", "hex integer ", "bin integer "};
    return (category == C_LITERAL ? lit[subcategory] : "") + cat[category];
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    return os << t.position << "\t" <<
                 t.strcategory() << "\t[" <<
                 t.strvalue() << "]\t\"" <<
                 t.raw_value << "\"";
}

std::ostream& operator<<(std::ostream& os, const Pos& p) {
    return os << "(" << p.line << ':' << p.column << ")";
}

bool operator==(const Token& t, Token::Category cat) {
    return t.category == cat;
}

bool operator!=(const Token& t, Token::Category cat) {
    return t.category != cat;
}

bool operator==(const Token& t, Token::Operator op) {
    return t.category == Token::C_OPERATOR && t.subcategory == op;
}

bool operator!=(const Token& t, Token::Operator op) {
    return !(t == op);
}

bool operator==(const Token& t, Token::Separator sep) {
    return t.category == Token::C_SEPARATOR && t.subcategory == sep;
}

bool operator!=(const Token& t, Token::Separator sep) {
    return !(t == sep);
}

bool operator==(const Token& t, Token::Reserved res) {
    return t.category == Token::C_RESERVED && t.subcategory == res;
}

bool operator!=(const Token& t, Token::Reserved res) {
    return !(t == res);
}

