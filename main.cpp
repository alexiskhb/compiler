#include <iostream>
#include <cxxopts.hpp>
#include <string>
#include <vector>
#include "scanner.h"
#include "parser.h"

using namespace std;

void lexical_analysis(const string& filename) {
    Scanner scanner(filename);
    if (!scanner.is_open()) {
        std::cerr << "Could not open " << filename << endl;
        return;
    }
    Token token;
    try {
        while (token = scanner++) {
            cout << token << endl;
        }
        cout << token << endl;
    } catch(const BadToken& e) {
        cerr << "bad token " <<
                e.value() << " at (" <<
                e.position().line << ":" <<
                e.position().column << "): " <<
                e.msg() << endl;
    }
}

void parse(const string& filename) {
    Parser parser(filename);
    if (!parser.is_open()) {
        std::cerr << "Could not open " << filename << endl;
        return;
    }
    parser.parse();
    parser.output_syntax_tree(cout);
}

int main(int argc, char *argv[]) {
//    lexical_analysis("test/err-big-escape-char-ord.errin");
//    parse("test-parse/12.in");
//    return 0;
    cxxopts::Options options(argv[0]);
    bool lexical = false;
    options.add_options()
            ("l,lexical", "lexical analysis", cxxopts::value<bool>(lexical))
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
    parse(files[0]);
}
