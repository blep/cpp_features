enum class E;

enum S: short;

struct A
{
    E enum_;
    S shortEnum_;
};

static A a;


int main()
{
    return 0;
}