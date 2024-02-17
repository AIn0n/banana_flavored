#ifndef BF_VM_HPP
#define BF_VM_HPP

#include <string>
#include <deque>
#include <map>
#include "bf_io.hpp"

static auto default_io = Bf_io_string_buff();

struct Bf_vm {
    uint32_t mem[UINT16_MAX] = {0};
    uint32_t ptr = 0;
    Bf_io &io;


    Bf_vm(Bf_io &io_ = default_io) : io(io_) {}

    bool build_check_lookup(const std::string &cmds) {
        std::deque<uint64_t> openings;

        for (auto i = 0; i < cmds.length(); ++i) {
            if (cmds[i] == '[') {
                openings.push_back(i);
            } else if (cmds[i] == ']') {
                if (openings.empty())
                    return true;
                const uint64_t opening = openings.back();
                openings.pop_back();
                bracket_lookup[opening] = i + 1;
                bracket_lookup[i] = opening;
            }
        }
        return !openings.empty();
    }

    void execute(const std::string &cmds)
    {
        if (build_check_lookup(cmds))
            return;

        for (uint64_t i = 0; i < cmds.size(); ++i) {
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
                if (!mem[ptr])
                    i = bracket_lookup[i];
                break;
            case ']':
                if (mem[ptr])
                    i = bracket_lookup[i];
            }
        }
    }
private:
    std::map<uint64_t, uint64_t> bracket_lookup;
};

#endif