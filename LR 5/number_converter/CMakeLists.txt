cmake_minimum_required(VERSION 3.10)
project(NumberConverter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -DDEBUG")

add_executable(number_converter main.c converter.c validator.c ui_handler.c)