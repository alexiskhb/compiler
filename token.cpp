#include "token.h"

Token::Token() {

}

Token::Token(Pos _position, Category _category, const std::string& _raw_value, int _subcategory) {
    position = _position;
    category = _category;
    raw_value = _raw_value;
    subcategory = _subcategory;
}
