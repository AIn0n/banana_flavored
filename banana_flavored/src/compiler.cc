#include "compiler.hpp"

const std::unordered_map<Token_type, Compiler::ParseRule> Compiler::rules = {
    {Token_type::PAREN_LEFT,{&Compiler::grouping, nullptr,        Precedence::BASE}},
    {Token_type::NUMBER,    {&Compiler::number,   nullptr,        Precedence::BASE}},
    {Token_type::PLUS,      {nullptr,           &Compiler::binary,  Precedence::TERM}},
    {Token_type::END_OF_FILE,{nullptr,          nullptr,  Precedence::NONE}}
};

Compiler::Compiler(const std::string &c) : 
    tokenizer(c),
    current("", Token_type::END_OF_FILE, 0),
    previous("",Token_type::END_OF_FILE, 0),
    had_error(false),
    panic_mode(false) {}

void
Compiler::advance()
{
    previous = current;

    for (;;) {
        current = tokenizer.next();
        if (current.type != Token_type::ERROR)
            break;
        error_at_current(current.lexeme);
    }
}

void
Compiler::error_at_current(const std::string msg)
{
    if (panic_mode)
        return;

    panic_mode = true;
    std::cout << "Line [" << current.line << "] Error ";
    if (current.type == Token_type::END_OF_FILE) {
        std::cout << "at end";
    } else if (current.type == Token_type::ERROR) {
        // do nothing
    } else {
        std::cout << "at " << current.lexeme;
    }
    std::cout << ": " << msg;
}

void
Compiler::consume(const Token_type expected, const std::string& msg)
{
    if (current.type == expected)
        return advance();
    
    error_at_current(msg);
}

void
Compiler::parse_precedence(Precedence precedence)
{
    advance();
    Compiler::parseFn prefix = rules.at(previous.type).prefix;
    if (prefix == nullptr) {
        error_at_current("expected expression");
        return;
    }

    (this->*prefix)();

    while (precedence <= rules.at(current.type).precedence) {
        advance();
        Compiler::parseFn infix = rules.at(previous.type).infix;

        (this->*infix)();
    }
}

void
Compiler::number()
{
    int num = std::stoi(previous.lexeme);
    /* put the value into the cell and move one cell up*/
    result += std::string(num, '+') + '>';
}

void
Compiler::binary()
{
    Compiler::ParseRule rule = rules.at(previous.type);
    parse_precedence(static_cast<Precedence>((int)rule.precedence + 1));
    result += "< [-<+>]";
}

void
Compiler::grouping()
{
    expression();
    consume(Token_type::PAREN_RIGHT, "Expected ) after the expression");
}

void
Compiler::expression()
{
    parse_precedence(Precedence::BASE);
}

std::string
Compiler::compile(void)
{
    advance();
    expression();
    consume(Token_type::END_OF_FILE, "Expected end of file\n");
    return result;
}