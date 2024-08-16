#pragma once
#include <string>
#include <vector>
#include "ASTNode.h"

enum class TokenType {
    Keyword,
    Identifier,
    Number,
    Operator,
    Symbol,
};

struct Token {
    enum class TokenType type;
    std::string value;
};



class Language {
private:
    std::vector<Token> tokens;
    
public:
    Language(const std::vector<Token>& tokens);
    Language();
    std::vector<Token> Lex(const std::string& code);
    std::vector<Token> Parse(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> ParseAST(const std::vector<Token>& tokens);
};
