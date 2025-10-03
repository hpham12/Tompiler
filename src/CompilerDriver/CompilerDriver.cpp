#include <cstdlib>
#include <cstring>
#include <string>
#include "CompilerDriver.h"
#include <iostream>

using namespace std;

int runCompilerDriver(vector<string> args, int argc) {
	string stepFlag = "";
	if (VALID_STEP_FLAGS.contains(args[0])) {
		stepFlag = args[0];
	}
	int nextIndex;
	if (stepFlag == COMPILE_FLAG) {
		string outputFileName = "";
		if (args[1] == OUTPUT_FLAG) {
			outputFileName = args[2];
			nextIndex = 3;
		} else {
			nextIndex = 1;
		}
		string compilerFlag = "";
		if (VALID_COMPILER_FLAG.contains(args[nextIndex])) {
			compilerFlag = args[nextIndex];
			if (compilerFlag == LEXER_FLAG) {
				if (outputFileName == "") {
					outputFileName = "a.lex";
				}
			} else if (compilerFlag == PARSER_FLAG) {
				if (outputFileName == "") {
					outputFileName = "a.parse";
				}
			} else {
				if (outputFileName == "") {
					outputFileName = "a.codegen";
				}
			}
			nextIndex++;
		} else if (args[2].starts_with("-")) {
			cout << "Invalid compiler flag" << endl;
			return 1;
		} else {
			if (outputFileName == "") {
				outputFileName = "a.o";
			}
		}
		string inputFile = args[nextIndex];
		cout << "Input file name: " << inputFile << endl;
		cout << "Output file name: " << outputFileName << endl;
		cout << "Compiler flag: " << compilerFlag << endl;
	} else {
		string cmd;
		for (int i = 0; i < args.size(); i++) {
			cmd += " " + args[0];
		}
		return system(("g++ " + cmd).c_str());
	}
}
