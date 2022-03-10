cmake_minimum_required(VERSION 3.21)
project(oxChat)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/oxCrypt)

add_subdirectory(src/server)
add_subdirectory(src/client_cli)