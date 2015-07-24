#include <string>

struct Product
{
    std::string name_;
    std::string code_ = "";
};

class Order
{
public:
    Product product_ = {"tarte", "TRT"};
    int quantity_ = 1;
};

bool orderEqual( const Order &o, std::string name, std::string code, int quantity )
{
    return o.product_.name_ == name 
        && o.product_.code_ == code  
        &&  o.quantity_ == quantity;
}

int main()
{
    Order orders[4] = { 
        {},
        { {"beignet"} },
        { {"crepe", "CRP"}, 2 },
        { {"galette"} }
    };
    if ( !orderEqual(orders[0], "tarte", "TRT", 1) )
        return 1;
    if ( !orderEqual(orders[1], "beignet", "", 1) )
        return 1;
    if ( !orderEqual(orders[2], "crepe", "CRP", 2) )
        return 1;
    if ( !orderEqual(orders[3], "galette", "", 1) )
        return 1;
    return 0;
}
