#include "symbol.h"
#include "symboltable.h"

using namespace std;

bool Symbol::use_strict;

PSymbolType SymbolType::max(PSymbolType a, PSymbolType b) {
	if (!SymbolType::is_arithmetic({a, b})) {
		throw runtime_error("arihmetic operation between non-arithmetic variables");
	}
	if (dynamic_pointer_cast<SymbolTypeFloat>(a)) {
		return a;
	}
	if (dynamic_pointer_cast<SymbolTypeFloat>(b)) {
		return b;
	}
	return a;
}

std::string Symbol::str() {
	return name;
}

std::string Symbol::output_str() {
	string result = "* " + to_string((uint64_t)this) + " " + str() + '\n';
	return result;
}

std::string SymbolVariable::output_str() {
	string result = "* " + to_string((uint64_t)this) + " " + str() + "\n";
	result += "^ " + to_string((uint64_t)this) + " " + to_string((uint64_t)type.get()) + '\n';
	result += type->output_str();
	return result;
}

std::string SymbolTypeRecord::output_str() {
	string result = "* " + to_string((uint64_t)this) + " " + str() + "\n";
	SymTable& st = *symtable;
	for (auto& p: st) {
		result += st[p.second]->output_str();
		result += "^ " + to_string((uint64_t)this) + " " + to_string((uint64_t)st[p.second].get()) + '\n';
	}
	return result;
}

std::string SymbolProcedure::output_str() {
	string result = "* " + to_string((uint64_t)this) + " " + str() + "\n";
	if (dynamic_cast<SymbolFunction*>(this)) {
		result += "^ " + to_string((uint64_t)this) + ' ' + to_string((uint64_t)dynamic_cast<SymbolFunction*>(this)->type.get()) + '\n';
		result += dynamic_cast<SymbolFunction*>(this)->type->output_str();
	}
	SymTable& lc = *locals;
	for (auto& p: lc) {
		result += lc[p.second]->output_str();
		result += "^ " + to_string((uint64_t)this) + " " + to_string((uint64_t)lc[p.second].get()) + '\n';
	}
	return result;
}

bool SymbolType::is_arithmetic(std::initializer_list<PSymbolType> ptrs) {
	for (PSymbolType p: ptrs) {
		if (!dynamic_pointer_cast<SymbolTypeInt>(p) && !dynamic_pointer_cast<SymbolTypeFloat>(p)) {
			return false;
		}
	}
	return true;
}

Symbol::Symbol() {

}

Symbol::Symbol(const string& name) :
    name(name) {
}

SymbolType::SymbolType(const string& name) :
	Symbol(name) {
}

SymbolTypePointer::SymbolTypePointer(const string& name, PSymbolType type) :
	SymbolType(name), type(type) {
}

SymbolTypeArray::SymbolTypeArray(int low, int high, PSymbolType type) :
	SymbolType(name), low(low), high(high), type(type) {
}

SymbolVariable::SymbolVariable(const std::string& name, PSymbolType type) :
    Symbol(name), type(type) {
}

SymbolTypeInt::SymbolTypeInt(const std::string& name) :
	SymbolType(name) {
}

SymbolTypeFloat::SymbolTypeFloat(const std::string& name) :
	SymbolType(name) {
}

SymbolTypeChar::SymbolTypeChar(const std::string& name) :
	SymbolType(name) {
}

SymbolTypeString::SymbolTypeString(const std::string& name) :
    SymbolType(name) {
}

uint64_t SymbolTypeRecord::counter = 0;

SymbolTypeRecord::SymbolTypeRecord() :
    SymbolType("$record_" + to_string(++SymbolTypeRecord::counter)) {
	symtable = make_shared<SymTable>();
}

SymbolConst::SymbolConst(const std::string& name) :
	Symbol(name) {
}

SymbolProcedure::SymbolProcedure(const std::string& name) :
	Symbol(name) {
	params = make_shared<SymTable>();
	locals = make_shared<SymTable>();
}

SymbolFunction::SymbolFunction(const std::string& name) :
	SymbolProcedure(name) {
}
