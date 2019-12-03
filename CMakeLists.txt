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

find_package(Boost 1.67 REQUIRED)

## Lib sources
set(LIB
    lib/src/Exception/Exception.cpp
    lib/src/Exception/MissingFileException.cpp
    lib/src/Exception/ConfigFileException.cpp
    lib/src/Exception/TcpSocketException.cpp
    lib/src/Log/Logger.cpp
    lib/src/Benchmarking/Breakpoint.cpp
)

set(ENTITY_ASTEROID
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Asteroid.cpp
)

set(ENTITY_SHIP
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Ship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/ShipEntryPoint.cpp
)

set(ENTITY_FLEET
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Ship.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Fleet.cpp
)

set(ENTITY_PLAYER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Player.cpp
)

set(ENTITY_BEES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/BeeEntrypoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Bee.cpp
)

set(ENTITY_SWARM
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/BeeSwarm.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Bee.cpp
)

set(ENTITY_PARALLAX
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Parallax.cpp
)

set(ENTITY_PARALLAXALT
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/entities/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities/Parallax2.cpp
)

## General sources
set(SRC
    src/ConfReader.cpp
    src/ConfWriter.cpp
)

## Server sources
set(SRC_SERVER
    src/engine/GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network/TcpConnection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network/TcpNetwork.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/network/UdpNetwork.cpp
    src/engine/DLLoader.cpp
    src/engine/ecs/ECS.cpp
    src/engine/scenesManagement/sceneMachine/SceneMachine.cpp
    src/engine/ecs/ECS.cpp
    src/engine/ecs/entities/Entity.cpp
    src/engine/ecs/entities/EntityFactory.cpp
    src/engine/ecs/systems/IASystem.cpp
    src/engine/ecs/systems/RenderSystem.cpp
    src/engine/ecs/systems/SpawnerSystem.cpp
    src/engine/ecs/systems/MovementSystem.cpp
    src/engine/ecs/systems/LifeSpanSystem.cpp
    src/engine/ecs/systems/AnimationSystem.cpp
    src/engine/ecs/systems/CollisionSystem.cpp
    src/engine/ecs/systems/HealthManipulatorSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/systems/TextSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Mediator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Hub.cpp
)

## Game sources

set (SRC_GAME
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/scenes/Level1Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/scenes/Level2Scene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/scenes/SplashScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/scenes/AScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/scenes/HubLoadingScene.cpp
)

## Game include location

set (INCLUDE_GAME
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/src/game/scenes
)

## Client sources

set (SRC_CLIENT
    ${LIB}
    src/client/GraphicalModule.cpp
    src/client/ClientMediator.cpp
    src/client/UdpConnection.cpp
    src/client/TcpConnection.cpp
    src/client/EntityClient.cpp
    src/client/menu.cpp
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
  src/network
  src/client
  src
  ${INCLUDE_GAME}
)

## Creating Librairies
add_library(asteroid SHARED ${ENTITY_ASTEROID})

add_library(ship SHARED ${ENTITY_SHIP})

add_library(fleet SHARED ${ENTITY_FLEET})

add_library(player SHARED ${ENTITY_PLAYER})

add_library(bee SHARED ${ENTITY_BEES})

add_library(swarm SHARED ${ENTITY_SWARM})

add_library(parallax SHARED ${ENTITY_PARALLAX})

add_library(parallaxalt SHARED ${ENTITY_PARALLAXALT})

## Creating server executable
add_executable(r-type_server
  ${LIB}
  ${SRC}
  ${SRC_SERVER}
  ${SRC_GAME}
  main.cpp
)

## Client executable
add_executable(r-type_client
    ${SRC}
    ${SRC_CLIENT}
    ${LIB}
    src/client/main.cpp
)

set (SRC_TEST
    tests/main.cpp
    tests/Exception/test_exception.cpp
    tests/Log/test_logger.cpp
    tests/network/test_tcp.cpp
    tests/main.cpp
    tests/Exception/test_exception.cpp
    tests/Log/test_logger.cpp
    tests/sceneMachine/test_sceneMachine.cpp
    tests/Benchmarking/test_breakpoints.cpp
    tests/ecs/test_ecs.cpp
    tests/entity/test_entity.cpp
    tests/entity/test_entityFactory.cpp
    tests/engine/test_gameEngine.cpp
    tests/component/test_text.cpp
    tests/component/test_Life.cpp
    tests/component/test_Speed.cpp
    tests/component/test_script.cpp
    tests/component/test_damage.cpp
    tests/component/test_health.cpp
    tests/component/test_Spawner.cpp
    tests/component/test_Animation.cpp
    tests/component/test_Particules.cpp
    tests/component/test_Acceleration.cpp
    tests/component/test_collisionBox.cpp
    tests/component/test_LifeSpan.cpp
    tests/systems/test_IA.cpp
    tests/systems/test_Render.cpp
    tests/systems/test_collision.cpp
    tests/systems/test_healthManipulator.cpp
    tests/configfile/config_test.cpp
    tests/client/test_EntityClient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Game/test_hub.cpp
)

## Creating executable of unit tests
include(GoogleTest)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../tests)
add_executable(unit_tests
  ${LIB}
  ${SRC_SERVER}
  ${SRC_GAME}
  ${SRC}
  ${SRC_TEST}
  ${SRC_CLIENT}
)

## Linking libraries
target_link_libraries(r-type_server
    CONAN_PKG::sfml
    CONAN_PKG::boost_system
    CONAN_PKG::boost_asio
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)

target_link_libraries(r-type_client
    CONAN_PKG::sfml
)

target_link_libraries(unit_tests PUBLIC
    CONAN_PKG::gtest
    pthread
    CONAN_PKG::boost_system
    CONAN_PKG::boost_asio
    CONAN_PKG::sfml
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}
)

ADD_CUSTOM_COMMAND(TARGET r-type_client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ressources/ $<TARGET_FILE_DIR:r-type_client>/../ressources/
)
ADD_CUSTOM_COMMAND(TARGET r-type_server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ressources/ $<TARGET_FILE_DIR:r-type_server>/../ressources/
)
