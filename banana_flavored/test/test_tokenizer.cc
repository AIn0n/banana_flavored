#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tokenizer.hpp"

#include <vector>

TEST_CASE("tokenize expression", "[base]")
{
    auto tokenizer = Tokenizer("a : cell = 1 + 2;");
    std::vector<Token> res;
    std::vector<Token> expected = {
        Token::IDENTIFIER,
        Token::COLON,
        Token::EQUAL, 
        Token::NUMBER,
        Token::PLUS,
        Token::NUMBER
    };

    Token token;
    do {
        token = tokenizer.next();
        res.push_back(token);
    } while (token != Token::END_OF_FILE);


    REQUIRE(res == expected);
}