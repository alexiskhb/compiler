#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>
#include <iostream>
#include "token.h"
#include <vector>
#include <deque>

class Scanner {
public:
    enum State : int;
    enum Character : int;

    Scanner();
    Scanner(const std::string& filename);
    bool is_open() const;
    Token get_next_token();
    void open(const std::string& filename);

    enum State : int {
        ST_START = 0,
        ST_ERROR,
        ST_EOF,
        ST_IDENTIFIER,
        ST_INTEGER,
        ST_FLOAT,
        ST_EXPONFLOAT,
        ST_EXPON,
        ST_COLON,
        ST_STRLIT,
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
        ST_LPARENAST, // (* <=> {
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
        CN_LF,
        CH_TAB,
        CH_SPACE,
        CH_OTHER,
        NORMALIZE,         // Service state
        SIZEOF_CHARACTERS, // Service state
    };

    static State st[SIZEOF_STATES][SIZEOF_CHARACTERS];
    static Character ch[256];
private:
    bool init_states();
    void save_token();
    std::ifstream m_file;
    std::deque<Token> m_tokens;
    std::string m_current_token;
    State m_state = ST_START;
};

#endif // SCANNER_H
