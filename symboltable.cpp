#include "symboltable.h"
#include "symbol.h"

using namespace std;

SymTable::SymTable() {

}

void SymTable::add(PSymbol symbol) {
	auto result = m_symbol_map.find(symbol->name);
	if (result != m_symbol_map.end()) {
		throw runtime_error("redefenition of symbol <" + symbol->name + ">");
	} else {
		m_symbol_map.insert({symbol->name, size()});
		this->push_back(symbol);
	}
}

SymTable& operator<<(SymTable& st, PSymbol p) {
	st.add(p);
	return st;
}

PSymTable& operator<<(PSymTable& st, PSymbol p) {
	st->add(p);
	return st;
}
