template<typename T>
struct Wrapper
{
    Wrapper()
        : value_( static_cast<T>(0) )
    {
    }

    operator T() const
    {
        return value_;
    }

    T value_;
};



int main()
{
    Wrapper<int *> p;
    // previous to this feature, the compiler would not
    // attempt to convert p to a pointer type.
    delete p;           


    // previous to this feature, the compiler would not
    // attempt to convert v to an integral type.
    Wrapper<int> v;
    switch ( v )
    {
    case 0:
        break;
    default:
        return 1;
    }

    return 0;
}