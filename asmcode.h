#ifndef ASMCODE_H
#define ASMCODE_H

#include <string>
#include "types.h"
#include <vector>
#include <deque>
#include <fstream>
#include <memory>
#include <algorithm>
#include <map>

enum Register {
	RAX,
	RBX,
	RCX,
	RDX,
	RDI,
	RSI,
	RSP,
	RBP,
	XMM0,
};

enum Opcode {
	MOVQ,
	XORQ,
	PUSHQ,
	POPQ,
	ADDQ,
	CALL,
	LEAQ,
	RET,
	SUBQ,
	IMULQ,
	IDIVQ,
	CQO,
	NONE,
};

enum Syscall {
	PRINTF,
};

class AsmOperand {
public:
	virtual std::string str() const = 0;
};

class AsmOperandReg : public AsmOperand {
public:
	AsmOperandReg(Register);
	std::string str() const override;
private:
	Register m_register;
};

class AsmOperandImm : public AsmOperand {
public:
	std::string str() const override;
};

class AsmImmInt : public AsmOperandImm {
public:
	AsmImmInt(int64_t);
	std::string str() const override;
private:
	int64_t m_value;
};

class AsmOperandOfffset : public AsmOperand {
public:
	std::string str() const override;
};

class AsmOperandIndirect : public AsmOperand {
public:
	std::string str() const override;
};

class AsmCmd {
public:
	AsmCmd(Opcode);
	virtual std::ostream& output(std::ostream&);
protected:
	Opcode m_opcode;
};

class AsmLabel : public AsmCmd {
public:
	AsmLabel(const std::string&);
	std::ostream& output(std::ostream&) override;
	std::string name;
};

class AsmVar : public AsmOperand, public AsmLabel {
public:
	AsmVar(const std::string&);
	std::string str() const override;
};

class AsmGlobl : public AsmLabel {
public:
	AsmGlobl(const std::string&);
	std::ostream& output(std::ostream&) override;
};

class AsmVarString : public AsmVar {
public:
	AsmVarString(const std::string&, const std::string&);
	std::ostream& output(std::ostream&);
	std::string value;
};

class AsmCode {
public:
	std::ostream& output(std::ostream&);
	void push(PAsmCmd);
	// true if the label was added before
	bool add_label(PAsmLabel);
	PAsmLabel add_data(PAsmLabel);
private:
	std::vector<PAsmLabel> m_header_labels;
	std::map<std::string, PAsmLabel> m_labels;
	std::deque<PAsmCmd> m_commands;
};

class AsmCmd0 : public AsmCmd {
public:
	AsmCmd0(Opcode);
	std::ostream& output(std::ostream&) override;
};

class AsmCmd1 : public AsmCmd {
public:
	AsmCmd1(Opcode, PAsmOperand);
	AsmCmd1(Opcode, PAsmVar);
	AsmCmd1(Opcode, Syscall);
	AsmCmd1(Opcode, Register);
	AsmCmd1(Opcode, int64_t);
	std::ostream& output(std::ostream&) override;
	PAsmOperand operand;
};

class AsmCmd2 : public AsmCmd {
public:
	AsmCmd2(Opcode, Register, Register);
	AsmCmd2(Opcode, PAsmVar, Register);
	AsmCmd2(Opcode, AsmVar, Register);
	std::ostream& output(std::ostream&) override;
	PAsmOperand operand1;
	PAsmOperand operand2;
};

class AsmComment : public AsmCmd {
public:
	AsmComment(const std::string&);
	std::ostream& output(std::ostream&) override;
private:
	std::string m_string;
};

AsmCode& operator<<(AsmCode& ac, PAsmCmd cmd);

template <class TAsmCmd>
AsmCode& operator<<(AsmCode& ac, TAsmCmd cmd) {
	ac.push(std::make_shared<TAsmCmd>(cmd));
	return ac;
}


#endif // ASMCODE_H


























