#include "compile_only_main.hpp"

class NotDerivable final
{
public:
    NotDerivable()
    {
    }
};


class DerivedWithCompileError : NotDerivable
{
public:
};
