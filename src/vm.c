//
// Created by Mykyta Khomiakov on 16/03/2026.
//

#include "../include/vm.h"
#include <stdio.h>

/**
 *
 * @brief Pushes a value onto the stack
 *
 * @details Checks for stack overflow first, otherwise stops the program.
 *
 * If no stack overflow found, value is pushed onto a stack.
 *
 * @param vm Reference to the virtual machine stack
 * @param value Value to push onto the referenced stack
 */
void push(VM *vm, int value) {
    if (vm->sp >= 256) {
        printf("Stack overflow\n");
        vm->running = 0;
        return;
    }

    vm->stack[vm->sp++] = value;
}

/**
 * @brief Pop the pointer value from the stack
 *
 * Runs a check on stuck underflow, so operations would perform if and only if there's something in the stack.
 *
 * @param vm Reference to the virtual machine stack
 * @return Performs the operation and returns the popped value.
 *
 * Think of it as taking the value from the data store first and then putting it into the variable to use later.
 */
int pop(VM *vm) {
    if (vm->sp == 0) {
        printf("Stack underflow\n");
        vm->running = 0;
        return 0;
    }

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

            /** Add two values together and pop them from the stack. Checks for underflow. */
            case OP_ADD: {
                if (vm->sp < 2) {
                    printf("Stack underflow\n");
                    vm->running = 0;
                    break;
                }

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
            case OP_PRINT:
                printf("%d\n", pop(vm));
                break;

            /** Stops the Virtual Machine */
            case OP_HALT:
                vm->running = 0;
                break;

            /** Multiplication. Checks for underflow. */
            case OP_MULT: {
                if (vm->sp < 2) {
                    printf("Stack underflow\n");
                    vm->running = 0;
                    break;
                }

                int b = pop(vm);
                int a = pop(vm);

                push(vm, a * b);
                break;
            }

            /** Division */
            case OP_DIV: {
                // Check for Stack Underflow
                if (vm->sp < 2) {
                    printf("Stack underflow\n");
                    vm->running = 0;
                    break;
                }

                // Initially take value of `b`
                int b = pop(vm);

                // Check whether it is equal to zero
                // If that's the case – interrupt operation
                if (b == 0) {
                    printf("Division by zero, error\n");
                    vm->running = 0;
                    break;
                }

                // Otherwise, we are good to go
                int a = pop(vm);

                push(vm, a / b);
                break;
            }
        }
    }
}