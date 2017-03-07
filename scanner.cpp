#include "scanner.h"

using namespace std;

Scanner::State Scanner::st[Scanner::SIZEOF_STATES][Scanner::SIZEOF_CHARACTERS];
Scanner::Character Scanner::ch[256];
Scanner::State Scanner::chtost[Scanner::SIZEOF_CHARACTERS];
Scanner::Character Scanner::sttoch[Scanner::SIZEOF_STATES];
Token::Category Scanner::state_to_cat[Scanner::SIZEOF_STATES];
int Scanner::state_to_subcat[Scanner::SIZEOF_STATES];
string stst[] = {"ST_START", "ST_ERROR", "ST_EOF", "ST_IDENTIFIER", "ST_STRLIT", "ST_INTEGER", "ST_FLOAT", "ST_EXPONFLOAT", "ST_EXPONCHAR", "ST_EXPONSIGN", "ST_EXPON", "ST_MLINECMT", "ST_COLON", "ST_PLUS", "ST_LBRACE", "ST_ASTER", "ST_MINUS", "ST_DOT", "ST_SLASH", "ST_LTHAN", "ST_DOLLAR", "ST_PERCENT", "ST_AT", "ST_CHARORD", "ST_GTHAN", "ST_LPAREN", "START_GREEDY", "ST_COMMENT", "ST_ASSIGN", "ST_PLUSAGN", "ST_MINUSAGN", "ST_FACAGN", "ST_MULAGN", "ST_LEQ", "ST_GEQ", "ST_NEQ", "ST_DOTDOT", "ST_COMMA", "ST_DIRECTIVE", "ST_RPAREN", "ST_LSQBRAC", "ST_RSQBRAC", "ST_RBRACE", "ST_CARET", "ST_EQUAL", "ST_SCOLON", "ST_SHL", "ST_SHR", "ST_LPARENDOT", "ST_RPARENDOT", "ST_LPARENAST", "ST_RPARENAST", "END_GREEDY", "SIZEOF_STATES"};

