cmake_minimum_required(VERSION 3.10)
project(NumberConverter C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -DDEBUG")

include_directories(include)
add_executable(number_converter 
    src/main.c 
    src/converter.c 
    src/validator.c 
    src/ui_handler.c
)