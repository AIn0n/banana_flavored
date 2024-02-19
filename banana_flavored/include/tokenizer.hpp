#include <string>

enum class Token_type {
    END_OF_FILE,
    IDENTIFIER,
    COLON,
    EQUAL, 
    NUMBER,
    PLUS
};

struct Token {
    const Token_type type;
    const std::string &start;
    const int line;

    Token(const std::string &str, const Token_type type_, const int line_) 
        : start(str), type(type_), line(line_) {}
    

};

struct Tokenizer {
    std::string::iterator curr;
    std::string::iterator start;
    uint64_t line;

    Tokenizer(std::string str) : curr(str.begin()), start(str.begin()), line(0) {}

    char
    advance(void)
    {
        char tmp = *curr;
        curr++;
        return tmp;
    }

    char peek(void) { return *curr; }

    bool
    is_at_end(void)
    {
        return *curr == '\0';
    }

    char
    peek_next(void)
    {
        if (is_at_end())
            return '\0';
        return *(curr + 1);
    }

    void
    skip_whitespaces_and_comments(void)
    {
        while(true) {
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
                if (peek_next() == '*') {
                    while(!is_at_end() && peek() != '*' && peek_next() != '/')
                        advance();
                }
            default:
                return;
            }
        }
    }

    Token next(void)
    {
        skip_whitespaces_and_comments();
        return Token("", Token_type::END_OF_FILE, 0);
    }
};