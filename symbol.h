#ifndef SYMBOL_H
#define SYMBOL_H

#include "symboltable.h"
#include <memory>

class SymbolType;
class SymTable;

typedef std::shared_ptr<SymbolType> PSymbolType;
typedef std::shared_ptr<SymTable> PSymTable;

class Symbol {
public:
    Symbol();
    std::string name;
};

class SymbolVariable : public Symbol {
public:
    PSymbolType type;
};

class SymbolType : public Symbol {

};

class SymbolTypeInt : public SymbolType {

};

class SymbolTypeFloat : public SymbolType {

};

class SymbolTypeChar : public SymbolType {

};

class SymbolTypePointer : public SymbolType {
    PSymbolType type;
};

class SymbolTypeArray : public SymbolType {
    size_t low;
    size_t high;
    PSymbolType type;
};

class SymbolTypeRecord : public SymbolType {
    PSymTable symtable;
};

class SymbolConst : public Symbol {

};

class SymbolProcedure : public Symbol {
    PSymTable params;
    PSymTable locals;
};

class SymbolFunction : public SymbolProcedure {
    PSymbolType type;
};


#endif // SYMBOL_H
