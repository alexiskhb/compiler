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
        parser.parse_simple_expressions();
    } catch (ParseError pe) {
        cerr << pe.msg() << ":\n";
        cerr << parser.get_line(pe.pos().line) << endl;
    }
    parser.output_syntax_tree(cout);
}

int main(int argc, char *argv[]) {
    cxxopts::Options options(argv[0]);
    bool lexical = false, parser = false, not_strict = false;
    options.add_options()
            ("l,lexical", "lexical analysis", cxxopts::value<bool>(lexical))
            ("p,parse", "parse", cxxopts::value<bool>(parser))
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
    if (lexical) {
        lexical_analysis(files[0]);
    }
    if (parser) {
        parse(files[0], !not_strict);
    }
}
