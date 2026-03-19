//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#ifndef VIRTUAL_MACHINE_LOGIC_H
#define VIRTUAL_MACHINE_LOGIC_H
#include "vm.h"

/**
 * @brief Equality operator.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_eq(VM *vm);

/**
 * @brief Less than operation. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_lt(VM *vm);

/**
 * @brief Greater than operation. Checks for the stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_gt(VM *vm);

/**
 * @brief Logical AND. Pops two values, pushes 1 if both are non-zero, else 0.
 *        Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_and(VM *vm);

/**
 * @brief Logical OR. Pops two values, pushes 1 if either is non-zero, else 0.
 *        Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_or(VM *vm);

/**
 * @brief Logical NOT. Pops one value, pushes 1 if it was zero, else 0.
 *        Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_not(VM *vm);

#endif //VIRTUAL_MACHINE_LOGIC_H