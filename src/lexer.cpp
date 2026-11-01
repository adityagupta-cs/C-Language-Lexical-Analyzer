#include <stdio.h>
#define MAX 100
#include "lexer.h"

#include <iostream>
#include <cctype>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Constructor
Lexer::Lexer(const string& input) {
    source = input;

    position = 0;
    line = 1;
    column = 1;
}

// Returns the current character
char Lexer::currentChar() {
    if (position >= source.size()) {
        return '\0';
    }

    return source[position];
}

// Looks ahead without moving the position
char Lexer::peek(int offset) {
    int nextPosition = position + offset;

    if (nextPosition >= source.size()) {
        return '\0';
    }

    return source[nextPosition];
}

// Moves to the next character
void Lexer::advance() {
    if (position >= source.size()) {
        return;
    }

    if (source[position] == '\n') {
        line++;
        column = 1;
    }
    else {
        column++;
    }

    position++;
}

void Lexer::skipWhitespace() {
    while (currentChar() != '\0' &&
           isspace(static_cast<unsigned char>(currentChar()))) {

        advance();
    }
}


void Lexer::scanIdentifierOrKeyword() {

    int startLine = line;
    int startColumn = column;

    string lexeme = "";

    // Read the complete identifier
    while (isalnum(static_cast<unsigned char>(currentChar())) ||
           currentChar() == '_') {

        lexeme += currentChar();
        advance();
    }

    // List of C keywords
    static const unordered_set<string> keywords = {
        "auto", "break", "case", "char",
        "const", "continue", "default", "do",
        "double", "else", "enum", "extern",
        "float", "for", "goto", "if",
        "int", "long", "register", "return",
        "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while",
        "_Alignas", "_Alignof", "_Atomic",
        "_Bool", "_Complex", "_Generic",
        "_Imaginary", "_Noreturn", "_Static_assert",
        "_Thread_local"
    };

    // Check whether the lexeme is a keyword
    if (keywords.count(lexeme)) {

        tokens.emplace_back(
            TokenType::KEYWORD,
            lexeme,
            startLine,
            startColumn
        );
    }
    else {

        tokens.emplace_back(
            TokenType::IDENTIFIER,
            lexeme,
            startLine,
            startColumn
        );
    }
}


void Lexer::scanNumber() {

    int startLine = line;
    int startColumn = column;

    string lexeme = "";

    bool isFloat = false;
    bool malformed = false;

    // Case 1: Number starts with a decimal point, e.g. .75
    if (currentChar() == '.') {

        isFloat = true;
        lexeme += currentChar();
        advance();

        while (isdigit(static_cast<unsigned char>(currentChar()))) {
            lexeme += currentChar();
            advance();
        }
    }

    // Case 2: Number starts with a digit, e.g. 100 or 25.5
    else {

        while (isdigit(static_cast<unsigned char>(currentChar()))) {
            lexeme += currentChar();
            advance();
        }

        // Check for decimal point
        if (currentChar() == '.') {

            isFloat = true;
            lexeme += currentChar();
            advance();

            while (isdigit(static_cast<unsigned char>(currentChar()))) {
                lexeme += currentChar();
                advance();
            }
        }
    }

    // Check for exponent: e or E
    if (currentChar() == 'e' || currentChar() == 'E') {

        isFloat = true;

        lexeme += currentChar();
        advance();

        // Optional exponent sign
        if (currentChar() == '+' || currentChar() == '-') {
            lexeme += currentChar();
            advance();
        }

        // Exponent must contain at least one digit
        if (!isdigit(static_cast<unsigned char>(currentChar()))) {
            malformed = true;
        }
        else {
            while (isdigit(static_cast<unsigned char>(currentChar()))) {
                lexeme += currentChar();
                advance();
            }
        }
    }

    // Detect invalid suffixes such as 123abc or 45xyz
    if (isalnum(static_cast<unsigned char>(currentChar())) ||
        currentChar() == '_') {

        malformed = true;

        while (isalnum(static_cast<unsigned char>(currentChar())) ||
               currentChar() == '_') {

            lexeme += currentChar();
            advance();
        }
    }

    // Detect malformed decimal forms such as 12.3.4
    if (currentChar() == '.' &&
        isdigit(static_cast<unsigned char>(peek()))) {

        malformed = true;

        while (currentChar() == '.' ||
               isdigit(static_cast<unsigned char>(currentChar()))) {

            lexeme += currentChar();
            advance();
        }
    }

    // Store the resulting token
    if (malformed) {

        tokens.emplace_back(
            TokenType::UNKNOWN,
            lexeme,
            startLine,
            startColumn
        );
    }
    else {

        TokenType type = isFloat
            ? TokenType::FLOAT_LITERAL
            : TokenType::INTEGER_LITERAL;

        tokens.emplace_back(
            type,
            lexeme,
            startLine,
            startColumn
        );
    }
}

