cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(EclataxEngine)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if (MSVC)
    add_compile_options(/W4 /WX-)
elseif(UNIX)
    add_compile_options(-g)
endif()

set(CMAKE_CXX_FLAGS "-W -Wall -fprofile-arcs -ftest-coverage")

## Enable Google test library
enable_testing()

## Required packages
find_package(Threads)
find_package(GTest REQUIRED)

find_package(Boost 1.67 REQUIRED)

## General sources
set(SRC
)

## Server sources
# set(SRC_SERVER
#     src/engine/GameEngine.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/network/TcpConnection.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/network/TcpNetwork.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/network/UdpNetwork.cpp
#     src/engine/DLLoader.cpp
#     src/engine/ecs/ECS.cpp
#     src/engine/scenesManagement/sceneMachine/SceneStateMachine.cpp
#     src/engine/scenesManagement/scenes/AScene.cpp
#     src/engine/ecs/ECS.cpp
#     src/engine/ecs/entities/Entity.cpp
#     src/engine/ecs/entities/EntityFactory.cpp
#     src/engine/ecs/systems/IASystem.cpp
#     src/engine/ecs/systems/RenderSystem.cpp
#     src/engine/ecs/systems/SpawnerSystem.cpp
#     src/engine/ecs/systems/MovementSystem.cpp
#     src/engine/ecs/systems/LifeSpanSystem.cpp
#     src/engine/ecs/systems/AnimationSystem.cpp
#     src/engine/ecs/systems/CollisionSystem.cpp
#     src/engine/ecs/systems/HealthManipulatorSystem.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/TextSystem.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/Mediator.cpp
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/Hub.cpp
# )

set (INCLUDE_ENGINE
    src/engine/scenesManagement/sceneMachine
    src/engine/scenesManagement/scenes
    src/engine/ecs/components
    src/engine/ecs/entities
    src/engine/ecs/systems
    src/engine/ecs
    src/engine
)

## Include headers to program
include_directories(
    src
)

## Test executable
add_executable(EclataxEngine-test
    src/main.cpp
)

set (SRC_TEST
    tests/main.cpp
)

## including google test library
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)

## Creating executable of unit tests
add_executable(unit_tests
    ${SRC}
    ${SRC_TEST}
)

## Linking libraries
# target_link_libraries(r-type_server
#     CONAN_PKG::sfml
#     CONAN_PKG::boost_system
#     CONAN_PKG::boost_asio
#     ${CMAKE_THREAD_LIBS_INIT}
#     ${CMAKE_DL_LIBS}
# )

target_link_libraries(unit_tests PUBLIC
    pthread
    CONAN_PKG::sfml
    CONAN_PKG::gtest
    CONAN_PKG::boost_system
    CONAN_PKG::boost_asio
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)