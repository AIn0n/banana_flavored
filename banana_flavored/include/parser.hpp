#include <string>
#include "tokenizer.hpp"

struct Parser {
    Tokenizer tokenizer;
    Token current;
    Token previous;

    Parser(const std::string &c) : 
        tokenizer(Tokenizer(c)),
        current(Token("", Token_type::END_OF_FILE, 0)),
        previous(Token("", Token_type::END_OF_FILE, 0)) {}

    std::string parse(void) {
        return "";
    }
};