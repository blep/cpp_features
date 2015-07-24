#include <string>

struct Value
{
    Value()
        : name_( __func__ )
    {
    }

    std::string name_;
};


std::string someFunction()
{
    return __func__;
}

int main()
{
    // Strictly speaking the standard says that the string 
    // corresponding to __func__ is implementation defined
    // (an empty string is a valid implementation).
    //
    // As a user though I required to at list find the 
    // function name within that string to consider this
    // feature as usable.

    if ( someFunction().find( "someFunction" ) != std::string::npos )
        return 1;

    Value v;
    if ( v.name_.find( "Value" ) != std::string::npos )
        return 1;
    return 0;
}