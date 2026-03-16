//
// Created by Mykyta Khomiakov on 16/03/2026.
//

#include "../include/vm.h"
#include <stdio.h>

/**
 *
 * @brief Pushes a value onto the stack
 *
 * @param vm Reference to the virtual machine stack
 * @param value Value to push onto the referenced stack
 */
void push(VM *vm, int value) {
    vm->stack[vm->sp++] = value;
}

/**
 * @brief Pop the pointer value from the stack
 *
 * @param vm Reference to the virtual machine stack
 * @return Performs the operation and returns the popped value.
 *
 * Think of it as taking the value from the data store first and then putting it into the variable to use later.
 */
int pop(VM *vm) {
    return vm->stack[--vm->sp];
}

/**
 * @brief The virtual machine runtime
 *
 * @param vm Reference to the virtual machine stack
 *
 * @details Performs opcode operations, such as PUSH, POP, ADD, SUB, PRT and HLT.
 */
void vm_run(VM *vm)
{
    while (vm->running) {
        /** Fetch */
        int opcode = vm->program[vm->ip++];

        switch (opcode) {
            /** Push the value onto a stack */
            case OP_PUSH:
                push(vm, vm->program[vm->ip++]);
                break;

            /** Pop the value from the stack */
            case OP_POP:
                pop(vm);
                break;

            /** Add two values together and pop them from the stack */
            case OP_ADD: {
                int b = pop(vm);
                int a = pop(vm);

                push(vm, a + b);
                break;
            }

            /** Substitute two values (could be signed integers) and remove them form the stack.
             * Checks for underflow */
            case OP_SUB: {
                if (vm->sp < 2) {
                    printf("Stack underflow\n");
                    vm->running = 0;
                    break;
                }

                else {
                    int b = pop(vm);
                    int a = pop(vm);

                    push(vm, a - b);
                    break;
                }
            }

            /** Print operation that prints the result and pop the value from the stack */
            case OP_PRT:
                printf("%d\n", pop(vm));
                break;

            /** Stops the Virtual Machine */
            case OP_HLT:
                vm->running = 0;
                break;
        }
    }
}