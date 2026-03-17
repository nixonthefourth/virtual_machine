//
// Created by Mykyta Khomiakov on 17/03/2026.
//

#ifndef VIRTUAL_MACHINE_OPERATIONS_H
#define VIRTUAL_MACHINE_OPERATIONS_H
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
 * @brief Adds two numbers together, allows for the signed numbers.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_add(VM *vm);

/**
 * @brief Subtraction operation, checks for underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_sub(VM *vm);

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
 * @brief Multiplies two numbers together, both signed and unsigned. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_mult(VM *vm);

/**
 * @brief Division operation. Allows for both signed and unsigned numbers.
 * Checks for stack underflow and division by zero.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_div(VM *vm);

/**
 * @brief Performs the modulo operation.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_mod(VM *vm);

/**
 * @brief Performs an unconditional jump.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jmp(VM *vm);

/**
 * @brief Jump if zero. Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump_zero(VM *vm);

#endif //VIRTUAL_MACHINE_OPERATIONS_H