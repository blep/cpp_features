#include <blcx/constexpr_writer.hpp>
#include <blcx/constexpr_assert.hpp>

constexpr size_t test1()
{
    auto msg = blcx::generateString([](auto writer) constexpr {
        writer.write("Hello, ");
        writer.write("world!");
    });
    return 1;
}


int main()
{
    char b1[test1()];
    return 0;
}
