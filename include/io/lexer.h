//
// lexer.h
// Splits a single line of source text into a mnemonic token and
// up to MAX_OPERANDS integer operands.
//

#ifndef VIRTUAL_MACHINE_LEXER_H
#define VIRTUAL_MACHINE_LEXER_H

/** Maximum number of operands a single instruction can carry. */
#define MAX_OPERANDS 2

/**
 * @brief Represents one tokenised instruction line.
 *
 * After a successful lex_line() call:
 *   - mnemonic  holds the uppercased opcode name  (e.g. "PUSH", "ADD")
 *   - operands  holds up to MAX_OPERANDS integer values
 *   - operand_count is the number of operands actually parsed
 */
typedef struct {
    char mnemonic[32];
    int  operands[MAX_OPERANDS];
    int  operand_count;
} Token;

/**
 * @brief Tokenise one source line into a Token.
 *
 * The function:
 *   1. Strips leading/trailing whitespace and inline comments (';' … EOL).
 *   2. Uppercases the first word and stores it as the mnemonic.
 *   3. Parses up to MAX_OPERANDS integer operands (decimal or 0x hex).
 *
 * @param line   NUL-terminated input string (modified in place).
 * @param out    Pointer to the Token to populate.
 * @return       1 on success, 0 if the line is empty or comment-only.
 */
int lex_line(char *line, Token *out);

#endif // VIRTUAL_MACHINE_LEXER_H
