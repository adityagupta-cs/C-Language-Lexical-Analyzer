
#include "report.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Function to display the token report
void printTokenReport(
    const vector<Token>& tokens,
    const string& filename
) {

    cout << "\n========== LEXICAL ANALYSIS REPORT ==========\n\n";

    cout << "File: " << filename << "\n\n";

    cout << left
         << setw(12) << "LINE:COL"
         << setw(24) << "TOKEN TYPE"
         << "LEXEME\n";

    cout << "----------------------------------------------------------\n";

    for (const Token& token : tokens) {

        string location =
            to_string(token.line) + ":" +
            to_string(token.column);

        cout << left
             << setw(12) << location
             << setw(24) << tokenTypeToString(token.type)
             << token.lexeme << "\n";
    }

    cout << "\nTotal Tokens: " << tokens.size() << "\n";

    // Display lexical errors
    cout << "\n========== LEXICAL ERRORS ==========\n";

    int errorCount = 0;

    for (const Token& token : tokens) {

        if (token.type == TokenType::UNKNOWN) {

            errorCount++;

            cout << "\n" << errorCount << ". "
                 << token.errorMessage << "\n";

            cout << "   Lexeme: " << token.lexeme << "\n";

            cout << "   Line: " << token.line
                 << ", Column: " << token.column << "\n";
        }
    }

    if (errorCount == 0) {
        cout << "No lexical errors found!\n";
    }

    cout << "\nTotal Lexical Errors: " << errorCount << "\n";
}


// Function to save the report in a file
void saveTokenReport(
    const vector<Token>& tokens,
    const string& filename,
    const string& outputPath
) {

    ofstream outputFile(outputPath);

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to create report file.\n";
        return;
    }

    outputFile << "========== LEXICAL ANALYSIS REPORT ==========\n\n";

    outputFile << "File: " << filename << "\n\n";

    outputFile << left
               << setw(12) << "LINE:COL"
               << setw(24) << "TOKEN TYPE"
               << "LEXEME\n";

    outputFile << "----------------------------------------------------------\n";

    int errorCount = 0;

    for (const Token& token : tokens) {

        string location =
            to_string(token.line) + ":" +
            to_string(token.column);

        outputFile << left
                   << setw(12) << location
                   << setw(24) << tokenTypeToString(token.type)
                   << token.lexeme << "\n";
    }

    outputFile << "\nTotal Tokens: " << tokens.size() << "\n";

    // Save detailed lexical errors
    outputFile << "\n========== LEXICAL ERRORS ==========\n";

    for (const Token& token : tokens) {

        if (token.type == TokenType::UNKNOWN) {

            errorCount++;

            outputFile << "\n" << errorCount << ". "
                       << token.errorMessage << "\n";

            outputFile << "   Lexeme: " << token.lexeme << "\n";

            outputFile << "   Line: " << token.line
                       << ", Column: " << token.column << "\n";
        }
    }

    if (errorCount == 0) {
        outputFile << "No lexical errors found!\n";
    }

    outputFile << "\nTotal Lexical Errors: " << errorCount << "\n";

    outputFile.close();

    cout << "\nReport saved successfully at: "
         << outputPath << "\n";
}
