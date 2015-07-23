auto fn_with_trailing_auto( int x ) -> auto
{
    return x * 2;
}

int main()
{
    int r = fn_with_trailing_auto( 10 );
    return r != 20;
}
