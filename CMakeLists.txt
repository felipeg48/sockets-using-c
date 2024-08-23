cmake_minimum_required(VERSION 3.9)
project(socket)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(http_server)
add_subdirectory(http_client)