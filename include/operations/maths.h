//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#ifndef VIRTUAL_MACHINE_MATHS_H
#define VIRTUAL_MACHINE_MATHS_H

#include "../../include/vm.h"

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

#endif //VIRTUAL_MACHINE_MATHS_H