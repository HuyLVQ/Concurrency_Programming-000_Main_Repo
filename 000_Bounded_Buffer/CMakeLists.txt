cmake_minimum_required(VERSION 2.8.9)

project(bounded_buffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main
    src/main.cpp
    src/bounded_buffer.cpp
)

target_link_libraries(main PRIVATE Threads::Threads)
