#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "lexer.h"

using namespace std;

namespace lexer {
	string readFileContent(const string& inputFileName);
	vector<Token*> tokenize(const string& input);
	TokenType getTokenType(const string& input);
	Token* createToken(TokenType type, void *value);

	vector<Token*> lex(const string& inputFileName) {
		string inputString = readFileContent(inputFileName);
		vector<Token*> tokens = tokenize(inputString);

		return tokens;
	}

	string readFileContent(const string& inputFileName) {
		ifstream inputFile;
		inputFile.open(inputFileName, ios::in | ios::ate);

		streampos size = inputFile.tellg();
		char* memBlock = new char [size];

		inputFile.seekg(0, ios::beg);
		inputFile.read(memBlock, size);

		inputFile.close();

		const string inputString = memBlock;

		return inputString;
	}

	vector<Token*> tokenize(const string& input) {
		size_t startingPos = 0;
		size_t currentPos = 0;
		size_t lastIndexWithValidToken = 0;
		TokenType lastValidTokenType = UNKNOWN;
		vector<Token*> tokens;
		while (currentPos < input.length()) {
			string token = input.substr(startingPos, currentPos - startingPos + 1);
			TokenType tokenType = getTokenType(token);
			if (tokenType != UNKNOWN) {
				lastValidTokenType = tokenType;
				lastIndexWithValidToken = currentPos;
				currentPos++;
				if (currentPos == input.length()) {
					string validTokenStr = input.substr(startingPos, lastIndexWithValidToken - startingPos + 1);
					Token* validToken = createToken(lastValidTokenType, &validTokenStr);
					tokens.push_back(validToken);
					break;
				}
			} else if (lastValidTokenType != UNKNOWN) {
				string validTokenStr = input.substr(startingPos, lastIndexWithValidToken - startingPos + 1);
				Token* validToken = createToken(lastValidTokenType, &validTokenStr);
				tokens.push_back(validToken);
				lastValidTokenType = UNKNOWN;
				startingPos = lastIndexWithValidToken + 1;
				while ((input[startingPos] == ' ' || input[startingPos] == '\n') && startingPos < input.length()) {
					startingPos++;
				}
				currentPos = startingPos;
			} else {
				throw;
			}
		}

		return tokens;
	}

	TokenType getTokenType(const string& input) {
		for (auto it = regexes.begin(); it != regexes.end(); ++it) {
			if (regex_match(input, regex(it->first))) {
				for (auto keywordIt = keywordRegexes.begin(); keywordIt != keywordRegexes.end(); ++keywordIt) {
					if (regex_match(input, regex(keywordIt->first))) {
						return keywordIt->second;
					}
				}
				return it->second;
			}
		}

		return UNKNOWN;
	}

	Token* createToken(TokenType type, void *value) {
		Token *token;
		if (type == IDENTIFIER) {
		
			token = new IdentifierToken(*(string*) value);
		} else if (type == CONSTANT) {
			string strVal = *(string*) value;
			int intVal = stoi(strVal);
			token = new ConstantToken(intVal);
		} else {
			token = new Token(type);
		}

		return token;
	}
}
