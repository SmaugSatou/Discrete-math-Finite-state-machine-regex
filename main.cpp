/**
 * @file main.cpp
 * @brief Main entry point for the regex matching utility
 * @ingroup RegexUtility
 */

#include <iostream>

#include "RegexFSM.h"
#include "states.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments!\n";
        std::cerr << "Usage: <program_name> <regex> <str1> <str2> ... <strN>\n";
        return 1;
    }

    std::string pattern = argv[1];

    std::vector<std::string> strings;
    for (int i = 2; i < argc; ++i) {
        strings.push_back(argv[i]);
    }

    RegexFSM regexFSM(pattern);

    for (const auto& str : strings) {
        std::cout << "Checking \"" << str << "\": "
            << (regexFSM.checkString(str) ? "Matched" : "Not matched") << '\n';
    }

    return 0;
}