cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project(EclataxEngine)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

if (MSVC)
    add_compile_options(/W4 /WX-)
elseif(UNIX)
    find_package(Threads)
    add_compile_options(-g)
endif()

## Enable Google test library
enable_testing()

set(CMAKE_CXX_FLAGS "-W -Wall -fprofile-arcs -ftest-coverage")

## Engine sources
set(ENGINE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/LibraryLoader.cpp
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

## Utils source
set(UTILS_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Utils/Log.cpp
)

## Lua sources
set(LUA_SRC
    
)

## General sources
set(SRC
    ${ENGINE_SRC}
    ${UTILS_SRC}
    ${LUA_SRC}
)

## Include headers to program
include_directories(
    src/engine/scenesManagement/sceneMachine
    src/engine/scenesManagement/scenes
    src/engine/ecs/components
    src/engine/ecs/entities
    src/engine/ecs/systems
    src/engine/ecs
    src/engine
    src/Utils
    src
)

## Test executable
add_executable(EclataxEngine-test
    ${SRC}
    src/main.cpp
)

## Static library
add_library(ecl STATIC
    ${SRC}
)

set (SRC_TEST_ENGINE
    tests/engine/test_gameEngine.cpp
    # tests/sceneMachine/test_SceneMachine.cpp
)

set (SRC_TEST_COMPONENT
    tests/component/test_Acceleration.cpp
    tests/component/test_Animation.cpp
    tests/component/test_CollisionBox.cpp
    tests/component/test_Damage.cpp
    tests/component/test_Health.cpp
    tests/component/test_Life.cpp
    tests/component/test_LifeSpan.cpp
    tests/component/test_Particules.cpp
    tests/component/test_Script.cpp
    tests/component/test_Spawner.cpp
    tests/component/test_Speed.cpp
    tests/component/test_Sprite.cpp
    tests/component/test_Text.cpp
)

set (SRC_TEST_SYSTEM
    tests/systems/test_Animation.cpp
    tests/systems/test_Collision.cpp
    tests/systems/test_HealthManipulator.cpp
    tests/systems/test_IA.cpp
    tests/systems/test_MovementSystem.cpp
    tests/systems/test_Render.cpp
)

set (SRC_TEST_ECS
    ${SRC_TEST_COMPONENT}
    ${SRC_TEST_SYSTEM}
    tests/ecs/test_ecs.cpp
    tests/entity/test_entity.cpp
    tests/entity/test_entityFactory.cpp
)

set (SRC_TEST_UTILS
)

set (SRC_TEST
    ${SRC_TEST_ENGINE}
    ${SRC_TEST_ECS}
    ${SRC_TEST_UTILS}
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
target_link_libraries(EclataxEngine-test PUBLIC
    ${CMAKE_DL_LIBS}
)

target_link_libraries(ecl PUBLIC
    ${CMAKE_DL_LIBS}
)

target_link_libraries(unit_tests PUBLIC
    CONAN_PKG::gtest
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)