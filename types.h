#ifndef TYPES_H
#define TYPES_H

#include <memory>

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
class SymbolConst;
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
typedef std::shared_ptr<SymbolConst> PSymbolConst;
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
class NodeStmtType;
class NodeStmtBlock;
class NodeVarDeclarationUnit;
class NodeTypeDeclarationUnit;
class NodeVariable;

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
typedef std::shared_ptr<NodeStmtType> PNodeStmtType;
typedef std::shared_ptr<NodeStmtBlock> PNodeStmtBlock;
typedef std::shared_ptr<NodeVarDeclarationUnit> PNodeVarDeclarationUnit;
typedef std::shared_ptr<NodeTypeDeclarationUnit> PNodeTypeDeclarationUnit;
typedef std::shared_ptr<NodeVariable> PNodeVariable;

typedef std::shared_ptr<NodeExprStmtFunctionCall> PNodeExprStmtFunctionCall;


#endif // TYPES_H
