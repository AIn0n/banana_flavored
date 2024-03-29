#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parser.hpp"
#include "bf_vm.hpp"
#include "bf_io.hpp"
#include "tokenizer.hpp"
#include <iostream>

TEST_CASE("code generated for expression returns expression value", "[base]")
{
    std::string code = "90 + 27";
    auto instr  = Parser(code).compile();
    auto vm     = Bf_vm();
    vm.execute(instr);
    REQUIRE(vm.mem[0] == 117);
}