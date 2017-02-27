#include "scanner.h"

using namespace std;

Scanner::State Scanner::st[Scanner::SIZEOF_STATES][Scanner::SIZEOF_CHARACTERS];
//function<void()> Scanner::fc[Scanner::SIZEOF_STATES][Scanner::SIZEOF_STATES];
Scanner::Character Scanner::ch[256];
string stst[] = {"ST_START", "ST_ERROR", "ST_EOF", "ST_IDENTIFIER", "ST_STRLIT", "ST_INTEGER", "ST_FLOAT", "ST_EXPONFLOAT", "ST_EXPONCHAR", "ST_EXPONSIGN", "ST_EXPON", "ST_MLINECMT", "ST_COLON", "ST_PLUS", "ST_LBRACE", "ST_ASTER", "ST_MINUS", "ST_DOT", "ST_SLASH", "ST_LTHAN", "ST_DOLLAR", "ST_PERCENT", "ST_AT", "ST_CHARORD", "ST_GTHAN", "ST_LPAREN", "START_GREEDY", "ST_COMMENT", "ST_ASSIGN", "ST_PLUSAGN", "ST_MINUSAGN", "ST_FACAGN", "ST_MULAGN", "ST_LEQ", "ST_GEQ", "ST_NEQ", "ST_DOTDOT", "ST_COMMA", "ST_DIRECTIVE", "ST_RPAREN", "ST_LSQBRAC", "ST_RSQBRAC", "ST_RBRACE", "ST_CARET", "ST_EQUAL", "ST_SCOLON", "ST_SHL", "ST_SHR", "ST_LPARENDOT", "ST_RPARENDOT", "ST_LPARENAST", "ST_RPARENAST", "END_GREEDY", "SIZEOF_STATES"};

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
    ch['e'] = ch['E'] = CH_EXPONCHAR;
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
    ch['\n']   = CH_LF;
    ch['	'] = CH_TAB;
    ch[' '] = CH_SPACE;

    for(int i = 0; i < SIZEOF_STATES; i++) {
        st[i][NORMALIZE] = (State)i;
    }
    for(int i = START_GREEDY; i < END_GREEDY; i++) {
        st[i][NORMALIZE] = ST_START;
    }
// Comments
    st[ST_LPAREN][CH_ASTER] = ST_MLINECMT;
    st[ST_SLASH][CH_SLASH] = ST_COMMENT;
    // Rewrite 'st[i][CH_SPACE] = ST_START;' there
    for(int i = 0; i < SIZEOF_CHARACTERS; i++) {
        st[ST_MLINECMT][i] = ST_MLINECMT;
    }
    // st[ST_LBRACE][CH_ASTER] = ST_MLINECMT;
    st[ST_MLINECMT][CH_RBRACE] = ST_START;
// Identifiers
    st[ST_IDENTIFIER][CH_LETTER] = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_DIGIT]  = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_UNDERS] = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_EXPONCHAR] = ST_IDENTIFIER;

    st[ST_IDENTIFIER][CH_SCOLON] = ST_START;
    st[ST_IDENTIFIER][CH_LF] = ST_START;
// Directives
    st[ST_MLINECMT][CH_DOLLAR] = ST_DIRECTIVE;
// Integer
    st[ST_INTEGER][CH_DIGIT] = ST_INTEGER;
// Float
    st[ST_INTEGER][CH_DOT] = ST_FLOAT;
    st[ST_FLOAT][CH_DIGIT] = ST_EXPONFLOAT;
    st[ST_EXPONFLOAT][CH_DIGIT] = ST_EXPONFLOAT;
    st[ST_EXPONFLOAT][CH_EXPONCHAR] = ST_EXPONCHAR;
    st[ST_EXPONCHAR][CH_PLUS] = ST_EXPONSIGN;
    st[ST_EXPONCHAR][CH_MINUS] = ST_EXPONSIGN;
    st[ST_EXPONCHAR][CH_DIGIT] = ST_EXPON;
    st[ST_EXPONSIGN][CH_DIGIT] = ST_EXPON;
    st[ST_START][CH_EXPONCHAR] = ST_IDENTIFIER;
//
    st[ST_START][CH_LETTER] = ST_IDENTIFIER;
