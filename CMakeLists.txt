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

## General sources
set(SRC
    ${ENGINE_SRC}
)

## Engine sources
set(ENGINE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/DLLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/ECS.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/scenesManagement/sceneMachine/SceneStateMachine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/scenesManagement/scenes/AScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/ECS.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/EntityFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/IASystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/RenderSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/SpawnerSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/MovementSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/LifeSpanSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/AnimationSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/CollisionSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/HealthManipulatorSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/TextSystem.cpp
)

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
    ${SRC}
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

target_link_libraries(unit_tests PUBLIC
    pthread
    CONAN_PKG::sfml
    CONAN_PKG::gtest
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)