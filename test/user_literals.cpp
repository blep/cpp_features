struct MyNumber
{
    explicit MyNumber( long double v )
        : value_( v )
    {
    }
    long double value_;
};

// Notes that the standard mandate very specific parameter type
// (you cannot replace long double by double).
MyNumber operator "" _num( long double v )
{
    return MyNumber( v );
}

long double operator "" _mul10( long double v )
{
    return v * 10;
}

unsigned long long operator "" _mul10( unsigned long long v )
{
    return v * 10;
}


int main()
{
    MyNumber n1 = 1234.0_num;
    long double d1 = 1234.0_mul10;
    unsigned long long i1 = 1234_mul10;

    if ( n1.value_ != 1234.0 )
        return 1;
    if ( d1 != 1234.0*10 )
        return 1;
    if ( i1 != 1234*10 )
        return 1;
    return 0;
}
