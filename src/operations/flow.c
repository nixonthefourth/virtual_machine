//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#include "../../include/operations/flow.h"
#include "../../include/vm.h"
#include <stdio.h>

/**
 * @brief Performs an unconditional jump.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump(VM *vm) {
    int addr = vm->program[vm->ip++];
    vm->ip = addr;
}

/**
 * @brief Jump if zero. Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump_zero(VM *vm) {
    // Operand fetch
    int addr = vm->program[vm->ip++];

    // Check for stack underflow
    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Get the top of the stack
    int top = pop(vm);

    // Perform action
    if (top == 0) {
        vm->ip = addr;
    }
}