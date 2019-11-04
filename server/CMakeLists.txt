cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 14)
project(test_network)

set(CMAKE_CXX_FLAGS "-Wall -fprofile-arcs -ftest-coverage")

find_package(Boost 1.6 COMPONENTS system REQUIRED)
find_package(Threads)

set(SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UdpNetwork.cpp
#  ${CMAKE_CURRENT_SOURCE_DIR}/TcpConnection.cpp
)

add_executable(test_network ${SRC})

target_link_libraries(test_network
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)
