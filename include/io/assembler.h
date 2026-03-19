//
// assembler.h
// Converts a sequence of Token structs into a flat integer program buffer
// ready to hand to vm_run().
//

#ifndef VIRTUAL_MACHINE_ASSEMBLER_H
#define VIRTUAL_MACHINE_ASSEMBLER_H

#include "lexer.h"

/** Maximum number of words (opcodes + operands) in a compiled program. */
#define MAX_PROGRAM_WORDS 1024

/**
 * @brief Assembled program ready for the VM.
 *
 * words[0..length-1] is the flat bytecode array.
 */
typedef struct {
    int words[MAX_PROGRAM_WORDS];
    int length;
} Program;

/**
 * @brief Translate a mnemonic string to its integer opcode.
 *
 * @param mnemonic   Uppercased mnemonic (e.g. "PUSH", "ADD").
 * @return           The opcode integer, or -1 if unrecognised.
 */
int mnemonic_to_opcode(const char *mnemonic);

/**
 * @brief Assemble one token into the program buffer.
 *
 * Appends the opcode word and any operand words to prog->words and
 * advances prog->length.
 *
 * @param prog   Program buffer to append into.
 * @param token  Token produced by lex_line().
 * @return       1 on success, 0 on unknown mnemonic or buffer overflow.
 */
int assemble_token(Program *prog, const Token *token);

#endif // VIRTUAL_MACHINE_ASSEMBLER_H
