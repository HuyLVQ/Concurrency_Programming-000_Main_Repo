cmake_minimum_required(VERSION 2.8.9)

project(bounded_buffer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Make headers visible
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main
    src/main.c
)
