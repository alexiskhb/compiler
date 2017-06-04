#include "asmgenerator.h"

using namespace std;

Generator::Generator(const std::string& filename) :
    m_parser(filename)
{}

bool Generator::is_open() const {
	return m_parser.is_open();
}

string Generator::get_line(int id) {
	return m_parser.get_line(id);
}

void Generator::generate(std::ostream& os) {
	m_parser.parse();
	m_generate(m_parser.tree());
	m_asmcode.output(os);
}

void Generator::m_generate(PNode node) {
	node->generate(m_asmcode);
}
