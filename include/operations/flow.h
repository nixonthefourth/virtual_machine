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
 * @brief Jump if zero. Pops the top of the stack; if it is zero, sets ip to addr.
 *        Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump_zero(VM *vm);

/**
 * @brief Jump if not zero. Pops the top of the stack; if it is non-zero, sets ip to addr.
 *        Checks for stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_jump_not_zero(VM *vm);

/**
 * @brief Function call. Pushes the return address onto the call stack and
 *        jumps to the target address encoded in the next bytecode word.
 *        Checks for call stack overflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_call(VM *vm);

/**
 * @brief Return from function. Pops the return address from the call stack
 *        and restores ip. Checks for call stack underflow.
 *
 * @param vm The reference to the actual memory of the virtual machine.
 */
void op_ret(VM *vm);

#endif //VIRTUAL_MACHINE_FLOW_H