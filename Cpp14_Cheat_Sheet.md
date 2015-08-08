
[TOC]


# C++14 Meta-programming cheat sheet


# Type deduction

C++ 98: two set of rules, for template:
- `T & / T *`
- `T`

C++14: 6 set of rules: auto variables, forward references, lambda capture and returns, decltype

## Template and auto type deduction

```
template<typename T>
void f( ParamType param );
```

with `ParamType` depending on `T`, for example: `const T &`.

Let's define a few function with different ParamType:
```
template<typename T>
void f_ref( T & param );

template<typename T>
void f_const_ref( const T & param );

template<typename T>
void f_ptr( T * param );

template<typename T>
void f_const_ptr( const T * param );)

template<typename T>
void f_fwd_ref( T && param );

template<typename T>
void f_by_value( T param );

```

Let's define a few variable to pass to the function call:

```
int x = 22;
const int cx = x;
const int &rcx = x;
const int *pcx = &x;
```

| expr               | T deduced as  | ParamType is |
|--------------------|---------------|--------------|
| `f_ref(x)`         | `int`         | `int &`      |
| `f_ref(cx)`        | `const int`   | `const int &`|
| `f_ref(rcx)`       | `const int`   | `const int &`|
| `f_const_ref(x)`   | `int`         | `int &`      |
| `f_const_ref(cx)`  | `int`         | `const int &`|
| `f_const_ref(rcx)` | `int`         | `const int &`|
| `f_ptr(&x)`        | `int`         | `int *`      |
| `f_ptr(pcx)`       | `const int`   | `const int *`|
| `f_fwd_ref(x)`     | `int &`       | `int &`      |
| `f_fwd_ref(cx)`    | `const int &` | `const int &`|
| `f_fwd_ref(rcx)`   | `const int &` | `int &`      |
| `f_fwd_ref(42)`    | `int`         | `int &&`     |
| `f_by_value(x)`    | `int`         | `int`        |
| `f_by_value(cx)`   | `int`         | `int`        |
| `f_by_value(rcx)`  | `int`         | `int`        |
| `f_by_value(42)`   | `int`         | `int`        |

Notes that in above table, `42` is an rvalue (temporary object).

- f_ref: T is not a reference
- f_const_ref: T is not reference and is not const
- f_fwd_ref: If `expr` is lvalue with deduced type `E`, `T` is deduced as `E &`. Reference collapsing yields `E & &&` to be `E &` for ParamType.
- f_by_value: reference/const qualifiers always dropped when deducing T.

auto is deduced using the same rule as T, with the initializer value replacing expr:

| declaration           | auto deduced as  | v type is |
|-----------------------|---------------|--------------|
| `auto &v = x`         | `int`         | `int &`      |
| `auto &v = cx`        | `const int`   | `const int &`|
| `auto &v = rcx`       | `const int`   | `const int &`|
| `const auto &v = x`   | `int`         | `int &`      |
| `const auto &v = cx`  | `int`         | `const int &`|
| `const auto &v = rcx` | `int`         | `const int &`|
| `auto *v = &x`        | `int`         | `int *`      |
| `auto *v = pcx`       | `const int`   | `const int *`|
| `auto &&v = x`        | `int &`       | `int &`      |
| `auto &&v = cx`       | `const int &` | `const int &`|
| `auto &&v = rcx`      | `const int &` | `int &`      |
| `auto &&v = 42`       | `int`         | `int &&`     |
| `auto v = x`          | `int`         | `int`        |
| `auto v = cx`         | `int`         | `int`        |
| `auto v = rcx`        | `int`         | `int`        |
| `auto v = 42`         | `int`         | `int`        |

**Special Case **

| declaration           | v type is                    |
|-----------------------|------------------------------|
| `auto v = {1, 2, 3}`  | `std::initializer_list<int>` |
| `auto v = {1}`        | `std::initializer_list<int>` |

**Beware of N3922 C++17 proposal** (already implement by Visual Studio 2015):

| declaration           | v type C++14                 |v type C++17 |
|-----------------------|------------------------------|
| `auto v{1, 2, 3}`     | `std::initializer_list<int>` | Compilation error |
| `auto v{1}`           | `std::initializer_list<int>` | `int`             | 

Guide-line: don't use auto with initializer_list with =.


Special treatment for exprs that are array/function type:
- when initializing a reference, array/function type deduced
- otherwise decays to a pointer before type deduction

## Lambda capture type deduction

- By reference: same as template type deduction for T &
- C++ 14's init capture: same as auto type deduction
- By value: same as template type deduction except CV qualifiers are retained

| expr               | captured member type  | ParamType is |
|--------------------|---------------|--------------|
| `f_ref(x)`         | `int`         | `int &`      |
| `f_ref(cx)`        | `const int`   | `const int &`|
| `f_ref(rcx)`       | `const int`   | `const int &`|
| `f_const_ref(x)`   | `int`         | `int &`      |
| `f_const_ref(cx)`  | `int`         | `const int &`|
| `f_const_ref(rcx)` | `int`         | `const int &`|
| `f_ptr(&x)`        | `int`         | `int *`      |
| `f_ptr(pcx)`       | `const int`   | `const int *`|
| `f_fwd_ref(x)`     | `int &`       | `int &`      |
| `f_fwd_ref(cx)`    | `const int &` | `const int &`|
| `f_fwd_ref(rcx)`   | `const int &` | `int &`      |
| `f_fwd_ref(42)`    | `int`         | `int &&`     |
| `[cx]{ ... }`      | `const int`   | `int`        |
| `[z=cx] { ... }`   | `int`         | `int`        |
| `f_by_value(rcx)`  | `int`         | `int`        |
| `f_by_value(42)`   | `int`         | `int`        |

