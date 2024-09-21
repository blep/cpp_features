// #include <cstdalign> // C99
#include <cstddef>
#include <__stddef_offsetof.h>

struct TestAlignAsType
{
    char pad1_;
    alignas(alignof(void*)) char buffer[8];
};

struct TestAlignAsIntegral
{
    char pad1_;
    alignas(128) char buffer[8];
};

int main()
{
    return offsetof(TestAlignAsType, buffer) != sizeof(void*)
        ||  offsetof(TestAlignAsIntegral, buffer) != 128;
}