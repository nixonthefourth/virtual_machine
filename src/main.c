#include <stdio.h>
#include "vm.h"

int main() {
    printf("Welcome to the Virtual Machine!\n");

    int program[] = {
        OP_PUSH, 8,
        OP_PUSH, 5,
        OP_ADD,
        OP_PRT,
        OP_HLT
    };

    VM vm = {0};

    vm.program = program;
    vm.running = 1;

    vm_run(&vm);

    return 0;
}