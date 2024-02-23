#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tokenizer.hpp"

#include <vector>

TEST_CASE("tokenize expression", "[base]")
{
    auto tokenizer = Tokenizer("a :cell= 1 + 2;");
    std::vector<Token_type> res;
    std::vector<Token_type> expected = {
        Token_type::IDENTIFIER,
        Token_type::COLON,
        Token_type::IDENTIFIER,
        Token_type::EQUAL, 
        Token_type::NUMBER,
        Token_type::PLUS,
        Token_type::NUMBER,
        Token_type::SEMICOLON,
        Token_type::END_OF_FILE
    };

    Token_type type;
    do {
        Token token = tokenizer.next();
        type = token.type;
        res.push_back(type);
    } while (type != Token_type::END_OF_FILE);


    REQUIRE(res == expected);
}

TEST_CASE("parsing the function with the expression inside", "[base]")
{
    auto tokenizer = Tokenizer("func(18 + 2 - 10);");
    std::vector<Token_type> res;
    std::vector<Token_type> expected = {
        Token_type::IDENTIFIER,
        Token_type::PAREN_LEFT,
        Token_type::NUMBER,
        Token_type::PLUS,
        Token_type::NUMBER,
        Token_type::MINUS,
        Token_type::NUMBER,
        Token_type::PAREN_RIGHT,
        Token_type::SEMICOLON,
        Token_type::END_OF_FILE
    };


    Token_type type;
    do {
        Token token = tokenizer.next();
        type = token.type;
        res.push_back(type);
    } while (type != Token_type::END_OF_FILE);

    REQUIRE(res == expected);
}