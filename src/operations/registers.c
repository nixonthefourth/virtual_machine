//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#include "../../include/operations/registers.h"
#include "../../include/vm.h"
#include <stdio.h>

/**
 * @brief Store operation. Checks for the register validity and stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_store(VM *vm) {
    /** Checks register */
    int reg = vm->program[vm->ip++];

    /** Cheks whether the register is valid */
    if (reg < 0 || reg >= 16) {
        printf("Invalid register: %d\n", reg);
        vm->running = 0;
    }

    /** Checks for stack undeflow */
    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    /** Remove value from the stack and push it to the register */
    vm->registers[reg] = pop(vm);
}

/**
 * @brief Load operation. Checks for the register validity and stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_load(VM *vm) {
    /** Select register */
    int reg = vm->program[vm->ip++];

    /** Check for the stack underflow */
    if (reg < 0 || reg >= 16) {
        printf("Invalid register: %d\n", reg);
        vm->running = 0;
    }

    // Successful Case
    else {
        /** Load the value into the register */
        push(vm, vm->registers[reg]);
    }
}
