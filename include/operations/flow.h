//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#ifndef VIRTUAL_MACHINE_FLOW_H
#define VIRTUAL_MACHINE_FLOW_H

#include "vm.h"

/**
 * @brief Performs an unconditional jump.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump(VM *vm);

/**
 * @brief Jump if zero. Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump_zero(VM *vm);

#endif //VIRTUAL_MACHINE_FLOW_H