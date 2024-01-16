#include <iostream>
#include <string>
#include "../lexer/tokens.h"
#include "../../inc/colorize.h"
using namespace Obsidian;

class LexerError {
public:
    static void error_lexer(Tokens::Scanner *scanner, std::string message) {
        std::cout << termcolor::red << "Error: " << termcolor::yellow << message << termcolor::reset << std::endl;
        std::cout << scanner->filename << ": [Line: " << termcolor::bright_blue << scanner->line << termcolor::reset << "] [" << "Column: " << termcolor::bright_blue << scanner->column - 1 << termcolor::reset << "]" << std::endl;
        const char *lineStart = scanner->get_line_content(scanner->line);
        const char *lineEnd = lineStart;
        while (*lineEnd != '\n' && *lineEnd != '\0') {
            lineEnd++;
        }
        std::cout << "    " << scanner->line << " | " << std::string(lineStart, lineEnd - lineStart) << std::endl;
        std::cout << "      |" << std::string(scanner->column - 2, ' ') << termcolor::red << "^" << termcolor::reset << std::endl;
    }
};
 