void Lexer::scanString() {

    int startLine = line;
    int startColumn = column;

    string lexeme = "";

    lexeme += currentChar();
    advance();

    bool closed = false;
    bool malformed = false;
    string errorMessage = "";

    while (currentChar() != '\0') {

        if (currentChar() == '"') {
            lexeme += currentChar();
            advance();

            closed = true;
            break;
        }

        if (currentChar() == '\n') {
            malformed = true;
            errorMessage = "Unterminated string literal";
            break;
        }

        if (currentChar() == '\\') {

            string escape = "";

            if (!scanEscapeSequence(escape)) {
                malformed = true;
                errorMessage = "Invalid escape sequence";
            }

            lexeme += escape;
        }
        else {
            lexeme += currentChar();
            advance();
        }
    }

    if (!closed) {
        malformed = true;

        if (errorMessage.empty()) {
            errorMessage = "Unterminated string literal";
        }
    }

    if (malformed) {
        addErrorToken(lexeme, startLine, startColumn, errorMessage);
    }
    else {
        tokens.emplace_back(
            TokenType::STRING_LITERAL,
            lexeme,
            startLine,
            startColumn
        );
    }
}


void Lexer::scanCharacter() {

    int startLine = line;
    int startColumn = column;

    string lexeme = "";

    lexeme += currentChar();
    advance();

    bool closed = false;
    bool malformed = false;

    int characterCount = 0;
    string errorMessage = "";

    while (currentChar() != '\0' &&
           currentChar() != '\n') {

        if (currentChar() == '\'') {
            lexeme += currentChar();
            advance();

            closed = true;
            break;
        }

        if (currentChar() == '\\') {

            string escape = "";

            if (!scanEscapeSequence(escape)) {
                malformed = true;
                errorMessage = "Invalid escape sequence";
            }

            lexeme += escape;
            characterCount++;
        }
        else {
            lexeme += currentChar();
            advance();

            characterCount++;
        }
    }

    if (!closed) {
        malformed = true;

        if (errorMessage.empty()) {
            errorMessage = "Unterminated character literal";
        }
    }

    if (characterCount != 1) {
        malformed = true;

        if (errorMessage.empty()) {
            errorMessage = "Character literal must contain exactly one character";
        }
    }

    if (malformed) {
        addErrorToken(lexeme, startLine, startColumn, errorMessage);
    }
    else {
        tokens.emplace_back(
            TokenType::CHAR_LITERAL,
            lexeme,
            startLine,
            startColumn
        );
    }
}

void Lexer::skipComment() {

    int startLine = line;
    int startColumn = column;

    // Case 1: Single-line comment //
    if (currentChar() == '/' && peek() == '/') {

        // Consume both slashes
        advance();
        advance();

        // Skip characters until newline or end of file
        while (currentChar() != '\0' &&
               currentChar() != '\n') {

            advance();
        }
    }

    // Case 2: Multi-line comment /*
    else if (currentChar() == '/' && peek() == '*') {

        string lexeme = "";

        // Consume /*
        lexeme += currentChar();
        advance();

        lexeme += currentChar();
        advance();

        bool closed = false;

        while (currentChar() != '\0') {

            // Check for closing */
            if (currentChar() == '*' && peek() == '/') {

                lexeme += currentChar();
                advance();

                lexeme += currentChar();
                advance();

                closed = true;
                break;
            }

            lexeme += currentChar();
            advance();
        }

        // If closing */ is missing, report an error
        if (!closed) {

            tokens.emplace_back(
                TokenType::UNKNOWN,
                lexeme,
                startLine,
                startColumn
            );
        }
    }
}



void Lexer::scanOperatorOrPunctuator() {

    int startLine = line;
    int startColumn = column;

    string lexeme = "";

    // Operators arranged from longest to shortest
    static const vector<string> operators = {

        // Three-character operators
        ">>=", "<<=",

        // Two-character operators
        "++", "--", "->",
        "&&", "||",
        "<=", ">=", "==", "!=",
        "+=", "-=", "*=", "/=", "%=",
        "&=", "|=", "^=",
        "<<", ">>",

        // Single-character operators
        "+", "-", "*", "/", "%",
        "=", "<", ">",
        "!", "&", "|", "^", "~",
        "...", "."
        
    };

    // Check operators using maximal munch
    for (const string& op : operators) {

        bool match = true;

        // Compare current source characters with operator
        for (int i = 0; i < op.size(); i++) {

            if (position + i >= source.size() ||
                source[position + i] != op[i]) {

                match = false;
                break;
            }
        }

        // If operator matches
        if (match) {

            lexeme = op;

            // Move forward by operator length
            for (int i = 0; i < op.size(); i++) {
                advance();
            }

            tokens.emplace_back(
                TokenType::OPERATOR,
                lexeme,
                startLine,
                startColumn
            );

            return;
        }
    }

    // All C punctuators, including ellipsis
    static const vector<string> punctuators = {
        "[", "]",
        "(", ")",
        "{", "}",
        ".", "...",
        ",", ";",
        ":", "?"
    };

    // Check punctuators
    for (const string& p : punctuators) {

        bool match = true;

        for (int i = 0; i < p.size(); i++) {

            if (position + i >= source.size() ||
                source[position + i] != p[i]) {

                match = false;
                break;
            }
        }

        if (match) {

            lexeme = p;

            for (int i = 0; i < p.size(); i++) {
                advance();
            }

            tokens.emplace_back(
                TokenType::PUNCTUATOR,
                lexeme,
                startLine,
                startColumn
            );

            return;
        }
    }

    // If no operator or punctuator matches,
    // classify the current character as UNKNOWN
    lexeme = currentChar();

    advance();

    tokens.emplace_back(
        TokenType::UNKNOWN,
        lexeme,
        startLine,
        startColumn
    );
}


