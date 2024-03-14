#include <string>
#include <functional>
#include <unordered_map>
#include "tokenizer.hpp"

enum class Precedence {
    BASE = 0, /* all */
    TERM = 1, /* + - */
    FACTOR = 2, /* * / */
};



struct Parser {
    Tokenizer tokenizer;
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;

    /* helpers functions */
    Parser(const std::string &c);
    void advance();
    void consume(Token_type, const std::string&);
    void error_at_current(const std::string);
    
    /* functions used to compile */
    void expression();
    void grouping();
    void parse_precedence(Precedence precedence);
    
    std::string compile();

    /* all definitions needed for table with the compiling rules */
    typedef void (Parser::*parseFn)();

    struct ParseRule {
        parseFn prefix;
        parseFn infix;
        Precedence precedence;
    };

    const static std::unordered_map<Token_type, Parser::ParseRule> rules;
};