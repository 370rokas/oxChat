cmake_minimum_required(VERSION 3.21)

add_executable(oxChat_CLI Main.cpp)

target_link_libraries(oxChat_CLI oxCrypt)
target_include_directories(oxChat_CLI PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib/oxCrypt/include)