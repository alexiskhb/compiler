#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include "token.h"
#include <vector>
#include <exception>
#include <deque>
#include <iterator>

class BadToken : public std::exception {
public:
    BadToken(Token t, const std::string& prev_state, const std::string &state) :
        m_bad_token(t), m_prev_state(prev_state), m_state(state) {
    }
    const char* what() const noexcept override {
        return ("(" + m_bad_token.raw_value + ") [" + m_prev_state + "][" + m_state + "]").c_str();
    }
    Pos position() const {
        return m_bad_token.position;
    }
    std::string prev_state() const {
        return m_prev_state;
    }
    std::string state() const {
        return m_state;
    }
    std::string wat() const {
        return ("(" + m_bad_token.raw_value + ") [" + m_prev_state + "][" + m_state + "]").c_str();
    }
private:
    Token m_bad_token;
    std::string m_prev_state, m_state;
};

class Scanner {
public:
    enum State : int;
    enum Character : int;

    Scanner();
    Scanner(const std::string& filename);
    bool is_open() const;
    Token get_next_token();
    void open(const std::string& filename);
    bool eof();
    bool last_token_success() const;
    operator bool() const {
        return last_token_success();
    }

    enum State : int {
        ST_START = 0,
        ST_ERROR,
        ST_EOF,
        ST_IDENTIFIER,
        ST_STRLIT,
        //
        ST_INTEGER,    //1
        ST_FLOAT,      //1.
        ST_EXPONFLOAT, //1.1
        ST_EXPONCHAR,  //1.1e
        ST_EXPONSIGN,  //1.1e+
        ST_EXPON,      //1.1e+1
        //
        ST_MLINECMT,
        ST_COLON,
        ST_PLUS,
        ST_LBRACE,
        ST_ASTER,
        ST_MINUS,
        ST_DOT,
        ST_SLASH,
        ST_LTHAN,
        ST_DOLLAR,  // $000bcdeF
        ST_PERCENT, // %10011
        ST_AT,      // pointer := @variable
        ST_CHARORD, // char := #32, ’the string starts here’#13#10’and continues on next line’
        ST_GTHAN,
        ST_LPAREN,
    // Greedy final states (always goto ST_START)
        START_GREEDY, // Service state
        ST_COMMENT,   // //
        ST_ASSIGN,    // :=
        ST_PLUSAGN,   // +=
        ST_MINUSAGN,  // -=
        ST_FACAGN,    // /=
        ST_MULAGN,    // *=
        ST_LEQ,       // <=
        ST_GEQ,       // >=
        ST_NEQ,       // <>
        ST_DOTDOT,    // ..
        ST_COMMA,     // ,
        ST_DIRECTIVE, // {$
        ST_RPAREN,    // )
        ST_LSQBRAC,   // [
        ST_RSQBRAC,   // ]
        ST_RBRACE,    // }
        ST_CARET,     // ^
        ST_EQUAL,     // =
        ST_SCOLON,    // ;
        ST_SHL,       // <<
        ST_SHR,       // >>
        ST_LPARENDOT, // (. <=> [
        ST_RPARENDOT, // .) <=> ]
        ST_LPARENAST, // (* <=> { see ST_MLINECMT
        ST_RPARENAST, // *) <=> }
        END_GREEDY,   // Service state
        SIZEOF_STATES,// Service state
    };

    enum Character : int {
        CH_DIGIT = 0,
        CH_LETTER,
        CH_NUMBER, // #
        CH_DOLLAR,
        CH_PERCENT,
        CH_EXPONCHAR,
        CH_APOST,
        CH_LPAREN,
        CH_RPAREN,
        CH_LSQBRAC,
        CH_RSQBRAC,
        CH_LBRACE,
        CH_RBRACE,
        CH_ASTER,
        CH_PLUS,
        CH_COMMA,
        CH_MINUS,
        CH_DOT,
        CH_SLASH,
        CH_COLON,
        CH_SCOLON,
        CH_LTHAN,
        CH_GTHAN,
        CH_EQUAL,
        CH_CARET,
        CH_UNDERS,
        CH_LF,
        CH_TAB,
        CH_SPACE,
        CH_OTHER,
        NORMALIZE,         // Service state
        SIZEOF_CHARACTERS, // Service state
    };

    static State st[SIZEOF_STATES][SIZEOF_CHARACTERS];
    static Character ch[256];
    static Token::Category state_to_cat[SIZEOF_STATES];
    static State chtost[SIZEOF_CHARACTERS];
    static Character sttoch[SIZEOF_STATES];
    static int state_to_subcat[SIZEOF_STATES];
private:
    void save_token();
    void clear_token();
    void begin_token();
    void updatesave_token();
    void throw_error();
    void update_token();
    bool init_states();
    bool init_fc();
    std::function<void()> fc[SIZEOF_STATES][SIZEOF_STATES];
    std::ifstream m_file;
    std::deque<Token> m_tokens;
    std::string m_filename;
    State m_state = ST_START, m_prev_state;
    Token m_current_token;
    char m_c;
    int m_line, m_column;
    bool m_last_token_success = true;
};

Scanner& operator>>(Scanner& scanner, Token& token);

#endif // SCANNER_H
