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
        Token_type::TYPE_IDENTIFIER,
        Token_type::EQUAL, 
        Token_type::NUMBER,
        Token_type::PLUS,
        Token_type::NUMBER
    };

    Token_type Token_type;
    do {
        Token_type = tokenizer.next().type;
        res.push_back(Token_type);
    } while (Token_type != Token_type::END_OF_FILE);


    REQUIRE(res == expected);
}