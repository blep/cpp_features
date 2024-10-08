# --output-on-failure
# CMake provide detection for some language features (and automatically set related compiler flags):
# http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
# http://www.cmake.org/cmake/help/v3.1/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html
# http://www.cmake.org/cmake/help/v3.1/prop_tgt/CXX_STANDARD.html
# http://www.cmake.org/cmake/help/v3.1/prop_tgt/CXX_STANDARD_REQUIRED.html

set(MAX_STANDARD_VERSION 23) # 98, 11, 14, 17


# It seems that travis-ci does not support CMake 3, so we add compiler flag using the recipe below
# include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
# CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
# if(COMPILER_SUPPORTS_CXX17)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# elseif(COMPILER_SUPPORTS_CXX14)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# elseif(COMPILER_SUPPORTS_CXX11)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# elseif(COMPILER_SUPPORTS_CXX0X)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# else()
#         message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
# endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Makes clan links against its own standard C++ library implementation.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

include_directories(".")


function( feature_add_test FIRST_SOURCE)
# Remarks: we could use CMAKE_PARSE_ARGUMENTS() for fancy stuffs like add_executable()
    string( REPLACE ".cpp" "" testname ${FIRST_SOURCE} )
    # ARGN contain all additional function parameters
    add_executable( ${testname} ${FIRST_SOURCE} ${ARGN} ) 
	set_property(TARGET ${testname} PROPERTY CXX_STANDARD ${MAX_STANDARD_VERSION})
    add_test( NAME ${testname} COMMAND ${testname} )
endfunction( feature_add_test )

function( feature_add_compile_fail_test FIRST_SOURCE)
    string( REPLACE ".cpp" "" testname ${FIRST_SOURCE} )
    add_executable( ${testname} ${FIRST_SOURCE} ${ARGN} )
    # Avoid building these targets normally
    set_target_properties(${testname} PROPERTIES
                      EXCLUDE_FROM_ALL TRUE
                      EXCLUDE_FROM_DEFAULT_BUILD TRUE)
    # Provide a PP definition to target the appropriate part of
    # "will_fail.cpp", or provide separate files per test.
    # target_compile_definitions(will_fail PRIVATE TEST1)
    
    # Add the tests.  These invoke "cmake --build ..." which is a
    # cross-platform way of building the given target.
    add_test(NAME "${testname}"
         COMMAND ${CMAKE_COMMAND} --build . --target ${testname} --config $<CONFIGURATION>
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    # Expect these tests to fail (i.e. cmake --build should return a non-zero value)
    set_tests_properties("${testname}" PROPERTIES WILL_FAIL TRUE)
endfunction( feature_add_compile_fail_test )

feature_add_test( aggregate_default_initializers_struct.cpp )
feature_add_test( aggregate_default_initializers_union.cpp )
feature_add_test( alias_templates_using.cpp )
feature_add_compile_fail_test( alias_templates_using_specialization_fail.cpp )
feature_add_test( align_as.cpp )
feature_add_test( auto_var_decl.cpp )
feature_add_test( auto_var_type_inference.cpp )
feature_add_test( auto_fn_trailing_return_type.cpp )
feature_add_test( auto_fn_trailing_return_decltype.cpp )
feature_add_test( auto_fn_trailing_return_decltype_recursion.cpp )
feature_add_compile_fail_test( auto_fn_trailing_return_decltype_recursion_fail.cpp )
feature_add_test( auto_fn_trailing_return_auto.cpp )
feature_add_test( auto_structured_binding.cpp )
feature_add_test( binary_literals.cpp )
feature_add_test( ifconstexpr_poly_return_type.cpp )
feature_add_test( class_template_arg_deduction.cpp )
feature_add_test( concept.cpp )
feature_add_test( concept_overload.cpp )
feature_add_test( constexpr_fun.cpp blcx/constexpr_assert.hpp blcx/constexpr_writer.hpp)
feature_add_test( constexpr_writer_test.cpp blcx/constexpr_writer.hpp)
feature_add_test( constexpr_template_param.cpp )
feature_add_test( contextual_conversions.cpp )
feature_add_test( default_function_template_args.cpp )
feature_add_test( delegating_constructors.cpp )
feature_add_test( digit_separators.cpp )
feature_add_test( enum_forward_declarations.cpp )
feature_add_test( enum_forward_declarations_class.cpp )
feature_add_test( for_range_generalization.cpp )
feature_add_test( final_class.cpp )
feature_add_test( final_contextual_keyword.cpp )
feature_add_compile_fail_test( final_class_compile_fail.cpp )
feature_add_test( format.cpp )
feature_add_test( func_identifier.cpp )
feature_add_test( inheriting_constructors.cpp )
feature_add_test(namespace_nested_decl_shorthand.cpp)
feature_add_test( reference_qualified_functions.cpp )
feature_add_test( static_assert_true.cpp )
feature_add_test( string_literals.cpp )
feature_add_compile_fail_test( static_assert_false.cpp )
feature_add_test( user_literals.cpp )
feature_add_test( user_literals_string.cpp )
feature_add_test( variable_templates.cpp )
feature_add_test( variadic_macros.cpp )
feature_add_test( variadic_templates.cpp )

