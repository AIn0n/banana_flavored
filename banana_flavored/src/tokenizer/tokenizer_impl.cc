#include "tokenizer.hpp"

Token
Tokenizer::make_token(const Token_type type) const
{
    return Token(std::string(start, curr), type, line);
}

Tokenizer::Tokenizer(const std::string& str) : 
    curr(str.begin()), 
    start(str.begin()), line(0) {}

char
Tokenizer::advance()
{
    char tmp = *curr;
    curr++;
    return tmp;
}

char
Tokenizer::peek_next()
{
    if (is_at_end())
        return '\0';
    return *(curr + 1);
}

void
Tokenizer::skip_whitespaces_and_comments()
{
    while (true) {
        switch(peek()) {
        case ' ':
        case '\t':
            advance();
            break;
        case '\n':
            advance();
            line++;
            break;
        case '/':
            if (peek_next() == '/') {
                while (!is_at_end() && peek() != '\n')
                    advance();
            }
        default:
            return;
        }
    }
}

bool
Tokenizer::match(const char c)
{
    if (is_at_end() || peek() != c)
        return false;
    advance();
    return true;
}

char Tokenizer::peek() const { return *curr; }
bool Tokenizer::is_at_end() const { return *curr == '\0'; }