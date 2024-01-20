#pragma once

#include <string>
#include <memory>

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
    END_OF_FILE
};

class Lexer {
public:
    Lexer(const std::string& source, const std::string& filename);

    struct Token {
        size_t length;
        TokenKind kind;
        int current;
        int column;
        int line;
    };

    struct Keyword {
        std::string name;
        TokenKind kind;
    };
    
    std::unique_ptr<Token> scanToken();
    std::unique_ptr<Token> errorToken(const std::string& message);
    Token token;
    const char *lineStart(int line);
    void reset();

private:
    struct Scanner {
        std::string current;
        std::string source;
        size_t start;
        int column;
        int line;
    };

    Scanner scanner;

    char peekNext();
    char advance();
    char peek();

    bool match(char expected);
    bool isAtEnd();

    std::unique_ptr<Token> makeToken(TokenKind kind);
    std::unique_ptr<Token> identifier();
    std::unique_ptr<Token> number();
    std::unique_ptr<Token> string();

    TokenKind checkKeyword(const std::string& indentifer);
    TokenKind identifierType();

    void skipWhitespace();
};
