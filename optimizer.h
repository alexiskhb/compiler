#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "asmcode.h"
#include <vector>
#include <functional>
#include <deque>

struct Optimizer {
	Optimizer(AsmCode&);
	void optimize(bool output_stats = false);
	AsmCode& ac;
	const std::vector<int> stats() const;
private:
	using Optimization = std::function<bool(int)>;
	using HoleSize = int;
	void m_move_cmds();
	void replace(uint, uint, const std::vector<PAsmCmd>& = std::vector<PAsmCmd>());

	bool is_num(PAsmOperand, int64_t n);
	bool is_int(PAsmOperand);
	bool is_reg(PAsmOperand);
	bool is_jmp(PAsmCmd);
	bool is_offs(PAsmOperand);
	bool is_var(PAsmOperand);
	bool is_label(PAsmCmd);
	bool is_special(Register);
	bool is_addr(PAsmOperand);
	bool operds_eq(PAsmOperand op, PAsmCmd cmd, int pos);
	bool cmd_contains(PAsmCmd, PAsmOperand);
	bool offs_contains(PAsmOperandOffset, PAsmOperand);

	std::vector<std::pair<Optimization, HoleSize>> optimizations;
	std::deque<PAsmCmd>& cmds;
	std::vector<int> m_stats;

};

#endif // OPTIMIZER_H
