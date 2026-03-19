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
    int addr = vm->program[vm->ip++];

    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
        return;
    }

    int top = pop(vm);

    if (top == 0) {
        vm->ip = addr;
    }
}

/**
 * @brief Jump if not zero. Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump_not_zero(VM *vm) {
    int addr = vm->program[vm->ip++];

    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
        return;
    }

    int top = pop(vm);

    if (top != 0) {
        vm->ip = addr;
    }
}

/**
 * @brief Function call. Saves return address on the call stack and jumps to target.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_call(VM *vm) {
    int addr = vm->program[vm->ip++];

    if (vm->csp >= 128) {
        printf("Call stack overflow\n");
        vm->running = 0;
        return;
    }

    /* Save the address of the instruction after CALL */
    vm->call_stack[vm->csp++] = vm->ip;

    vm->ip = addr;
}

/**
 * @brief Return from function. Restores ip from the call stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_ret(VM *vm) {
    if (vm->csp == 0) {
        printf("Call stack underflow\n");
        vm->running = 0;
        return;
    }

    vm->ip = vm->call_stack[--vm->csp];
}