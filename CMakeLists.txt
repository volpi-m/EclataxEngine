cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(APCPPLib)

# Adding valgrind flags
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-g)
endif()

set(CMAKE_CXX_FLAGS "-Wall -fprofile-arcs -ftest-coverage")

## Enable Google test library
enable_testing()

# Required packages
find_package(Boost 1.6 COMPONENTS system REQUIRED)
find_package(Threads)
find_package(GTest REQUIRED)

set(LIB lib/src/Exception/Exception.cpp
        lib/src/Log/Logger.cpp
        lib/src/Benchmarking/Breakpoint.cpp)
set(SRC src/ecs/entities/Entity.cpp
        src/engine/GameEngine.cpp
        src/ecs/ECS.cpp)

set(SRC_SERVER
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/TcpConnection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/TcpNetwork.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/server/UdpNetwork.cpp
)

## Include headers to program
include_directories(
  include
  lib/src/Exception
  lib/src/Log
  lib/src/Benchmarking
  src/ecs/components/
  src/ecs/entities/
  src/ecs
  src/engine
  src
  src/server
)

## Creating executable
add_executable(APCPPLib
  ${LIB}
  ${SRC}
  ${SRC_SERVER}
  main.cpp)

## Creating executable of unit tests
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)
add_executable(unit_tests
              ${LIB}
              tests/main.cpp
              tests/Exception/test_exception.cpp
	            tests/Log/test_logger.cpp)

## Linking libraries
target_link_libraries(APCPPLib ${CMAKE_THREAD_LIBS_INIT}
                                ${Boost_LIBRARIES}
                                ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unit_tests PUBLIC
                      ${GTEST_LIBRARIES} pthread
                      ${CMAKE_THREAD_LIBS_INIT})
