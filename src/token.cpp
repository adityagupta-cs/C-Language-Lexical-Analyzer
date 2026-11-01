
#include "token.h"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD:
            return "KEYWORD";

        case TokenType::IDENTIFIER:
            return "IDENTIFIER";

        case TokenType::INTEGER_LITERAL:
            return "INTEGER_LITERAL";

        case TokenType::FLOAT_LITERAL:
            return "FLOAT_LITERAL";

        case TokenType::STRING_LITERAL:
            return "STRING_LITERAL";

        case TokenType::CHAR_LITERAL:
            return "CHAR_LITERAL";

        case TokenType::OPERATOR:
            return "OPERATOR";

        case TokenType::PUNCTUATOR:
            return "PUNCTUATOR";

        case TokenType::PREPROCESSOR:
            return "PREPROCESSOR";

        case TokenType::UNKNOWN:
            return "UNKNOWN";
    }

    return "UNKNOWN";
}
