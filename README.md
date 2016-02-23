# cpp_features
Demo of new C++ features (C++ 03, 11, 14) accross compiler.

Use CMake ctest to test for successful execution or expected compilation failure.

Test to do:
- final with inheritance
- __func__ not in param decl

Stuffs to investigate:
inheriting_constructors.cpp:
  - when debugging, step into on SubDefault variable construction does not step into Base constructor
  - putting a break-point in Base constructor force compiler to break though.

Idea to explore:
Can you use UDL to generate compile time string formatting ?
"Hello %s!"fmt( "World" );
=> no reasonnable until C++ 17 as currently constexpr must be recursive.
=> additional constexpr is not evaluated only once on all compilers
  
  
Experimental C++ 17 stuffs:
https://www.visualstudio.com/en-us/news/vs2015-vs.aspx#C++

- Resumable Functions (resume/await) The resume and await keywords provide language-level support for asynchronous programming and enables resumable functions. Currently, this feature is only available for x64 targets. Proposed for C++17 [N3858]

VS 2015 standard conformance (nearly all c++14 an a lot c++17):
http://blogs.msdn.com/b/vcblog/archive/2015/06/19/c-11-14-17-features-in-vs-2015-rtm.aspx
