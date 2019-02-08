#include <array>

// Using a constexpr iterating over a string to determine array size and template param
constexpr size_t computeBufferSize(const char *cstr)
{
    size_t s = 0;
    while (*cstr++ != 0)
    {
        ++s;
    }
    return s;
}


template<size_t N>
struct Buffer
{
    char buffer[N];
};


// Using a const local var to determine template parameter value
constexpr size_t constLocalVar()
{
    const size_t x = 3;
    auto buffer = std::array<char, x>{};
    return buffer.max_size();
}

int main()
{
    char buffer[computeBufferSize("hello")];
    static_assert(sizeof(buffer) == 5);

    auto templateBuffer = Buffer< computeBufferSize("hello") >{};
    static_assert(sizeof(templateBuffer.buffer) == 5);

    char buffer2[constLocalVar()];
    static_assert(sizeof(buffer2) == 3);

    return 0;
}
