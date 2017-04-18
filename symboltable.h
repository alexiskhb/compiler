#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include <map>
#include <string>
#include "types.h"
#include <memory>

class SymTable : public std::vector<PSymbol> {
public:
	SymTable();
	void add(PSymbol);
	PSymbol operator[](size_t n) {
		return this->at(n);
	}

	PSymbol operator[](const std::string& s) {
		auto r = m_symbol_map.find(s);
		return r == m_symbol_map.end() ? nullptr : this->at(r->second);
	}

//	size_t size() const {
//		return m_symbol_list.size();
//	}

//	PSymbol back() {
//		return m_symbol_list.back();
//	}

private:
//	std::vector<PSymbol> m_symbol_list;
	std::map<std::string, size_t> m_symbol_map;
};

SymTable&  operator<<(SymTable&, PSymbol);
PSymTable& operator<<(PSymTable&, PSymbol);

#endif // SYMBOLTABLE_H
