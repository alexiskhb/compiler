#ifndef TYPES_H
#define TYPES_H

#include <memory>
#include <string>

class Symbol;
class SymbolVariable;
class SymbolType;
class SymbolTypeInt;
class SymbolTypeFloat;
class SymbolTypeChar;
class SymbolTypeString;
class SymbolTypePointer;
class SymbolTypeArray;
class SymbolTypeRecord;
class SymbolTypeProc;
class SymbolTypeFunc;
class SymbolConst;
class SymbolConstInt;
class SymbolConstFloat;
class SymbolProcedure;
class SymbolFunction;

class SymTable;
typedef std::shared_ptr<SymTable> PSymTable;

typedef std::shared_ptr<Symbol> PSymbol;
typedef std::shared_ptr<SymbolVariable> PSymbolVariable;
typedef std::shared_ptr<SymbolType> PSymbolType;
typedef std::shared_ptr<SymbolTypeInt> PSymbolTypeInt;
typedef std::shared_ptr<SymbolTypeFloat> PSymbolTypeFloat;
typedef std::shared_ptr<SymbolTypeChar> PSymbolTypeChar;
typedef std::shared_ptr<SymbolTypeString> PSymbolTypeString;
typedef std::shared_ptr<SymbolTypePointer> PSymbolTypePointer;
typedef std::shared_ptr<SymbolTypeArray> PSymbolTypeArray;
typedef std::shared_ptr<SymbolTypeRecord> PSymbolTypeRecord;
typedef std::shared_ptr<SymbolTypeProc> PSymbolTypeProc;
typedef std::shared_ptr<SymbolTypeFunc> PSymbolTypeFunc;
typedef std::shared_ptr<SymbolConst> PSymbolConst;
typedef std::shared_ptr<SymbolConstInt> PSymbolConstInt;
typedef std::shared_ptr<SymbolConstFloat> PSymbolConstFloat;
typedef std::shared_ptr<SymbolProcedure> PSymbolProcedure;
typedef std::shared_ptr<SymbolFunction> PSymbolFunction;

class Node;
class NodeSeparated;
class NodeExpression;
class NodeInteger;
class NodeEof;
class NodeFloat;
class NodeString;
class NodeIdentifier;
class NodeBinaryOperator;
class NodeActualParameters;
class NodeUnaryOperator;
class NodeArrayAccess;
class NodeRecordAccess;
class NodeFormalParameterSection;
class NodeType;
class NodeInitializer;

typedef std::shared_ptr<Node> PNode;
typedef std::shared_ptr<NodeSeparated> PNodeSeparated;
typedef std::shared_ptr<NodeExpression> PNodeExpression;
typedef std::shared_ptr<NodeInteger> PNodeInteger;
typedef std::shared_ptr<NodeEof> PNodeEof;
typedef std::shared_ptr<NodeFloat> PNodeFloat;
typedef std::shared_ptr<NodeString> PNodeString;
typedef std::shared_ptr<NodeIdentifier> PNodeIdentifier;
typedef std::shared_ptr<NodeBinaryOperator> PNodeBinaryOperator;
typedef std::shared_ptr<NodeActualParameters> PNodeActualParameters;
typedef std::shared_ptr<NodeUnaryOperator> PNodeUnaryOperator;
typedef std::shared_ptr<NodeArrayAccess> PNodeArrayAccess;
typedef std::shared_ptr<NodeRecordAccess> PNodeRecordAccess;
typedef std::shared_ptr<NodeFormalParameterSection> PNodeFormalParameterSection;
typedef std::shared_ptr<NodeType> PNodeType;
typedef std::shared_ptr<NodeInitializer> PNodeInitializer;

class NodeProgram;
class NodeStmt;
class NodeStmtIf;
class NodeStmtWhile;
class NodeStmtAssign;
class NodeStmtConst;
class NodeStmtRepeat;
class NodeStmtVar;
class NodeStmtFor;
class NodeStmtProcedure;
class NodeStmtFunction;
class NodeTypeRecord;
class NodeTypeArray;
class NodeTypeProc;
class NodeTypeFunc;
class NodeStmtType;
class NodeStmtBlock;
class NodeStmtBreak;
class NodeStmtContinue;
class NodeVarDeclarationUnit;
class NodeTypeDeclarationUnit;
class NodeVariable;
class NodeConstant;
class NodeConstantInt;
class NodeConstantFloat;

