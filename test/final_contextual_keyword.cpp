static int f()
{
    typedef int final;
    final x = 20;
    return x;
}

int main()
{
    int final = 10;
    return final != 10  ||  f() != 20;
}
