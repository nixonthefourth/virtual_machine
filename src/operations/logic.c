//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#include "../../include/operations/logic.h"
#include "../../include/vm.h"
#include <stdio.h>

/**
 * @brief Equality operator.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_eq(VM *vm) {
    // Check for stack underflow
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful Case
    else {
        int b = pop(vm);
        int a = pop(vm);
        push(vm, a == b);
    }
}

/**
 * @brief Less than operation. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_lt(VM *vm) {
    // Check for stack underflow
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful Case
    else {
        int b = pop(vm);
        int a = pop(vm);
        push(vm, a < b);
    }
}

/**
 * @brief Greater than operation. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_gt(VM *vm) {
    // Check for stack underflow
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful Case
    else {
        int b = pop(vm);
        int a = pop(vm);
        push(vm, a > b);
    }
}