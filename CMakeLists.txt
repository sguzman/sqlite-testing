cmake_minimum_required(VERSION 3.11)
project(sqlite)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O6")

add_executable(sqlite_server src/main.cpp)
link_directories(/usr/local/lib)
target_link_libraries(sqlite_server sqlite3)