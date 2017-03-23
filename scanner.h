#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include "token.h"
#include <vector>
#include <exception>
#include <deque>
#include <iterator>

class Scanner {
public:
    Scanner();
    Scanner(const std::string& filename);
    bool is_open() const;
    Token get_next_token();
    void next_token();
    Token top() const;
    Token require(std::initializer_list<Token::Operator>);
    Token require(std::initializer_list<Token::Category>);
    Token require(std::initializer_list<Token::Reserved>);
    void open(const std::string& filename);
    bool eof() const;
    bool last_token_success() const;
    explicit operator bool() const {
        return last_token_success();
    }
    explicit operator Token::Operator() const {
        return static_cast<Token::Operator>(top());
    }
    explicit operator Token::Separator() const {
        return static_cast<Token::Separator>(top());
    }
    explicit operator Token::Reserved() const {
        return static_cast<Token::Reserved>(top());
    }
    operator Token() const {
        return top();
    }
    Token operator++();
    Token operator++(int);
    std::string get_line(int);

private:
    enum State : int {
        ST_START = 0,
        ST_ERROR,
        ST_ERROR_INVALID_BININT,
        ST_ERROR_INVALID_HEXINT,
        ST_EOF,
        ST_IDENTIFIER,
        ST_STRLIT,
        ST_STRLIT_RIGHTAPOST,
        ST_STRLIT_ESCSTART,
        ST_STRLIT_ESCNUM,
        //
        ST_INTEGER,    //1
        ST_FLOAT,      //1.
        ST_EXPONFLOAT, //1.1
        ST_EXPONCHAR,  //1.1e
        ST_EXPONSIGN,  //1.1e+
        ST_EXPON,      //1.1e+1
        ST_HEXINTEGER,
        ST_BININTEGER,
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
        CH_AT,
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

    void save_token();
    void clear_token();
    void upd_strlit();
    void begin_token();
    void noop();
    void updatesave_token();
    void throw_error();
    void update_token();
    void update_intliteral_token();
    void save_int_dotdot_token();
    bool init_states();
    bool init_fc();
    bool is_hex(char c);
    bool is_bin(char c);
    std::function<void()> fc[SIZEOF_STATES][SIZEOF_STATES];
    std::ifstream m_file;
    std::deque<Token> m_tokens;
    std::deque<Token>::size_type m_current_to_return = 0;
    std::string m_filename;
    State m_state = ST_START, m_prev_state;
    Token m_current_token;
    char m_c;
    size_t m_line, m_column;
    bool m_last_token_success = true;
    bool m_eof_returned = false;
    bool m_token_done;
};

Scanner& operator>>(Scanner& scanner, Token& token);
bool operator==(const Scanner& s, Token::Category);
bool operator==(const Scanner& s, Token::Operator);
bool operator==(const Scanner& s, Token::Separator);
bool operator!=(const Scanner& s, Token::Category);
bool operator!=(const Scanner& s, Token::Operator);
bool operator!=(const Scanner& s, Token::Separator);

#endif // SCANNER_H
