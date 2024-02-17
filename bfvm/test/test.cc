#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bf_vm.hpp"

#include <string>

TEST_CASE("Executing plus sign N times returns N", "[base]")
{
    Bf_vm vm = Bf_vm();
    auto curr = GENERATE(1, 8, 42, 90);

    vm.execute(std::string(curr, '+'));
    REQUIRE(vm.mem[0] == curr);
}

TEST_CASE("Executing plus sign X times, then Y times, returns X+Y", "[base]")
{
    Bf_vm vm = Bf_vm();
    auto X = GENERATE(1, 8, 42, 90), Y = GENERATE(30, 37, 3278, 9083);
    vm.execute(std::string(X + Y, '+'));
    
    REQUIRE(vm.mem[0] == X + Y);
}

TEST_CASE("Executing plus sign X times, then minus sign Y times, leave X-Y", "[base]")
{
    Bf_vm vm = Bf_vm();
    auto X = GENERATE(39, 412, 800), Y = GENERATE(90, 200, 302);

    vm.execute(std::string(X, '+') + std::string(Y,'-'));
    REQUIRE(vm.mem[0] == X - Y);
}

TEST_CASE("subtracing from zero returns wrapped int", "[base]")
{
    Bf_vm vm = Bf_vm();
    auto X = GENERATE(39, 59, 127);
    vm.execute(std::string(X, '-'));
    REQUIRE(vm.mem[0] == UINT32_MAX + 1 - X);
}

TEST_CASE("dot operator print out char", "[base]")
{
    auto io = Bf_io_string_buff();
    char32_t X = GENERATE(U'A', U'B', U'c', U'f');
    Bf_vm(io).execute(std::string(static_cast<uint32_t>(X), '+') + ".");

    REQUIRE(io.out[0] == X);
}

TEST_CASE("adding, then moving pointer, pointer land on empty cell", "[base]")
{
    auto io = Bf_io_string_buff();
    auto offset = GENERATE(10, 20, 30, 40), pluses = GENERATE(1, 2, 8, 91);
    Bf_vm(io).execute(std::string(pluses, '+') + std::string(offset, '>') + ".");

    REQUIRE(io.out[0] == 0);
}