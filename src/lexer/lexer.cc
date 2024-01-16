#include <unordered_map>
#include <iostream>
#include <cctype>
#include <string>
#include "tokens.h"
#include "../helper/errors.h"

using namespace Obsidian;

Tokens::Tokens(const char *src, const char *filename) {
    scanner.filename = filename;
    scanner.current = src;
    scanner.src = src;
    scanner.start = src;
    scanner.column = 1;
    scanner.line = 1;
}

void Tokens::reset() {
    scanner.current = scanner.start;
    scanner.column = 1;
    scanner.line = 1;
}

char Tokens::peekNext() {
    return scanner.current[1];
}

const char* Tokens::Scanner::get_line_content(int line) {
    const char *start = src;
    int currentLine = 1;

    while (currentLine != line) {
        if (*start == '\n')
            currentLine++;
        start++;
    }
    return start;
}

char Tokens::advance() {
    scanner.current++;
    scanner.column++;
    return scanner.current[-1];
}

char Tokens::peek() {
    return *scanner.current;
}

bool Tokens::isAtEnd() {
    return *scanner.current == '\0';
}

bool Tokens::match(char exp) {
    if (isAtEnd()) {
        return false;
    } 
    if (*scanner.current != exp) {
        return false;
    }
    scanner.current++;
    scanner.column++;
    return true;
}

Tokens::Token Tokens::makeToken(TokenKind kind) {
    Token tk; 
    tk.start = std::move(scanner.start);
    tk.kind = kind;
    tk.line = scanner.line;
    tk.pos = scanner.column;
    tk.length = std::distance(scanner.start, scanner.current);
    return tk;
}

Tokens::TokenKind Tokens::identifierType() {
    std::string keywords(scanner.start, scanner.current);
    return checkKeyword(keywords.c_str());
}

Tokens::Token Tokens::identifier() {
    while (isalpha(peek()) || isdigit(peek())) {
        advance();
    }
    return makeToken(identifierType());
}

Tokens::TokenKind Tokens::checkKeyword(const char *identifier) {
    const std::unordered_map<std::string, TokenKind> keyword = {
        {"fn", TokenKind::FN},
        {"let", TokenKind::VAR},
        {"loop", TokenKind::LOOP},
        {"local", TokenKind::LOCAL},
        {"global", TokenKind::GLOBAL},
        {"print", TokenKind::PRINT},
        {"if", TokenKind::IF},
        {"else", TokenKind::ELSE},
        {"exit", TokenKind::EXIT},
        {"return", TokenKind::RETURN},
        {"const", TokenKind::CONST},
        {"class", TokenKind::CLASS},
        {"switch", TokenKind::SWITCH},
        {"case", TokenKind::CASE},
        {"break", TokenKind::BREAK},
        {"this", TokenKind::THIS}
    };

    auto it = keyword.find(identifier);
    if (it != keyword.end()) return it->second;
    return TokenKind::IDNET;
}

Tokens::Token Tokens::number() {
    while (isdigit(peek())) {
        advance();
    }
    return makeToken(TokenKind::NUMBER);
}

Tokens::Token Tokens::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            scanner.line++;
        }
        advance();
    }
    if (isAtEnd()) {
        exit(1);
    }
    advance();
    return makeToken(TokenKind::STRING);
}

void Tokens::skipWhitespace() {
    while (true) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;

            case '\n':
                scanner.line++;
                scanner.column = 1;
                advance();
                break;
            case '#':
                while (peek() != '\n' && !isAtEnd()) {
                    advance();
                }
                break;
            default:
                return;
        }
    }
}

Tokens::Token Tokens::scan_token() {
    skipWhitespace();

    scanner.start = scanner.current;

    if (isAtEnd()) {
        return makeToken(TokenKind::END_OF_FILE);
    }

    char c = advance();

    if (isalpha(c)) {
        return identifier();
    } else if (isdigit(c)) {
        return number();
    }

    switch(c) {
        case '(':
            return makeToken(TokenKind::LPAREN);
        case ')':
            return makeToken(TokenKind::RPAREN);
        case '{':
            return makeToken(TokenKind::LBRACE);
        case '}':
            return makeToken(TokenKind::RBRACE);
        case '[':
            return makeToken(TokenKind::LBRACKET);
        case ']':
            return makeToken(TokenKind::RBRACKET);
        case ',':
            return makeToken(TokenKind::COMMA);
        case '*':
            return makeToken(TokenKind::STAR);
        case '/':
            return makeToken(TokenKind::SLASH);
        case '-':
            return makeToken(match('-') ? TokenKind::DEC : TokenKind::MINUS);
        case '+':
            return makeToken(match('+') ? TokenKind::INC : TokenKind::PLUS);
        case '=':
            return makeToken(match('=') ? TokenKind::EQUAL_EQUAL : TokenKind::EQUAL);
        case '!':
            return makeToken(match('=') ? TokenKind::BANG_EQUAL : TokenKind::BANG);
        case '<':
            return makeToken(match('=') ? TokenKind::LESS_EQUAL : TokenKind::LESS);
        case '>':
            return makeToken(match('=') ? TokenKind::GREATER_EQUAL : TokenKind::GREATER);
        case ':':
            return makeToken(TokenKind::COLON);
        case ';':
            return makeToken(TokenKind::SEMICOLON);
        case '.':
            return makeToken(TokenKind::DOT);
        case '"':
            return string();
    }

    LexerError::error_lexer(&scanner, "Unexpected character: " + std::string(1, c));
    return makeToken(ERROR_TOKEN);
}