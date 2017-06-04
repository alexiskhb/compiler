#include "asmcode.h"

AsmCmd::AsmCmd(Opcode oc) :
    m_opcode(oc)
{}

AsmComment::AsmComment(const std::string& str) :
    AsmCmd(NONE), m_string(str)
{}

void AsmCode::push(PAsmCmd cmd) {
	m_commands.push_back(cmd);
}

std::ostream& AsmCode::output(std::ostream& os) {
	for (PAsmCmd cmd: this->m_commands) {
		cmd->output(os);
	}
	return os;
}

std::ostream& AsmCmd::output(std::ostream& os) {
	return os;
}

AsmCmd1::AsmCmd1(Opcode oc, PAsmOperand pao) :
    AsmCmd(oc), operand(pao)
{}

std::ostream& AsmComment::output(std::ostream& os) {
	os << "// " + m_string + "\n";
	return os;
}

AsmCmd0::AsmCmd0(Opcode oc) :
    AsmCmd(oc)
{}

AsmCode& operator<<(AsmCode& ac, PAsmCmd cmd) {
	ac.push(cmd);
	return ac;
}
