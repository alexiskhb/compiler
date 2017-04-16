#include "symboltable.h"
#include "symbol.h"

using namespace std;

SymTable::SymTable() {

}

void SymTable::add(PSymbol symbol) {
	auto result = this->find(symbol->name);
	if (result != this->end()) {
		throw runtime_error("redefenition of symbol <" + symbol->name + ">");
	} else {
		insert({symbol->name, m_symbol_list.size()});
		m_symbol_list.push_back(symbol);
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
