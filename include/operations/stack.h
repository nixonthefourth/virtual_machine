//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#ifndef VIRTUAL_MACHINE_STACK_H
#define VIRTUAL_MACHINE_STACK_H
#include "vm.h"

/**
 * @brief Pushes the value onto a stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_push(VM *vm);

/**
 * @brief Pop the value from the stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_pop(VM *vm);

/**
 * @brief Simply print the latest result from the stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_print(VM *vm);

/**
 * @brief Halts the virtual machine.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_halt(VM *vm);

/**
 * @brief Duplicate the top of the stack.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_dup(VM *vm);

/**
 * @brief Swap for two.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_swap(VM *vm);

/**
 * @brief Non-destructive read that checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_peek(VM *vm);

#endif //VIRTUAL_MACHINE_STACK_H