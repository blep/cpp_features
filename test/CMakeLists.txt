function( feature_add_test FIRST_SOURCE)
# Remarks: we could use CMAKE_PARSE_ARGUMENTS() for fancy stuffs like add_executable()
    string( REPLACE ".cpp" "" testname ${FIRST_SOURCE} )
    # ARGN contain all additional function parameters
    add_executable( ${testname} ${FIRST_SOURCE} ${ARGN} ) 
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

feature_add_test( auto_var_decl.cpp )
feature_add_test( auto_fn_trailing_return_type.cpp )
feature_add_test( auto_fn_trailing_return_decltype.cpp )
feature_add_test( auto_fn_trailing_return_decltype_recursion.cpp )
feature_add_compile_fail_test( auto_fn_trailing_return_decltype_recursion_fail.cpp )
feature_add_test( auto_fn_trailing_return_auto.cpp )
feature_add_test( final_class.cpp )
feature_add_compile_fail_test( final_class_compile_fail.cpp )
feature_add_test( static_assert_true.cpp )
feature_add_compile_fail_test( static_assert_false.cpp )
