#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "parser.hpp"
#include "bf_vm.hpp"
#include "bf_io.hpp"

TEST_CASE("code generated for expression returns expression value", "[base]")
{
    auto io     = Bf_io_string_buff();
    auto instr  = Parser("func(90 + 27 - 3);").compile();
    Bf_vm(io).execute(instr);
    REQUIRE(io.out == U"114");
}