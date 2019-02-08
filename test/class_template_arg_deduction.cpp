#include <utility>
#include <type_traits>

#if __cpp_deduction_guides
#else
#error "Class Template Argument Deduction is not supported by the compiler"
#endif



template<typename A, typename B>
struct MyPair
{
    MyPair(const A &, const B &)
    {
    }
};


template<int Size>
struct StaticString
{
    StaticString(const char (&str)[Size]): c_str(str)
    {
    }

    const char *c_str;
};


template<typename T>
struct Container
{
    struct Iterator
    {
        using value_type = T;
    };

    template<typename It>
    Container( It begin, It end )
    {
        
    }
};


// Class Template Argument Deduction guide (must be outside the class, in the same namespace).
template<typename It>
Container(It begin, It end) ->Container<typename It::value_type>;



template<typename A, typename B>
struct MyPerfectPair
{
    // perfect forwarding like
    template<typename U, typename V>
    MyPerfectPair(U &&, V &&)
    {
    }
};

/**
 * // CTAD guide, signature does not need to match. 
 * 
 * Use "decay by value" trick. 
 * 
 * Takes by value to partially simulate decay. See https://youtu.be/-H-ut6j1BYU?list=PLHTh1InhhwT6V9RVdFRoCG_Pm5udDxG1c&t=1987
 * 
 * CTAD signature does not impact with ctor parameter overload resolution. It will be done as usual, but in the context of type MyPerfectPair<A,B>.
 */
template<typename A, typename B>
MyPerfectPair(A, B) -> MyPerfectPair<A, B>;



void typeTracer(int x)
{
}

int main()
{
    // CTAG automatically deduce template argument type based on constructor parameters
    MyPair p1{ 1729, 3.14 };
    StaticString s1{ "hello" };
//    typeTracer(s1);
    static_assert( std::is_same_v<decltype(s1), StaticString<6>> );

    Container<int>::Iterator it;
    Container cont{ it, it };  // using CTAD deduction guide

    int i1 = 12;
    double d2 = 3.4;
    MyPerfectPair p2{ std::move(i1), std::move(d2) };
    static_assert(std::is_same_v<decltype(p2), MyPerfectPair<int, double>>);

    return 0;
}