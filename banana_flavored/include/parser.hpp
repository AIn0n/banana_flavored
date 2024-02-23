#include <string>

struct Parser {
    const std::string code;
    
    Parser(const std::string &c) : code(c) {}

    std::string parse(void) {
        return "";
    }
};