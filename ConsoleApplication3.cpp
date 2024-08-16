#include <iostream>
#include <windows.h>
#include "lang.h"
#include <vector>

void checkTokens(std::string code)
{
    Language language;
    std::vector<Token> tokens = language.Lex(code);
    std::cout << "tokens : " << std::endl;
    for (Token& token : tokens)
    {
        std::cout << "type : ";
        switch (token.type)
        {
        case TokenType::Keyword:
            std::cout << "keyword";
            break;
        case TokenType::Identifier:
            std::cout << "identifier";
            break;
        case TokenType::Number:
            std::cout << "number";
            break;
        case TokenType::Operator:
            std::cout << "operator";
            break;
        case TokenType::Symbol:
            std::cout << "symbol";
            break;
        }
        std::cout << "\nvalue : " << token.value << std::endl;
        std::cout << std::endl;
    }

    std::vector<Token> parsedTokens = language.Parse(tokens);

    std::cout << "\n\n\nparsed tokens : " << std::endl;
    for (Token& token : parsedTokens)
    {
        std::cout << "type : ";
        switch (token.type)
        {
        case TokenType::Keyword:
            std::cout << "keyword";
            break;
        case TokenType::Identifier:
            std::cout << "identifier";
            break;
        case TokenType::Number:
            std::cout << "number";
            break;
        case TokenType::Operator:
            std::cout << "operator";
            break;
        case TokenType::Symbol:
            std::cout << "symbol";
            break;
        }
        std::cout << "\nvalue : " << token.value << std::endl;
        std::cout << std::endl;
    }
}


int main()
{

    std::string code = "int x = 42;";

    Language language;

    std::vector<Token> tokens = language.Lex(code);

    std::cout << "Tokens :" << std::endl;
    for (const auto& token : tokens) {
        std::cout << "Type : " << static_cast<int>(token.type) << ", Value : " << token.value << std::endl;
    }

    std::unique_ptr<ASTNode> ast = language.ParseAST(tokens); 

    if (ast) {
        std::cout << "AST generated" << std::endl;
    }
    else {
        std::cout << "failed to generate AST" << std::endl;
    }

    checkTokens(code);

    return 0;
}


