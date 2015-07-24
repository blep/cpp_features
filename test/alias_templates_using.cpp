template<typename A, typename B>
struct Capture
{
    using TA = A;
    using TB = B;
};

template<typename B>
using SimpleCapture = Capture<int, B>;

struct Value {};

int main()
{
    Value v;
    SimpleCapture<Value>::TB s = v;
    return 0;
}
