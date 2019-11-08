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

## Required packages
find_package(Threads)
find_package(GTest REQUIRED)

## Lib sources
set(LIB
    lib/src/Exception/Exception.cpp
    lib/src/Log/Logger.cpp
    lib/src/Benchmarking/Breakpoint.cpp
)

## General sources
set(SRC
    src/engine/GameEngine.cpp
    src/engine/scenesManagement/sceneMachine/SceneMachine.cpp
    src/engine/scenesManagement/scenes/DumyScene.cpp
    src/engine/ecs/ECS.cpp
    src/engine/ecs/entities/Entity.cpp
    src/engine/ecs/systems/MovementSystem.cpp
)

## Server sources
set(SRC_SERVER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/TcpConnection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/TcpNetwork.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server/UdpNetwork.cpp
)

## Include headers to program
include_directories(
  include
  lib/src/Benchmarking
  lib/src/Exception
  lib/src/Log
  src/engine/scenesManagement/sceneMachine
  src/engine/scenesManagement/scenes
  src/engine/ecs/components
  src/engine/ecs/entities
  src/engine/ecs/systems
  src/engine/ecs
  src/engine
  src/server
  src
)

## Creating executable
add_executable(rtype
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
target_link_libraries(rtype
    CONAN_PKG::sfml
    CONAN_PKG::boost_system
    ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(unit_tests PUBLIC
    ${GTEST_LIBRARIES}
    pthread
    ${CMAKE_THREAD_LIBS_INIT})