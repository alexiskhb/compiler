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
    {XMM0,	"xmm0"},
    {XMM1,	"xmm1"},
    {AL,	"al"},
    {CL,	"cl"},
    {R9,	"r9"},
	{R10,	"r10"},
	{R11,	"r11"},
	{R12,	"r12"},
	{R13,	"r13"},
	{R14,	"r14"},
	{R15,	"r15"},
};
const string reg_prefix = "%";
const string imm_prefix = "$";
const string label_prefix = "..L";
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
    {CVTSI2SD,	"cvtsi2sd"},
    {CVTSD2SI,	"cvtsd2si"},
    {SETE,	"sete"},
    {SETNE,	"setne"},
    {SETL,	"setl"},
    {SETG,	"setg"},
    {SETGE,	"setge"},
    {SETLE,	"setle"},
    {SETA,	"seta"},
    {SETB,	"setb"},
    {SETAE,	"setae"},
    {SETBE,	"setbe"},
    {CMPQ,	"cmpq"},
    {ADDSD,	"addsd"},
    {SUBSD,	"subsd"},
    {DIVSD,	"divsd"},
    {MULSD,	"mulsd"},
    {MOVSD,	"movsd"},
    {COMISD,	"comisd"},
    {NEGQ,	"negq"},
    {XORPD,	"xorpd"},
    {SHLQ,	"shlq"},
    {SHRQ,	"shrq"},
    {MOV,	"mov"},
    {JZ,	"jz"},
    {JNZ,	"jnz"},
    {JMP,	"jmp"},
    {JE,	"je"},
    {JGE,	"jge"},
    {JLE,	"jle"},
    {JG,	"jg"},
    {JL,	"jl"},
    {TESTQ,	"testq"},
    {NONE,	""}
};

uint64_t AsmLabel::counter = 0;

AsmLabel::AsmLabel() :
    name(label_prefix + to_string(++counter))
{}

AsmCmd::AsmCmd() :
    m_opcode(NONE)
{}

AsmCmd::AsmCmd(Opcode oc) :
    m_opcode(oc)
{}

Opcode AsmCmd::oc() const {
	return m_opcode;
}

AsmComment::AsmComment(const std::string& str) :
    AsmCmd(NONE), m_string(str)
{}

AsmImmInt::AsmImmInt(int64_t a_value) :
    m_value(a_value)
{}

AsmImmFloat::AsmImmFloat(double a_value) :
    m_value(a_value)
{}

AsmOperandOffset::AsmOperandOffset(Register reg) :
    base(make_shared<AsmOperandReg>(reg))
{}

AsmOperandOffset::AsmOperandOffset(Register a_base, Register a_index, int64_t a_scale) :
    base(make_shared<AsmOperandReg>(a_base)), index(make_shared<AsmOperandReg>(a_index)), scale(make_shared<AsmRawInt>(a_scale))
{}

AsmRawInt::AsmRawInt(int64_t a_value) :
    value(a_value)
{}

void AsmCode::push_buf(PAsmCmd cmd) {
	m_commands.push_back(cmd);
}

void AsmCode::append(const AsmCode& other) {
	m_commands.insert(m_commands.end(), other.m_commands.begin(), other.m_commands.end());
	m_header_labels.insert(m_header_labels.end(), other.m_header_labels.begin(), other.m_header_labels.end());
}

AsmCode& AsmCode::push_buf() {
	this->buffers.push(make_shared<AsmCode>());
	return buf();
}

void AsmCode::pop_buf() {
	this->append(buf());
	buffers.pop();
}

AsmCode& AsmCode::buf() {
	return *this->buffers.top();
}

