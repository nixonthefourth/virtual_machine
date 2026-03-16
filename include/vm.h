//
// Created by Mykyta Khomiakov on 16/03/2026.
//

#ifndef VIRTUAL_MACHINE_VM_H
#define VIRTUAL_MACHINE_VM_H

/**
 * @brief Defines the opcodes for the Virtual Machine
 *
 * @details Opcodes are as such: PUSH, POP, ADD, SUB, PRT and HLT.
 */
enum {
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_SUB,
    OP_PRT,
    OP_HLT
};

/**
 * @brief Virtual Machine State
 *
 * @details Contains the runtime data required for executing the bytecode operations
 */
typedef struct {

    /** Stack Memory for arithmetic */
    int stack[256];

    /** General purpose registers */
    int registers[16];

    /** Stack Pointer */
    int sp;

    /** Instruction Pointer */
    int ip;

    /** Execution state flag */
    int running;

    /** Pointer to the program bytecode */
    int *program;
} VM;

/**
 *
 * @brief Pushes a value onto the stack
 *
 * @param vm Reference to the virtual machine stack
 * @param value Value to push onto the referenced stack
 */
void push(VM *vm, int value);

/**
 * @brief Pop the pointer value from the stack
 *
 * @param vm Reference to the virtual machine stack
 * @return Performs the operation and returns the popped value.
 *
 * Think of it as taking the value from the data store first and then putting it into the variable to use later.
 */
int pop(VM *vm);

/**
 * @brief The virtual machine runtime
 *
 * @param vm Reference to the virtual machine stack
 *
 * @details Performs opcode operations, such as PUSH, POP, ADD, SUB, PRT and HLT.
 */
void vm_run(VM *vm);

#endif //VIRTUAL_MACHINE_VM_H