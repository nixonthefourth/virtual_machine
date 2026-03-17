//
// Created by Mykyta Khomiakov on 17/03/2026.
//

#include "../include/operations.h"
#include "../include/vm.h"
#include <stdio.h>

/**
 * @brief Pushes the value onto a stack
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
 * @brief Adds two numbers together, allows for the signed numbers.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_add(VM *vm) {
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    int b = pop(vm);
    int a = pop(vm);

    push(vm, a + b);
}

/**
 * @brief Subtraction operation, checks for underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_sub(VM *vm) {
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    else {
        int b = pop(vm);
        int a = pop(vm);

        push(vm, a - b);
    }
}

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
 * @brief Multiplies two numbers together, both signed and unsigned. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_mult(VM *vm) {
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    int b = pop(vm);
    int a = pop(vm);

    push(vm, a * b);
}

/**
 * @brief Division operation. Allows for both signed and unsigned numbers.
 * Checks for stack underflow and division by zero.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_div(VM *vm) {
    // Check for Stack Underflow
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Initially take value of `b`
    int b = pop(vm);

    // Check whether it is equal to zero
    // If that's the case – interrupt operation
    if (b == 0) {
        printf("Division by zero, error\n");
        vm->running = 0;
    }

    // Otherwise, we are good to go
    int a = pop(vm);

    push(vm, a / b);
}