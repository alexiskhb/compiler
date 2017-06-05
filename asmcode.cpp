#include "asmcode.h"

using namespace std;

const std::map<Syscall, string> syscalls = {{PRINTF, "printf"}};
const std::map<Register, string> registers =
{
    {RAX,	"rax"},
    {RBX,	"rbx"},
    {RCX,	"rcx"},
    {RDX,	"rdx"},
    {RDI,	"rdi"},
    {RSI,	"rsi"},
    {RSP,	"rsp"},
    {RBP,	"rbp"},
    {XMM0,	"xmm0"}
};
const string reg_prefix = "%";
const string imm_prefix = "$";
const std::map<Opcode, string> opcodes =
{
	{MOVQ,	"movq"},
	{XORQ,	"xorq"},
	{PUSHQ,	"pushq"},
	{POPQ,	"popq"},
	{CALL,	"call"},
	{LEAQ,	"leaq"},
	{RET,	"ret"},
	{ADDQ,	"addq"},
	{SUBQ,	"subq"},
	{IMULQ,	"imulq"},
	{IDIVQ,	"idivq"},
    {CQO,	"cqo"},
	{NONE,	""}
};

AsmCmd::AsmCmd(Opcode oc) :
    m_opcode(oc)
{}

AsmComment::AsmComment(const std::string& str) :
    AsmCmd(NONE), m_string(str)
{}

AsmImmInt::AsmImmInt(int64_t a_value) :
    m_value(a_value){

}

void AsmCode::push(PAsmCmd cmd) {
	m_commands.push_back(cmd);
}

bool AsmCode::add_label(PAsmLabel a_label) {
	bool is_found = m_labels[a_label->name] != 0;
	m_labels[a_label->name] = a_label;
	return is_found;
}

PAsmLabel AsmCode::add_data(PAsmLabel a_label) {
	if (!add_label(a_label)) {
		m_header_labels.push_back(a_label);
	}
	return a_label;
}

std::ostream& AsmCode::output(std::ostream& os) {
	for (PAsmLabel label: m_header_labels) {
		label->output(os);
	}
	for (PAsmCmd cmd: this->m_commands) {
		cmd->output(os);
	}
	os << '\n';
	return os;
}

std::ostream& AsmCmd::output(std::ostream& os) {
	return os;
}

AsmOperandReg::AsmOperandReg(Register a_register) :
    m_register(a_register)
{}

AsmCmd1::AsmCmd1(Opcode oc, PAsmOperand a_operand) :
    AsmCmd(oc), operand(a_operand)
{}

AsmCmd1::AsmCmd1(Opcode oc, PAsmVar a_label) :
    AsmCmd(oc), operand(a_label)
{}

AsmCmd1::AsmCmd1(Opcode oc, Syscall sc) :
    AsmCmd(oc), operand(make_shared<AsmVar>(syscalls.at(sc)))
{}

AsmCmd1::AsmCmd1(Opcode oc, Register a_register) :
    AsmCmd(oc), operand(make_shared<AsmOperandReg>(a_register))
{}

AsmCmd1::AsmCmd1(Opcode oc, int64_t a_value) :
    AsmCmd(oc), operand(make_shared<AsmImmInt>(a_value))
{}

AsmCmd2::AsmCmd2(Opcode oc, Register a_register_1, Register a_register_2) :
    AsmCmd(oc), operand1(make_shared<AsmOperandReg>(a_register_1)), operand2(make_shared<AsmOperandReg>(a_register_2))
{}

AsmCmd2::AsmCmd2(Opcode oc, PAsmVar a_var, Register a_register) :
    AsmCmd(oc), operand1(a_var), operand2(make_shared<AsmOperandReg>(a_register))
{}

AsmCmd2::AsmCmd2(Opcode oc, AsmVar a_var, Register a_register) :
    AsmCmd(oc), operand1(make_shared<AsmVar>(a_var)), operand2(make_shared<AsmOperandReg>(a_register))
{}

std::ostream& AsmCmd0::output(std::ostream& os) {
	os << '\t' << opcodes.at(this->m_opcode) << "\n";
	return os;
}

std::ostream& AsmCmd1::output(std::ostream& os) {
	os << '\t' << opcodes.at(this->m_opcode) << "\t" << operand->str() << '\n';
	return os;
}

std::ostream& AsmCmd2::output(std::ostream& os) {
	os << '\t' << opcodes.at(this->m_opcode) << "\t" << operand1->str() << ", " << operand2->str() << '\n';
	return os;
}

std::ostream& AsmComment::output(std::ostream& os) {
	os << "// " + m_string + "\n";
	return os;
}

AsmCmd0::AsmCmd0(Opcode oc) :
    AsmCmd(oc)
{}

AsmLabel::AsmLabel(const std::string& a_label) :
    AsmCmd(NONE), name(a_label)
{}

AsmVar::AsmVar(const std::string& a_name) :
    AsmLabel(a_name)
{}

AsmGlobl::AsmGlobl(const std::string& a_name) :
    AsmLabel(a_name)
{}

AsmVarString::AsmVarString(const std::string& a_var, const std::string& a_value) :
    AsmVar(a_var), value(a_value)
{}

std::ostream& AsmVarString::output(std::ostream& os) {
	os << name << ":\n\t.string \"" << value << "\"\n";
	return os;
}

std::ostream& AsmLabel::output(std::ostream& os) {
	os << name + ":\n";
	return os;
}

std::ostream& AsmGlobl::output(std::ostream& os) {
	os << "\t.globl " << name << '\n';
	return os;
}

AsmCode& operator<<(AsmCode& ac, PAsmCmd cmd) {
	ac.push(cmd);
	return ac;
}

std::string AsmOperandReg::str() const {
	return reg_prefix + registers.at(m_register);
}

std::string AsmOperandImm::str() const {
    return "";
}

std::string AsmVar::str() const {
	return name;
}

std::string AsmImmInt::str() const {
    return imm_prefix + to_string(m_value);
}
















