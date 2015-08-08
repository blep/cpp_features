
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


// Remarks: as of 2015/07 VS2015 ignore constexpr and
// convert the literal on each expression evaluation
constexpr int parseInt( int value, const char *s )
{
    return (*s == 0) ? value
                     : parseInt( value * 10 + int(*s - '0'), s+1);
}

constexpr int operator "" _compile_time_int( const char *s )
{
    return parseInt( 0, s );
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
