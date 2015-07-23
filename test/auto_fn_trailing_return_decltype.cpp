auto fn_with_trailing_decltype( int x ) -> decltype( x * 2 )
{
    return x * 2;
}

int main()
{
    int r = fn_with_trailing_decltype( 10 );
    return r != 20;
}
