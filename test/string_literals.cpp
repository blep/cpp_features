#include <string>
#include <string_view>
#include <iostream>
#include <type_traits>

int main() 
{
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    auto s1 = "hello, "s;
    static_assert(std::is_same_v<decltype(s1), std::string>);

    auto s2 = "world!"sv;
    static_assert(std::is_same_v<decltype(s2), std::string_view>);

    auto s3 = u8"123";
    static_assert(std::is_same_v<decltype(s3), const char *>);
    auto s3s = u8"123"s;
    static_assert(std::is_same_v<decltype(s3s), std::string>);
    auto s3sv = u8"123"sv;
    static_assert(std::is_same_v<decltype(s3sv), std::string_view>);

    auto s4 = u"123";
    static_assert(std::is_same_v<decltype(s4), const char16_t *>);
    auto s4s = u"123"s;
    static_assert(std::is_same_v<decltype(s4s), std::u16string>);
    auto s4sv = u"123"sv;
    static_assert(std::is_same_v<decltype(s4sv), std::u16string_view>);

    auto s5 = U"123";
    static_assert(std::is_same_v<decltype(s5), const char32_t *>);
    auto s5s = U"123"s;
    static_assert(std::is_same_v<decltype(s5s), std::u32string>);
    auto s5sv = U"123"sv;
    static_assert(std::is_same_v<decltype(s5sv), std::u32string_view>);

    std::cout << s1 << s2 << "\n";
    std::cout << s3 << s3s << s3sv << "\n";

    // Cannot serialize u16 / u32 using cout/wcout...
    //std::cout << s4 << s4s << s4sv << "\n";
    //std::cout << s5 << s5s << s5sv << "\n";
}