bool Scanner::init_states() {
//    fill(&st[0][0], &st[0][0] + SIZEOF_STATES*SIZEOF_CHARACTERS, ST_ERROR);
    fill(ch, ch + 256, CH_OTHER);
    ch['_'] = CH_LETTER;
    fill(ch + 'A', ch + 'Z' + 1, CH_LETTER);
    fill(ch + 'a', ch + 'z' + 1, CH_LETTER);
    fill(ch + '0', ch + '9' + 1, CH_DIGIT);
    fill(state_to_cat, state_to_cat + SIZEOF_STATES, Token::C_OPERATOR);
    fill(sttoch, sttoch + SIZEOF_STATES, (Character)-1);
    fill(chtost, chtost + SIZEOF_CHARACTERS, (State)-1);

    state_to_cat[ST_IDENTIFIER] = Token::C_IDENTIFIER;
    state_to_cat[ST_INTEGER] = Token::C_LITERAL;
    state_to_cat[ST_HEXINTEGER] = Token::C_LITERAL;
    state_to_cat[ST_BININTEGER] = Token::C_LITERAL;
    state_to_cat[ST_FLOAT] = Token::C_LITERAL;
    state_to_cat[ST_EXPON] = Token::C_LITERAL;
    state_to_cat[ST_EXPONFLOAT] = Token::C_LITERAL;

    state_to_cat[ST_STRLIT] = Token::C_LITERAL;
    state_to_cat[ST_SCOLON] = Token::C_SEPARATOR;
    state_to_cat[ST_COLON] = Token::C_SEPARATOR;
    state_to_cat[ST_COMMA] = Token::C_SEPARATOR;
    state_to_cat[ST_COMMENT] = Token::C_COMMENT;
    state_to_cat[ST_MLINECMT] = Token::C_COMMENT;

    state_to_subcat[ST_EQUAL] = Token::OP_EQUAL;
    state_to_subcat[ST_GTHAN] = Token::OP_GTHAN;
    state_to_subcat[ST_LTHAN] = Token::OP_LTHAN;
    state_to_subcat[ST_PLUS] = Token::OP_PLUS;
    state_to_subcat[ST_MINUS] = Token::OP_MINUS;
    state_to_subcat[ST_SLASH] = Token::OP_SLASH;
    state_to_subcat[ST_ASTER] = Token::OP_ASTER;
    state_to_subcat[ST_LBRACE] = Token::OP_LBRACE;
    state_to_subcat[ST_LPAREN] = Token::OP_LPAREN;
    state_to_subcat[ST_ASSIGN] = Token::OP_ASSIGN;
    state_to_subcat[ST_PLUSAGN] = Token::OP_PLUSAGN;
    state_to_subcat[ST_MINUSAGN] = Token::OP_MINUSAGN;
    state_to_subcat[ST_FACAGN] = Token::OP_FACAGN;
    state_to_subcat[ST_MULAGN] = Token::OP_MULAGN;
    state_to_subcat[ST_LEQ] = Token::OP_LEQ;
    state_to_subcat[ST_GEQ] = Token::OP_GEQ;
    state_to_subcat[ST_NEQ] = Token::OP_NEQ;
    state_to_subcat[ST_DOTDOT] = Token::OP_DOTDOT;
    state_to_subcat[ST_DIRECTIVE] = Token::OP_DIRECTIVE;
    state_to_subcat[ST_RPAREN] = Token::OP_RPAREN;
    state_to_subcat[ST_LSQBRAC] = Token::OP_LSQBRAC;
    state_to_subcat[ST_RSQBRAC] = Token::OP_RSQBRAC;
    state_to_subcat[ST_RBRACE] = Token::OP_RBRACE;
    state_to_subcat[ST_CARET] = Token::OP_CARET;
    state_to_subcat[ST_SHL] = Token::OP_SHL;
    state_to_subcat[ST_SHR] = Token::OP_SHR;
    state_to_subcat[ST_DOT] = Token::OP_DOT;
    state_to_subcat[ST_AT] = Token::OP_AT;

    state_to_subcat[ST_SCOLON] = Token::S_SCOLON;
    state_to_subcat[ST_COLON] = Token::S_COLON;
    state_to_subcat[ST_COMMA] = Token::S_COMMA;

    state_to_subcat[ST_INTEGER] = Token::L_INTEGER;
    state_to_subcat[ST_HEXINTEGER] = Token::L_HEXINTEGER;
    state_to_subcat[ST_BININTEGER] = Token::L_BININTEGER;
    state_to_subcat[ST_FLOAT] = Token::L_FLOAT;
    state_to_subcat[ST_EXPON] = Token::L_FLOAT;
    state_to_subcat[ST_EXPONFLOAT] = Token::L_FLOAT;
    state_to_subcat[ST_STRLIT] = Token::L_STRING;

    ch['e'] = ch['E'] = CH_EXPONCHAR;
    ch['#'] = CH_NUMBER;
    ch['$'] = CH_DOLLAR;
    ch['@'] = CH_AT;
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
    ch['\n'] = CH_LF;
    ch['\t'] = CH_TAB;
    ch[' '] = CH_SPACE;

//    sttoch [chtost[CH_DOLLAR]  = ST_DOLLAR ] = CH_DOLLAR;
//    sttoch [chtost[CH_PERCENT] = ST_PERCENT] = CH_PERCENT;
    sttoch [chtost[CH_LPAREN]  = ST_LPAREN ] = CH_LPAREN;
    sttoch [chtost[CH_RPAREN]  = ST_RPAREN ] = CH_RPAREN;
    sttoch [chtost[CH_LSQBRAC] = ST_LSQBRAC] = CH_LSQBRAC;
    sttoch [chtost[CH_RSQBRAC] = ST_RSQBRAC] = CH_RSQBRAC;
    sttoch [chtost[CH_LBRACE]  = ST_LBRACE ] = CH_LBRACE;
    sttoch [chtost[CH_RBRACE]  = ST_RBRACE ] = CH_RBRACE;
    sttoch [chtost[CH_ASTER]   = ST_ASTER  ] = CH_ASTER;
    sttoch [chtost[CH_PLUS]    = ST_PLUS   ] = CH_PLUS;
    sttoch [chtost[CH_COMMA]   = ST_COMMA  ] = CH_COMMA;
    sttoch [chtost[CH_MINUS]   = ST_MINUS  ] = CH_MINUS;
    sttoch [chtost[CH_DOT]     = ST_DOT    ] = CH_DOT;
    sttoch [chtost[CH_AT]      = ST_AT     ] = CH_AT;
    sttoch [chtost[CH_SLASH]   = ST_SLASH  ] = CH_SLASH;
    sttoch [chtost[CH_COLON]   = ST_COLON  ] = CH_COLON;
    sttoch [chtost[CH_SCOLON]  = ST_SCOLON ] = CH_SCOLON;
    sttoch [chtost[CH_LTHAN]   = ST_LTHAN  ] = CH_LTHAN;
    sttoch [chtost[CH_GTHAN]   = ST_GTHAN  ] = CH_GTHAN;
    sttoch [chtost[CH_EQUAL]   = ST_EQUAL  ] = CH_EQUAL;
    sttoch [chtost[CH_CARET]   = ST_CARET  ] = CH_CARET;

// Comments
//    st[ST_LPAREN][CH_ASTER] = ST_MLINECMT;
    st[ST_SLASH][CH_SLASH] = ST_COMMENT;
    // st[ST_LBRACE][CH_ASTER] = ST_MLINECMT;
// Common signs
    for(int s = 0; s < SIZEOF_STATES; ++s) {
        st[s][CH_LF] = ST_START;
        st[s][CH_SPACE] = ST_START;
        st[s][CH_TAB] = ST_START;
        st[s][CH_SCOLON] = ST_START;
        if (sttoch[s] == Character(-1)) {
            continue;
        }
        State S = (State)(s);
        Character C = sttoch[s];
        st[ST_START][C] = S;
        st[ST_IDENTIFIER][C] = S;
        st[ST_INTEGER][C] = S;
        st[S][CH_LETTER] = ST_IDENTIFIER;
        st[S][CH_DIGIT] = ST_INTEGER;
//        st[S][C] = S;
    }
    for(int s = 0; s < SIZEOF_STATES; ++s) {
        st[s][CH_LBRACE] = ST_MLINECMT;
    }
// Identifiers
    st[ST_IDENTIFIER][CH_LETTER] = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_DIGIT]  = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_UNDERS] = ST_IDENTIFIER;
    st[ST_IDENTIFIER][CH_EXPONCHAR] = ST_IDENTIFIER;
