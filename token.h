#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Pos {
    bool operator==(const Pos& other) {
        return fstream_pos == other.fstream_pos;
    }
    operator bool() {
        return fstream_pos;
    }

    size_t line, column;
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
    bool empty() const;
    bool is_broken() const;
    std::string strvalue() const;
    std::string strcategory() const;
    static int is_reserved(std::string s);
    static int is_reserved_operator(Reserved);
    explicit operator bool() const {
        return !(empty() || category == C_EOF);
    }
    explicit operator Token::Category() const {
        return category;
    }
    explicit operator Token::Operator() const {
        return category == C_OPERATOR ? (Operator)subcategory : NOT_OPERATOR;
    }
    explicit operator Token::Separator() const {
        return category == C_SEPARATOR ? (Separator)subcategory : NOT_SEPARATOR;
    }

    Pos position;
    Category category;
    std::string raw_value;
    std::string err_msg = "";
    int subcategory;
    int value_id;

    static std::vector<int> int_values;
    static std::vector<long double> float_values;
    static std::vector<std::string> string_values;
    static std::map<std::string, Reserved> reserved_lst;
    static std::map<Reserved, std::string> reversed_reserved_lst;
    static std::map<Reserved, Operator> reserved_operator_lst;
    static std::map<Operator, std::string> operator_lst;
    static std::map<Separator, std::string> separator_lst;

    enum Category : int {
        C_OPERATOR,
        C_SEPARATOR,
        C_RESERVED,
        C_LITERAL,
        C_IDENTIFIER,
        C_COMMENT,
        C_EOF,
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
        OP_DOT,
        OP_AT,
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
        NOT_OPERATOR,
        SIZEOF_OPERATORS,
    };

    enum Separator : int {
        S_COMMA,
        S_COLON,
        S_SCOLON,
        NOT_SEPARATOR,
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
        L_FLOAT
    };

    static const char ETX = (char)3;
private:
    static bool init_reversed_reserved();
    int eval_int_literal(std::string s);
    std::string eval_str_literal(const std::string& s);
};

std::ostream& operator<<(std::ostream& os, const Token& t);
bool operator==(const Token& t, Token::Category);
bool operator==(const Token& t, Token::Operator);
bool operator==(const Token& t, Token::Separator);
bool operator!=(const Token& t, Token::Category);
bool operator!=(const Token& t, Token::Operator);
bool operator!=(const Token& t, Token::Separator);

class BadToken : public std::exception {
public:
    BadToken(Token t, const std::string& msg) :
        m_bad_token(t), m_msg(msg) {
    }
    const char* what() const noexcept override {
        return ("\"" + m_bad_token.raw_value + "\"").c_str();
    }
    Pos position() const {
        return m_bad_token.position;
    }
    std::string msg() const {
        return m_msg;
    }
    std::string value() const {
        return " \"" + m_bad_token.raw_value + "\"";
    }
private:
    Token m_bad_token;
    std::string m_msg;
};

#endif // TOKEN_H
