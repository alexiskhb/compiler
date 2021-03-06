#ifndef SYMBOL_H
#define SYMBOL_H

#include "types.h"
#include <memory>
#include <string>
#include "asmcode.h"
#include "exceptions.h"

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
	virtual uint size() const;
};

class SymbolVariable : public Symbol {
public:
	SymbolVariable(const std::string& name, PSymbolType);
	std::string output_str() const override;
	PSymbolType type;
	uint size() const override;
};

class SymbolConst : public SymbolVariable {
public:
	SymbolConst(const std::string& name, PSymbolType);
};

class SymbolConstInt : public SymbolConst {
public:
	SymbolConstInt(const std::string& name, PSymbolType, int64_t);
	int64_t value;
};

class SymbolConstFloat : public SymbolConst {
public:
	SymbolConstFloat(const std::string& name, PSymbolType, double);
	double value;
};

class SymbolType : public Symbol {
public:
	SymbolType(const std::string& name);
	static PSymbolType max(PSymbolType, PSymbolType);
	static PSymbolType notype();
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
	virtual void gen_write(AsmCode&);
	virtual void gen_declare(AsmCode&, const std::string&);

	virtual void gen_typecast(AsmCode&, PSymbolType) const;
	virtual void gen_typecast(AsmCode&, const SymbolTypeFloat&) const;
	virtual void gen_typecast(AsmCode&, const SymbolTypeInt&) const;

	virtual bool equals(PSymbolType) const;
	virtual bool equals(const SymbolType&) const;
	virtual bool equals(const SymbolTypeInt&) const;
	virtual bool equals(const SymbolTypeFloat&) const;
	virtual bool equals(const SymbolTypeChar&) const;
	virtual bool equals(const SymbolTypeString&) const;
	virtual bool equals(const SymbolTypePointer&) const;
	virtual bool equals(const SymbolTypeArray&) const;
	virtual bool equals(const SymbolTypeRecord&) const;
	virtual bool equals(const SymbolTypeProc&) const;
	virtual bool equals(const SymbolTypeFunc&) const;
protected:
	static uint64_t counter;
};

class SymbolTypeInt : public SymbolType {
public:
	SymbolTypeInt(const std::string& name);
	uint size() const override;
	void gen_write(AsmCode&) override;
	void gen_declare(AsmCode&, const std::string&) override;
	static std::string fml_label;

	void gen_typecast(AsmCode&, PSymbolType) const override;
	void gen_typecast(AsmCode&, const SymbolTypeFloat&) const override; /// float to int

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeInt&) const override;
};

class SymbolTypeFloat : public SymbolType {
public:
	SymbolTypeFloat(const std::string& name);
	static std::string fml_label;
	void gen_write(AsmCode&) override;
	void gen_declare(AsmCode&, const std::string&) override;
	uint size() const override;

	void gen_typecast(AsmCode&, PSymbolType) const override;
	void gen_typecast(AsmCode&, const SymbolTypeInt&) const override; /// int to float

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeFloat&) const override;
};

class SymbolTypeChar : public SymbolType {
public:
	SymbolTypeChar(const std::string& name);
	uint size() const override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeChar&) const override;
};

class SymbolTypeString : public SymbolType {
public:
	SymbolTypeString(const std::string& name);
	uint size() const override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeString&) const override;
};

class SymbolTypePointer : public SymbolType {
public:
	SymbolTypePointer(const std::string& name, PSymbolType);
	SymbolTypePointer(PSymbolType);
	uint size() const override;
	void gen_declare(AsmCode&, const std::string&) override;
	PSymbolType type;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypePointer&) const override;
};

class SymbolTypeArray : public SymbolType {
public:
	SymbolTypeArray();
	SymbolTypeArray(const std::string& name, const SymbolTypeArray&);
	uint size() const override;
	void gen_declare(AsmCode&, const std::string&) override;
	std::vector<std::pair<int, int>> bounds;
	PSymbolType type;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeArray&) const override;
};

class SymbolTypeRecord : public SymbolType {
public:
	SymbolTypeRecord();
	SymbolTypeRecord(const std::string& name);
	uint size() const override;
	void gen_declare(AsmCode&, const std::string&) override;
	PSymTable symtable;
	std::string output_str() const override;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeRecord&) const override;
};

class SymbolTypeProc : public SymbolType {
public:
	SymbolTypeProc();
	SymbolTypeProc(const std::string&, PSymbolProcedure);
	SymbolTypeProc(PSymbolProcedure);
	PSymbolProcedure proc;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeProc&) const override;
};

class SymbolTypeFunc : public SymbolType {
public:
	SymbolTypeFunc();
	SymbolTypeFunc(const std::string&, PSymbolFunction);
	SymbolTypeFunc(PSymbolFunction);
	PSymbolFunction func;

	bool equals(PSymbolType) const override;
	bool equals(const SymbolTypeFunc&) const override;
};

class SymbolProcedure : public Symbol {
public:
	std::string output_str() const override;
	SymbolProcedure(const std::string& name);
	PSymTable params;
	PSymTable locals;
	std::vector<bool> is_nth_var;
};

class SymbolFunction : public SymbolProcedure {
public:
	SymbolFunction(const std::string& name);
	PSymbolType type;
};

bool operator==(PSymbolType, PSymbolType);
bool operator!=(PSymbolType, PSymbolType);


#endif // SYMBOL_H
