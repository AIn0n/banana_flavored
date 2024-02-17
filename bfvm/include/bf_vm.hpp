#ifndef BF_VM_HPP
#define BF_VM_HPP

#include <string>

struct Bf_vm {
    uint32_t mem[UINT16_MAX] = {0};
    uint32_t ptr = 0;

    void execute(const std::string &cmds)
    {
        for (const auto &it : cmds) {
            if (it == '+')
                ++mem[ptr];
            if (it == '-')
                --mem[ptr];
        }
    }
};

#endif