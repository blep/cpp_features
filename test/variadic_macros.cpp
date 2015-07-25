#include <cstdio>

#define LOG( category, fmt, ... )  if ( category ) std::printf( fmt, __VA_ARGS__ )

int main( int argc, const char *argv[] )
{
    bool app = true;
    bool compute = false;
    LOG( app, "Application %s started\n", argv[ 0 ] );
    LOG( compute, "Computed %d + %d = %d\n", 3, 2, 3+2 );
    return 0;
}