// Spaces and delimiters
    st[ST_START][CH_SPACE]  = ST_START;
    st[ST_START][CH_TAB]    = ST_START;
    st[ST_START][CH_LF]     = ST_START;
    st[ST_START][CH_SCOLON] = ST_START;

    st[ST_IDENTIFIER][CH_SPACE] = ST_START;
    st[ST_INTEGER]   [CH_SPACE] = ST_START;
    st[ST_FLOAT]     [CH_SPACE] = ST_START;
    st[ST_EXPONFLOAT][CH_SPACE] = ST_START;
    st[ST_EXPON]     [CH_SPACE] = ST_START;

    st[ST_IDENTIFIER][CH_TAB] = ST_START;
    st[ST_INTEGER]   [CH_TAB] = ST_START;
    st[ST_FLOAT]     [CH_TAB] = ST_START;
    st[ST_EXPONFLOAT][CH_TAB] = ST_START;
    st[ST_EXPON]     [CH_TAB] = ST_START;

    st[ST_IDENTIFIER][CH_LF] = ST_START;
    st[ST_INTEGER]   [CH_LF] = ST_START;
    st[ST_FLOAT]     [CH_LF] = ST_START;
    st[ST_EXPONFLOAT][CH_LF] = ST_START;
    st[ST_EXPON]     [CH_LF] = ST_START;

    st[ST_IDENTIFIER][CH_SCOLON] = ST_START;
    st[ST_INTEGER]   [CH_SCOLON] = ST_START;
    st[ST_FLOAT]     [CH_SCOLON] = ST_START;
    st[ST_EXPONFLOAT][CH_SCOLON] = ST_START;
    st[ST_EXPON]     [CH_SCOLON] = ST_START;

// Colon
    st[ST_START][CH_COLON] = ST_COLON;
    st[ST_COLON][CH_LETTER] = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_COLON] = ST_COLON;
    st[ST_INTEGER][CH_COLON] = ST_COLON;
    st[ST_COLON][CH_SPACE] = ST_START;
    st[ST_COLON][CH_LF] = ST_START;

    return true;
}

bool Scanner::init_fc() {
    auto beg_tk = bind(&Scanner::begin_token, this);
    auto sav_tk = bind(&Scanner::save_token, this);
    auto upd_tk = bind(&Scanner::update_token, this);
    auto thr_er = bind(&Scanner::throw_error, this);
    for(int i = 0; i < SIZEOF_STATES; i++) {
        fc[ST_START][i] = sav_tk;
        fc[i][ST_ERROR] = thr_er;
        fc[i][ST_START] = sav_tk;
        fc[i][i] = upd_tk;
        for(int g = START_GREEDY; g < END_GREEDY; g++) {
            fc[i][g] = sav_tk;
        }
    }
    fc[ST_START][ST_START] = 0;
    fc[ST_START][ST_IDENTIFIER] = beg_tk;
    fc[ST_START][ST_INTEGER]    = upd_tk;
    fc[ST_IDENTIFIER][ST_ASTER] = sav_tk;
    fc[ST_IDENTIFIER][ST_SCOLON] = sav_tk;
    fc[ST_IDENTIFIER][ST_COLON] = sav_tk;
    fc[ST_IDENTIFIER][ST_START] = sav_tk;
    fc[ST_IDENTIFIER][ST_EOF] = sav_tk;
    fc[ST_COLON][ST_IDENTIFIER] = sav_tk;

}

Scanner::Scanner() {

}

Scanner::Scanner(const string& filename) {
    this->open(filename);
}

void Scanner::open(const string& filename) {
    static bool init = init_states();
    init_fc();
    m_line = 0;
    m_file.open(filename);
    m_filename = filename;
}

bool Scanner::is_open() const {
    return m_file.is_open();
}

void Scanner::save_token() {
    if (m_current_token.empty()) {
        return;
    }
    m_tokens.push_back(m_current_token);
    clear_token();
    update_token();
}

void Scanner::update_token() {
    m_current_token.position.line = m_line;
    m_current_token.position.column = m_column - m_current_token.raw_value.size();
    m_current_token.raw_value.push_back(m_c);
}

void Scanner::clear_token() {
    m_current_token.clear();
}

void Scanner::begin_token() {
    clear_token();
    update_token();
}


bool Scanner::eof() {
    return m_file.eof() && m_tokens.empty();
}

void Scanner::throw_error() {
    update_token();
    throw BadToken(m_current_token);
}

Token Scanner::get_next_token() {
    if (!m_tokens.empty()) {
        Token result = m_tokens.front();
        m_tokens.pop_front();
        return result;
    }
    string unseparated_chars;
    getline(m_file, unseparated_chars);
    ++m_line;
    unseparated_chars.push_back('\n');
    State state = m_state, prev_state;
    for(m_column = 0; m_column < unseparated_chars.size(); m_column++) {
        m_c = unseparated_chars[m_column];
        prev_state = state;
        state = st[state][ch[m_c]];
        if (fc[prev_state][state]) {
            fc[prev_state][state]();
        } else if (state != ST_START || prev_state != ST_START) {
            cout << "There's no action for [" << stst[prev_state] << "][" << stst[state] << "] on char '" << m_c << "'" << endl;
        }
        state = st[state][NORMALIZE];
    }
    if (m_tokens.size() == 0) {
        return Token();
    }
    Token result = m_tokens.front();
    m_tokens.pop_front();
    return result;
}

