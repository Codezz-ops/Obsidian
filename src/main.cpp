#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "lexer/lexer.hpp"
#include "common.hpp"
#include "helper/flags.hpp"

int main(int argc, char *argv[]) {
    flags(argc, argv);
    
    const char* filePath = argv[1];
    const char* src = readfile(filePath);
    Lexer tokens(src, filePath);
    Lexer::Token token = tokens.scanToken();

    while (token.kind != TokenKind::END_OF_FILE) {
        std::cout << token.kind << std::endl;
        token = tokens.scanToken();
    }

    return 0;
}