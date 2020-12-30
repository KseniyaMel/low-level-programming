cmake_minimum_required(VERSION 3.16)
project(lab6 C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(main.c image_parser.h structs.h image_parser.c image_manip.h image_manip.c)

target_link_libraries(lab6 m)
