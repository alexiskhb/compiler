#include <iostream>
#include <cxxopts.hpp>
#include <string>
#include <vector>
#include "scanner.h"
#include "parser.h"
#include "asmgenerator.h"
#include <fstream>

using namespace std;

int compile_result = 0;

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
		compile_result = 1;
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
		compile_result = 1;
	}
	parser.output_symbols(cout);
	parser.output_syntax_tree(cout);
}

void generate(const string& filename, string output_filename) {
	Generator generator(filename);
	if (!generator.is_open()) {
		std::cerr << "Could not open " << filename << endl;
		return;
	}
	if (output_filename.size() == 0) {
		output_filename = "/dev/stdout";
	}
	ofstream output(output_filename);
	if (!output.is_open()) {
		std::cerr << "Could not open " << output_filename << endl;
		return;
	}
	try {
		generator.generate(output);
	} catch (ParseError pe) {
		cerr << pe.msg() << ":\n";
		cerr << generator.get_line(pe.pos().line) << endl;
		compile_result = 1;
	}
}

int main(int argc, char *argv[]) {
//	generate("./test-gen/arr-rec-arr.in", "");
//	parse("./test-parse/not.in", true);
//	return 0;
	cxxopts::Options options(argv[0]);
	bool mode_lexical = false, mode_parse_simple = false, mode_parse = false, mode_generate = false;
	string asm_output_filename;
	options.add_options()
			("l,lexical", "lexical analysis", cxxopts::value<bool>(mode_lexical))
	        ("s,parse-simple", "parse simple", cxxopts::value<bool>(mode_parse_simple))
			("p,parse", "parse", cxxopts::value<bool>(mode_parse))
	        ("S,generate", "generate", cxxopts::value<bool>(mode_generate))
	        ("o,output", "asm output filename", cxxopts::value<string>(asm_output_filename))
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
	if (mode_generate) {
		generate(files[0], asm_output_filename);
	}
	return compile_result;
}










