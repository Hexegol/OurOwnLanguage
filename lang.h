#pragma once
#include <string>
#include <vector>

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
    std::vector<Token> Lex(const std::string& code);
    std::vector<Token> Parse(const std::vector<Token>& tokens);
};