// Directives
    st[ST_MLINECMT][CH_DOLLAR] = ST_DIRECTIVE;
// Integer
    st[ST_INTEGER][CH_DIGIT] = ST_INTEGER;
    st[ST_START][CH_DIGIT] = ST_INTEGER;
    st[ST_START][CH_DOLLAR] = ST_HEXINTEGER;
    st[ST_START][CH_PERCENT] = ST_BININTEGER;
    st[ST_BININTEGER][CH_DIGIT] = ST_BININTEGER;
    st[ST_HEXINTEGER][CH_DIGIT] = ST_HEXINTEGER;
    st[ST_HEXINTEGER][CH_LETTER] = ST_HEXINTEGER;
    st[ST_HEXINTEGER][CH_EXPONCHAR] = ST_HEXINTEGER;
// Float
    st[ST_INTEGER][CH_DOT] = ST_FLOAT;
    st[ST_FLOAT][CH_DIGIT] = ST_EXPONFLOAT;
    st[ST_EXPONFLOAT][CH_DIGIT] = ST_EXPONFLOAT;
    st[ST_INTEGER][CH_EXPONCHAR] = ST_EXPONCHAR;
    st[ST_EXPONFLOAT][CH_EXPONCHAR] = ST_EXPONCHAR;
    st[ST_FLOAT][CH_EXPONCHAR] = ST_EXPONCHAR;
    st[ST_EXPONCHAR][CH_PLUS] = ST_EXPONSIGN;
    st[ST_EXPONCHAR][CH_MINUS] = ST_EXPONSIGN;
    st[ST_EXPONCHAR][CH_DIGIT] = ST_EXPON;
    st[ST_EXPONSIGN][CH_DIGIT] = ST_EXPON;
    st[ST_EXPON][CH_DIGIT] = ST_EXPON;
    st[ST_START][CH_EXPONCHAR] = ST_IDENTIFIER;
//
    st[ST_START][CH_LETTER] = ST_IDENTIFIER;
