#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <fstream>
#include <iostream>
#include "token.h"
#include <vector>
#include <deque>

class Scanner
{
public:
    Scanner();
    Scanner(const std::string& filename);
    bool is_open() const;
    Token get_next_token();
    void open(const std::string& filename);
private:
    void save_token();
    std::ifstream m_file;
    std::deque<Token> m_tokens;
    std::string m_current_token;
};

#endif // SCANNER_H
