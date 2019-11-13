cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(rtype)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Adding valgrind flags
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-g)
endif()

set(CMAKE_CXX_FLAGS "-W -Wall -fprofile-arcs -ftest-coverage")

## Enable Google test library
enable_testing()

# Required packages
find_package(Threads)
find_package(GTest REQUIRED)

set(LIB 
    lib/src/Exception/Exception.cpp
    lib/src/Log/Logger.cpp
    lib/src/Benchmarking/Breakpoint.cpp)
set(SRC
    src/ecs/entities/Entity.cpp
    src/engine/GameEngine.cpp
    src/ecs/ECS.cpp)
set(SRC_NETWORK
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network/TcpConnection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network/TcpNetwork.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network/UdpNetwork.cpp
)

## Include headers to program
include_directories(
  include
  lib/src/Benchmarking
  lib/src/Exception
  lib/src/Log
  src/ecs/components
  src/ecs/entities
  src/ecs/systems
  src/engine
  src/network
  src/ecs
  src
)

## Creating executable
add_executable(r-type_server
  ${LIB}
  ${SRC}
  ${SRC_NETWORK}
  main.cpp
)

## Creating executable of unit tests
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)
add_executable(unit_tests
  ${LIB}
  ${SRC_NETWORK}
  tests/main.cpp
  tests/Exception/test_exception.cpp
  tests/Log/test_logger.cpp
  tests/network/test_tcp.cpp
)

## Linking libraries
target_link_libraries(r-type_server
    CONAN_PKG::sfml
    CONAN_PKG::boost_system
    ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(unit_tests PUBLIC
    ${GTEST_LIBRARIES}
    pthread
    CONAN_PKG::boost_system
    ${CMAKE_THREAD_LIBS_INIT}
)
