#include <cstdlib>
#include <cstring>
#include <string>
#include "CompilerDriver.h"
#include <iostream>
#include <cstdio>
#include "../lexer/lexer.h"

using namespace std;

int runCompilerDriver(vector<string> args) {
	string firstArg = args[0];
	string sourceFile{""};
	string option{""};
	if (firstArg.starts_with("-")) {
		option = firstArg;
		if (!VALID_OPTIONS.contains(option)) {
			throw invalid_argument("Invalid option " + option);
		}
		if (option != HELP_FLAG) {
			sourceFile = args[1];
		}
	} else {
		sourceFile = firstArg;
	}

	size_t extensionIndx = sourceFile.find(".");
	string sourceFileWithoutExtension = sourceFile.substr(0, extensionIndx);
	string preprocessedOutputFile = sourceFileWithoutExtension + ".i";
	
	if (option == "") {
		// no option specified		
		if (preprocess(sourceFile, preprocessedOutputFile) != 0) {
			return 1;
		}
		string compiledOutputFile = sourceFileWithoutExtension + ".s";
		if (compile(preprocessedOutputFile, compiledOutputFile) != 0) {
			return 1;
		}
		remove(preprocessedOutputFile.c_str());
		if (assembleAndLink({compiledOutputFile}, sourceFileWithoutExtension) != 0) {
			return 1;
		}
		remove(compiledOutputFile.c_str());
	} else if (option == HELP_FLAG) {
		return printHelpMenu();
	} else if (option == COMPILE_FLAG) {
		if (preprocess(sourceFile, preprocessedOutputFile) != 0) {
			return 1;
		}
		string compiledOutputFile = sourceFileWithoutExtension + ".s";
		if (compile(preprocessedOutputFile, compiledOutputFile) != 0) {
			return 1;
		}
		remove(preprocessedOutputFile.c_str());
	} else if (option == LEXER_FLAG) {
		if (preprocess(sourceFile, preprocessedOutputFile) != 0) {
			return 1;
		}
		lex(preprocessedOutputFile);
		remove(preprocessedOutputFile.c_str());
	} else if (option == PARSER_FLAG) {
		if (preprocess(sourceFile, preprocessedOutputFile) != 0) {
			return 1;
		}
		parse(preprocessedOutputFile);
		remove(preprocessedOutputFile.c_str());
	} else if (option == CODEGEN_FLAG) {
		if (preprocess(sourceFile, preprocessedOutputFile) != 0) {
			return 1;
		}
		codeGen(preprocessedOutputFile);
		remove(preprocessedOutputFile.c_str());
	}

	return 0;
}

int printHelpMenu() {
	cout << "The following options are supported: " << endl;
	cout << "	-h: See help menu" << endl;
	cout << "	-S: Produce an assembly file, but not assembly or link it" << endl;
	cout << "	--lex: Run the lexer, but stop before parsing" << endl;
	cout << "	--parse: run the lexer and parser, but stop before assembly generation" << endl;
	cout << "	--codegen: Directs it to perform lexing, parsing, and assembly generation, but stop before code emission" << endl;
	cout << "Example usage:" << endl;
	cout << "	./tpl -h" << endl;
	cout << "	./tpl /path/to/file/prog.c" << endl;
	cout << "	./tpl -S /path/to/file/prog.c" << endl;
	cout << "	./tpl -S /path/to/file/prog.c" << endl;
	cout << "	./tpl --lex /path/to/file/prog.c" << endl;
	cout << "	./tpl --parse /path/to/file/prog.c" << endl; 
	cout << "	./tpl --codegen /path/to/file/prog.c" << endl;

	return 0;
}

int preprocess(string inputFileName, string outputFileName) {
	return system(("gcc -E -P " + inputFileName + " -o " + outputFileName).c_str());
}

int compile(string inputFileName, string outputFileName) {
	// Temporary stub
	return system(("gcc -S " + inputFileName + " -o " + outputFileName).c_str());
}

int lex(string inputFileName) {
	cout << "Running lexer for " << inputFileName << endl;
	lexer::lex(inputFileName);
	return 0;
}

int parse(string inputFileName) {
	cout << "Running parse for " << inputFileName << endl;
	return 0;
}

int codeGen(string inputFileName) {
	cout << "Running codegen for " << inputFileName << endl;
	return 0;
}

int assembleAndLink(vector<string> inputFileNames, string outputFileName) {
	string inputFileNamesCombined{""};
	for (string inputFileName : inputFileNames) {
		inputFileNamesCombined += (inputFileName + " ");
	}
	return system(("gcc " + inputFileNamesCombined + "-o " + outputFileName).c_str());
}
