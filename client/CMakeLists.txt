cmake_minimum_required(VERSION 3.8)
project(GraphVisualization LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

set(SRC_LIST client.cpp client_function.cpp)
add_executable(client ${SRC_LIST})