void Lexer::scanPreprocessor() {

    int startLine = line;
    int startColumn = column;

    string lexeme = "";

    // Consume the # symbol and the rest of the directive
    while (currentChar() != '\0') {

        // Handle backslash-newline continuation
        if (currentChar() == '\\' && peek() == '\n') {
            lexeme += currentChar();
            advance();

            lexeme += currentChar();
            advance();

            continue;
        }

        // Stop at the end of the directive line
        if (currentChar() == '\n') {
            break;
        }

        lexeme += currentChar();
        advance();
    }

    tokens.emplace_back(
        TokenType::PREPROCESSOR,
        lexeme,
        startLine,
        startColumn
    );
}


bool Lexer::scanEscapeSequence(string& lexeme) {

    // Current character must be backslash
    if (currentChar() != '\\') {
        return false;
    }

    lexeme += currentChar();
    advance();

    char ch = currentChar();

    if (ch == '\0' || ch == '\n') {
        return false;
    }

    // Valid simple escape sequences
    string validEscapes = "'\"?\\abfnrtv";

    if (validEscapes.find(ch) != string::npos) {

        lexeme += currentChar();
        advance();

        return true;
    }

    // Octal escape: \0 to \777
    if (ch >= '0' && ch <= '7') {

        int count = 0;

        while (count < 3 &&
               currentChar() >= '0' &&
               currentChar() <= '7') {

            lexeme += currentChar();
            advance();

            count++;
        }

        return true;
    }

    // Hexadecimal escape: \x followed by hex digits
    if (ch == 'x') {

        lexeme += currentChar();
        advance();

        int count = 0;

        while (isxdigit(static_cast<unsigned char>(currentChar()))) {

            lexeme += currentChar();
            advance();

            count++;
        }

        return count > 0;
    }

    // Universal character name: \u followed by 4 hex digits
    if (ch == 'u' || ch == 'U') {

        int requiredDigits = (ch == 'u') ? 4 : 8;

        lexeme += currentChar();
        advance();

        for (int i = 0; i < requiredDigits; i++) {

            if (!isxdigit(static_cast<unsigned char>(currentChar()))) {
                return false;
            }

            lexeme += currentChar();
            advance();
        }

        return true;
    }

    // Unknown escape sequence
    lexeme += currentChar();
    advance();

    return false;
}


vector<Token> Lexer::tokenize() {

    while (currentChar() != '\0') {

        // 1. Ignore whitespace
        if (isspace(static_cast<unsigned char>(currentChar()))) {
            skipWhitespace();
            continue;
        }

        // 2. Handle comments before operators
        if (currentChar() == '/' &&
            (peek() == '/' || peek() == '*')) {

            skipComment();
            continue;
        }

        // 3. Handle preprocessor directives
        if (currentChar() == '#') {
            scanPreprocessor();
            continue;
        }

        // 4. Handle identifiers and keywords
        if (isalpha(static_cast<unsigned char>(currentChar())) ||
            currentChar() == '_') {

            scanIdentifierOrKeyword();
            continue;
        }

        // 5. Handle numbers
        if (isdigit(static_cast<unsigned char>(currentChar())) ||
            (currentChar() == '.' &&
             isdigit(static_cast<unsigned char>(peek())))) {

            scanNumber();
            continue;
        }

        // 6. Handle string literals
        if (currentChar() == '"') {
            scanString();
            continue;
        }

        // 7. Handle character literals
        if (currentChar() == '\'') {
            scanCharacter();
            continue;
        }

        // 8. Handle operators and punctuators
        scanOperatorOrPunctuator();
    }

    return tokens;
}

void Lexer::addErrorToken(
    const std::string& lexeme,
    int errorLine,
    int errorColumn,
    const std::string& message
) {
    tokens.emplace_back(
        TokenType::UNKNOWN,
        lexeme,
        errorLine,
        errorColumn,
        message
    );
}
