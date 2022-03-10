cmake_minimum_required(VERSION 3.21)

add_executable(oxChat_Server Main.cpp)

target_link_libraries(oxChat_Server oxCrypt)
target_include_directories(oxChat_Server PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/oxCrypt/include)

