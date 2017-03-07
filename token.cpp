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
{OP_EQUAL, "EQUAL"},
{OP_GTHAN, "GTHAN"},
{OP_LTHAN, "LTHAN"},
{OP_PLUS, "PLUS"},
{OP_MINUS, "MINUS"},
{OP_SLASH, "SLASH"},
{OP_ASTER, "ASTER"},
{OP_LBRACE, "LBRACE"},
{OP_LPAREN, "LPAREN"},
{OP_ASSIGN, "ASSIGN"},
{OP_PLUSAGN, "PLUSAGN"},
{OP_MINUSAGN, "MINUSAGN"},
{OP_FACAGN, "FACAGN"},
{OP_MULAGN, "MULAGN"},
{OP_LEQ, "LEQ"},
{OP_GEQ, "GEQ"},
{OP_NEQ, "NEQ"},
{OP_DOT, "DOT"},
{OP_AT, "AT"},
{OP_DOTDOT, "DOTDOT"},
{OP_DIRECTIVE, "DIRECTIVE"},
{OP_RPAREN, "RPAREN"},
{OP_LSQBRAC, "LSQBRAC"},
{OP_RSQBRAC, "RSQBRAC"},
{OP_RBRACE, "RBRACE"},
{OP_CARET, "CARET"},
{OP_SHL, "SHL"},
{OP_SHR, "SHR"},
{OP_AND, "AND"},
{OP_OR, "OR"},
{OP_NOT, "NOT"},
{OP_XOR, "XOR"},
{OP_IN, "IN"},
{OP_DIV, "DIV"},
{OP_MOD, "MOD"}
};
std::map<Token::Separator, std::string> Token::separator_lst = {
{S_COMMA, "COMMA"},
{S_COLON, "COLON"},
{S_SCOLON, "SEMICOLON"}
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
    switch(subcategory){
    case L_HEXINTEGER:
        s[0] = '0';
        return stoi(s, 0, 16);
    case L_BININTEGER:
        s[0] = '0';
        return stoi(s, 0, 2);
    default: return stoi(s);
    }
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
    case L_INTEGER:case L_HEXINTEGER:case L_BININTEGER: {
        value_id = int_values.size();
        int_values.push_back(eval_int_literal(raw_value));
    } break;
    case L_FLOAT: {
        value_id = float_values.size();
        float_values.push_back(stold(raw_value));
    } break;
    case L_STRING: {
        value_id = string_values.size();
        string_values.push_back(raw_value);
    } break;
    default: break;
    }

    return *this;
}

bool Token::empty() const {
    return raw_value.empty();
}

int Token::is_reserved(string s) {
    static bool init_rr = init_reversed_reserved();
    transform(s.begin(), s.end(), s.begin(), (int (*)(int))toupper);
    auto result = Token::reserved_lst.find(s);
    return result == Token::reserved_lst.end() ? 0 : result->second;
}

string Token::strvalue() const {
    switch(category) {
    case C_OPERATOR: return operator_lst[(Operator)subcategory];
    case C_RESERVED: return reversed_reserved_lst[(Reserved)subcategory];
    case C_SEPARATOR: return separator_lst[(Separator)subcategory];
    case C_IDENTIFIER:
    case C_EOF: case C_COMMENT: return "";
    }

    if (subcategory == -1) {
        return "";
    }
    switch (subcategory) {
    case L_INTEGER:case L_HEXINTEGER:case L_BININTEGER: {
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
    return os  << "(" <<
                 t.position.line << ':' <<
                 t.position.column << ")\t" <<
                 t.strcategory() << "\t[" <<
                 t.strvalue() << "]\t\"" <<
                 t.raw_value << "\"";
}
