
#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,

    INTEGER_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    CHAR_LITERAL,

    OPERATOR,
    PUNCTUATOR,
    PREPROCESSOR,

    UNKNOWN
};


struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
    std::string errorMessage;

    Token(
        TokenType t,
        const std::string& value,
        int ln,
        int col,
        const std::string& error = ""
    )
        : type(t),
          lexeme(value),
          line(ln),
          column(col),
          errorMessage(error) {}
};


std::string tokenTypeToString(TokenType type);

#endif
