cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(APCPPLib VERSION 1.0 DESCRIPTION "A library designed to help you during the developpement of your C++ projects")

# Adding valgrind flags
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-g -ldl)
endif()

set(CMAKE_CXX_FLAGS "-Wall -fprofile-arcs -ftest-coverage")

# Enable Google test library
enable_testing()

# Required packages
find_package(Threads)
find_package(GTest REQUIRED)  

# source files
set(SRC lib/src/Exception/Exception.cpp
        lib/src/Exception/ConfigFileException.cpp
        lib/src/Exception/MissingFileException.cpp
        lib/src/Exception/TcpSocketException.cpp
        lib/src/Log/Logger.cpp
        lib/src/Benchmarking/Breakpoint.cpp
        lib/src/Maths/Triangles.cpp
        lib/src/Utils/LibraryLoader.cpp)

# Include headers to program
include_directories(
  lib/src/Log
  lib/src/Maths
  lib/src/Utils
  lib/src/Exception
  lib/src/Benchmarking
  include)

# Creating the library
add_library(APCPPLib STATIC ${SRC})

# Set library version
set_target_properties(APCPPLib PROPERTIES VERSION ${PROJECT_VERSION})

# Creating executable of unit tests
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)
add_executable(apcpplib_unit_tests
              tests/main.cpp
              tests/Exception/test_exception.cpp
              tests/Maths/test_triangles.cpp
              tests/Utils/test_tuples.cpp
	            tests/Log/test_logger.cpp)

## Linking libraries
target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(apcpplib_unit_tests PUBLIC
                      APCPPLib
                      ${GTEST_LIBRARIES} pthread
                      ${CMAKE_THREAD_LIBS_INIT})
