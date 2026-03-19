//
// Created by Mykyta Khomiakov on 19/03/2026.
//

#ifndef VIRTUAL_MACHINE_REGISTERS_H
#define VIRTUAL_MACHINE_REGISTERS_H
#include "vm.h"

/**
 * @brief Store operation. Checks for the register validity and stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_store(VM *vm);

/**
 * @brief Load operation. Checks for the register validity and stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_load(VM *vm);

#endif //VIRTUAL_MACHINE_REGISTERS_H