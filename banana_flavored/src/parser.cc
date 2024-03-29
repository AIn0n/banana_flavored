#include "parser.hpp"

const std::unordered_map<Token_type, Parser::ParseRule> Parser::rules = {
    {Token_type::PAREN_LEFT,{&Parser::grouping, nullptr,        Precedence::BASE}},
    {Token_type::NUMBER,    {&Parser::number,   nullptr,        Precedence::BASE}},
    {Token_type::PLUS,      {nullptr,           &Parser::plus,  Precedence::TERM}},
    {Token_type::END_OF_FILE,{nullptr,          nullptr,  Precedence::NONE}}
};

Parser::Parser(const std::string &c) : 
    tokenizer(c),
    current("", Token_type::END_OF_FILE, 0),
    previous("",Token_type::END_OF_FILE, 0),
    had_error(false),
    panic_mode(false) {}

void
Parser::advance()
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
Parser::error_at_current(const std::string msg)
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
Parser::consume(const Token_type expected, const std::string& msg)
{
    if (current.type == expected)
        return advance();
    
    error_at_current(msg);
}

void
Parser::parse_precedence(Precedence precedence)
{
    advance();
    Parser::parseFn prefix = rules.at(previous.type).prefix;
    if (prefix == nullptr) {
        error_at_current("expected expression");
        return;
    }

    (this->*prefix)();

    while (precedence <= rules.at(current.type).precedence) {
        advance();
        Parser::parseFn infix = rules.at(previous.type).infix;

        (this->*infix)();
    }
}

void
Parser::number()
{
    int num = std::stoi(previous.lexeme);
    /* put the value into the cell and move one cell up*/
    result += std::string(num, '+') + '>';
}

void
Parser::plus()
{
    Parser::ParseRule rule = rules.at(previous.type);
    parse_precedence(static_cast<Precedence>((int)rule.precedence + 1));
    result += "< [-<+>]";
}

void
Parser::grouping()
{
    expression();
    consume(Token_type::PAREN_RIGHT, "Expected ) after the expression");
}

void
Parser::expression()
{
    parse_precedence(Precedence::BASE);
}

std::string
Parser::compile(void)
{
    advance();
    expression();
    consume(Token_type::END_OF_FILE, "Expected end of file\n");
    return result;
}