
namespace A::B {
    struct Base
    {
    };
}



namespace A::B::Impl {
    struct Thing : Base
    {
    };
}


int main() {
    auto thing = A::B::Impl::Thing{};

    return 0;
}