// Assign
    st[ST_COLON][CH_EQUAL] = ST_ASSIGN;
    st[ST_ASSIGN][CH_LETTER] = ST_IDENTIFIER;
    st[ST_ASSIGN][CH_DIGIT] = ST_INTEGER;

    st[ST_PLUS][CH_EQUAL] = ST_PLUSAGN;
    st[ST_MINUS][CH_EQUAL] = ST_MINUSAGN;
    st[ST_SLASH][CH_EQUAL] = ST_FACAGN;
    st[ST_ASTER][CH_EQUAL] = ST_MULAGN;
    st[ST_LTHAN][CH_EQUAL] = ST_LEQ;
    st[ST_LTHAN][CH_GTHAN] = ST_NEQ;
    st[ST_GTHAN][CH_EQUAL] = ST_GEQ;

    fill(st[ST_COMMENT], st[ST_COMMENT] + SIZEOF_CHARACTERS, ST_COMMENT);
    fill(st[ST_MLINECMT], st[ST_MLINECMT] + SIZEOF_CHARACTERS, ST_MLINECMT);
    st[ST_COMMENT][CH_LF] = ST_START;
    st[ST_MLINECMT][CH_RBRACE] = ST_START;
    st[ST_MLINECMT][CH_LF] = ST_MLINECMT;
    return true;
}

bool Scanner::init_fc() {
    auto beg_tk = bind(&Scanner::begin_token, this);
    auto sav_tk = bind(&Scanner::save_token, this);
    auto upd_tk = bind(&Scanner::update_token, this);
    auto upd_intl_tk = bind(&Scanner::update_intliteral_token, this);
    auto thr_er = bind(&Scanner::throw_error, this);
    auto upsav_tk = bind(&Scanner::updatesave_token, this);
    for(int i = 0; i < SIZEOF_STATES; i++) {
        fc[ST_START][i] = sav_tk;
        fc[i][ST_ERROR] = thr_er;
        fc[i][ST_START] = sav_tk;
        fc[i][ST_EOF] = sav_tk;
        fc[i][i] = upd_tk;
        fc[ST_START][i] = beg_tk;
        if (sttoch[i] == Character(-1)) {
            continue;
        }
        fc[ST_IDENTIFIER][i] = sav_tk;
        fc[ST_INTEGER][i] = sav_tk;
        fc[ST_FLOAT][i] = sav_tk;
    }
    fc[ST_START][ST_START] = 0;
    for(int s = 0; s < SIZEOF_STATES; ++s) {
        fc[ST_MLINECMT][s] = 0;
        if (sttoch[s] == Character(-1)) {
            continue;
        }
        State S = (State)(s);
        Character C = sttoch[s];
        fc[S][ST_IDENTIFIER] = sav_tk;
        fc[ST_IDENTIFIER][S] = sav_tk;
        fc[S][ST_INTEGER] = sav_tk;
        fc[ST_INTEGER][S] = sav_tk;
    }
// Assign
    fc[ST_COLON][ST_ASSIGN] = upd_tk;
    fc[ST_ASSIGN][ST_IDENTIFIER] = upsav_tk;
// Digits
    fc[ST_INTEGER][ST_FLOAT] = upd_tk;
    fc[ST_FLOAT][ST_EXPONFLOAT] = upd_tk;
    fc[ST_INTEGER][ST_FLOAT] = upd_tk;
    fc[ST_FLOAT][ST_EXPONFLOAT] = upd_tk;
    fc[ST_EXPONFLOAT][ST_EXPONCHAR] = upd_tk;
    fc[ST_EXPONCHAR][ST_EXPON] = upd_tk;
    fc[ST_INTEGER][ST_EXPONCHAR] = upd_tk;
    fc[ST_EXPONCHAR][ST_EXPONSIGN] = upd_tk;
    fc[ST_EXPONSIGN][ST_EXPON] = upd_tk;
// Commennts
    fc[ST_SLASH][ST_COMMENT] = upd_tk;
    fc[ST_MLINECMT][ST_MLINECMT] = upd_tk;
    fc[ST_MLINECMT][ST_START] = upsav_tk;

    fc[ST_PLUS][ST_PLUSAGN] = upd_tk;
    fc[ST_PLUS][ST_PLUSAGN] = upd_tk;
    fc[ST_MINUS][ST_MINUSAGN] = upd_tk;
    fc[ST_MINUS][ST_MINUSAGN] = upd_tk;
    fc[ST_ASTER][ST_MULAGN] = upd_tk;
    fc[ST_ASTER][ST_MULAGN] = upd_tk;
    fc[ST_SLASH][ST_FACAGN] = upd_tk;
    fc[ST_SLASH][ST_FACAGN] = upd_tk;

    fc[ST_GTHAN][ST_GEQ] = upd_tk;
    fc[ST_LTHAN][ST_LEQ] = upd_tk;
    fc[ST_LTHAN][ST_NEQ] = upd_tk;
    fc[ST_FLOAT][ST_EXPONCHAR] = upd_tk;

    fc[ST_BININTEGER][ST_BININTEGER] = upd_intl_tk;
    fc[ST_HEXINTEGER][ST_HEXINTEGER] = upd_intl_tk;
}

