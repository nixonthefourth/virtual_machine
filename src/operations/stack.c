//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#include "../../include/operations/stack.h"
#include "../../include/vm.h"
#include <stdio.h>

/**
 * @brief Pushes the value onto a stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_push(VM *vm) { push(vm, vm->program[vm->ip++]); }

/**
 * @brief Pop the value from the stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_pop(VM *vm) { pop(vm); }

/**
 * @brief Simply print the latest result from the stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_print(VM *vm) { printf("%d\n", pop(vm)); }

/**
 * @brief Halts the virtual machine.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_halt(VM *vm) { vm->running = 0; }

/**
 * @brief Duplicate the top of the stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_dup(VM *vm) {
    // Check for stack underflow
    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful case
    else {
        int top = vm->stack[vm->sp - 1];
        push(vm, top);
    }
}

/**
 * @brief Swap for two.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_swap(VM *vm) {
    /** Check for the stack underflow */
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful Case
    else {
        int a = pop(vm);
        int b = pop(vm);
        push(vm, a);
        push(vm, b);
    }
}

/**
 * @brief Non-destructive read that checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_peek(VM *vm) {
    /** Check for stack underflow */
    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Perform the operation
    printf("%d\n", vm->stack[vm->sp - 1]);
}