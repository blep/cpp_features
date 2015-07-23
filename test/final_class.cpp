class NotDerivable final
{
public:
    NotDerivable( int x )
        : x_( x )
    {
    }

    int x_;
};

int main()
{
    NotDerivable s( 10 );
    return s.x_ != 10;
}