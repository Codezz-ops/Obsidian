#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "helper/version.h"
#include "lexer/tokens.h"
#include "common.h"
#include "helper/flags.h"

using namespace Obsidian;

int main(int argc, char *argv[]) {
    flags(argc, argv);
    
    const char *filePath = argv[1];
    const char *src = readfile(filePath);
    Tokens tokens(src, filePath);
    Tokens::Token token = tokens.scan_token();

    while (token.kind != Tokens::TokenKind::END_OF_FILE) {
        std::cout << token.kind << std::endl;
        token = tokens.scan_token();
    }

    return 0;
}