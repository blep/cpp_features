#include <vector>

template<typename T, typename R=std::vector<T>>
R vec()
{
    return R();
}

int main()
{
    std::vector<int> v = vec<int>();
    return 0;
}