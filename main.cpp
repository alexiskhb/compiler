#include <iostream>
#include <cxxopts.hpp>
#include <string>
#include <vector>
#include "scanner.h"
#include "parser.h"

using namespace std;

void lexical_analysis(const string& filename) {
	Scanner scanner;
	try {
		scanner.open(filename);
		if (!scanner.is_open()) {
			std::cerr << "Could not open " << filename << endl;
			return;
		}
		Token token;
		while ((token = scanner++) != Token::C_EOF) {
			cout << token << endl;
		}
		cout << token << endl;
	} catch(BadToken e) {
		cerr << "bad token " <<
				e.value() << " at (" <<
				e.position().line << ":" <<
				e.position().column << "): " <<
				e.msg() << endl;
	}
}

void parse(const string& filename, const bool strict) {
	Parser parser(filename, strict);
	if (!parser.is_open()) {
		std::cerr << "Could not open " << filename << endl;
		return;
	}
	try {
		parser.parse();
	} catch (ParseError pe) {
		cerr << pe.msg() << ":\n";
		cerr << parser.get_line(pe.pos().line) << endl;
	}
	parser.output_symbols(cout);
	parser.output_syntax_tree(cout);
}

int main(int argc, char *argv[]) {
//	parse("./test-parse/record-record-access.in", true);
//	parse("./test-parse-simple/dot-01.in", false);
//	return 0;
	cxxopts::Options options(argv[0]);
	bool mode_lexical = false, mode_parse_simple = false, mode_parse = false;
	options.add_options()
			("l,lexical", "lexical analysis", cxxopts::value<bool>(mode_lexical))
			("s,parse-simple", "parse-simple", cxxopts::value<bool>(mode_parse_simple))
			("p,parse", "parse", cxxopts::value<bool>(mode_parse))
			("positional", "", cxxopts::value<vector<string>>());
	options.parse_positional({"", "", "positional"});
	options.parse(argc, argv);
	auto files = options["positional"].as<vector<string>>();
	if (files.size() == 0) {
		cerr << "Usage: ./compiler [options] file..." << endl;
		cerr << "Options:\n"
				"  --lexical   Start lexical analisys" << endl;
		cerr << "Alexey Shchurov, 8303A, 2017" << endl;
		return 0;
	}
	if (mode_lexical) {
		lexical_analysis(files[0]);
	}
	if (mode_parse_simple) {
		parse(files[0], false);
	}
	if (mode_parse) {
		parse(files[0], true);
	}
}










