template<typename T>
constexpr T pi = T( 3.1415926535897932385 );

int main()
{
    pi<float> pif;
    pi<double> pid;

    return 0;
}
