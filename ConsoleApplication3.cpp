#include <iostream>
#include <windows.h>
#include "lang.h"
#include <vector>
#include "Context.h"

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


int main() {
    std::string code = "int x = 42;";
    Context context;
    Language language;
    std::vector<Token> tokens = language.Lex(code);
    std::unique_ptr<ASTNode> ast = language.ParseAST(tokens);

    if (ast)
    {
        int result = ast->interpret(context);
        std::cout << "result : " << result << std::endl;
    }
    else
    {
        std::cout << "failed to generate AST" << std::endl;
    }

    return 0;
}
