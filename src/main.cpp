#include <iostream>
#include "CompilerDriver/CompilerDriver.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> argvStr;
	for (int i = 1; i < argc; i++) {		
		argvStr.push_back(argv[i]);
	}
	return runCompilerDriver(argvStr, argc);
}