#include <string>

union Value
{
    int intValue_ = 1234;
    double doubleValue;
};

int main()
{
    Value v1 = {};
    return v1.intValue_ != 1234;
}
