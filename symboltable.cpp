#include "symboltable.h"
#include "symbol.h"
#include "scanner.h"

using namespace std;

SymTable::SymTable() {

}

void SymTable::add(PSymbol symbol) {
	auto result = m_symbol_map.find(symbol->name);
	if (result == m_symbol_map.end()) {
		m_symbol_map.insert({symbol->name, size()});
		this->push_back(symbol);
	} else {
		throw ParseError(Scanner::current_position(), "redefenition of symbol \"" + symbol->name + "\"");
	}
}

uint SymTable::sizeb() const {
	uint result = 0;
	for (PSymbol t: *this) {
		result += t->size();
	}
	return result;
}

uint SymTable::offsetb(const std::string& s) {
	uint result = 0, i = 0;
	while ((*this)[i]->name != s) {
		result += (*this)[i]->size();
		++i;
	}
	return result;
}

SymTable& operator<<(SymTable& st, PSymbol p) {
	st.add(p);
	return st;
}

PSymTable& operator<<(PSymTable& st, PSymbol p) {
	st->add(p);
	return st;
}
