
struct Algo {
    template<typename T>
    static T sum( T x )
    {
        return x;
    }


    template<typename X, typename... Args>
    static auto sum( X x, Args... args ) -> decltype( x + sum(args) )
    {
        return x + sum(args...);
    }
};


int main()
{
    int r = Algo::sum( 10 );
    if ( r != 10 )
        return 1;
    r = Algo::sum( 10, 20 );
    if ( r != (10+20) )
        return 1;
    r = Algo::sum( 10, 20, 30, 40 );
    return r != (10+20+30+40);
}
