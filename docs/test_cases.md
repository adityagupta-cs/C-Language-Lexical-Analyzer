# Test Cases – C Language Lexical Analyzer

## 1. Introduction

This document describes the test cases used to verify the functionality of the C Language Lexical Analyzer.

The test programs cover token recognition, operator identification, comment removal, literal validation, and lexical error detection.

## 2. Test Case 1 – Keyword Recognition

**File:** `tests/test_keywords.c`

**Objective:** Verify that C keywords and identifiers are classified correctly.

**Test input:**

```c
int main() {
    int a = 10;
    float b = 20.5;
    char c = 'A';

    if (a > 5) {
        return 0;
    }

    while (a > 0) {
        a--;
    }

    return 0;
}
```

**Expected results:**

- Keywords such as `int`, `float`, `char`, `if`, `while`, and `return` are recognized.
- Names such as `main`, `a`, `b`, and `c` are recognized as identifiers.
- No lexical errors are expected.

**Observed results:**

- Total tokens: 46
- Lexical errors: 0
- Status: PASSED

## 3. Test Case 2 – Operator Recognition

**File:** `tests/test_operators.c`

**Objective:** Verify the recognition of arithmetic, relational, logical, increment, decrement, and assignment operators.

**Test input:**

```c
int main() {
    int a = 10;
    int b = 5;

    a++;
    b--;

    int sum = a + b;
    int diff = a - b;
    int product = a * b;
    int division = a / b;

    if (a >= b && a != 0) {
        a += b;
    }

    return 0;
}
```

**Expected results:**

- Operators such as `++`, `--`, `+`, `-`, `*`, `/`, `>=`, `&&`, `!=`, and `+=` are recognized.
- Multi-character operators are recognized as single tokens.
- No lexical errors are expected.

**Observed results:**

- Total tokens: 69
- Lexical errors: 0
- Status: PASSED

## 4. Test Case 3 – Comment Removal

**File:** `tests/test_comments.c`

**Objective:** Verify that single-line and multi-line comments are ignored during tokenization.

**Test input:**

```c
#include <stdio.h>

// Single-line comment

int main() {

    /*
       Multi-line comment
       This should be ignored.
    */

    int a = 10; // Inline comment

    printf("Value: %d", a);

    return 0;
}
```

**Expected results:**

- Single-line comments are skipped.
- Multi-line comments are skipped.
- Inline comments are skipped.
- Code outside comments is tokenized correctly.

**Observed results:**

- Total tokens: 22
- Lexical errors: 0
- Status: PASSED

## 5. Test Case 4 – Literal and Escape Sequence Validation

**File:** `tests/test_literals.c`

**Objective:** Verify string literals, character literals, and supported escape sequences.

**Test input:**

```c
int main() {

    char a = 'A';
    char b = '\n';
    char c = '\t';

    char message[] = "Hello World";
    char path[] = "C:\\Users\\Student";

    char d = '\q';

    return 0;
}
```

**Expected results:**

- Valid character literals are recognized.
- Valid string literals are recognized.
- Supported escape sequences are accepted.
- Invalid escape sequence `\q` is reported as a lexical error.

**Observed results:**

- Total tokens: 43
- Lexical errors: 1
- Detected error: Invalid escape sequence `\q`
- Status: PASSED (expected error detected)

## 6. Test Summary

| Test Case | Total Tokens | Lexical Errors | Result |
|---|---:|---:|---|
| Keyword Recognition | 46 | 0 | PASSED |
| Operator Recognition | 69 | 0 | PASSED |
| Comment Removal | 22 | 0 | PASSED |
| Literal Validation | 43 | 1 expected | PASSED |

## 7. Conclusion

All four test programs produced the expected results.

The testing process verifies the implemented token recognition, comment removal, escape sequence validation, source position tracking, and basic lexical error reporting functionality.

These tests cover selected cases of the supported C language subset and do not establish complete ISO C compliance.