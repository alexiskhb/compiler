#include <iostream>
#include <cxxopts.hpp>
#include <string>
#include <vector>
#include "scanner.h"

using namespace std;

int main(int argc, char *argv[])
{
    cxxopts::Options options(argv[0]);
    options.add_options() ("positional", "", cxxopts::value<vector<string>>());
    options.parse_positional({"", "", "positional"});
    options.parse(argc, argv);
    auto files = options["positional"].as<vector<string>>();
    if (files.empty()) {
        return -1;
    }
    Scanner scanner(files[0]);
    if (!scanner.is_open()) {
        std::cerr << "Could not open " << files[0] << endl;
        return -1;
    }

}
