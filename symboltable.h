#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include <map>
#include <string>
#include "types.h"

class SymTable {
public:
	SymTable();
	void add(PNodeIdentifier);
private:
	std::vector<PSymbol> m_symbol_list;
	std::map<std::string, size_t> m_symbol_map;
};

#endif // SYMBOLTABLE_H
