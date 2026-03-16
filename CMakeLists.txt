cmake_minimum_required(VERSION 4.1)
project(virtual_machine C)

set(CMAKE_C_STANDARD 11)

add_executable(virtual_machine src/main.c
        src/vm.c
        include/vm.h)
