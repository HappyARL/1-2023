cmake_minimum_required(VERSION 3.25)
project(1C_algo)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined -std=c++20)

add_link_options(-pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined -std=c++20)

add_executable(1C_algo main.cpp)
