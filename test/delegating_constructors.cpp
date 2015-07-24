#include <stdexcept>

class ComplexValue
{
public:
    ComplexValue( double x, int rank, int secondaryRank )
        : x_( x )
        , rank_( rank )
        , secondaryRank_( secondaryRank )
    {
        isValid_ = ( secondaryRank >= rank );
    }

    ComplexValue( double x )
        : ComplexValue( x, 1, 2 )
    {
    }

    ComplexValue( int rank, int secondaryRank )
        : ComplexValue( 1, rank, secondaryRank )
    {
    }

    double x_;
    int rank_;
    int secondaryRank_;
    bool isValid_;
};

int main()
{
    ComplexValue v1( 1234.0, 5, 7 );
    ComplexValue v2( 567.0 );
    ComplexValue v3( 7, 8 );
    if ( v1.x_ != 1234.0  ||  v1.rank_ != 5  ||  v1.secondaryRank_ != 7  ||  !v1.isValid_ )
        return 1;
    if ( v2.x_ != 567.0  ||  v2.rank_ != 1  ||  v2.secondaryRank_ != 2  ||  !v2.isValid_ )
        return 1;
    if ( v3.x_ != 1.0  ||  v3.rank_ != 7  ||  v3.secondaryRank_ != 8  ||  !v3.isValid_ )
        return 1;
    return 0;
}
