#ifndef ASMCODE_H
#define ASMCODE_H

#include <string>
#include "types.h"
#include <vector>
#include <deque>
#include <fstream>
#include <memory>
#include <map>

class AsmOperand {
public:
};

class AsmOperandReg : public AsmOperand {
public:
};

class AsmOperandImm : public AsmOperand {
public:
};

class AsmOperandOfffset : public AsmOperand {
public:
};

class AsmOperandIndirect : public AsmOperand {
public:
};

class AsmLabel {
public:
	AsmLabel() {}
	std::string label;
};

class AsmLabelString : public AsmLabel {

};

class AsmCode {
public:
	std::ostream& output(std::ostream&);
	void push(PAsmCmd);
	void add_global();
private:
	std::map<std::string, PAsmLabel> m_labels;
	std::deque<PAsmCmd> m_commands;
};

class AsmCmd {
public:
	enum Opcode {
		MOV,
		XOR,
		PUSH,
		POP,
		ADD,
		CALL,
		NONE
	};
	AsmCmd(Opcode);
	virtual std::ostream& output(std::ostream&);
protected:
	Opcode m_opcode;
};

class AsmCmd0 : public AsmCmd {
public:
	AsmCmd0(Opcode);
};

class AsmCmd1 : public AsmCmd {
public:
	AsmCmd1(Opcode, PAsmOperand);
	PAsmOperand operand;
};

class AsmCmd2 : public AsmCmd {
public:
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


























