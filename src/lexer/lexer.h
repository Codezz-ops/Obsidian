#pragma once

#include <string>


enum TokenKind {
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    RBRACKET,
    LBRACKET,
    COMMA,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    SEMICOLON,
    COLON,
    DOT,        
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    INC,
    DEC,
    IDNET,
    NUMBER,
    STRING,
    FN,
    VAR,
    RETURN,
    LOOP,
    PRINT,
    EXIT,
    LOCAL,
    GLOBAL,
    IF,
    ELSE,
    CLASS,
    CONST,
    DEFAULT,
    BREAK,
    SWITCH,
    CASE,
    THIS,
    NEW,
    ERROR_TOKEN,
    INT,
    BOOL,
    FLOAT,
    CHAR,
    END_OF_FILE
};

class Lexer {
public:
    Lexer(const char* source, const char* filename);

    struct Token {
        const char* start;
        TokenKind kind;
        int current;
        int column;
        int line;
    };

    struct Keyword {
        std::string name;
        TokenKind kind;
    };
    
    Token scanToken();
    Token token;
    Token errorToken(std::string message);
    const char *lineStart(int line);
    void reset();

private:
    struct Scanner {
        const char* current;
        const char* source;
        const char* start;
        int column;
        int line;
    };

    Scanner scanner;

    char peekNext();
    char advance();
    char peek();

    bool match(char expected);
    bool isAtEnd();

    Token makeToken(TokenKind kind);
    Token identifier();
    Token number();
    Token string();

    TokenKind checkKeyword(std::string indentifer);
    TokenKind identifierType();

    void skipWhitespace();
};