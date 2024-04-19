#include "tokenizer.hpp"

Tokenizer::Iterator::Iterator(Tokenizer *_tokenizer, Token _curr) : 
    tokenizer(_tokenizer), curr(_curr), eof_counter(0) {}

Tokenizer::Iterator&
Tokenizer::Iterator::operator++()
{
    if (curr.type == Token_type::END_OF_FILE)
        eof_counter++;
    curr = tokenizer->next();
    return *this;
}

bool
Tokenizer::Iterator::operator!=(Iterator& other) const
{
    return eof_counter < 1;
}

const Token&
Tokenizer::Iterator::operator*() const
{
    return curr;
}

Tokenizer::Iterator 
Tokenizer::begin()
{
    Token curr = this->next();
    return Iterator(this, curr);
}

Tokenizer::Iterator Tokenizer::end()
{
    return Iterator(nullptr, Token("", Token_type::END_OF_FILE, 0));
}