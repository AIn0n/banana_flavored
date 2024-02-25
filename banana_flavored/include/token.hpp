#include <string>

/* IDEA: what about doing the same number in the ASCII table?

Will it be faster than doing that current, naive way?
These numbers in current version don't have any kind of meaning,
and the order is random, based on time where I worked on features.
Maybe except the END_OF_FILE token which is 0, this will be tested pretty often
so probably it is faster to check.
*/
enum class Token_type {
    END_OF_FILE = 0,
    IDENTIFIER  = 1,
    COLON       = 2,
    EQUAL       = 3, 
    NUMBER      = 4,
    PLUS        = 5,
    SEMICOLON   = 6,
    BANG_EQUAL  = 7,
    ERROR       = 8,
    PAREN_LEFT  = 9,
    PAREN_RIGHT = 10,
    MINUS       = 11
};

struct Token {
    const Token_type type;
    const std::string lexeme;
    const int line;

    Token(const std::string str, const Token_type type_, const int line_) 
        : lexeme(str), type(type_), line(line_) {}
};