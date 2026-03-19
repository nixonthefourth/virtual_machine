//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#include "../../include/operations/maths.h"
#include "../../include/vm.h"
#include <stdio.h>

/**
 * @brief Adds two numbers together, allows for the signed numbers.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_add(VM *vm) {
    /** Check for stack underflow */
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful case
    else {
        int b = pop(vm);
        int a = pop(vm);

        push(vm, a + b);
    }
}

/**
 * @brief Subtraction operation, checks for underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_sub(VM *vm) {
    /** Check for stack underflow */
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful case
    else {
        int b = pop(vm);
        int a = pop(vm);

        push(vm, a - b);
    }
}

/**
 * @brief Multiplies two numbers together, both signed and unsigned. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_mult(VM *vm) {
    /** Check for stack underflow */
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful Case
    else {
        int b = pop(vm);
        int a = pop(vm);

        push(vm, a * b);
    }
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

/**
 * @brief Performs the modulo operation.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_mod(VM *vm) {
    // Check for Stack Underflow
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    }

    // Successful Case
    else {
        int b = pop(vm);
        int a = pop(vm);

        push(vm, a % b);
    }
}