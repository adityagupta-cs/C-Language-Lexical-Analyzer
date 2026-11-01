#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "token.h"

class Lexer {

private:

    std::string source;

    int position;
    int line;
    int column;

    std::vector<Token> tokens;

    char currentChar();
    char peek(int offset = 1);
    void advance();

    void skipWhitespace();
    void skipComment();
    void scanPreprocessor();

    void scanIdentifierOrKeyword();
    void scanNumber();
    void scanString();
    void scanCharacter();
    bool scanEscapeSequence(std::string& lexeme);
    void scanOperatorOrPunctuator();

    void addErrorToken(
    const std::string& lexeme,
    int errorLine,
    int errorColumn,
    const std::string& message
);

public:

    Lexer(const std::string& input);

    std::vector<Token> tokenize();
};

#endif
