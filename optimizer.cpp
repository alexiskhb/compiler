#include "optimizer.h"
#include <iostream>

using namespace std;

typedef PAsmOperand PAO;

Optimizer::Optimizer(AsmCode& a_ac) :
	ac(a_ac), cmds(a_ac.m_commands)
{
	///subq/addq  $0, %rxx
	///-->
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 if (cmd && (cmd == ADDQ || cmd == SUBQ) && is_num(cmd->operand1, 0) && is_reg(cmd->operand2)) {
			 replace(i, 1, {});
			 return true;
		 }
		 return false;
	}, 1});

	///imulq  $1, %rxx
	///-->
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 if (cmd && cmd == IMULQ && is_num(cmd->operand1, 1) && is_reg(cmd->operand2)) {
			 replace(i, 1, {});
			 return true;
		 }
		 return false;
	}, 1});

	///movq  %rxx, %rxx
	///-->
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 if (cmd && cmd == MOVQ && cmd->operand1 == cmd->operand2) {
			 replace(i, 1, {});
			 return true;
		 }
		 return false;
	}, 1});

	///movq  $0, %rxx
	///-->xorq  %rxx, %rxx (compiler must not generate flags-dependent code)
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 if (cmd && cmd == MOVQ && is_num(cmd->operand1, 0) && is_reg(cmd->operand2)) {
			 replace(i, 1, {make_shared<AsmCmd2>(XORQ, cmd->operand2, cmd->operand2)});
			 return true;
		 }
		 return false;
	}, 1});

	///leaq  (addr), %rxx
	///-->movq  addr, %rxx
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmOperandOffset offs = cmd ? dynamic_pointer_cast<AsmOperandOffset>(cmd->operand1) : 0;
		 if (cmd && cmd == LEAQ && offs && (!offs->offset && !offs->index) && is_reg(cmd->operand2)) {
			 replace(i, 1, {make_shared<AsmCmd2>(MOVQ, PAO(offs->base), PAO(cmd->operand2))});
			 return true;
		 }
		 return false;
	}, 1});

	///pushq  %rx1/(%rx1)/imm
	///popq   %rx2
	///-->movq  %rx1/(%rx1)/imm, %rx2
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd1 cmd1 = dynamic_pointer_cast<AsmCmd1>(cmds[i]);
		 PAsmCmd1 cmd2 = dynamic_pointer_cast<AsmCmd1>(cmds[i + 1]);
		 if (cmd1 && cmd2 && cmd1 == PUSHQ && cmd2 == POPQ && (is_reg(cmd2->operand) || is_var(cmd2->operand) || (is_offs(cmd2->operand) && !is_var(cmd1->operand)))) {
			 replace(i, 2, {make_shared<AsmCmd2>(MOVQ, cmd1->operand, cmd2->operand)});
			 return true;
		 }
		 return false;
	}, 2});

	///movq       $int1, %rxx
	///addq/subq  $int2, %rxx
	///-->cmd  $int1 +/- #int2, %rxx
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 PAsmImmInt imm1 = cmd1 ? dynamic_pointer_cast<AsmImmInt>(cmd1->operand1) : 0;
		 PAsmImmInt imm2 = cmd2 ? dynamic_pointer_cast<AsmImmInt>(cmd2->operand1) : 0;
		 if (cmd1 && cmd2 && cmd1 == MOVQ &&
			(cmd2 == ADDQ || cmd2 == SUBQ) &&
			 is_reg(cmd1->operand2) && cmd1->operand2 == cmd2->operand2 && imm1 && imm2)
		 {
			 replace(i, 2, {
				 make_shared<AsmCmd2>(
						  MOVQ,
						  make_shared<AsmImmInt>(imm1->value() + (cmd2 == ADDQ ? imm2->value() : -imm2->value())),
						  cmd1->operand2)});
			 return true;
		 }
		 return false;
	}, 2});

	///movq  %rx1, %rx2
	///movq  %rx2, %rx1
	///-->
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 if (cmd1 && cmd2 && cmd1 == MOVQ && cmd2 == MOVQ && is_reg(cmd1->operand1) && is_reg(cmd1->operand2) &&
			 cmd1->operand1 == cmd2->operand2 && cmd1->operand2 == cmd2->operand1) {
			 replace(i, 2, {});
			 return true;
		 }
		 return false;
	}, 2});

	///movq  operand, %rx1
	///cmd   %rx1, %rx2
	///-->cmd  operand, %rx2 //rx2 != xmm
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 if (cmd1 && cmd2 && cmd1 == MOVQ && is_reg(cmd1->operand2) && is_reg(cmd2->operand2) &&
			 cmd1->operand2 == cmd2->operand1 && cmd2->operand2 != XMM0 && cmd2->operand2 != XMM1 &&
			 cmd2->operand1 != cmd2->operand2 && cmd2->operand1 != XMM0 && cmd2->operand1 != XMM1)
		 {
			 replace(i, 2, {make_shared<AsmCmd2>(cmd2->oc(), cmd1->operand1, cmd2->operand2)});
			 return true;
		 }
		 return false;
	}, 2});

	///movq  %xmm, %rx1
	///movq  %rx1, %rx2
	///-->movq  %xmm, %rx2
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 if (cmd1 && cmd2 && cmd1 == MOVQ && is_reg(cmd1->operand2) && is_reg(cmd2->operand2) &&
			 cmd1->operand2 == cmd2->operand1 && cmd2->operand2 != XMM0 && cmd2->operand2 != XMM1 &&
			 cmd2->operand1 != cmd2->operand2 && cmd2->operand1 != XMM0 && cmd2->operand1 != XMM1)
		 {
			 replace(i, 2, {make_shared<AsmCmd2>(cmd2->oc(), cmd1->operand1, cmd2->operand2)});
			 return true;
		 }
		 return false;
	}, 2});

	///xorq       %rx1, %rx1
	///subq/addq  %rx1, %rx2
	///-->xorq  %rx1, %rx1
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 if (cmd1 && cmd2 && cmd1 == XORQ && (cmd2 == ADDQ || cmd2 == SUBQ) && is_reg(cmd1->operand1) &&
			 cmd1->operand1 == cmd1->operand2 && cmd1->operand1 == cmd2->operand1)
		 {
			 replace(i, 2, {cmd1});
			 return true;
		 }
		 return false;
	}, 2});

	///mov  addr, %rx1
	///mov  oprd, (%rx1)
	///-->mov  oprd, (addr)
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 PAsmOperandOffset offs = cmd2 ? dynamic_pointer_cast<AsmOperandOffset>(cmd2->operand2) : 0;
		 if (cmd1 && cmd2 && cmd1 == MOVQ && cmd2 == MOVQ && is_reg(cmd1->operand2) && is_addr(cmd1->operand1) &&
			 offs && offs->base->equals(cmd1->operand2) && !offs->index && !offs->offset)
		 {
			 replace(i, 2, {make_shared<AsmCmd2>(MOVQ, cmd2->operand1, cmd1->operand1)});
			 return true;
		 }
		 return false;
	}, 2});

	///cmd  %rxx, operand
	///movq  %rxx, operand(!(%rxx))
	///-->movq  %rxx, operand
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 PAsmOperandOffset offs = cmd2 ? dynamic_pointer_cast<AsmOperandOffset>(cmd2->operand2) : 0;
		 if (cmd1 && cmd2 && cmd2 == MOVQ && is_reg(cmd1->operand1) && cmd1->operand1 == cmd2->operand1 &&
			 (!offs || offs->base != cmd1->operand1) && cmd1->operand2 == cmd2->operand2)
		 {
			 replace(i, 2, {cmd1});
			 return true;
		 }
		 return false;
	}, 2});

	/// leaq arg, %rxx
	/// popq (%rxx)
	/// --> popq arg
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd1 cmd2 = dynamic_pointer_cast<AsmCmd1>(cmds[i + 1]);
		 PAsmOperandOffset offs = cmd2 ? dynamic_pointer_cast<AsmOperandOffset>(cmd2->operand) : 0;
		 if (cmd1 && cmd2 && cmd1 == LEAQ && cmd2 == POPQ && offs && is_reg(cmd1->operand2) && cmd1->operand2->equals(offs->base) && !offs->offset && !offs->index)
		 {
			 replace(i, 2, {make_shared<AsmCmd1>(POPQ, cmd1->operand1)});
			 return true;
		 }
		 return false;
	}, 2});

	///leaq var, %rax
	///cmd  opd, (%rax)
	///-->cmd opd, var
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 PAsmOperandOffset offs = cmd2 ? dynamic_pointer_cast<AsmOperandOffset>(cmd2->operand2) : 0;
		 if (cmd1 && cmd2 && cmd1 == LEAQ && offs && !offs->offset && !offs->index && cmd1->operand2->equals(offs->base) &&
			 (is_var(cmd1->operand1) || is_offs(cmd1->operand1)))
		 {
			 replace(i, 2, {make_shared<AsmCmd2>(cmd2->oc(), cmd2->operand1, cmd1->operand1)});
			 return true;
		 }
		 return false;
	}, 2});

	/// movq var, %rxx
	/// cmd  oprd, %rxx
	/// movq %rxx, var
	///--> cmd oprd, var
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 PAsmCmd2 cmd3 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 2]);
		 if (cmd1 && cmd2 && cmd3 && cmd1 == MOVQ && cmd3 == MOVQ && is_reg(cmd1->operand2) &&
			 cmd1->operand2 == cmd2->operand2 && cmd1->operand2 == cmd3->operand1 &&
			 is_var(cmd1->operand1) && cmd1->operand1 == cmd3->operand2)
		 {
			 replace(i, 3, {make_shared<AsmCmd2>(cmd2->oc(), cmd2->operand1, cmd1->operand1)});
			 return true;
		 }
		 return false;
	}, 3});

	/// xorq %rxx, %rxx
	/// test %rxx, %rxx
	/// jz label
	///--> jmp label
	optimizations.push_back(
	{[&](int i) {
		 PAsmCmd2 cmd1 = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
		 PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmds[i + 1]);
		 PAsmCmd1 cmd3 = dynamic_pointer_cast<AsmCmd1>(cmds[i + 2]);
		 if (cmd1 && cmd2 && cmd3 && cmd1 == XORQ && cmd2 == TESTQ && is_reg(cmd1->operand1) &&
			 cmd1->operand1 == cmd1->operand2 && cmd1->operand2 == cmd2->operand1 &&
			 cmd2->operand1 == cmd2->operand2 && cmd3 == JZ)
		 {
			 replace(i, 3, {make_shared<AsmCmd1>(JMP, cmd3->operand)});
			 return true;
		 }
		 return false;
	}, 3});
	m_stats.resize(optimizations.size());
}

