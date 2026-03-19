//
// assembler.c
//

#include "io/assembler.h"
#include "vm.h"

#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
    int         opcode;
    int         operand_count; /* words that follow the opcode in bytecode */
} MnemonicEntry;

static const MnemonicEntry MNEMONIC_TABLE[] = {
    /* Stack */
    { "PUSH",  PUSH,  1 },
    { "POP",   POP,   0 },
    { "DUP",   DUP,   0 },
    { "SWAP",  SWAP,  0 },
    { "PEEK",  PEEK,  0 },
    /* Arithmetic */
    { "ADD",   ADD,   0 },
    { "SUB",   SUB,   0 },
    { "MULT",  MULT,  0 },
    { "DIV",   DIV,   0 },
    { "MOD",   MOD,   0 },
    /* Logic */
    { "EQ",    EQ,    0 },
    { "LT",    LT,    0 },
    { "GT",    GT,    0 },
    { "AND",   AND,   0 },
    { "OR",    OR,    0 },
    { "NOT",   NOT,   0 },
    /* I/O */
    { "PRINT", PRINT, 0 },
    /* Control flow */
    { "JMP",   JMP,   1 },
    { "JZ",    JZ,    1 },
    { "JNZ",   JNZ,   1 },
    { "CALL",  CALL,  1 },
    { "RET",   RET,   0 },
    /* Registers */
    { "LD",    LD,    1 },
    { "ST",    ST,    1 },
    /* Termination */
    { "HALT",  HALT,  0 },
};

#define TABLE_SIZE ((int)(sizeof(MNEMONIC_TABLE) / sizeof(MNEMONIC_TABLE[0])))

// Public API

/**
 * @brief Translate a mnemonic string to its integer opcode.
 *
 * @param mnemonic   Uppercased mnemonic (e.g. "PUSH", "ADD").
 * @return           The opcode integer, or -1 if unrecognised.
 */
int mnemonic_to_opcode(const char *mnemonic) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(MNEMONIC_TABLE[i].name, mnemonic) == 0) {
            return MNEMONIC_TABLE[i].opcode;
        }
    }
    return -1;
}

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
int assemble_token(Program *prog, const Token *token) {
    /* Look up mnemonic */
    const MnemonicEntry *entry = NULL;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(MNEMONIC_TABLE[i].name, token->mnemonic) == 0) {
            entry = &MNEMONIC_TABLE[i];
            break;
        }
    }

    if (!entry) {
        fprintf(stderr, "Error: unknown mnemonic '%s'\n", token->mnemonic);
        return 0;
    }

    /* Warn if the user supplied a different number of operands than expected */
    if (token->operand_count != entry->operand_count) {
        fprintf(stderr,
                "Warning: '%s' expects %d operand(s), got %d\n",
                entry->name, entry->operand_count, token->operand_count);
    }

    /* Check buffer capacity: 1 opcode word + operand words */
    int words_needed = 1 + entry->operand_count;
    if (prog->length + words_needed > MAX_PROGRAM_WORDS) {
        fprintf(stderr, "Error: program buffer overflow\n");
        return 0;
    }

    /* Emit opcode */
    prog->words[prog->length++] = entry->opcode;

    /* Emit operands from the token */
    for (int i = 0; i < entry->operand_count; i++) {
        int operand = (i < token->operand_count) ? token->operands[i] : 0;
        prog->words[prog->length++] = operand;
    }

    return 1;
}
