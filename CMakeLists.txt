cmake_minimum_required(VERSION 3.10)

project(emu)

include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(emu
                main.c
                fetch.c
                execute.c
                decode.c
                context.c)