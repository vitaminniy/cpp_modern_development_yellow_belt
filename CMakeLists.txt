cmake_minimum_required(VERSION 3.19)

project(cpp_modern_development LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

add_subdirectory(src)
