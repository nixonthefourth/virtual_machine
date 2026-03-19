cmake_minimum_required(VERSION 4.1)
project(virtual_machine C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(src)

add_executable(virtual_machine src/main.c
        src/vm.c
        include/vm.h
        src/operations/stack.c
        include/operations/stack.h
        src/operations/maths.c
        include/operations/maths.h
        src/operations/flow.c
        include/operations/flow.h
        src/operations/logic.c
        include/operations/logic.h
        src/operations/registers.c
        include/operations/registers.h
        src/io/assembler.c
        include/io/assembler.h
        src/io/lexer.c)
