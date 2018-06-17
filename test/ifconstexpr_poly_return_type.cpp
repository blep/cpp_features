#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <string>
#include <array>
#include <vector>


/*
 * A new very powerful features of C++17 related to "if constexpr":
 * in a constexpr function, each "if constexpr" block is allowed to return a 
 * different return type. The only constraint is that each block must remain parsable (but it is not required to be valid)
 */
template<typename T>
constexpr auto listOf(T value) -> auto {
    if constexpr (std::is_trivial_v<T>) {
        return std::array<T, 1>{ value };
    }
    else if constexpr (!std::is_trivial_v<T>) {
        return std::vector<T>{ value };
    }
}


int main()
{
    auto listInt = listOf(3);
    auto listString = listOf(std::string("toto"));

    static_assert(std::is_same_v< decltype(listInt), std::array<int, 1> >);
    static_assert(std::is_same_v< decltype(listString), std::vector<std::string> >);

    return 0;
}