Scanner::Scanner() {

}

bool Scanner::is_hex(char c) {
    return c >= '0' && c <= '9' || c >= 'a' && c <= 'f' || c >= 'A' && c <= 'F';
}

bool Scanner::is_bin(char c) {
    return c == '0' || c == '1';
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
    m_current_token.category = state_to_cat[m_prev_state];
    if (m_prev_state == ST_IDENTIFIER) {
        int is_reserved = Token::is_reserved(m_current_token.raw_value);
        if (is_reserved) {
            m_current_token.category = Token::C_RESERVED;
            m_current_token.subcategory = is_reserved;
        }
    } else {
        m_current_token.subcategory = state_to_subcat[m_prev_state];
    }
    m_tokens.push_back(m_current_token.evaluate());
    m_token_done = true;
    clear_token();
    update_token();
}

void Scanner::update_token() {
    if (m_current_token.position.line == 0 && m_current_token.position.column == 0) {
        m_current_token.position.line = m_line;
        m_current_token.position.column = m_column;
    }
    m_current_token.raw_value.push_back(m_c);
}

void Scanner::update_intliteral_token() {
    if (m_current_token.position.line == 0 && m_current_token.position.column == 0) {
        m_current_token.position.line = m_line;
        m_current_token.position.column = m_column;
    }
    if (m_state == ST_BININTEGER && !is_bin(m_c) || m_state == ST_HEXINTEGER && !is_hex(m_c)) {
        throw_error();
    }
    m_current_token.raw_value.push_back(m_c);
}

void Scanner::clear_token() {
    m_current_token.clear();
}

void Scanner::begin_token() {
    clear_token();
    update_token();
}

void Scanner::updatesave_token() {
    update_token();
    save_token();
}

bool Scanner::eof() {
    return m_file.eof() && m_tokens.empty() || m_eof_returned;
}

void Scanner::throw_error() {
    update_token();
    throw BadToken(m_current_token, stst[m_prev_state], stst[m_state]);
}

Token Scanner::get_next_token() {
    if (m_eof_returned) {
        m_last_token_success = false;
        return Token();
    }
    if (!m_tokens.empty()) {
        Token result = m_tokens.front();
        m_tokens.pop_front();
        m_last_token_success = true;
        return result;
    }
    m_token_done = false;
    while (!m_token_done) {
        string unseparated_chars = "";
        while(unseparated_chars.size() == 0 && !m_file.eof()) {
            getline(m_file, unseparated_chars);
            ++m_line;
        }
        if (unseparated_chars.size() == 0) {
            m_eof_returned = true;
            return Token(m_current_token.position, Token::C_EOF, " ");
        }
        unseparated_chars.push_back('\n');
        for(m_column = 0; m_column < unseparated_chars.size(); m_column++) {
            m_c = unseparated_chars[m_column];
            m_prev_state = m_state;
            m_state = st[m_state][ch[m_c]];
            if (fc[m_prev_state][m_state]) {
                fc[m_prev_state][m_state]();
            } else if (m_state != ST_START || m_prev_state != ST_START) {
                cerr << "There's no action for [" << stst[m_prev_state] << "][" << stst[m_state] << "] on char '" << m_c << "'" << endl;
            }
        }
    }
    if (m_tokens.size() == 0) {
        m_eof_returned = true;
        return Token(m_current_token.position, Token::C_EOF, "[invalid]");
    }
    Token result = m_tokens.front();
    m_tokens.pop_front();
    m_last_token_success = true;
    return result;
}

bool Scanner::last_token_success() const {
    return m_last_token_success;
}

Scanner& operator>>(Scanner& scanner, Token& token) {
    token = scanner.get_next_token();
    return scanner;
}

