#pragma once

#include <iostream>
#include <string>
#include "../lexer/tokens.h"
#include "../../inc/colorize.h"
using namespace Obsidian;

class LexerError {
private:
public:
    static void error_lexer(Tokens::Scanner *scanner, std::string message) {
        std::cout << termcolor::red << "Error" << termcolor::reset 
          << ": [line: " << termcolor::blue << scanner->line << termcolor::reset
          << ", column: " << termcolor::blue << scanner->column - 1
          << termcolor::reset << "] " << termcolor::yellow << message
          << termcolor::reset << std::endl;
    }
};
