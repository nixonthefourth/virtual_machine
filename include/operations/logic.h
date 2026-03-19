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

#endif //VIRTUAL_MACHINE_LOGIC_H