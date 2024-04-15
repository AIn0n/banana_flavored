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
    MINUS       = 11,
    STAR        = 12,
    EXCLAMATION = 13,
    IF          = 14,
    MORE        = 15,
    BRACE_LEFT  = 16,
    BRACE_RIGHT = 17
};

struct Token {
    Token_type type;
    std::string lexeme;
    int line;

    Token(const std::string str, const Token_type type_, const int line_) 
        : type(type_), lexeme(str), line(line_) {}
};