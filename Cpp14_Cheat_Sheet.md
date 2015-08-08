# C++14 Meta-programming cheat sheet
## rvalues, lvalues...



## Type deduction

C++ 98: two set of rules, for template:
- `T & / T *`
- `T`

Six set of rules:
auto variables, forward references, lambda capture and returns, decltype

C++ 11:
- `T&&`
- `T& / T*` -> lambda capture
- `T` -> auto object, lambda init capture
- decltype, decltype(auto)

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


## Reference collapsing

| Original Type | Equivalent simplified type |
|---------------|----------------------------|
| `T & &`       | `T &`                      |
| `T & &&`      | `T &`                      |

## Standard type traits

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

## TODO

ref-qualifiers
struct S { std::string m; };
● decltype(auto) S::f() const & { return m; }
– std::string
● decltype(auto) S::g() & { return m; }
– std::string
● decltype(auto) S::h() && { return m; }
– std::string

# Sources
- 112-CppCon 2014 - Scott Meyers 'Type Deduction and Why You Care'.mp4
