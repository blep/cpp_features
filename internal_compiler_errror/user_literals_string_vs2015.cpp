
// Evaluated at run-time when evaluating the literal expression
int operator "" _myint( const char *literal )
{
    int value = 0;
    for ( ; *literal != 0; ++literal )
    {
        char c = *literal;
        if ( c >= '0'  &&  c < '9' )
            value = value * 10 + int( c - '0' );
    }
    return value;
}


template<char... digits>
struct ParseInt
{
    static const int value = 1234;
};

template<char... digits>
int operator "" _compile_time_int()
{
    return ParseInt<digits>::value;
}



int main()
{
    int i1 = 1234_myint;

    if ( i1 != 1234 )
        return 1;

    int i2 = 1234_compile_time_int;
    if ( i2 != 1234 )
        return 1;
    return 0;
}
