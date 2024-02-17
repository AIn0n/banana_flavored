#include <stdint.h>
#include <string>

class Bf_io {
public:
    virtual uint32_t get_input(void) = 0;
    virtual void append_output(uint32_t out) = 0;
};

struct Bf_io_string_buff : Bf_io {

    const std::u32string in;
    std::u32string out;
    size_t in_ptr = 0;

    Bf_io_string_buff(const std::u32string &input = U"") : in(input) {}

    virtual uint32_t get_input(void)
    {
        uint32_t tmp = static_cast<uint32_t>(in[in_ptr++]);
        return tmp;
    }

    virtual void append_output(uint32_t out) {
        this->out += out;
    }
};