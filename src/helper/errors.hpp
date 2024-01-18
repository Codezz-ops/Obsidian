#pragma once

#include "../../inc/colorize.h"
#include "../lexer/lexer.hpp"
#include "../common.hpp"
#include <iostream>
#include <cstring>

class Error {
public:
    static void error(Lexer::Token token, std::string msg, Lexer &lexer) {
    int errorCount = 0;
    std::cout << termcolor::red << "Error" << termcolor::reset
              << ": [line: " << termcolor::bright_blue << token.line << termcolor::reset
              << ", column: " << termcolor::bright_blue << token.column
              << termcolor::reset << "] " << termcolor::yellow << msg
              << termcolor::reset << std::endl;

    const char *lineStart = lexer.lineStart(token.line);
    const char *lineEnd = lineStart;
    while (*lineEnd != '\n' && *lineEnd != '\0')
      lineEnd++;
    std::cout << "    " << token.line << " | " << std::string(lineStart, lineEnd - lineStart) << std::endl;
    std::cout << "      |" << std::string(token.column, ' ') << termcolor::red << "^" << termcolor::reset << std::endl;

    if (errorCount == 5)
      Exit(ExitValue::_ERROR);
    errorCount++;
  }
};