class NodeExprStmtFunctionCall;

typedef std::shared_ptr<NodeProgram> PNodeProgram;
typedef std::shared_ptr<NodeStmt> PNodeStmt;
typedef std::shared_ptr<NodeStmtIf> PNodeStmtIf;
typedef std::shared_ptr<NodeStmtWhile> PNodeStmtWhile;
typedef std::shared_ptr<NodeStmtAssign> PNodeStmtAssign;
typedef std::shared_ptr<NodeStmtConst> PNodeStmtConst;
typedef std::shared_ptr<NodeStmtRepeat> PNodeStmtRepeat;
typedef std::shared_ptr<NodeStmtVar> PNodeStmtVar;
typedef std::shared_ptr<NodeStmtFor> PNodeStmtFor;
typedef std::shared_ptr<NodeStmtProcedure> PNodeStmtProcedure;
typedef std::shared_ptr<NodeStmtFunction> PNodeStmtFunction;
typedef std::shared_ptr<NodeTypeRecord> PNodeTypeRecord;
typedef std::shared_ptr<NodeTypeArray> PNodeTypeArray;
typedef std::shared_ptr<NodeTypeProc> PNodeTypeProc;
typedef std::shared_ptr<NodeTypeFunc> PNodeTypeFunc;
typedef std::shared_ptr<NodeStmtType> PNodeStmtType;
typedef std::shared_ptr<NodeStmtBlock> PNodeStmtBlock;
typedef std::shared_ptr<NodeStmtBreak> PNodeStmtBreak;
typedef std::shared_ptr<NodeStmtContinue> PNodeStmtContinue;
typedef std::shared_ptr<NodeVarDeclarationUnit> PNodeVarDeclarationUnit;
typedef std::shared_ptr<NodeTypeDeclarationUnit> PNodeTypeDeclarationUnit;
typedef std::shared_ptr<NodeVariable> PNodeVariable;
typedef std::shared_ptr<NodeConstant> PNodeConstant;
typedef std::shared_ptr<NodeConstantInt> PNodeConstantInteger;
typedef std::shared_ptr<NodeConstantFloat> PNodeConstantFloat;

typedef std::shared_ptr<NodeExprStmtFunctionCall> PNodeExprStmtFunctionCall;

class AsmOperand;
class AsmOperandReg;
class AsmOperandImm;
class AsmOperandOfffset;
class AsmOperandIndirect;
class AsmCode;
class AsmCmd;
class AsmCmd0;
class AsmCmd1;
class AsmCmd2;
class AsmComment;
class AsmVar;
class AsmVarString;
class AsmLabel;

typedef std::shared_ptr<AsmOperand> PAsmOperand; 
typedef std::shared_ptr<AsmOperandReg> PAsmOperandReg; 
typedef std::shared_ptr<AsmOperandImm> PAsmOperandImm; 
typedef std::shared_ptr<AsmOperandOfffset> PAsmOperandOfffset; 
typedef std::shared_ptr<AsmOperandIndirect> PAsmOperandIndirect; 
typedef std::shared_ptr<AsmCode> PAsmCode; 
typedef std::shared_ptr<AsmCmd> PAsmCmd; 
typedef std::shared_ptr<AsmCmd0> PAsmCmd0; 
typedef std::shared_ptr<AsmCmd1> PAsmCmd1; 
typedef std::shared_ptr<AsmCmd2> PAsmCmd2; 
typedef std::shared_ptr<AsmComment> PAsmComment; 
typedef std::shared_ptr<AsmVar> PAsmVar;
typedef std::shared_ptr<AsmVarString> PAsmVarString;
typedef std::shared_ptr<AsmLabel> PAsmLabel;

struct Pos {
	bool operator==(const Pos& other) const {
		return fstream_pos == other.fstream_pos;
	}
	explicit operator bool() const {
		return fstream_pos;
	}
	operator std::string() const {
		return "(" + std::to_string(line) + ":" + std::to_string(column) + ")";
	}

	size_t line, column;
	unsigned long long fstream_pos;
};

#endif // TYPES_H
