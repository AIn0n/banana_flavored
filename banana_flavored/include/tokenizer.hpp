#pragma once

#include <string>
#include <cctype>
#include <iostream>
#include "token.hpp"
#include <map>

struct Tokenizer {
    std::string::const_iterator curr;
    std::string::const_iterator start;
    uint64_t line;
    const std::map<std::string, Token_type> keywords = {
        {"if", Token_type::IF}
    };

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

        std::string str = std::string(start, curr);

        if (keywords.find(str) == keywords.end())
            return make_token(Token_type::IDENTIFIER);

        const Token_type keyword_token = keywords.at(str);
        return make_token(keyword_token);
    }

    Token number()
    {
        while(isdigit(peek()))
            advance();
        return make_token(Token_type::NUMBER);
    }

    Token make_string()
    {
        while (peek() != '"' && !is_at_end()) {
            if (peek() == '\n')
                line++;
            advance();
        }
        if (is_at_end()) // TODO add real functionality here
            return make_token(Token_type::STRING);

        advance(); // consume closing bracket
        return make_token(Token_type::STRING);
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
        case '*':
            return make_token(Token_type::STAR);
        case '=':
            return make_token(match('=') ? Token_type::BANG_EQUAL : Token_type::EQUAL);
        case '!':
            return make_token(Token_type::EXCLAMATION);
        case '{':
            return make_token(Token_type::BRACE_LEFT);
        case '}':
            return make_token(Token_type::BRACE_RIGHT);
        case '>':
            return make_token(Token_type::MORE);
        case '"':
            return make_string();
        }

        return Token("Unexpected token", Token_type::ERROR, line);
    }
};