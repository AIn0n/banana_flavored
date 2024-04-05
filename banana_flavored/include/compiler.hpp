#include <string>
#include <functional>
#include <unordered_map>
#include "tokenizer.hpp"

enum class Precedence {
    NONE = 0, /* EOF */
    BASE = 1, /* all */
    TERM = 2, /* + - */
    FACTOR = 3, /* * / */
    PRIMARY = 4, /* unary operations etc */
};



struct Compiler {
    Tokenizer tokenizer;
    Token current;
    Token previous;
    bool had_error;
    bool panic_mode;
    std::string result;

    /* helpers functions */
    Compiler(const std::string &c);
    void advance();
    void consume(Token_type, const std::string&);
    void error_at_current(const std::string);
    
    /* functions used to compile */
    void expression();
    void grouping();
    void number();
    void binary();
    void negation();
    void parse_precedence(Precedence precedence);
    
    std::string compile();

    /* all definitions needed for table with the compiling rules */
    typedef void (Compiler::*parseFn)();

    struct ParseRule {
        parseFn prefix;
        parseFn infix;
        Precedence precedence;
    };

    const static std::unordered_map<Token_type, Compiler::ParseRule> rules;
};