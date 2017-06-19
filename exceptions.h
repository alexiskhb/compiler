#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include "types.h"

class ParseError {
public:
	ParseError(const Pos& pos, const std::string& msg) :
	    m_msg("at " + (std::string)pos + ": " + msg), m_pos(pos) {
	}
	std::string msg() const {
		return m_msg;
	}
	Pos pos() const {
		return m_pos;
	}
protected:
	std::string m_msg;
	Pos m_pos;
};

class SymbolNotFound : public ParseError {
public:
	SymbolNotFound(const Pos& pos, const std::string& symname) :
	    ParseError(pos, "symbol '" + symname + "' not found")
	{}
};


#endif // EXCEPTIONS_H
