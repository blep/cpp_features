#include <stdio.h>
#include <algorithm>
#include <string>
#include <type_traits>

template<typename T>
struct TypeLogger
{
    //template<typename U>
    //static std::string getConst( U & )
    //{
    //    return "";
    //}
    //template<typename U>
    //static std::string getConst( const U & )
    //{
    //    return "const";
    //}

    //template<typename T>
    //static void log( const char *name, T &&value )
    //{
    //    std::string kind = getConst(value);
    //    if (std::is_lvalue_reference<T>::value)
    //        kind += "& ";
    //    if (std::is_rvalue_reference<T>::value)
    //        kind += "&& ";
    //    printf( "%s%s\n", kind.c_str(), name );
    //}

    static void log( const char *name, T && value )
    {
        printf( "%s &&\n", name );
    }
    static void log( const char *name, T & value )
    {
        printf( "%s &\n", name );
    }
    static void log( const char *name, const T & value )
    {
        printf( "%s const &\n", name );
    }
};


struct NCType
{
    explicit NCType( int value )
        : x_( value )
    {
    }

    void which() const
    {
        printf( "const method\n" );
    }

    void which()
    {
        printf( "non-const method\n" );
    }

private:
    NCType( const NCType &other );
    NCType &operator =( const NCType &other );

    int x_;
};


void modIt( int &x )
{
    printf( "x=%d\n", x );
    ++x;
}

template<typename T>
void tellMeWhich( T &value )
{
    value.which();
}


int main()
{
    auto &&x = 1234;
    // auto &xref = 1234; Doesn't compile
    const auto &xcref = 1234;
    TypeLogger<int>::log( "int", x );
//    TypeLogger<int>::log( "int", xref );
    TypeLogger<int>::log( "int", xcref );
    TypeLogger<int>::log( "int", std::move(x) );

    auto &&nctA = NCType( 1234 );
    //auto &nctA_ar = NCType( 1234 ); // doesn't compile on clang
    const auto &nctA_acr = NCType( 1234 );
    TypeLogger<NCType>::log( "NCType", nctA );
    //TypeLogger<NCType>::log( "NCType", nctA_ar );
    TypeLogger<NCType>::log( "NCType", nctA_acr );
    TypeLogger<NCType>::log( "NCType", std::move(nctA) );
    nctA.which();
    nctA_acr.which();
    tellMeWhich( nctA );
    tellMeWhich( nctA_acr );

    modIt( x );
    modIt( x );
    modIt( x );

    return 0;
}