// #include <cstdalign> // C99
#include <cstddef>

struct TestAlignAsType
{
    char pad1_;
    char alignas(void*) buffer[8];
};

struct TestAlignAsIntegral
{
    char pad1_;
    char alignas(128) buffer[8];
};

int main()
{
    return offsetof(TestAlignAsType, buffer) != sizeof(void*)
        ||  offsetof(TestAlignAsIntegral, buffer) != 128;
}