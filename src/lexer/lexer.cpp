#include <unordered_map>

#include "../helper/errors.hpp"
#include "lexer.hpp"

Lexer::Lexer(const char* source, const char* filename) {
    scanner.current = source;
    scanner.source = source;
    scanner.start = source;
    scanner.column = 1;
    scanner.line = 1;
}

void Lexer::reset() {
    scanner.current = scanner.start;
    scanner.column = 1;
    scanner.line = 1;
}

char Lexer::peekNext() {
    return scanner.current[1];
}

char Lexer::advance() {
    scanner.current++;
    scanner.column++;
    return scanner.current[-1];
}

char Lexer::peek() {
    return *scanner.current;
}

const char* Lexer::lineStart(int line) {
    const char* start = scanner.source;
    int currentLine = 1;

    while (currentLine != line) {
        if (*start == '\n')
            currentLine++;
        start++;
    }
    
    return start;
}

bool Lexer::match(char expected) {
    if (isAtEnd())
        return false;
    if (*scanner.current != expected)
        return false;

    scanner.current++;
    scanner.column++;
    return true;
}

bool Lexer::isAtEnd() {
    return *scanner.current == '\0';
}

Lexer::Token Lexer::errorToken(std::string message) {
    Error::error(token, message, *this);
    return makeToken(TokenKind::ERROR_TOKEN);
}

Lexer::Token Lexer::makeToken(TokenKind kind) {
    token.column = scanner.column;
    token.start = scanner.start;
    token.line = scanner.line;
    token.kind = kind;
    return token;
}

Lexer::Token Lexer::identifier() {
    while (isalpha(peek()) || isdigit(peek()))
        advance();
    return makeToken(identifierType());
}

Lexer::Token Lexer::number() {
    while (isdigit(peek()))
        advance();

    if (peek() == '.' && isdigit(peekNext())) {
        advance();

        while (isdigit(peek()))
            advance();
    }

    return makeToken(TokenKind::NUMBER);
}

Lexer::Token Lexer::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            token.line++;
        advance();
    }

    if (isAtEnd())
        return errorToken("Unterminated string.");
    advance();

    return makeToken(TokenKind::STRING);
}

TokenKind Lexer::checkKeyword(std::string identifier) {
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
        {"this", TokenKind::THIS},
    };

    auto it = keyword.find(identifier);
    if (it != keyword.end()) return it->second;
    return TokenKind::IDNET;
}

TokenKind Lexer::identifierType() {
    std::string keyword(scanner.start, scanner.current);
    return checkKeyword(keyword.c_str());
}

void Lexer::skipWhitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                scanner.column = 0;
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

Lexer::Token Lexer::scanToken() {
  skipWhitespace();

  scanner.start = scanner.current;

  if (isAtEnd())
    return makeToken(TokenKind::END_OF_FILE);

  char c = Lexer::advance();

  if (isalpha(c))
    return identifier();
  if (isdigit(c))
    return number();

  switch (c) {
  case '(':
    return makeToken(TokenKind::LPAREN);
  case ')':
    return makeToken(TokenKind::RPAREN);
  case '{':
    return makeToken(TokenKind::LBRACE);
  case '}':
    return makeToken(TokenKind::RBRACE);
  case ';':
    return makeToken(TokenKind::SEMICOLON);
  case ',':
    return makeToken(TokenKind::COMMA);
  case '.':
    return makeToken(TokenKind::DOT);
  case '-':
    return makeToken(TokenKind::MINUS);
  case '+':
    return makeToken(TokenKind::PLUS);
  case '/':
    return makeToken(TokenKind::SLASH);
  case '*':
    return makeToken(TokenKind::STAR);
  case '[':
    return makeToken(TokenKind::LBRACKET);
  case ']':
    return makeToken(TokenKind::RBRACKET);
  case '=':
    return makeToken(match('=') ? TokenKind::EQUAL_EQUAL : TokenKind::EQUAL);
  case '!':
    return makeToken(match('=') ? TokenKind::BANG_EQUAL : TokenKind::BANG);
  case '<':
    return makeToken(match('=') ? TokenKind::LESS_EQUAL : TokenKind::LESS);
  case '>':
    return makeToken(match('=') ? TokenKind::GREATER_EQUAL : TokenKind::GREATER);
  case '"':
    return string();
  }

  Error::error(token, "Unexpected character: " + std::string(1, c), *this);
  return makeToken(TokenKind::ERROR_TOKEN);
}