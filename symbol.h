#ifndef SYMBOL_H
#define SYMBOL_H

#include "types.h"
#include <memory>
#include <string>

template <class T>
std::shared_ptr<T>& operator>>(PSymbol symbol, std::shared_ptr<T>& symbol_derived) {
	symbol_derived = std::dynamic_pointer_cast<T>(symbol);
	return symbol_derived;
}

class Symbol {
public:
	Symbol();
	Symbol(const std::string& name);
	std::string name;
	static bool use_strict;
	virtual std::string str();
	virtual std::string output_str();
};

class SymbolVariable : public Symbol {
public:
	SymbolVariable(const std::string& name, PSymbolType);
	std::string output_str() override;
	PSymbolType type;
};

class SymbolType : public Symbol {
public:
	SymbolType(const std::string& name);
	static PSymbolType max(PSymbolType, PSymbolType);
	static bool is_arithmetic(std::initializer_list<PSymbolType>);
	template <class T>
	static std::shared_ptr<T> equals(const std::initializer_list<PSymbolType>& lst,  std::shared_ptr<T> ptr) {
		for (auto& t: lst) {
			if (!std::dynamic_pointer_cast<T>(t)) {
				return nullptr;
			}
		}
		return ptr;
	}
};

class SymbolTypeInt : public SymbolType {
public:
	SymbolTypeInt(const std::string& name);
};

class SymbolTypeFloat : public SymbolType {
public:
	SymbolTypeFloat(const std::string& name);
};

class SymbolTypeChar : public SymbolType {
public:
	SymbolTypeChar(const std::string& name);
};

class SymbolTypeString : public SymbolType {
public:
	SymbolTypeString(const std::string& name);
};

class SymbolTypePointer : public SymbolType {
public:
	SymbolTypePointer(const std::string& name, PSymbolType);
	PSymbolType type;
};

class SymbolTypeArray : public SymbolType {
public:
	SymbolTypeArray(int low, int high, PSymbolType type);
	int low;
	int high;
	PSymbolType type;
private:

};

class SymbolTypeRecord : public SymbolType {
public:
	SymbolTypeRecord();
	SymbolTypeRecord(const std::string& name);
	PSymTable symtable;
	std::string output_str() override;
private:
	static uint64_t counter;
};

class SymbolConst : public Symbol {
public:
	SymbolConst(const std::string& name);

};

class SymbolProcedure : public Symbol {
public:
	std::string output_str() override;
	SymbolProcedure(const std::string& name);
	PSymTable params;
	PSymTable locals;
};

class SymbolFunction : public SymbolProcedure {
public:
	SymbolFunction(const std::string& name);
	PSymbolType type;
};


#endif // SYMBOL_H
