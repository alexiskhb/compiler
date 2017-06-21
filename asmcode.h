#ifndef ASMCODE_H
#define ASMCODE_H

#include <string>
#include "types.h"
#include <vector>
#include <deque>
#include <fstream>
#include <stack>
#include <memory>
#include <algorithm>
#include <map>

const std::string var_prefix = ".__";

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
	XMM1,
	AL,
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
	CVTSI2SD,
	CVTSD2SI,
	SETE,
	SETNE,
	SETL,
	SETG,
	SETGE,
	SETLE,
	SETA,
	SETB,
	SETAE,
	SETBE,
	CMPQ,
	ADDSD,
	SUBSD,
	DIVSD,
	MULSD,
	MOVSD,
	COMISD,
	NEGQ,
	XORPD,
	NONE,
};

enum Directive {
	DATA,
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

class AsmImmFloat : public AsmOperandImm {
public:
	AsmImmFloat(double);
	std::string str() const override;
private:
	double m_value;
};

class AsmOperandOffset : public AsmOperand {
public:
	AsmOperandOffset(Register);
	std::string str() const override;
	PAsmOperand offset = nullptr;
	PAsmOperandReg base = nullptr;
	PAsmOperandReg index = nullptr;
	PAsmRawInt scale = nullptr;
};
typedef AsmOperandOffset AsmOffs;

class AsmRawInt : public AsmOperand {
public:
	AsmRawInt(int64_t);
	std::string str() const override;
	int64_t value;
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
	std::ostream& output(std::ostream&) override;
	std::string str() const override;
};

class AsmSyscall : public AsmOperand, public AsmLabel {
public:
	AsmSyscall(const std::string&);
	std::ostream& output(std::ostream&) override;
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

class AsmVarInt : public AsmVar {
public:
	AsmVarInt(const std::string&, int64_t value = 0);
	std::ostream& output(std::ostream&);
private:
	int64_t m_value;
};

class AsmVarFloat : public AsmVar {
public:
	AsmVarFloat(const std::string&, double value = 0);
	std::ostream& output(std::ostream&);
private:
	double m_value;
};

class AsmVarArray : public AsmVar {
public:
	AsmVarArray(const std::string&, uint, const std::vector<std::pair<int, int>>&);
	std::ostream& output(std::ostream&);
private:
	uint _m_size() const;
	double m_value;
	const uint m_element_size;                       // Do not
	const std::vector<std::pair<int, int>> m_bounds; // change
	const uint m_size;                               // order.
};

class AsmCode {
public:
	std::ostream& output(std::ostream&);
	void push_buf(PAsmCmd);
	void append(const AsmCode&);
	AsmCode& push_buf();
	void pop_buf();
	AsmCode& buf();
	// true if the label was added before
	bool add_label(PAsmLabel);
	PAsmLabel add_data(PAsmLabel);
	std::stack<PAsmCode> buffers;
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
	AsmCmd1(Opcode, AsmVar);
	AsmCmd1(Opcode, Syscall);
	AsmCmd1(Opcode, Register);
	AsmCmd1(Opcode, AsmOperandOffset);
	explicit AsmCmd1(Opcode, int64_t);
	explicit AsmCmd1(Opcode, double);
	std::ostream& output(std::ostream&) override;
	PAsmOperand operand;
};

class AsmCmd2 : public AsmCmd {
public:
	AsmCmd2(Opcode, Register, Register);
	AsmCmd2(Opcode, PAsmVar, Register);
	AsmCmd2(Opcode, AsmVar, Register);
	AsmCmd2(Opcode, double, Register);
	AsmCmd2(Opcode, int64_t, Register);
	AsmCmd2(Opcode, Register, AsmVar);
	std::ostream& output(std::ostream&) override;
	PAsmOperand operand1;
	PAsmOperand operand2;
};

class AsmDirective : public AsmCmd {
public:
	AsmDirective(Directive);
private:
	Directive m_directive;
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
	ac.push_buf(std::make_shared<TAsmCmd>(cmd));
	return ac;
}


#endif // ASMCODE_H


























