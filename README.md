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
