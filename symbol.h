#ifndef SYMBOL_H
#define SYMBOL_H

#include "types.h"
#include <memory>
#include <string>
#include "asmcode.h"

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
	virtual std::string str() const;
	virtual std::string output_str() const;
	/// Size in bytes
	virtual unsigned size() const;
};

class SymbolVariable : public Symbol {
public:
	SymbolVariable(const std::string& name, PSymbolType);
	std::string output_str() const override;
	PSymbolType type;
	unsigned size() const override;
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
	virtual void write(AsmCode&);
	virtual void declare(AsmCode&, const std::string&);

	virtual bool equals(PSymbolType) const;
	virtual bool equals(const SymbolType&) const;
	virtual bool equals(const SymbolTypeInt&) const;
	virtual bool equals(const SymbolTypeFloat&) const;
	virtual bool equals(const SymbolTypeChar&) const;
	virtual bool equals(const SymbolTypeString&) const;
	virtual bool equals(const SymbolTypePointer&) const;
	virtual bool equals(const SymbolTypeArray&) const;
	virtual bool equals(const SymbolTypeRecord&) const;
};

class SymbolTypeInt : public SymbolType {
public:
	SymbolTypeInt(const std::string& name);
	unsigned size() const override;
	void write(AsmCode&) override;
	void declare(AsmCode&, const std::string&) override;
	static std::string fml_label;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeInt&) const override;
};

class SymbolTypeFloat : public SymbolType {
public:
	SymbolTypeFloat(const std::string& name);
	static std::string fml_label;
	void write(AsmCode&) override;
	unsigned size() const override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeFloat&) const override;
};

class SymbolTypeChar : public SymbolType {
public:
	SymbolTypeChar(const std::string& name);
	unsigned size() const override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeChar&) const override;
};

class SymbolTypeString : public SymbolType {
public:
	SymbolTypeString(const std::string& name);
	unsigned size() const override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeString&) const override;
};

class SymbolTypePointer : public SymbolType {
public:
	SymbolTypePointer(const std::string& name, PSymbolType);
	unsigned size() const override;
	PSymbolType type;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypePointer&) const override;
};

class SymbolTypeArray : public SymbolType {
public:
	SymbolTypeArray();
	SymbolTypeArray(const std::string& name, const SymbolTypeArray&);
	unsigned size() const override;
	std::vector<std::pair<int, int>> bounds;
	PSymbolType type;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeArray&) const override;
private:
	static uint64_t counter;
};

class SymbolTypeRecord : public SymbolType {
public:
	SymbolTypeRecord();
	SymbolTypeRecord(const std::string& name);
	unsigned size() const override;
	PSymTable symtable;
	std::string output_str() const override;
	void declare(AsmCode&, const std::string&) override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeRecord&) const override;
private:
	static uint64_t counter;
};

class SymbolConst : public Symbol {
public:
	SymbolConst(const std::string& name);
};

class SymbolProcedure : public Symbol {
public:
	std::string output_str() const override;
	SymbolProcedure(const std::string& name);
	PSymTable params;
	PSymTable locals;
};

class SymbolFunction : public SymbolProcedure {
public:
	SymbolFunction(const std::string& name);
	PSymbolType type;
};

bool operator==(PSymbolType, PSymbolType);


#endif // SYMBOL_H
