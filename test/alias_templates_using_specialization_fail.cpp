#include "compile_only_main.hpp"

template<typename A, typename B>
struct Capture
{
    using TA = A;
    using TB = B;
};

template<typename B>
using SimpleCapture = Capture<int, B>;

template<typename B>
struct SimpleCapture<int>
{
    using TA = double;
    using TB = double;
};
