struct Base
{
    Base()
        : x_( 1234 )
    {
    }

    explicit Base( int x )
        : x_( x )
    {
    }

    Base( int x, int y )
        : x_( x + y )
    {
    }

    int x_;
};


struct SubDefault : Base
{
    using Base::Base; // inherit all constructors
};

struct SubOverride : Base
{
    using Base::Base; // inherit all constructors

    // Since we redefined some constructors,
    // we are forced to redefined the default constructor
    SubOverride()
    {
    }

    // but override some
    SubOverride( int x, int y )
        : Base( x * y )
    {
    }

};


int main()
{
    SubDefault d1;
    SubDefault d2( 2 );
    SubDefault d3( 2, 3 );
    
    SubOverride o1;
    SubOverride o2( 5 );
    SubOverride o3( 2, 3 );

    if (d1.x_ != 1234)
        return 1;
    if (d2.x_ != 2)
        return 1;
    if (d3.x_ != (2+3))
        return 1;
    if (o1.x_ != 1234)
        return 1;
    if (o2.x_ != 5)
        return 1;
    if (o3.x_ != (2*3))
        return 1;
    return 0;
}
