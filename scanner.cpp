#include "scanner.h"

using namespace std;

enum State {
    ST_START = 0,
    ST_ERROR,
    ST_EOF,
    ST_IDENTIFIER,
    ST_INTEGER,
    ST_FLOAT,
    ST_COLON,
    ST_STRLIT,
    ST_PLUS,
    ST_LBRACE,
    ST_ASTER,
    ST_MINUS,
    ST_DOT,
    ST_SLASH,
    ST_LTHAN,
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
    END_GREEDY, // Service state
    SIZEOF_STATES, // Service state
    //    ST_DOLLAR,
    //    ST_PERCENT,
    //    ST_AMPERS,
    //    ST_BSLASH,
    //    ST_UNDERS,
};

enum Character {
    CH_DIGIT = 0,
    CH_LETTER,
    CH_NUMBER, // #
    CH_DOLLAR,
    CH_PERCENT,
    CH_APOST,  // '
    CH_LPAREN,
    CH_RPAREN,
    CH_LSQBRAC,
    CH_RSQBRAC,
    CH_LBRACE,
    CH_RBRACE,
    CH_ASTER,  // *
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
    CH_UNDERS, // _
    CN_LF,     // \n
    CH_TAB,
    CH_SPACE,
    CH_OTHER,
    NORMALIZE, // Service state
    SIZEOF_CHARACTERS, // Service state
    //    CH_EXCLAM,
    //    CH_QUOTE,
    //    CH_AMPERS,
    //    CH_BSLASH,
};

// State transitions
State st[SIZEOF_STATES][SIZEOF_CHARACTERS];
Character ch[256];

bool init_states() {
    for(int i = 0; i < SIZEOF_STATES; i++) {
        for(int j = 0; j < SIZEOF_CHARACTERS; j++) {
            st[i][j] = ST_ERROR;
        }
    }
    for(int i = 0; i < 256; i++) {
        ch[i] = CH_OTHER;
    }
    ch['_'] = CH_LETTER;
    for(int i = 'A'; i <= 'Z'; i++) {
        ch[i] = ch[i - 'A' + 'a'] = CH_LETTER;
    }
    for(int i = '0'; i <= '9'; i++) {
        ch[i] = CH_DIGIT;
    }
//    ch['!'] = CH_EXCLAM;
//    ch['"'] = CH_QUOTE;
    ch['#'] = CH_NUMBER;
    ch['$'] = CH_DOLLAR;
    ch['%'] = CH_PERCENT;
//    ch['&'] = CH_AMPERS;
    ch['\''] = CH_APOST;
    ch['('] = CH_LPAREN;
    ch[')'] = CH_RPAREN;
    ch['['] = CH_LSQBRAC;
    ch[']'] = CH_RSQBRAC;
    ch['{'] = CH_LBRACE;
    ch['}'] = CH_RBRACE;
    ch['*'] = CH_ASTER;
    ch['+'] = CH_PLUS;
    ch[','] = CH_COMMA;
    ch['-'] = CH_MINUS;
    ch['.'] = CH_DOT;
    ch['/'] = CH_SLASH;
    ch[':'] = CH_COLON;
    ch[';'] = CH_SCOLON;
    ch['<'] = CH_LTHAN;
    ch['>'] = CH_GTHAN;
    ch['='] = CH_EQUAL;
//    ch['\\'] = CH_BSLASH;
    ch['^'] = CH_CARET;
//    ch['_'] = CH_UNDERS;
    ch['\n']   = CN_LF;
    ch['	'] = CH_TAB;
    ch[' '] = CH_SPACE;

    for(int i = 0; i < SIZEOF_STATES; i++) {
        st[i][NORMALIZE] = (State)i;
    }
    for(int i = START_GREEDY; i < END_GREEDY; i++) {
        st[i][NORMALIZE] = ST_START;
    }
    st[ST_IDENTIFIER][CH_LETTER] = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_DIGIT]  = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_UNDERS] = ST_IDENTIFIER;

    return true;
}

Scanner::Scanner() {

}

Scanner::Scanner(const string& filename) {
    this->open(filename);
}

void Scanner::open(const string& filename) {
    static bool init = init_states();
    m_file.open(filename);
}

bool Scanner::is_open() const {
    return m_file.is_open();
}

void Scanner::save_token() {
//    m_tokens.emplace_back(m_current_token);
}

Token Scanner::get_next_token() {
    if (!m_tokens.empty()) {
        Token result = m_tokens.front();
        m_tokens.pop_front();
        return result;
    }
    string unseparated_chars;
    m_file >> unseparated_chars;
    unseparated_chars.push_back(' ');
    State state = ST_START;
    for(const char c: unseparated_chars) {

        state = st[state][ch[c]];
        state = st[state][NORMALIZE];
    }
    Token result = m_tokens.front();
    m_tokens.pop_front();
    return result;
}

