#include <string>

struct Obj
{
    std::string value() &
    {
        return "mutable";
    }
    std::string value() const &
    {
        return "const";
    }
    std::string value() &&
    {
        return "movable";
    }
};


int main()
{
    Obj o;
    if (o.value() != "mutable")
        return 1;

    const Obj &co = o;
    if (co.value() != "const")
        return 1;

    Obj && mo = std::move(o);
    if (mo.value() != "mutable") // mo is an lvalue, hence can only be resolved to & or const &
        return 1;

    return 0;
}