#include "symboltable.h"
#include "symbol.h"

using namespace std;

SymTable::SymTable() {

}

void SymTable::add(PSymbol symbol) {
	auto result = m_symbol_map.find(symbol->name);
	if (result == m_symbol_map.end()) {
		m_symbol_map.insert({symbol->name, size()});
		this->push_back(symbol);
	} else {
		throw runtime_error("redefenition of symbol <" + symbol->name + ">");
	}
}

unsigned SymTable::bsize() const {
	unsigned result = 0;
	for (PSymbol t: *this) {
		result += t->size();
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
