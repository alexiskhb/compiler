#include "scanner.h"

using namespace std;

Scanner::State Scanner::st[Scanner::SIZEOF_STATES][Scanner::SIZEOF_CHARACTERS];
Scanner::Character Scanner::ch[256];

bool Scanner::init_states() {
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
    ch['#'] = CH_NUMBER;
    ch['$'] = CH_DOLLAR;
    ch['%'] = CH_PERCENT;
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
    State state = m_state;
    for(const char c: unseparated_chars) {

        state = st[state][ch[c]];
        state = st[state][NORMALIZE];
    }
    Token result = m_tokens.front();
    m_tokens.pop_front();
    return result;
}

