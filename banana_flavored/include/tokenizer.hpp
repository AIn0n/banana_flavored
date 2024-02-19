#include <string>

enum class Token {
    END_OF_FILE,
    IDENTIFIER,
    COLON,
    EQUAL, 
    NUMBER,
    PLUS
};

struct Tokenizer {
    std::string code;
    Tokenizer(std::string str) : code(str) {}

    Token next(void)
    {
        return Token::END_OF_FILE;
    }
};