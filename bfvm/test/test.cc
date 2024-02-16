#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bf_vm.hpp"


TEST_CASE( "Executing plus sign N times returns N", "[base]" )
{
    Bf_vm vm = Bf_vm();
    auto curr = GENERATE(1, 8, 42, 90);
    std::string cmds = "";
    for (auto i = 0; i < curr; ++i)
        cmds += "+";

    vm.execute(cmds);
    REQUIRE(vm.mem[0] == curr);
}