int main()
{
    return 1'000'000 != 1000*1000
        ||  1'0'0'0'0'0'0 != 1000*1000
        ||  0x10'00 != 0x1000;
}