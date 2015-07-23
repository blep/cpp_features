struct Struct
{
    typedef int MyNestedType;

    auto method_with_trailing_return_type( int x ) -> MyNestedType;
};

auto Struct::method_with_trailing_return_type( int x ) -> MyNestedType
{
    return x * 2;
}

int main()
{
    Struct s;
    return s.method_with_trailing_return_type( 10 ) != 20;
}
