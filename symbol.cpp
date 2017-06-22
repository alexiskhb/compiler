#include "symbol.h"
#include "symboltable.h"

using namespace std;

bool Symbol::use_strict;
std::string SymbolTypeInt::fml_label = "._fmt_int_";
std::string SymbolTypeFloat::fml_label = "._fmt_float_";

uint64_t SymbolType::counter = 0;

PSymbolType SymbolType::max(PSymbolType a, PSymbolType b) {
	/// float > integer
	if (dynamic_pointer_cast<SymbolTypeFloat>(a)) {
		if (dynamic_pointer_cast<SymbolTypePointer>(b)) {
			return nullptr;
		}
		return a;
	}
	if (dynamic_pointer_cast<SymbolTypeFloat>(b)) {
		if (dynamic_pointer_cast<SymbolTypePointer>(b)) {
			return nullptr;
		}
		return b;
	}
	if (dynamic_pointer_cast<SymbolTypePointer>(a)) {
		return a;
	}
	if (dynamic_pointer_cast<SymbolTypePointer>(b)) {
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
		if (!dynamic_pointer_cast<SymbolTypeInt>(p) && !dynamic_pointer_cast<SymbolTypeFloat>(p) && !dynamic_pointer_cast<SymbolTypePointer>(p)) {
			return false;
		}
	}
	return true;
}

Symbol::Symbol() {

}

Symbol::Symbol(const string& a_name) :
    name(a_name) {
}

SymbolType::SymbolType(const string& a_name) :
	Symbol(a_name) {
}

SymbolTypePointer::SymbolTypePointer(const string& a_name, PSymbolType type) :
	SymbolType(a_name), type(type) {
}

SymbolTypePointer::SymbolTypePointer(PSymbolType type) :
    SymbolType("$pointer_" + type->name + "_" + to_string(++counter)), type(type) {
}

SymbolVariable::SymbolVariable(const std::string& a_name, PSymbolType type) :
    Symbol(a_name), type(type) {
}

SymbolConst::SymbolConst(const std::string& a_name, PSymbolType type) :
    SymbolVariable(a_name, type) {
}

SymbolConstInt::SymbolConstInt(const std::string& a_name, PSymbolType type, int64_t a_value) :
    SymbolConst(a_name, type), value(a_value) {
}

SymbolConstFloat::SymbolConstFloat(const std::string& a_name, PSymbolType type, double a_value) :
    SymbolConst(a_name, type), value(a_value) {
}

SymbolTypeInt::SymbolTypeInt(const std::string& a_name) :
	SymbolType(a_name) {
}

SymbolTypeFloat::SymbolTypeFloat(const std::string& a_name) :
	SymbolType(a_name) {
}

SymbolTypeChar::SymbolTypeChar(const std::string& a_name) :
	SymbolType(a_name) {
}

SymbolTypeString::SymbolTypeString(const std::string& a_name) :
    SymbolType(a_name) {
}

SymbolTypeArray::SymbolTypeArray() :
    SymbolType("$array_" + to_string(++SymbolType::counter)) {
}

SymbolTypeArray::SymbolTypeArray(const std::string& a_name, const SymbolTypeArray& sym) :
    SymbolType(a_name) {
	this->bounds = sym.bounds;
	this->type = sym.type;
}

SymbolTypeRecord::SymbolTypeRecord() :
    SymbolType("$record_" + to_string(++SymbolType::counter)) {
	symtable = make_shared<SymTable>();
}

SymbolTypeRecord::SymbolTypeRecord(const string& a_name) :
    SymbolType(a_name) {
	symtable = make_shared<SymTable>();
}

SymbolTypeProc::SymbolTypeProc() :
    SymbolType("$procedure_" + to_string(SymbolType::counter)) {
	proc = make_shared<SymbolProcedure>("$procedure_" + to_string(SymbolType::counter));
	++SymbolType::counter;
}

SymbolTypeProc::SymbolTypeProc(const string& a_name, PSymbolProcedure a_proc) :
    SymbolType(a_name), proc(a_proc) {
}

SymbolTypeProc::SymbolTypeProc(PSymbolProcedure a_proc) :
    SymbolType("$procedure_" + to_string(++SymbolType::counter)), proc(a_proc) {
}

SymbolTypeFunc::SymbolTypeFunc() :
    SymbolType("$function_" + to_string(SymbolType::counter)) {
	func = make_shared<SymbolFunction>("$function_" + to_string(SymbolType::counter));
	++SymbolType::counter;
}

SymbolTypeFunc::SymbolTypeFunc(const string& a_name, PSymbolFunction a_func) :
    SymbolType(a_name), func(a_func) {
}

SymbolTypeFunc::SymbolTypeFunc(PSymbolFunction a_func) :
    SymbolType("$function_" + to_string(++SymbolType::counter)), func(a_func) {
}

SymbolProcedure::SymbolProcedure(const std::string& a_name) :
    Symbol(a_name) {
	params = make_shared<SymTable>();
	locals = make_shared<SymTable>();
}

SymbolFunction::SymbolFunction(const std::string& a_name) :
    SymbolProcedure(a_name) {
}

uint Symbol::size() const {
	return 0;
}

uint SymbolVariable::size() const {
	return type->size();
}

uint SymbolTypePointer::size() const {
	return 8;
}

uint SymbolTypeArray::size() const {
	uint result = 1;
	for (pair<int, int> p: this->bounds) {
		result *= (p.second - p.first + 1)*this->type->size();
	}
	return result;
}

uint SymbolTypeInt::size() const {
	return 8;
}

uint SymbolTypeFloat::size() const {
	return 8;
}

