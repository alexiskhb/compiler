#include "token.h"

Token::Token() {

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
}

void Token::evaluate() {

}

bool Token::empty() {
    return raw_value.empty();
}

std::ostream& operator<<(std::ostream& os, const Token& t) {
    return os << t.raw_value << ' ' << '(' <<
                 t.position.line << ':' <<
                 t.position.column << ')';
}