AsmCode& AsmCode::proc_defs() {
	if (!m_procedures) {
		m_procedures = make_shared<AsmCode>();
	}
	return *m_procedures;
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
	return os << '\t' << opcodes.at(this->m_opcode) << '\n';
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

AsmCmd1::AsmCmd1(Opcode oc, AsmVar a_label) :
    AsmCmd(oc), operand(make_shared<AsmVar>(a_label))
{}

AsmCmd1::AsmCmd1(Opcode oc, Syscall sc) :
    AsmCmd(oc), operand(make_shared<AsmSyscall>(syscalls.at(sc)))
{}

AsmCmd1::AsmCmd1(Opcode oc, Register a_register) :
    AsmCmd(oc), operand(make_shared<AsmOperandReg>(a_register))
{}

AsmCmd1::AsmCmd1(Opcode oc, AsmLabel a_label) :
    AsmCmd(oc), operand(make_shared<AsmLabel>(a_label))
{}

AsmCmd1::AsmCmd1(Opcode oc, AsmOperandOffset a_offs) :
    AsmCmd(oc), operand(make_shared<AsmOperandOffset>(a_offs))
{}

AsmCmd1::AsmCmd1(Opcode oc, int64_t a_value) :
    AsmCmd(oc), operand(make_shared<AsmImmInt>(a_value))
{}

AsmCmd1::AsmCmd1(Opcode oc, double a_value) :
    AsmCmd(oc), operand(make_shared<AsmImmFloat>(a_value))
{}

AsmCmd2::AsmCmd2(Opcode oc, PAsmOperand a_op1, PAsmOperand a_op2) :
	AsmCmd(oc), operand1(a_op1), operand2(a_op2)
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

AsmCmd2::AsmCmd2(Opcode oc, Register a_register, AsmVar a_var) :
    AsmCmd(oc), operand1(make_shared<AsmOperandReg>(a_register)), operand2(make_shared<AsmVar>(a_var))
{}

AsmCmd2::AsmCmd2(Opcode oc, AsmOffs a_offs, Register a_register) :
    AsmCmd(oc), operand1(make_shared<AsmOffs>(a_offs)), operand2(make_shared<AsmOperandReg>(a_register))
{}

AsmCmd2::AsmCmd2(Opcode oc, int64_t a_value, AsmOffs a_offs) :
    AsmCmd(oc), operand1(make_shared<AsmImmInt>(a_value)), operand2(make_shared<AsmOffs>(a_offs))
{}

AsmCmd2::AsmCmd2(Opcode oc, double a_var, Register a_register) :
    AsmCmd(oc), operand1(make_shared<AsmImmFloat>(a_var)), operand2(make_shared<AsmOperandReg>(a_register))
{}

AsmCmd2::AsmCmd2(Opcode oc, int64_t a_var, Register a_register) :
    AsmCmd(oc), operand1(make_shared<AsmImmInt>(a_var)), operand2(make_shared<AsmOperandReg>(a_register))
{}

AsmDirective::AsmDirective(Directive a_directive) :
    AsmCmd(NONE), m_directive(a_directive)
{}

std::ostream& AsmCmd0::output(std::ostream& os) {
	return os << '\t' << opcodes.at(this->m_opcode) << "\n";
}

std::ostream& AsmCmd1::output(std::ostream& os) {
	return os << '\t' << opcodes.at(this->m_opcode) << "\t" << operand->str() << '\n';
}

std::ostream& AsmCmd2::output(std::ostream& os) {
	return os << '\t' << opcodes.at(this->m_opcode) << "\t" << operand1->str() << ", " << operand2->str() << '\n';
}

std::ostream& AsmComment::output(std::ostream& os) {
	return os << "// " + m_string + "\n";
}

AsmCmd0::AsmCmd0(Opcode oc) :
    AsmCmd(oc)
{}

AsmLabel::AsmLabel(const std::string& a_label) :
    AsmCmd(NONE), name(a_label)
{}

AsmVar::AsmVar(const std::string& a_name) :
    AsmLabel(var_prefix + a_name)
{}

AsmSyscall::AsmSyscall(const std::string& a_name) :
    AsmLabel(a_name)
{}

AsmGlobl::AsmGlobl(const std::string& a_name) :
    AsmLabel(a_name)
{}

AsmVarString::AsmVarString(const std::string& a_var, const std::string& a_value) :
    AsmVar(a_var), value(a_value)
{}

AsmVarInt::AsmVarInt(const std::string& a_var, int64_t a_value) :
    AsmVar(a_var), m_value(a_value)
{}

AsmVarFloat::AsmVarFloat(const std::string& a_var, double a_value) :
    AsmVar(a_var), m_value(a_value)
{}

AsmVarArray::AsmVarArray(const std::string& a_var, uint a_esize, const std::vector<std::pair<int, int>>& bounds) :
    AsmVar(a_var), m_element_size(a_esize), m_bounds(bounds), m_size(_m_size())
{}

AsmVarRecord::AsmVarRecord(const std::string& a_var, PSymTable a_st) :
    AsmVar(a_var), st(a_st), m_size(a_st->sizeb())
{}

uint AsmVarArray::_m_size() const {
	uint result = 1;
	for (const pair<int, int>& p: this->m_bounds) {
		result *= p.second - p.first + 1;
	}
	return result;
}

std::ostream& AsmVarString::output(std::ostream& os) {
	return os << name << ":\n\t.string \"" << value << "\"\n";
}

std::ostream& AsmVarInt::output(std::ostream& os) {
	return os << ".data\n\t" << name << ": .quad " << m_value << "\n";
}

std::ostream& AsmVarFloat::output(std::ostream& os) {
	return os << ".data\n\t" << name << ": .double " << m_value << "\n";
}

std::ostream& AsmVarArray::output(std::ostream& os) {
	return os << ".data\n\t" << name << ": .fill " << this->m_size*m_element_size << ",1,0\n";
}

std::ostream& AsmVarRecord::output(std::ostream& os) {
	return os << ".data\n\t" << name << ": .fill " << this->m_size << ",1,0\n";
}

std::ostream& AsmLabel::output(std::ostream& os) {
	return os << name + ":\n";
}

std::ostream& AsmVar::output(std::ostream& os) {
	return os << name + ":\n";
}

std::ostream& AsmSyscall::output(std::ostream& os) {
	return os << name + " output syscall :\n";
}

std::ostream& AsmGlobl::output(std::ostream& os) {
	return os << "\t.globl " << name << '\n';
}

AsmCode& operator<<(AsmCode& ac, PAsmCmd cmd) {
	ac.push_buf(cmd);
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

std::string AsmSyscall::str() const {
	return name;
}

std::string AsmImmInt::str() const {
	return imm_prefix + to_string(m_value);
}

std::string AsmImmFloat::str() const {
	return imm_prefix + to_string(m_value);
}

std::string AsmRawInt::str() const {
	return to_string(value);
}

std::string AsmLabel::str() const {
	return name;
}

Register AsmOperandReg::reg() const {
	return m_register;
}

int64_t AsmImmInt::value() const {
	return m_value;
}

double AsmImmFloat::value() const {
	return m_value;
}

std::string AsmOperandOffset::str() const {
	return (offset ? offset->str() : "") +
	        "(" + base->str() +
	            (index ? ("," + index->str() +
	                     (scale ? ("," + scale->str()) : ""))
	                     : "")
	        + ")";
}


bool AsmOperandReg      ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmOperandImm      ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmImmInt          ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmImmFloat        ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmOperandOffset   ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmRawInt          ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmOperandIndirect ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}
bool AsmLabel           ::equals(PAsmOperand oprd) const {return oprd->equals(*this);}

bool AsmOperand::equals(const AsmOperandReg&)      const {return false;}
bool AsmOperand::equals(const AsmOperandImm&)      const {return false;}
bool AsmOperand::equals(const AsmImmInt&)          const {return false;}
bool AsmOperand::equals(const AsmImmFloat&)        const {return false;}
bool AsmOperand::equals(const AsmOperandOffset&)   const {return false;}
bool AsmOperand::equals(const AsmRawInt&)          const {return false;}
bool AsmOperand::equals(const AsmOperandIndirect&) const {return false;}
bool AsmOperand::equals(const AsmLabel&)           const {return false;}
bool AsmOperand::equals(PAsmOperand)               const {return false;}

bool AsmOperandReg::equals(const AsmOperandReg& oprd) const {
	return this->m_register == oprd.m_register;
}

bool AsmOperandImm::equals(const AsmOperandImm& oprd) const {
	return false;
}

bool AsmImmInt::equals(const AsmImmInt& oprd) const {
	return this->m_value == oprd.m_value;
}

bool AsmImmFloat::equals(const AsmImmFloat& oprd) const {
	return this->m_value == oprd.m_value;
}

bool AsmOperandOffset::equals(const AsmOperandOffset& oprd) const {
	return
			this->base->equals(oprd.base) &&
			((!this->index  && !oprd.index ) || (this->index  && oprd.index && this->index->equals(oprd.index))) &&
			((!this->scale  && !oprd.scale ) || (this->scale  && oprd.scale && this->scale->equals(oprd.scale))) &&
			((!this->offset && !oprd.offset) || (this->offset && oprd.offset && this->offset->equals(oprd.offset)));
}

bool AsmRawInt::equals(const AsmRawInt& oprd) const {
	return this->value == oprd.value;
}

bool AsmOperandIndirect::equals(const AsmOperandIndirect& oprd) const {
	return false;
}

bool AsmLabel::equals(const AsmLabel& oprd) const {
	return this->name == oprd.name;
}

bool operator==(PAsmOperand opr1, PAsmOperand opr2) {
	return opr1->equals(opr2);
}

bool operator!=(PAsmOperand opr1, PAsmOperand opr2) {
	return !(opr1->equals(opr2));
}

bool operator==(PAsmOperand opr, Register reg) {
	PAsmOperandReg r = dynamic_pointer_cast<AsmOperandReg>(opr);
	return r && r->reg() == reg;
}

bool operator!=(PAsmOperand opr, Register reg) {
	return !(opr == reg);
}

bool operator==(PAsmCmd cmd, Opcode opc) {
	PAsmCmd1 acd1 = dynamic_pointer_cast<AsmCmd1>(cmd);
	if (acd1) {
		if (acd1 == opc) {
			return true;
		}
		return false;
	}
	PAsmCmd2 acd2 = dynamic_pointer_cast<AsmCmd2>(cmd);
	if (acd2) {
		if (acd2 == opc) {
			return true;
		}
		return false;
	}
	PAsmCmd0 acd0 = dynamic_pointer_cast<AsmCmd0>(cmd);
	if (acd0) {
		if (acd0 == opc) {
			return true;
		}
		return false;
	}
	return false;
}

bool operator==(PAsmCmd0 op, Opcode opc) {
	return op->oc() == opc;
}

bool operator==(PAsmCmd1 op, Opcode opc) {
	return op->oc() == opc;
}

bool operator==(PAsmCmd2 op, Opcode opc) {
	return op->oc() == opc;
}












