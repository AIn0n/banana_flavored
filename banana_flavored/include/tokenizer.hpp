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
        Tokenizer *tokenizer;
        Token curr;
        uint8_t eof_counter;

        Iterator(Tokenizer *_tokenizer, Token _curr) : 
            tokenizer(_tokenizer),
            curr(_curr),
            eof_counter(0) {}

        const Token& operator*() const { return curr; }

        Iterator& operator++() {
            if (curr.type == Token_type::END_OF_FILE)
                eof_counter++;
            curr = tokenizer->next();
            return *this;
        }

        bool operator!=(Iterator& other) const { return eof_counter < 1; }
    };

    Iterator begin()
    {
        Token curr = this->next();
        return Iterator(this, curr);
    }

    Iterator end() { return Iterator(nullptr, Token("", Token_type::END_OF_FILE, 0)); }

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