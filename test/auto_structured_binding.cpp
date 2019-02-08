#include <iostream>
#include <tuple>
#include <type_traits>


// A struct with specific override of std::tuple_size, std::tuple_element and providing a get function
struct Point
{
    int xy[2];
};


template<size_t index>
constexpr int &get(Point &p)
{
    return p.xy[index];
}

template<size_t index>
constexpr int get(const Point &p)
{
    return p.xy[index];
}


namespace std {
    template<>
    class tuple_size< Point > : public std::integral_constant<size_t, 2> 
    {
    };

    template<size_t index>
    class tuple_element< index, Point >
    {
    public:
        using type = int; // type of the element at 'index'
    };
}



// A plain old struct
struct MyPair
{
    int x;
    int y;
};



int main()
{
    int values[] = { 10, 20 };
    auto[x1, y1] = values;
    std::cout << "x1:" << x1 << ", y1=" << y1 << "\n";

    auto tis = std::make_tuple(int{ 1234 }, std::string{ "hello" });
    auto[tis1, tis2] = tis;
    static_assert(std::is_same_v<decltype(tis1), int>);
    static_assert(std::is_same_v<decltype(tis2), std::string>);

    auto point = Point{ 100, 200 };
    auto[px, py] = point;
    std::cout << "px:" << px << ", py=" << py << "\n";

    auto data = MyPair{ 12, 22 };
    auto[pairX, pairY] = data;
    std::cout << "pairX:" << pairX << ", pairY=" << pairY << "\n";

    return 0;
}
