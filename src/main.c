#include <stdio.h>
#include "vm.h"

int main() {
    printf("Welcome to the Virtual Machine!\n");

    int program[] = {
        PUSH, 8,
        PUSH, 5,
        ADD,
        PRINT,
        HALT
    };

    VM vm = {0};

    vm.program = program;
    vm.running = 1;

    vm_run(&vm);

    return 0;
}