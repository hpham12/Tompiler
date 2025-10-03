#include <set>

#pragma once

using namespace std;

const string PREPROCESS_FLAG = "-E";
const string COMPILE_FLAG = "-S";
const string ASSEMBLE_FLAG = "-c";
const set<string> VALID_STEP_FLAGS = {PREPROCESS_FLAG, COMPILE_FLAG, ASSEMBLE_FLAG};
const string OUTPUT_FLAG = "-o";

const string LEXER_FLAG = "--lex";
const string PARSER_FLAG = "--parse";
const string CODEGEN_FLAG = "--codegen";
const set<string> VALID_COMPILER_FLAG = {LEXER_FLAG, PARSER_FLAG, CODEGEN_FLAG};

int runCompilerDriver(vector<string> args, int argc);