## decltype type deduction

### decltype(some_name)

- Given the declaration type of some_one
- Preserve CV qualifiers, references...

## decltype( lvalue expr of type T ) = T &

- decltype( arr[0] ): int &, int arr[10]

Remarks: (some_name) is no longer a name but is an lvalue expr.

## decltype has some more subtilities

For hard-code library developper, see the spec.


## Return type deduction (auto, decltype(auto))

### auto: use template type deduction rules

```
auto myFunc() { // deduced to be int
	static int z = 10;
    return z;
}
```

Deduced like an auto variable declaration:

```
auto v = z;
```

### decltype(auto): use decltype type deduction rules


```
decltype(auto) myFunc() { // deduced to be int &
	static int z = 10;
    return z;
}
```

Deduced like a decltype:

```
decltype(z) returnValue = z;
```

## Reference collapsing

| Original Type | Equivalent simplified type |
|---------------|----------------------------|
| `T & &`       | `T &`                      |
| `T & &&`      | `T &`                      |








## Standard type traits

### enable_if: make a function overload visible depending on a condition


```
        template<typename NumericType>
        static typename std::enable_if< std::is_floating_point<NumericType>::value, bool >::type
            isFinite(NumericType value)
        {
            return std::isnormal(value); // check that value is not NaN, or -/+ Inf
        }

        template<typename NumericType>
        static typename std::enable_if< !std::is_floating_point<NumericType>::value, bool >::type
            isFinite(NumericType /*value*/)
        {
            return true; // not a floating-point type
        }

```


### common_type: Returns a type that all arguments can be implicitly converted to

| Types | Evaluated to |
|--------|--------|
| `common_type_t<int, long>` | `long` |
| `common_type_t<const int, int>` | `int` |
| `common_type_t<int volatile &, int volatile &>` | `int` |

### conditional: Conditionally select ThenType or ElseType

## Forwarding function calls

a.k.a Perfect forwarding.

Forwards a function call ensuring all argument types are preserved.

```
template<typename T>
decltype(auto) parameter(T && x) {
return std::forward<T>(x);
}
```

# noexcept

Important for move constructor and move assignment operator.

STL containers such as `vector` will *only* replace copying by moving on `push_back, resize`... when the move constructor/assignment operator is non throwing. They use `std::move_if_noexcept`.

**BEWARE**: if an exception is thrown by a noexcept function, then `std::terminate()` is called.

### Condionally noexcept function

You can make no except condtional:

```
template<class T1, class T2>
struct pair
{
	void swap( pair &other ) noexcept( 
    	noexcept( swap(first, other.first)
                  && noexcept(swap(second, other.second) );	
};

```	

## Debugging: how to display type at compile time ?

### How to debug type deduction

```
template<typename T> class TypeDisplayer; // declared but not defined

template<typename T> void f( T &param )
{
	TypeDisplayer<T> tType;
    TypeDisplayer<decltype(param)> paramType;
    // Cause both tType and paramType to be shown in the compilation error message
}

void main() {
	int x = 10;
    const int cx = x;
    f( x );
    f( cx );

    auto &v = cx;
    TypeDisplayer<decltype(v)> vType;
}
```

### At run-time

Don't use typeid, it is required by the standard to returns type as if passed by value (discard references and CV qualifiers).

Use Boost.TypeIndex library:

```
#include <boost/type_index.hpp>

template<typename T>
void f( const T &param )
{
	using boost:type_index::type_id_with_cvr;
    std::cout << "T=" << type_id_with_cvr<T>().pretty_name() << "\n";
    std::cout << "T=" << type_id_with_cvr<decltype(param)>().pretty_name() << "\n";
}

```


# Lambda function

```
int x = 10;
const int cx = x;

```

Mutable force the compiler to generate a non-const call operator, allow captured member to be modified:
```
auto lam1 = [cx=cx] mutable { cx = 10 };
```

## Return type deduction

C++11: only for lambda of 1 statement
C++14: all lambda and functions



# ref-qualifiers

Motivation: in addition to overloading member function on constness and mutability, allow overloading for movability.

Motivation example:

```
template <typename T>
class optional
{
  // ...
  T&       value() &;
  T&&      value() &&;
  T const& value() const&;
};

```


Const/Reference qualifiers equivalence:

| C\++98          | C\++11            |
|-----------------|-------------------|
| R value()       | R value() &       |
| R value() const | R value() const & |
| N/A             | R value() &&      |

Notes that you cannot mix C\++98 still declaration and C\++11 declaration for the same member function.

# Sources
- 112-CppCon 2014 - Scott Meyers 'Type Deduction and Why You Care'.mp4
- [ref-qualifiers](https://akrzemi1.wordpress.com/2014/06/02/ref-qualifiers/)