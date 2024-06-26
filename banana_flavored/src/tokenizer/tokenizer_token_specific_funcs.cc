#include "tokenizer.hpp"

Token 
Tokenizer::identifier()
{
    while(isalpha(peek()) || isdigit(peek()))
        advance();

    std::string str = std::string(start, curr);

    if (keywords.find(str) == keywords.end())
        return make_token(Token_type::IDENTIFIER);

    const Token_type keyword_token = keywords.at(str);
    return make_token(keyword_token);
}

Token 
Tokenizer::number()
{
    while(isdigit(peek()))
        advance();
    return make_token(Token_type::NUMBER);
}

Token
Tokenizer::make_string()
{
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n')
            line++;
        advance();
    }
    if (is_at_end()) // TODO add real functionality here
        return make_token(Token_type::STRING);

    advance(); // consume closing bracket
    return make_token(Token_type::STRING);
}

Token
Tokenizer::next(void)
{
    skip_whitespaces_and_comments();
    start = curr;

    if (is_at_end())
        return make_token(Token_type::END_OF_FILE);

    char c = advance();

    if (isalpha(c))
        return identifier();

    if (isdigit(c))
        return number();

    switch (c) {
    case '+':
        return make_token(Token_type::PLUS);
    case '-':
        return make_token(Token_type::MINUS);
    case ':':
        return make_token(Token_type::COLON);
    case ';':
        return make_token(Token_type::SEMICOLON);
    case '(':
        return make_token(Token_type::PAREN_LEFT);
    case ')':
        return make_token(Token_type::PAREN_RIGHT);
    case '*':
        return make_token(Token_type::STAR);
    case '=':
        return make_token(match('=') ? Token_type::BANG_EQUAL : Token_type::EQUAL);
    case '!':
        return make_token(Token_type::EXCLAMATION);
    case '{':
        return make_token(Token_type::BRACE_LEFT);
    case '}':
        return make_token(Token_type::BRACE_RIGHT);
    case '>':
        return make_token(Token_type::MORE);
    case '"':
        return make_string();
    }

    return Token("Unexpected token", Token_type::ERROR, line);
}