uint SymbolTypeChar::size() const {
	return 1;
}

uint SymbolTypeString::size() const {
	return 255;
}

uint SymbolTypeRecord::size() const {
	return symtable->bsize();
}

void SymbolType::gen_write(AsmCode&) {}
void SymbolType::gen_declare(AsmCode&, const string&) {}

void SymbolTypeInt::gen_write(AsmCode& ac) {
	ac << AsmCmd2{LEAQ, AsmVar{SymbolTypeInt::fml_label}, RDI}
	   << AsmCmd1{POPQ, RSI}
	   << AsmCmd1{CALL, PRINTF};
}

void SymbolTypeFloat::gen_write(AsmCode& ac) {
	ac << AsmCmd2{LEAQ, AsmVar{SymbolTypeFloat::fml_label}, RDI}
	   << AsmCmd1{POPQ, RAX}
	   << AsmCmd2{MOVQ, RAX, XMM0}
	   << AsmCmd2{MOVQ, (int64_t)1, RAX}
	   << AsmCmd1{CALL, PRINTF};
}

void SymbolTypeRecord::gen_declare(AsmCode& ac, const std::string& a_name) {
	ac << AsmComment{"record " + a_name};
}

void SymbolTypeArray::gen_declare(AsmCode& ac, const std::string& a_name) {
	ac.add_data(make_shared<AsmVarArray>(a_name, this->type->size(), this->bounds));
}

void SymbolTypeFloat::gen_declare(AsmCode& ac, const std::string& a_name) {
	ac.add_data(make_shared<AsmVarFloat>(a_name));
}

void SymbolTypePointer::gen_declare(AsmCode& ac, const std::string& a_name) {
	ac.add_data(make_shared<AsmVarInt>(a_name));
}

void SymbolTypeInt::gen_declare(AsmCode& ac, const string& a_name) {
	ac.add_data(make_shared<AsmVarInt>(a_name));
}

void SymbolTypeInt::  gen_typecast(AsmCode& ac, PSymbolType symt) const {symt->gen_typecast(ac, *this);}
void SymbolTypeFloat::gen_typecast(AsmCode& ac, PSymbolType symt) const {symt->gen_typecast(ac, *this);}
void SymbolType::gen_typecast(AsmCode&, PSymbolType) const {}

void SymbolType::gen_typecast(AsmCode&, const SymbolTypeFloat&) const {}
void SymbolType::gen_typecast(AsmCode&, const SymbolTypeInt&)   const {}

/// float to int
void SymbolTypeInt::gen_typecast(AsmCode& ac, const SymbolTypeFloat& symt) const {
	ac << AsmCmd1{POPQ, RAX}
	   << AsmCmd2{MOVQ, RAX, XMM0}
	   << AsmCmd2{CVTSD2SI, XMM0, RAX}
	   << AsmCmd1{PUSHQ, RAX};
}

/// int to float
void SymbolTypeFloat::gen_typecast(AsmCode& ac, const SymbolTypeInt& symt) const {
	ac << AsmCmd1{POPQ, RAX}
	   << AsmCmd2{CVTSI2SD, RAX, XMM0}
	   << AsmCmd2{MOVQ, XMM0, RAX}
	   << AsmCmd1{PUSHQ, RAX};
}


bool SymbolType       ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeInt    ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeFloat  ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeChar   ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeString ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypePointer::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeArray  ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeRecord ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeProc   ::equals(PSymbolType symt) const {return symt->equals(*this);}
bool SymbolTypeFunc   ::equals(PSymbolType symt) const {return symt->equals(*this);}

bool SymbolType::equals(const SymbolType       &) const {return false;}
bool SymbolType::equals(const SymbolTypeInt    &) const {return false;}
bool SymbolType::equals(const SymbolTypeFloat  &) const {return false;}
bool SymbolType::equals(const SymbolTypeChar   &) const {return false;}
bool SymbolType::equals(const SymbolTypeString &) const {return false;}
bool SymbolType::equals(const SymbolTypePointer&) const {return false;}
bool SymbolType::equals(const SymbolTypeArray  &) const {return false;}
bool SymbolType::equals(const SymbolTypeRecord &) const {return false;}
bool SymbolType::equals(const SymbolTypeProc   &) const {return false;}
bool SymbolType::equals(const SymbolTypeFunc   &) const {return false;}

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

bool SymbolTypeProc::equals(const SymbolTypeProc& sym) const {
	if (this->proc->params->size() != sym.proc->params->size()) {
		return false;
	}
	for (int i = 0; i < this->proc->params->size(); i++) {
		PSymbolVariable v1 = dynamic_pointer_cast<SymbolVariable>(this->proc->params->at(i));
		PSymbolVariable v2 = dynamic_pointer_cast<SymbolVariable>(sym.proc->params->at(i));
		if (v1->type != v2->type) {
			return false;
		}
	}
	return true;
}

bool SymbolTypeFunc::equals(const SymbolTypeFunc& sym) const {
	if (this->func->params->size() != sym.func->params->size()) {
		return false;
	}
	for (int i = 0; i < this->func->params->size(); i++) {
		PSymbolVariable v1 = dynamic_pointer_cast<SymbolVariable>(this->func->params->at(i));
		PSymbolVariable v2 = dynamic_pointer_cast<SymbolVariable>(sym.func->params->at(i));
		if (v1->type != v2->type) {
			return false;
		}
	}
	return this->func->type == sym.func->type;
}

bool operator==(PSymbolType a, PSymbolType b) {
	return a->equals(b);
}

bool operator!=(PSymbolType a, PSymbolType b) {
	return !(a == b);
}




