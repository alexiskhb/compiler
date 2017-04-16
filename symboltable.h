#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include <map>
#include <string>
#include "types.h"
#include <memory>

class SymTable : public std::map<std::string, size_t> {
public:
	SymTable();
	void add(PSymbol);
	PSymbol operator[](size_t n) {
		return m_symbol_list[n];
	}

	PSymbol operator[](const std::string& s) {
		auto r = this->find(s);
		return r == this->end() ? nullptr : m_symbol_list[r->second];
	}

	size_t size() const {
		return m_symbol_list.size();
	}

	PSymbol back() {
		return m_symbol_list.back();
	}

private:
	std::vector<PSymbol> m_symbol_list;
};

SymTable&  operator<<(SymTable&, PSymbol);
PSymTable& operator<<(PSymTable&, PSymbol);

#endif // SYMBOLTABLE_H
