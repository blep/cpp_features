// Overload resolution rules:
// - overload with no matching concepts are discarded
// - the most specialized concept overload win
// - equally matching "specialization" are ambiguity and cause compilation error

#include <stdint.h>
#include <string>
#include <type_traits>
#include <iostream>

template<typename T>
concept Is32Bits = sizeof(T) == 4;
template<typename T>
concept Is64Bits = sizeof(T) == 8;

template<typename T>
concept IsTrivial = std::is_trivial_v<T>;

template<typename T>
concept Trivial32Bits = IsTrivial<T>  &&  Is32Bits<T>;
template<typename T>
concept Trivial64Bits = IsTrivial<T>  &&  Is64Bits<T>;

template<typename T>
concept IsNotTrivial = !IsTrivial<T>;

template<Is32Bits T>
std::string what_are_you(T value) {
  return "32 bits value";
}

template<Trivial32Bits T>
std::string what_are_you(T value) {
    return "trivial 32 bits value";
}

template<Trivial64Bits T>
std::string what_are_you(T value) {
    return "trivial 64 bits value";
}

template<Is64Bits T>
std::string what_are_you(T value) {
    return "64 bits value";
}

template<IsTrivial T>
std::string what_are_you(T value) {
  return "trivial value";
}

// Presence of this overload would cause an ambiguity because call to
// what_are_you( Reg32 ) become ambiguous as two overload become valid:
// - what_are_you( Is32Bits )
// - what_are_you( IsNotTrivial )
// template<IsNotTrivial T>
// std::string what_are_you(T value) {
//     return "not trivial value";
// }


// This overload as no concept, so it is considered less specialized than all the above.
template<typename T>
std::string what_are_you(T value) {
    return "not trivial value";
}


#define REPORT_WHAT_ARE_YOU( expr ) \
  report_what_are_you( #expr, expr )

template<typename T>
void report_what_are_you(const std::string_view &expr_text, T value) {
  std::cout << expr_text << ": " << what_are_you( value ) << std::endl;
}

struct Pair2x64 {
    uint64_t first;
    uint64_t second;
};

struct Reg32 {
    Reg32() : value( 0 ) {
    }

    uint32_t value;
};

int main() {
    REPORT_WHAT_ARE_YOU( uint32_t(12345) );
    REPORT_WHAT_ARE_YOU( Reg32() );
    REPORT_WHAT_ARE_YOU( uint64_t(12345) );
    REPORT_WHAT_ARE_YOU( Pair2x64{} );
    REPORT_WHAT_ARE_YOU( std::string("hello") );
    return 0;
}