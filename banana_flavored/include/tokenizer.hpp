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

    // constructors and iterator constructors
    Tokenizer(const std::string& str);
    Iterator begin();
    Iterator end();

    // helpers to construct different types of token
    Token make_token(const Token_type type) const;

    // moving thru and checking characters functions
    char advance    ();
    char peek       () const;
    bool is_at_end  () const;
    char peek_next  ();
    bool match      (const char c);
    void skip_whitespaces_and_comments();

    // functions generating different tokens
    Token make_string   ();
    Token identifier    ();
    Token number        ();
    Token next          ();
};