void Optimizer::optimize(bool output_stats) {
	/// remove comments
	cmds.erase(std::remove_if(cmds.begin(), cmds.end(), [](const PAsmCmd& cmd) {
		return dynamic_pointer_cast<AsmComment>(cmd);
	}), cmds.end());
	bool changed_any = true;
	while (changed_any) {
		m_move_cmds();
		changed_any = false;
		for (int k = 0; k < optimizations.size(); k++) {
			const pair<Optimization, HoleSize>& opt = optimizations[k];
			for (int cmd = cmds.size() - opt.second; cmd >= 0; cmd--) {
				bool result = opt.first(cmd);
				changed_any |= result;
				m_stats[k] += result;
			}
		}
	}
	if (output_stats) {
		for (int i = 0; i < m_stats.size(); i++) {
			if (m_stats[i]) {
				cout << '#' << i + 1 << ": " << m_stats[i] << '\n';
			}
		}
	}
}

void Optimizer::m_move_cmds() {
	for (int i = 0; i < cmds.size(); i++) {
		bool moved = false;
		if (cmds[i] == PUSHQ) {
			PAsmOperand op = dynamic_pointer_cast<AsmCmd1>(cmds[i])->operand;
			for (int j = i; j < cmds.size() - 1; j++) {
				if (cmds[j + 1] == POPQ || cmds[j + 1] == PUSHQ || is_jmp(cmds[j + 1]) || is_label(cmds[j + 1]) || operds_eq(op, cmds[j + 1], 2)) {
					break;
				}
				swap(cmds[j], cmds[j + 1]);
				moved = true;
			}
		} else if (cmds[i] == POPQ) {
			PAsmOperand op = dynamic_pointer_cast<AsmCmd1>(cmds[i])->operand;
			for (int j = i; j > 0; j--) {
				if (cmds[j - 1] == POPQ || cmds[j - 1] == PUSHQ || is_jmp(cmds[j - 1]) || is_label(cmds[j - 1]) || cmd_contains(cmds[j - 1], op)) {
					break;
				}
				break;
				swap(cmds[j], cmds[j - 1]);
//				moved = true;
			}
		} else if (cmds[i] == MOVQ) {
			PAsmCmd2 cmd = dynamic_pointer_cast<AsmCmd2>(cmds[i]);
			PAsmOperandReg op = dynamic_pointer_cast<AsmOperandReg>(cmd->operand2);
			if (dynamic_pointer_cast<AsmImmInt>(cmd->operand1) && op && !is_special(op->reg())) {
				for (int j = i; j < cmds.size() - 1; j++) {
					if (cmds[j + 1] == PUSHQ || cmds[j + 1] == POPQ || is_jmp(cmds[j + 1]) ||
						is_label(cmds[j + 1]) || cmd_contains(cmds[j + 1], op)) {
						break;
					}
//					break;
					swap(cmds[j], cmds[j + 1]);
//					moved = true;
				}
			}
		}
		i -= moved;
	}
}

