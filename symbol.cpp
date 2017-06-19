#include "symbol.h"
#include "symboltable.h"

using namespace std;

bool Symbol::use_strict;
std::string SymbolTypeInt::fml_label = "._fmt_int_";
std::string SymbolTypeFloat::fml_label = "._fmt_float_";
std::string var_prefix = ".__";

uint64_t SymbolTypeRecord::counter = 0;
uint64_t SymbolTypeArray::counter = 0;
uint64_t SymbolTypePointer::counter = 0;

PSymbolType SymbolType::max(PSymbolType a, PSymbolType b) {
	/// float > integer
	if (dynamic_pointer_cast<SymbolTypeFloat>(a)) {
		return a;
	}
	if (dynamic_pointer_cast<SymbolTypeFloat>(b)) {
		return b;
	}
	return a;
}

PSymbolType SymbolType::notype() {
	static PSymbolType _notype = make_shared<SymbolType>("VOID");
	return _notype;
}

std::string Symbol::str() const {
	return name;
}

std::string Symbol::output_str() const {
	string result = "* " + to_string((uint64_t)this) + " " + str() + '\n';
	return result;
}

std::string SymbolVariable::output_str() const {
	string result = "* " + to_string((uint64_t)this) + " " + str() + "\n";
	result += "^ " + to_string((uint64_t)this) + " " + to_string((uint64_t)type.get()) + '\n';
	result += type->output_str();
	return result;
}

std::string SymbolTypeRecord::output_str() const {
	string result = "* " + to_string((uint64_t)this) + " " + str() + "\n";
	SymTable& st = *symtable;
	for (PSymbol p: st) {
		result += p->output_str();
		result += "^ " + to_string((uint64_t)this) + " " + to_string((uint64_t)p.get()) + '\n';
	}
	return result;
}

std::string SymbolProcedure::output_str() const {
	string result = "* " + to_string((uint64_t)this) + " " + str() + "\n";
	if (dynamic_cast<const SymbolFunction*>(this)) {
		result += "^ " + to_string((uint64_t)this) + ' ' + to_string((uint64_t)dynamic_cast<const SymbolFunction*>(this)->type.get()) + '\n';
		result += dynamic_cast<const SymbolFunction*>(this)->type->output_str();
	}
	SymTable& lc = *locals;
	for (PSymbol p: lc) {
		result += p->output_str();
		result += "^ " + to_string((uint64_t)this) + " " + to_string((uint64_t)p.get()) + '\n';
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

SymbolTypePointer::SymbolTypePointer(PSymbolType type) :
    SymbolType("$pointer_" + type->name + "_" + to_string(counter++)), type(type) {
}

SymbolVariable::SymbolVariable(const std::string& name, PSymbolType type) :
    Symbol(name), type(type) {
}

SymbolConst::SymbolConst(const std::string& name, PSymbolType type) :
    SymbolVariable(name, type) {
}

SymbolConstInt::SymbolConstInt(const std::string& name, PSymbolType type, int64_t a_value) :
    SymbolConst(name, type), value(a_value) {
}

SymbolConstFloat::SymbolConstFloat(const std::string& name, PSymbolType type, double a_value) :
    SymbolConst(name, type), value(a_value) {
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

SymbolTypeArray::SymbolTypeArray() :
    SymbolType("$array_" + to_string(++SymbolTypeArray::counter)) {
}

SymbolTypeArray::SymbolTypeArray(const std::string& name, const SymbolTypeArray& sym) :
    SymbolType(name) {
	this->bounds = sym.bounds;
	this->type = sym.type;
}

SymbolTypeRecord::SymbolTypeRecord() :
    SymbolType("$record_" + to_string(++SymbolTypeRecord::counter)) {
	symtable = make_shared<SymTable>();
}

SymbolTypeRecord::SymbolTypeRecord(const string& name) :
    SymbolType(name) {
	symtable = make_shared<SymTable>();
}

SymbolProcedure::SymbolProcedure(const std::string& name) :
	Symbol(name) {
	params = make_shared<SymTable>();
	locals = make_shared<SymTable>();
}

SymbolFunction::SymbolFunction(const std::string& name) :
	SymbolProcedure(name) {
}

unsigned Symbol::size() const {
	return 0;
}

unsigned SymbolVariable::size() const {
	return type->size();
}

unsigned SymbolTypePointer::size() const {
	return 8;
}

unsigned SymbolTypeArray::size() const {
	return 0;
//	return (high - low + 1)*type->size();
}

unsigned SymbolTypeInt::size() const {
	return 8;
}

unsigned SymbolTypeFloat::size() const {
	return 8;
}

unsigned SymbolTypeChar::size() const {
	return 1;
}

unsigned SymbolTypeString::size() const {
	return 255;
}

unsigned SymbolTypeRecord::size() const {
	return symtable->bsize();
}

void SymbolType::write(AsmCode&) {}
void SymbolType::declare(AsmCode&, const string&) {}

void SymbolTypeInt::write(AsmCode& ac) {
	ac << AsmCmd2{LEAQ, AsmVar{SymbolTypeInt::fml_label}, RDI}
	   << AsmCmd1{POPQ, RSI}
	   << AsmCmd1{CALL, PRINTF};
}

void SymbolTypeFloat::write(AsmCode& ac) {
	ac << AsmCmd2{LEAQ, AsmVar{SymbolTypeFloat::fml_label}, RDI}
	   << AsmCmd1{POPQ, RAX}
	   << AsmCmd2{MOVQ, RAX, XMM0}
	   << AsmCmd2{MOVQ, (int64_t)1, RAX}
	   << AsmCmd1{CALL, PRINTF};
}

void SymbolTypeRecord::declare(AsmCode& ac, const std::string& a_name) {
	ac << AsmComment{"record " + a_name};
}

void SymbolTypeInt::declare(AsmCode& ac, const string& a_name) {
	ac.add_data(make_shared<AsmVarInt>(var_prefix + a_name));
}

bool SymbolType       ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeInt    ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeFloat  ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeChar   ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeString ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypePointer::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeArray  ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeRecord ::equals(PSymbolType symt) const {return symt->equals(*this);}

bool SymbolType::equals(const SymbolType       &) const {return false;}
bool SymbolType::equals(const SymbolTypeInt    &) const {return false;}
bool SymbolType::equals(const SymbolTypeFloat  &) const {return false;}
bool SymbolType::equals(const SymbolTypeChar   &) const {return false;}
bool SymbolType::equals(const SymbolTypeString &) const {return false;}
bool SymbolType::equals(const SymbolTypePointer&) const {return false;}
bool SymbolType::equals(const SymbolTypeArray  &) const {return false;}
bool SymbolType::equals(const SymbolTypeRecord &) const {return false;}

bool SymbolTypeInt   ::equals(const SymbolTypeInt   &) const {return true;}
bool SymbolTypeFloat ::equals(const SymbolTypeFloat &) const {return true;}
bool SymbolTypeChar  ::equals(const SymbolTypeChar  &) const {return true;}
bool SymbolTypeString::equals(const SymbolTypeString&) const {return true;}

bool SymbolTypePointer::equals(const SymbolTypePointer& sym) const {
	return this->type == sym.type;
}

bool SymbolTypeArray::equals(const SymbolTypeArray& sym) const {
	return this->type == sym.type && this->bounds == sym.bounds;
}

bool SymbolTypeRecord::equals(const SymbolTypeRecord& sym) const {
	return this->symtable == sym.symtable;
}

bool operator==(PSymbolType a, PSymbolType b) {
	return a->equals(b);
}

bool operator!=(PSymbolType a, PSymbolType b) {
	return !(a == b);
}




