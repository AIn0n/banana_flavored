#ifndef BF_VM_HPP
#define BF_VM_HPP

#include <string>
#include <deque>
#include "bf_io.hpp"
#include <iostream>

static auto default_io = Bf_io_string_buff();

struct Bf_vm {
    uint32_t mem[UINT16_MAX] = {0};
    uint32_t ptr = 0;
    Bf_io &io;


    Bf_vm(Bf_io &io_ = default_io) : io(io_) {}

    void execute(const std::string &cmds)
    {
        for (uint64_t i = 0; i < cmds.size(); ++i) {
            std::cout << "executing: " << cmds[i] << " iter: " << i << '\n';
            switch (cmds[i])
            {
            case '+':
                ++mem[ptr];
                break;
            case '-':
                --mem[ptr];
                break;
            case '.':
                io.append_output(mem[ptr]);
                break;
            case '>':
                ptr++;
                break;
            case '<':
                ptr--;
                break;
            case ',':
                mem[ptr] = io.get_input();
            case '[':
                if (!mem[ptr]) {
                    while(cmds[i++] != ']') {}
                    break;
                }
                openings.push_back(i);
                break;
            case ']':
                i = openings.back() - 1;
                openings.pop_back();
            }
        }
    }
private:
    std::deque<uint64_t> openings;
};

#endif