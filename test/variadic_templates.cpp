#include <utility>

template<typename... Types>
struct List
{
};

template<typename... Types>
struct GetFirst;

template<typename Head, typename... Types>
struct GetFirst< List<Head, Types...> >
{
    typedef Head type;
};

template<typename... Types>
struct GetLength;

template<typename... Types>
struct GetLength
{
    static std::size_t get()
    {
        return sizeof... (Types);
    }
};

typedef List<int, float, bool> L1;

typedef GetFirst<L1>::type IntType;

int main()
{
    IntType x = 1234;
    if ( x != 1234 )
        return 1;
    if ( GetLength<int, float, double, char>::get() != 4 )
        return 1;
    return 0;
}