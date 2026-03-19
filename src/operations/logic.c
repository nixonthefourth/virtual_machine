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
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    } else {
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
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    } else {
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
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    } else {
        int b = pop(vm);
        int a = pop(vm);
        push(vm, a > b);
    }
}

/**
 * @brief Logical AND. Pops two values, pushes 1 if both are non-zero, else 0.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_and(VM *vm) {
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    } else {
        int b = pop(vm);
        int a = pop(vm);
        push(vm, (a != 0) && (b != 0));
    }
}

/**
 * @brief Logical OR. Pops two values, pushes 1 if either is non-zero, else 0.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_or(VM *vm) {
    if (vm->sp < 2) {
        printf("Stack underflow\n");
        vm->running = 0;
    } else {
        int b = pop(vm);
        int a = pop(vm);
        push(vm, (a != 0) || (b != 0));
    }
}

/**
 * @brief Logical NOT. Pops one value, pushes 1 if it was zero, else 0.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_not(VM *vm) {
    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
    } else {
        int a = pop(vm);
        push(vm, (a == 0) ? 1 : 0);
    }
}