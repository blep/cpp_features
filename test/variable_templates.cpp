template<typename T>
constexpr T pi = T( 3.1415926535897932385 );

int main()
{
    float pif = pi<float>;
    double pid = pi<double>;

    return 0;
}
