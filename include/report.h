
#ifndef REPORT_H
#define REPORT_H

#include <string>
#include <vector>
#include "token.h"

void printTokenReport(
    const std::vector<Token>& tokens,
    const std::string& filename
);

void saveTokenReport(
    const std::vector<Token>& tokens,
    const std::string& filename,
    const std::string& outputPath
);

#endif
