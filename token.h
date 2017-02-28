#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Pos {
    int line, column;
    unsigned long long fstream_pos;
};

class Token {
public:
    enum Category : int;
    enum Operator : int;
    enum Separator : int;
    enum Reserved : int;
    enum Literal : int;

    Token();
    Token(Pos _position, Category _category, const std::string& _raw_value, int _subcategory = -1);
    void clear();
    Token& evaluate();
    bool empty();
    std::string strvalue() const;
    std::string strcategory() const;
    static int is_reserved(std::string s);

    Pos position;
    Category category;
    std::string raw_value;
    int subcategory;
    int value_id;

    static std::vector<int> int_values;
    static std::vector<double> float_values;
    static std::vector<std::string> string_values;
    static std::map<std::string, Reserved> reserved_lst;
    static std::map<Reserved, std::string> reversed_reserved_lst;
    static std::map<Operator, std::string> operator_lst;
    static std::map<Separator, std::string> separator_lst;

    enum Category : int {
        C_OPERATOR,
        C_SEPARATOR,
        C_RESERVED,
        C_LITERAL,
        C_IDENTIFIER,
    };

    enum Operator : int {
        OP_EQUAL = 1,
        OP_GTHAN,
        OP_LTHAN,
        OP_PLUS,
        OP_MINUS,
        OP_SLASH,
        OP_ASTER,
        OP_LBRACE,
        OP_LPAREN,
        OP_ASSIGN,    // :=
        OP_PLUSAGN,   // +=
        OP_MINUSAGN,  // -=
        OP_FACAGN,    // /=
        OP_MULAGN,    // *=
        OP_LEQ,       // <=
        OP_GEQ,       // >=
        OP_NEQ,       // <>
        OP_DOTDOT,    // ..
        OP_DIRECTIVE, // {$
        OP_RPAREN,    // )
        OP_LSQBRAC,   // [
        OP_RSQBRAC,   // ]
        OP_RBRACE,    // }
        OP_CARET,     // ^
        OP_SHL,       // <<
        OP_SHR,       // >>
        OP_AND,       // and
        OP_OR,        // or
        OP_NOT,       // not
        OP_XOR,       // xor
        OP_IN,        // in
        OP_DIV,       // div
        OP_MOD,       // mod
    };

    enum Separator : int {
        S_COMMA,
        S_COLON,
        S_SCOLON,
    };

    enum Reserved : int {
        R_AND = 1,
        R_ASM,
        R_ARRAY,
        R_BEGIN,
        R_CASE,
        R_CONST,
        R_CONSTRUCTOR,
        R_DESTRUCTOR,
        R_DIV,
        R_DO,
        R_DOWNTO,
        R_ELSE,
        R_END,
        R_EXPORTS,
        R_FILE,
        R_FOR,
        R_FUNCTION,
        R_GOTO,
        R_IF,
        R_IMPLEMENTATION,
        R_IN,
        R_INHERITED,
        R_INLINE,
        R_INTERFACE,
        R_LABEL,
        R_LIBRARY,
        R_MOD,
        R_NIL,
        R_NOT,
        R_OBJECT,
        R_OF,
        R_OR,
        R_PACKED,
        R_PROCEDURE,
        R_PROGRAM,
        R_RECORD,
        R_REPEAT,
        R_SET,
        R_SHL,
        R_SHR,
        R_STRING,
        R_THEN,
        R_TO,
        R_TYPE,
        R_UNIT,
        R_UNTIL,
        R_USES,
        R_VAR,
        R_WHILE,
        R_WITH,
        R_XOR,
    };

    enum Literal : int {
        L_STRING,
        L_INTEGER,
        L_FLOAT,
    };
private:
    static bool init_reversed_reserved();
};

std::ostream& operator<<(std::ostream& os, const Token& t);

#endif // TOKEN_H
