#include <set>

#pragma once

using namespace std;

const string COMPILE_FLAG = "-S";
const string HELP_FLAG = "-h";
const string LEXER_FLAG = "--lex";
const string PARSER_FLAG = "--parse";
const string CODEGEN_FLAG = "--codegen";
const set<string> VALID_OPTIONS = {
	LEXER_FLAG, PARSER_FLAG, CODEGEN_FLAG,
	COMPILE_FLAG, HELP_FLAG
};

int runCompilerDriver(vector<string> args);
int printHelpMenu();
int preprocess(string inputFileName, string outputFileName);
int compile(string inputFileName, string outputFileName);
int lex(string inputFileNam);
int parse(string inputFileName);
int codeGen(string inputFileName);
int assembleAndLink(vector<string> inputFileNames, string outputFileName);
