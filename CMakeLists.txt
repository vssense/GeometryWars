cmake_minimum_required(VERSION 3.0)

project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fsanitize=address -O2")

add_executable(game)

target_include_directories(game PUBLIC src)

add_subdirectory(src)

find_package(X11 REQUIRED)
target_link_libraries(game m X11)
