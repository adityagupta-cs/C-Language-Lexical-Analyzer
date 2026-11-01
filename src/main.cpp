
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "lexer.h"
#include "report.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Default input file
    string filename = "example/input_program.c";

    // Accept custom input file
    if (argc > 1) {
        filename = argv[1];
    }

    // Open source file
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file: "
             << filename << endl;

        return 1;
    }

    // Read complete source code
    stringstream buffer;
    buffer << inputFile.rdbuf();

    string sourceCode = buffer.str();

    inputFile.close();

    // Create Lexer
    Lexer lexer(sourceCode);

    // Generate tokens
    vector<Token> tokens = lexer.tokenize();

    // Display report
    printTokenReport(tokens, filename);

    // Save report
    saveTokenReport(
        tokens,
        filename,
        "output/token_report.txt"
    );

    return 0;
}