bool Optimizer::operds_eq(PAsmOperand op, PAsmCmd cmd, int pos) {
	switch (pos) {
	case 0: return false;
	case 1: {
		PAsmCmd1 cmd1 = dynamic_pointer_cast<AsmCmd1>(cmd);
		if (cmd1) {
			return op->equals(cmd1->operand);
		}
		PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmd);
		if (cmd2) {
			return op->equals(cmd2->operand1);
		}
		return false;
	}
	case 2: {
		PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmd);
		if (cmd2) {
			return op->equals(cmd2->operand2);
		}
	}
	default: return false;
	}
	return false;
}

void Optimizer::replace(uint idx, uint n, const std::vector<PAsmCmd>& a_cmds) {
	/// equalize under-replace hole size and n. of new cmds
	if (a_cmds.size() == 0 && n == 0) {
		return;
	} else if (a_cmds.size() > n) {
		vector<PAsmCmd> t(a_cmds.size() - n, 0);
		cmds.insert(cmds.begin() + idx, t.begin(), t.end());
	} else if (a_cmds.size() < n) {
		cmds.erase(cmds.begin() + idx, cmds.begin() + idx + n - a_cmds.size());
	}
	/// replace old cmds by new
	for (PAsmCmd cmd: a_cmds) {
		cmds[idx++] = cmd;
	}
}

