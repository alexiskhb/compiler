#ifndef ASMGENERATOR_H
#define ASMGENERATOR_H

#include <string>
#include <fstream>
#include "parser.h"
#include "asmcode.h"
#include "types.h"

class Generator {
public:
	Generator(const std::string& filename);
	bool is_open() const;
	std::string get_line(int);
	void generate(std::ostream&);
private:
	void m_generate(PNode);
	Parser m_parser;
	AsmCode m_asmcode;
};

#endif // ASMGENERATOR_H
