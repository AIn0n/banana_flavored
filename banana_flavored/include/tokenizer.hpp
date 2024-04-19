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

    struct Iterator {
        Tokenizer   *tokenizer;
        Token       curr;
        uint8_t     eof_counter;

        Iterator(Tokenizer *_tokenizer, Token _curr);
        bool        operator!=(Iterator& other) const;
        const       Token& operator*()          const;
        Iterator&   operator++();
    };

    Iterator begin();
    Iterator end();

    Token make_token(const Token_type type) const;
    Tokenizer(const std::string& str);
    char advance();
    char peek() const;
    bool is_at_end() const;
    char peek_next();
    void skip_whitespaces_and_comments();
    bool match(const char c);
    Token identifier();
    Token number();
    Token make_string();
    Token next();
};