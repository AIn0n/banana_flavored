#ifndef BF_VM_HPP
#define BF_VM_HPP

#include <string>
#include "bf_io.hpp"

static auto default_io = Bf_io_string_buff();

struct Bf_vm {
    uint32_t mem[UINT16_MAX] = {0};
    uint32_t ptr = 0;
    Bf_io &io;


    Bf_vm(Bf_io &io_ = default_io) : io(io_) {}

    void execute(const std::string &cmds)
    {
        for (const auto &it : cmds) {
            if (it == '+')
                ++mem[ptr];
            if (it == '-')
                --mem[ptr];
            if (it == '.')
                io.append_output(mem[ptr]);
            if (it == '>')
                ptr++;
            if (it == '<')
                ptr--;
        }
    }
};

#endif