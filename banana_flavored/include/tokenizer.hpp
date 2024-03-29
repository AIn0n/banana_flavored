#pragma once

#include <string>
#include <cctype>
#include <iostream>
#include "token.hpp"

struct Tokenizer {
    std::string::const_iterator curr;
    std::string::const_iterator start;
    uint64_t line;

    Token make_token(const Token_type type) const
    {
        return Token(std::string(start, curr), type, line);
    }

    Tokenizer(const std::string& str) : curr(str.begin()), start(str.begin()), line(0) {}

    char
    advance(void)
    {
        char tmp = *curr;
        curr++;
        return tmp;
    }

    char peek(void) const { return *curr; }

    bool is_at_end(void) const { return *curr == '\0'; }

    char
    peek_next(void)
    {
        if (is_at_end())
            return '\0';
        return *(curr + 1);
    }

    void
    skip_whitespaces_and_comments(void)
    {
        while (true) {
            switch(peek()) {
            case ' ':
            case '\t':
                advance();
                break;
            case '\n':
                advance();
                line++;
                break;
            case '/':
                if (peek_next() == '/') {
                    while (!is_at_end() && peek() != '\n')
                        advance();
                }
            default:
                return;
            }
        }
    }

    bool match(const char c)
    {
        if (is_at_end() || peek() != c)
            return false;
        advance();
        return true;
    }

    Token identifier()
    {
        while(isalpha(peek()) || isdigit(peek()))
            advance();
        return make_token(Token_type::IDENTIFIER);
    }

    Token number()
    {
        while(isdigit(peek()))
            advance();
        return make_token(Token_type::NUMBER);
    }

    Token next(void)
    {
        skip_whitespaces_and_comments();
        start = curr;

        if (is_at_end())
            return make_token(Token_type::END_OF_FILE);

        char c = advance();

        if (isalpha(c))
            return identifier();

        if (isdigit(c))
            return number();

        switch (c) {
        case '+':
            return make_token(Token_type::PLUS);
        case '-':
            return make_token(Token_type::MINUS);
        case ':':
            return make_token(Token_type::COLON);
        case ';':
            return make_token(Token_type::SEMICOLON);
        case '(':
            return make_token(Token_type::PAREN_LEFT);
        case ')':
            return make_token(Token_type::PAREN_RIGHT);
        case '=':
            return make_token(match('=') ? Token_type::BANG_EQUAL : Token_type::EQUAL);
        }

        return Token("Unexpected token", Token_type::ERROR, line);
    }
};