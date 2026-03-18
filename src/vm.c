//
// Created by Mykyta Khomiakov on 16/03/2026.
//

#include "../include/vm.h"
#include <stdio.h>
#include "../include/operations.h"

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
 * @param vm Reference to the virtual machine stack.
 *
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
 * @brief The virtual machine runtime simulation.
 *
 * @param vm Reference to the virtual machine stack.
 *
 * @details Performs opcode operations, such as PUSH, POP, ADD, SUB, PRT and HLT.
 */
void vm_run(VM *vm)
{
    while (vm->running != 0) {
        /** Fetch */
        int opcode = vm->program[vm->ip++];

        switch (opcode) {
            /** Push the value onto a stack */
            case PUSH: { op_push(vm); break; }

            /** Pop the value from the stack */
            case POP: { op_pop(vm); break; }

            /** Add two values together and pop them from the stack. Checks for underflow. */
            case ADD: { op_add(vm); break; }

            /** Substitute two values (could be signed integers) and remove them form the stack.
             * Checks for underflow */
            case SUB: { op_sub(vm); break; }

            /** Print operation that prints the result and pop the value from the stack */
            case PRINT: { op_print(vm); break; }

            /** Stops the Virtual Machine */
            case HALT: { op_halt(vm); break; }

            /** Multiplication. Checks for underflow. */
            case MULT: { op_mult(vm); break; }

            /** Division */
            case DIV: { op_div(vm); break; }

            /** Modulo */
            case MOD: { op_mod(vm); break; }

            /** Jump */
            case JMP: { op_jump(vm); break; }

            /** Jump if Zero */
            case JZ: { op_jump_zero(vm); break; }

            /** Duplicate the top of the stack */
            case DUP: { op_dup(vm); break; }

            /** Swap */
            case SWAP: { op_swap(vm); break; }

            /** Equality Operator */
            case EQ: { op_eq(vm); break; }

            /** Less Than Operator */
            case LT: { op_lt(vm); break; }

            /** Greater Than Operator */
            case GT: { op_gt(vm); break; }

            /** Load */
            case LD: { op_load(vm); break; }

            /** Store */
            case ST: { op_store(vm); break; }

            /** Peek */
            case PEEK: { op_peek(vm); break; }
        }
    }
}