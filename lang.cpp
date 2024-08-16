#include "lang.h"
#include <iostream>
#include "ASTNode.h"

Language::Language(const std::vector<Token>& tokens)
{
	this->tokens = tokens;
}

Language::Language()
{

}

std::vector<Token> Language::Lex(const std::string& code) {
	std::vector<Token> tokens;
	std::string currentToken;
	TokenType currentType;

	for (char ch : code) {
		if (isspace(ch)) {
			continue;
		}

		if (isalpha(ch)) {
			currentToken += ch;
			currentType = TokenType::Identifier;
		}
		else if (isdigit(ch)) {
			currentToken += ch;
			currentType = TokenType::Number;
		}
		else if (ch == '=') {
			if (!currentToken.empty()) {
				tokens.push_back({ currentType, currentToken });
				currentToken.clear();
			}
			tokens.push_back({ TokenType::Operator, std::string(1, ch) });
		}
		else if (ch == ';') {
			if (!currentToken.empty()) {
				tokens.push_back({ currentType, currentToken });
				currentToken.clear();
			}
			tokens.push_back({ TokenType::Symbol, std::string(1, ch) });
		}
		else {
			std::cerr << "Lexing error: unknown character '" << ch << "'" << std::endl;
		}
	}

	if (!currentToken.empty()) {
		tokens.push_back({ currentType, currentToken });
	}

	return tokens;
}



std::vector<Token> Language::Parse(const std::vector<Token>& tokens)
{
	std::vector<Token> parsedTokens;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i].type == TokenType::Keyword && tokens[i].value == "int")
		{
			if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::Identifier)
			{
				parsedTokens.push_back(tokens[i]);
				parsedTokens.push_back(tokens[i + 1]);
				if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::Operator)
				{
					parsedTokens.push_back(tokens[i + 2]);
					if (i + 3 < tokens.size() && tokens[i + 3].type == TokenType::Number)
					{
						parsedTokens.push_back(tokens[i + 3]);
						i += 4;
					}
					else
					{
						std::cerr << "syntax error : waited expression after '='." << std::endl;
						break;
					}
				}
				else
				{
					std::cerr << "syntax error : '=' waited after identificator" << std::endl;
					break;
				}
			}
			else
			{
				std::cerr << "syntax error : identificator waited after keyword 'int'" << std::endl;
				break;
			}
		}
		else
		{
			parsedTokens.push_back(tokens[i]);
			i++;
		}
	}
	return parsedTokens;
}


std::unique_ptr<ASTNode> Language::ParseAST(const std::vector<Token>& tokens) {
	std::unique_ptr<ASTNode> root = nullptr;
	for (size_t i = 0; i < tokens.size();) {
		if (tokens[i].type == TokenType::Keyword && tokens[i].value == "int") 
		{
			if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::Identifier)
			{
				auto idNode = std::make_unique<IdentifierNode>(tokens[i + 1].value);

				if (i + 2 < tokens.size() && tokens[i + 2].type == TokenType::Operator && tokens[i + 2].value == "=")
				{
					if (i + 3 < tokens.size() && tokens[i + 3].type == TokenType::Number)
					{
						auto numNode = std::make_unique<NumberNode>(std::stoi(tokens[i + 3].value));
						auto assignNode = std::make_unique<BinaryOpNode>("=", std::move(idNode), std::move(numNode));
						root = std::make_unique<VariableDeclNode>("int", std::move(assignNode));
						i += 4;  
					}
					else 
					{
						std::cerr << "syntax error : waited expression after '='." << std::endl;
						return nullptr;
					}
				}
				else 
				{
					std::cerr << "syntax error : '=' waited after identificator" << std::endl;
					return nullptr;
				}
			}
			else 
			{
				std::cerr << "syntax error : identificator waited after keyword 'int'" << std::endl;
				return nullptr;
			}
		}
		else 
		{
			i++;
		}
	}
	return root;
}

