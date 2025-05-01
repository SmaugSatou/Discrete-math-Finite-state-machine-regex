
#include <iostream>

#include "RegexFSM.h"
#include "states.h"

int main() {
	std::string pattern = "a*4.+hi";

	RegexFSM regexFSM(pattern);

	std::cout << regexFSM.checkString("aaaaaa4uhi") << '\n';
	std::cout << regexFSM.checkString("4uhi") << '\n';
	std::cout << regexFSM.checkString("meow") << '\n';

	return 0;
}