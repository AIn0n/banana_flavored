#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "bf_vm.hpp"

#include <string>
#include <locale>
#include <codecvt>


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
    auto X = GENERATE(1, 8, 42, 90);
    auto Y = GENERATE(30, 37, 3278, 9083);
    vm.execute(std::string(X, '+'));
    vm.execute(std::string(Y, '+'));
    
    REQUIRE(vm.mem[0] == X + Y);
}

TEST_CASE("Executing plus sign X times, then minus sign Y times, leave X-Y", "[base]")
{
    Bf_vm vm = Bf_vm();
    auto X = GENERATE(39, 412, 800);
    auto Y = GENERATE(90, 200, 302);
    uint32_t expected = X - Y;

    vm.execute(std::string(X, '+') + std::string(Y,'-'));
    REQUIRE(vm.mem[0] == expected);
}

TEST_CASE("subtracing from zero returns wrapped int", "[base]")
{
    Bf_vm vm = Bf_vm();
    auto X = GENERATE(39, 59, 127);
    uint32_t expected = UINT32_MAX + 1 - X;
    vm.execute(std::string(X, '-'));
    REQUIRE(vm.mem[0] == expected);
}

TEST_CASE("dot operator print out char", "[base]")
{
    auto io = Bf_io_string_buff();
    Bf_vm vm(io);
    char32_t X = GENERATE(U'A', U'B', U'c', U'f');
    const uint32_t pluses = static_cast<uint32_t>(X);
    vm.execute(std::string(pluses, '+') + ".");

    REQUIRE(io.out[0] == X);
}

TEST_CASE("adding, then moving pointer, pointer land on empty cell", "[base]")
{
    auto vm = Bf_vm();
    auto offset = GENERATE(10, 20, 30, 40);
    auto pluses = GENERATE(1, 2, 8, 91);
    vm.execute(std::string(offset, '>') + std::string(pluses, '+'));

    REQUIRE(vm.mem[vm.ptr] == 0);
}