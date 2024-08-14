#include "lang.h"
#include <iostream>

Language::Language(const std::vector<Token>& tokens)
{
	this->tokens = tokens;
}

Language::Language()
{

}

std::vector<Token> Language::Lex(const std::string& code)
{
	std::vector<Token> tokens;
	std::string currentToken;
	for (char c : code)
	{
		if (std::isspace(c))
		{
			continue;
		}
		if (std::isalpha(c))
		{
			currentToken += c;
		}
		else if (std::isdigit(c))
		{
			currentToken += c;
		} 
		else
		{
			if (currentToken.empty())
			{
				tokens.push_back({ TokenType::Identifier, currentToken });
				currentToken.clear();
			}
			tokens.push_back({ TokenType::Operator, std::string(1, c) });
		}
	}
	if (!currentToken.empty())
	{
		tokens.push_back({ TokenType::Identifier, currentToken });
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
