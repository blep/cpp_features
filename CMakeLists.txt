cmake_minimum_required(VERSION 2.6)

# Notes: project must be at the top of this file, otherwise the following error is generated:
#CMake Error: Error required internal CMake variable not set, cmake may be not be built correctly.
#Missing variable is:
#CMAKE_FIND_LIBRARY_PREFIXES
project( CppFeatures )

# Output all libraries and executables in the same directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Single directory for all libraries.")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin
    CACHE PATH "Single directory for all executables.")
mark_as_advanced( LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH ) 

enable_testing()

macro(UseCompilationWarningAsError)
	if ( MSVC )
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX ")
	endif( MSVC )
endmacro() 

if ( MSVC )
    # Force parallel compilation
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP4")
endif( MSVC )

add_subdirectory( test )
