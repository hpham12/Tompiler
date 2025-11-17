#pragma once

#include <unordered_map>
#include <map>
#include <iostream>

using namespace std;

enum TokenType {
	IDENTIFIER, CONSTANT, INT_KEYWORD, VOID_KEYWORD, RETURN_KEYWORD,
	OPEN_PARENTHESIS, CLOSE_PARENTHESIS, OPEN_BRACE, CLOSE_BRACE, SEMICOLON,
	UNKNOWN
};

inline map<string, TokenType> regexes = {
	{"[a-zA-Z_]\\w*\\b", IDENTIFIER},
	{"[0-9]+\\b", CONSTANT},
	{"int\\b", INT_KEYWORD},
	{"void\\b", VOID_KEYWORD},
	{"return\\b", RETURN_KEYWORD},
	{"\\(", OPEN_PARENTHESIS},
	{"\\)", CLOSE_PARENTHESIS},
	{"\\{", OPEN_BRACE},
	{"\\}", CLOSE_BRACE},
	{";", SEMICOLON}
};

inline map<string, TokenType> keywordRegexes = {
	{"int\\b", INT_KEYWORD},
	{"void\\b", VOID_KEYWORD},
	{"return\\b", RETURN_KEYWORD}
};

inline unordered_map<TokenType, string> values = {
	{INT_KEYWORD, "int"},
	{VOID_KEYWORD, "void"},
	{RETURN_KEYWORD, "return"},
	{OPEN_PARENTHESIS, "("},
	{CLOSE_PARENTHESIS, ")"},
	{OPEN_BRACE, "{"},
	{CLOSE_BRACE, "}"},
	{SEMICOLON, ";"}
};

namespace lexer {
	class Token {
		TokenType type;
	public:
		explicit Token(TokenType t) : type(t) {}

		Token() : type(UNKNOWN) {}

		TokenType getType() const {
			return type;
		}

		virtual void* getValue() {
			return &values[type];
		}
	};

	class IdentifierToken final : public Token {
		string value;

	public:
		explicit IdentifierToken(string value) : Token(IDENTIFIER), value(value) {
			
		}

		void* getValue() override {
			return &value;
		}
	};

	class ConstantToken final : public Token {
		int value;

	public:
		explicit ConstantToken(int value) : Token(CONSTANT), value(value) {
		}

		void* getValue() override {
			return &value;
		}
	};

	vector<Token*> lex(const string& inputFileName);
}