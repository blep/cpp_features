#include <iostream>

struct Counter
{
    int to;

    struct CounterIt 
    {
        int value = 0;

        CounterIt &operator ++()
        {
            ++value;
            return *this;
        }

        int operator *() const
        {
            return value;
        }

        bool operator !=(const Counter &end) const
        {
            return value != end.to;
        }
    };

    CounterIt begin() const
    {
        return CounterIt{};
    }

    Counter end() const
    {
        return *this;
    }
};




Counter countTo(int end)
{
    return Counter{ end };
}


int main() 
{
    // for range now allow begin and end "iterator" to be of different types (here CounterIt and Counter).
    for (auto x : countTo(7))
    {
        std::cout << x << "\n";
    }


}