#include "lang.h"

Language::Language(const std::vector<Token>& tokens)
{
	this->tokens = tokens;
}

std::vector<Token> Language::Lex(const std::string& code)
{
	std::vector<Token> tokens;
	return tokens;
}


std::vector<Token> Language::Parse(const std::vector<Token>& tokens)
{
	std::vector<Token> tokens;
	return tokens;
}