#pragma once

namespace Obsidian {
    class Tokens {
        public:
            Tokens(const char *src, const char *filename);
            enum TokenKind {
                // Single-character tokens
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

                // One or two character tokens
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

                // Literals
                IDNET,
                NUMBER,
                STRING,

                // Keywords
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

        struct Token {
            const char *start;
            int length;
            TokenKind kind;
            int line;
            int pos;
        };

        struct Scanner {
            const char *filename;
            const char *current;
            const char *src;
            const char *start;
            int column;
            int line;
            const char *get_line_content(int line);
        };

        Token scan_token();
        Token error_token();
        void reset();

        private:
            Scanner scanner;

            char peekNext();
            char advance();
            char peek();

            bool match(char exp);
            bool isAtEnd();

            Token makeToken(TokenKind kind);
            Token identifier();
            Token number();
            Token string();

            TokenKind checkKeyword(const char *identifier);
            TokenKind identifierType();

            void skipWhitespace();
    };
}