# Project Architecture – C Language Lexical Analyzer

## 1. Introduction

The C Language Lexical Analyzer is developed using C++17. It analyzes C source code and converts it into a sequence of tokens.

The project follows a modular architecture in which different files handle input processing, lexical analysis, token representation, and report generation.

## 2. Architecture Overview

The project consists of four main source modules:

1. `main.cpp`
2. `lexer.cpp`
3. `token.cpp`
4. `report.cpp`

The header files define the interfaces and data structures shared between these modules.

## 3. Module Description

### 3.1 main.cpp – Main Driver Module

Responsibilities:

- Accepts the C source file path.
- Opens and reads the source file.
- Loads the source code into a string.
- Creates an object of the Lexer class.
- Calls the tokenize() function.
- Sends the generated tokens to the reporting module.

### 3.2 lexer.cpp – Lexical Analysis Module

This is the core module of the project.

Responsibilities:

- Reads source code character by character.
- Identifies keywords and identifiers.
- Recognizes integer and floating-point literals.
- Recognizes string and character literals.
- Identifies operators and punctuators.
- Skips single-line and multi-line comments.
- Recognizes preprocessor directives.
- Validates supported escape sequences.
- Detects malformed tokens and lexical errors.
- Tracks line and column positions.

The lexer uses helper functions to perform different scanning operations.

### 3.3 token.cpp – Token Management Module

The token module implements the token type conversion function.

Responsibilities:

- Converts token categories into readable names.
- Provides readable descriptions of token types for reports.

The Token structure and TokenType enumeration are declared in `token.h`.

Each token stores:

- Token type
- Lexeme
- Line number
- Column number
- Error message, when applicable

### 3.4 report.cpp – Reporting Module

Responsibilities:

- Displays the token table in the terminal.
- Displays lexical errors with their locations.
- Calculates the total number of tokens.
- Calculates the total number of lexical errors.
- Saves the lexical analysis report into a text file.

The generated report is stored in:

`output/token_report.txt`

## 4. Processing Workflow

The lexical analysis process follows these steps:

1. The main module reads the input C source file.
2. The source code is passed to the Lexer object.
3. The lexer scans the source code character by character.
4. Whitespace and comments are skipped.
5. Tokens are identified and classified.
6. Supported escape sequences and malformed tokens are validated.
7. Each token is stored with its source position.
8. The token collection is passed to the reporting module.
9. The final report is displayed and saved.

## 5. Token Representation

The project uses an enumeration named `TokenType` to classify tokens.

Supported categories include:

- KEYWORD
- IDENTIFIER
- INTEGER_LITERAL
- FLOAT_LITERAL
- STRING_LITERAL
- CHAR_LITERAL
- OPERATOR
- PUNCTUATOR
- PREPROCESSOR
- UNKNOWN

The `UNKNOWN` category is used for malformed or unrecognized input detected by the lexer.

## 6. Error Handling

The lexer performs basic lexical error detection.

Examples include:

- Invalid escape sequences.
- Malformed numeric literals.
- Unterminated string literals.
- Invalid character literals.
- Unterminated block comments.
- Unrecognized characters.

Error information is stored with the corresponding UNKNOWN token and displayed in the final report.

## 7. Output Generation

The project generates two forms of output:

1. Terminal output containing the token table and lexical error details.
2. A text report saved at `output/token_report.txt`.

Each token includes its line and column position to help locate it in the original source code.

## 8. Conclusion

The modular architecture makes the lexical analyzer easier to understand, maintain, test, and extend.

The project demonstrates fundamental compiler design concepts, including lexical analysis, token classification, source position tracking, and lexical error detection.

**Note:** This is an educational lexical analyzer supporting a subset of C language constructs. It is not a fully ISO C-compliant lexer.