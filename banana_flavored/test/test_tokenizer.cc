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

TEST_CASE("IF statement in the code is parsed as IF_KEYWORD", "[identifiers]")
{
    auto code = "if (5 > 1) { func(); }";
    auto tokenizer = Tokenizer(code);
    std::vector<Token_type> res;
    std::vector<Token_type> expected = {
        Token_type::IF,
        Token_type::PAREN_LEFT,
        Token_type::NUMBER,
        Token_type::MORE,
        Token_type::NUMBER,
        Token_type::PAREN_RIGHT,
        Token_type::BRACE_LEFT,
        Token_type::IDENTIFIER,
        Token_type::PAREN_LEFT,
        Token_type::PAREN_RIGHT,
        Token_type::SEMICOLON,
        Token_type::BRACE_RIGHT,
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

TEST_CASE("string should be tokenized properly and string inside token should be equal to value in brackets", "[strings]")
{
    std::string _string = "Hello world!";
    auto code = "a := \"" + _string + "\";";
    auto tokenizer = Tokenizer(code);
    std::vector<Token_type> expected = {
        Token_type::IDENTIFIER,
        Token_type::COLON,
        Token_type::EQUAL,
        Token_type::STRING,
        Token_type::SEMICOLON
    };

    std::vector<Token_type> res;
    Token_type type;
    do {
        Token token = tokenizer.next();
        type = token.type;
        res.push_back(type);
    } while (type != Token_type::END_OF_FILE);

    REQUIRE(res == expected);
}