bool Optimizer::is_num(PAsmOperand op, int64_t n) {
	PAsmImmInt imm = dynamic_pointer_cast<AsmImmInt>(op);
	return imm && imm->value() == n;
}

bool Optimizer::is_int(PAsmOperand op) {
	return (bool)dynamic_pointer_cast<AsmImmInt>(op);
}

bool Optimizer::is_reg(PAsmOperand op) {
	return (bool)dynamic_pointer_cast<AsmOperandReg>(op);
}

bool Optimizer::is_addr(PAsmOperand op) {
	return (bool)dynamic_pointer_cast<AsmVar>(op);
}

bool Optimizer::is_offs(PAsmOperand op) {
	return (bool)dynamic_pointer_cast<AsmOperandOffset>(op);
}

bool Optimizer::is_var(PAsmOperand op) {
	return (bool)dynamic_pointer_cast<AsmVar>(op);
}

bool Optimizer::cmd_contains(PAsmCmd cmd, PAsmOperand op) {
	if (dynamic_pointer_cast<AsmCmd0>(cmd)) {
		return false;
	}
	PAsmCmd1 cmd1 = dynamic_pointer_cast<AsmCmd1>(cmd);
	if (cmd1) {
		PAsmOperandOffset offs = dynamic_pointer_cast<AsmOperandOffset>(cmd1->operand);
		return (offs && offs_contains(offs, op)) || op->equals(cmd1->operand);
	}
	PAsmCmd2 cmd2 = dynamic_pointer_cast<AsmCmd2>(cmd);
	if (cmd2) {
		PAsmOperandOffset offs1 = dynamic_pointer_cast<AsmOperandOffset>(cmd2->operand1);
		PAsmOperandOffset offs2 = dynamic_pointer_cast<AsmOperandOffset>(cmd2->operand2);
		return (offs1 && offs_contains(offs1, op)) || (offs2 && offs_contains(offs2, op)) ||
				op->equals(cmd2->operand1) || op->equals(cmd2->operand2);
	}
	return false;
}

bool Optimizer::offs_contains(PAsmOperandOffset offs, PAsmOperand op) {
	return op->equals(offs->base) ||
		   (offs->index && op->equals(offs->index)) ||
		   (offs->scale && op->equals(offs->scale)) ||
		   (offs->offset && op->equals(offs->offset));
}

bool Optimizer::is_jmp(PAsmCmd cmd) {
	return
			cmd == JZ || cmd == JNZ || cmd == JMP ||
			cmd == JE || cmd == JGE || cmd == JLE ||
			cmd == JG || cmd == JL || cmd == CALL ||
			cmd == RET;
}

bool Optimizer::is_label(PAsmCmd cmd) {
	return dynamic_pointer_cast<AsmLabel>(cmd) &&
	      !dynamic_pointer_cast<AsmVar>(cmd) &&
	      !dynamic_pointer_cast<AsmSyscall>(cmd) &&
	      !dynamic_pointer_cast<AsmGlobl>(cmd);
}

bool Optimizer::is_special(Register reg) {
	return reg == RAX || reg == RSI || reg == RDI || reg == RCX || reg == RSP || reg == RBP;
}

const std::vector<int> Optimizer::stats() const {
	return m_stats;
}















