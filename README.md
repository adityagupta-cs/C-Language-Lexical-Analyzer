# C Language Lexical Analyzer (Tokenizer)

A C language lexical analyzer developed using **C++17** as part of a Compiler Design project. It reads C source code, identifies tokens, validates supported lexical patterns, and generates a detailed token report with line and column information.

## 🚀 Features

- **Keyword Recognition:** Identifies C keywords such as `int`, `float`, `if`, `while`, and `return`.
- **Identifier Recognition:** Detects variable names and function identifiers.
- **Numeric Literals:** Recognizes integer and floating-point literals.
- **String and Character Literals:** Identifies string and character constants.
- **Escape Sequence Validation:** Validates supported escape sequences such as `\n`, `\t`, `\\`, and `\"`.
- **Operator Recognition:** Detects arithmetic, relational, logical, assignment, and other supported operators.
- **Punctuator Recognition:** Identifies symbols such as `{}`, `()`, `[]`, `;`, and `,`.
- **Comment Removal:** Skips single-line (`//`) and multi-line (`/* */`) comments.
- **Preprocessor Recognition:** Identifies preprocessor directives such as `#include`.
- **Lexical Error Detection:** Detects malformed tokens and invalid escape sequences.
- **Position Tracking:** Tracks the line and column of each token.
- **Detailed Reports:** Displays token information and lexical errors in the terminal and saves the report to a text file.

## 🛠️ Technologies Used

- C++17
- Standard Template Library (STL)
- File Handling
- Object-Oriented Programming
- VS Code
- GCC / G++

## 📁 Project Structure

```text
Tokenizer/
│
├── src/
│   ├── main.cpp
│   ├── lexer.cpp
│   ├── token.cpp
│   └── report.cpp
│
├── include/
│   ├── lexer.h
│   ├── token.h
│   └── report.h
│
├── example/
│   ├── input_program.c
│   └── test_errors.c
│
├── tests/
│   ├── test_keywords.c
│   ├── test_operators.c
│   ├── test_comments.c
│   └── test_literals.c
│
├── output/
│   └── token_report.txt
│
├── lexer.exe
└── README.md
```

## ⚙️ Installation and Execution

### 1. Clone the repository

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

### 2. Navigate to the project directory

```bash
cd Tokenizer
```

### 3. Compile the project

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/lexer.cpp src/token.cpp src/report.cpp -o lexer.exe
```

### 4. Run the lexer

Run the default example:

```bash
./lexer.exe
```

Or provide a custom C source file:

```bash
./lexer.exe example/test_errors.c
```

On Windows PowerShell, use:

```powershell
.\lexer.exe
```

## 🧪 Testing

The project includes test programs covering the following areas:

| Test File | Purpose |
|---|---|
| `test_keywords.c` | Tests keyword and identifier recognition |
| `test_operators.c` | Tests operator and punctuator recognition |
| `test_comments.c` | Tests single-line and multi-line comment removal |
| `test_literals.c` | Tests string, character, and escape sequence validation |

The test cases verify correct token classification, source position tracking, and lexical error reporting.

## 📊 Sample Output

```text
LINE:COL    TOKEN TYPE              LEXEME
----------------------------------------------------------
1:1         KEYWORD                 int
1:5         IDENTIFIER              main
1:9         PUNCTUATOR              (
1:10        PUNCTUATOR              )
1:12        PUNCTUATOR              {
2:5         KEYWORD                 int
2:9         IDENTIFIER              a
2:11        OPERATOR                =
2:13        INTEGER_LITERAL         10
2:15        PUNCTUATOR              ;

Total Tokens: 9

========== LEXICAL ERRORS ==========
No lexical errors found!

Total Lexical Errors: 0
```

## 🧠 Concepts Implemented

- Lexical Analysis
- Tokenization
- Maximal Munch Principle
- Finite State Based Scanning
- Symbol Classification
- Source Code Position Tracking
- Lexical Error Handling

## 🔮 Future Improvements

- Support for additional C numeric literal formats.
- More comprehensive C lexical standard compliance.
- Improved lexical error diagnostics.
- Support for additional preprocessing constructs.
- Automated regression testing.

## 👨‍💻 Author

**Aditya Gupta**

B.Tech – Computer Science and Engineering (Artificial Intelligence)

---

*This project implements an educational lexical analyzer for a supported subset of C language constructs. It is not intended to be a fully ISO C-compliant compiler lexer.*