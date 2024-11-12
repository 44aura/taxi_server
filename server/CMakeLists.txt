cmake_minimum_required(VERSION 3.8)
project(GraphVisualization LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

set(SRC_LIST start_accept.cpp server.cpp handle_passenger.cpp handle_driver.cpp handle_client.cpp make_route.cpp get_address.cpp arrive.cpp manipulate.cpp get_moscow_time.cpp create_log.cpp add_log.cpp)
add_executable(server ${SRC_LIST})
