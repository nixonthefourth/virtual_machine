//
// main.c
// Interactive terminal assembler + VM runner.
//
// Usage:
//   Type one instruction per line.
//   A blank line or "RUN" executes the program.
//   "RESET" clears the buffer so you can start over.
//   "LIST"  shows the instructions entered so far (with word indices).
//   "HELP"  prints a quick opcode reference.
//   "QUIT"  exits.
//
// Lines starting with ';' are treated as comments and ignored.
//
// Example session:
//   > PUSH 10
//   > PUSH 32
//   > ADD
//   > PRINT
//   > HALT
//   >           <- blank line triggers execution
//   42
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "vm.h"
#include "io/lexer.h"
#include "io/assembler.h"

#define LINE_BUF_SIZE 256

/**
 * @brief Helper Text
 */
static void print_help(void) {
    printf(
        "\n"
        "  Opcodes (case-insensitive):\n"
        "\n"
        "  Stack        PUSH <n>   POP   DUP   SWAP   PEEK\n"
        "  Arithmetic   ADD   SUB   MULT   DIV   MOD\n"
        "  Comparison   EQ    LT    GT\n"
        "  Logic        AND   OR    NOT\n"
        "  I/O          PRINT\n"
        "  Flow         JMP <addr>   JZ <addr>   JNZ <addr>\n"
        "               CALL <addr>  RET\n"
        "  Registers    LD <reg>   ST <reg>    (registers 0-15)\n"
        "  Control      HALT\n"
        "\n"
        "  Shell commands (not assembled into the program):\n"
        "    RUN    -- assemble and run what you have typed so far\n"
        "    LIST   -- show entered instructions with word indices\n"
        "    RESET  -- clear the current program buffer\n"
        "    HELP   -- this message\n"
        "    QUIT   -- exit\n"
        "\n"
        "  A blank line also triggers RUN.\n"
        "  Comments start with ';' and are stripped before assembly.\n"
        "\n"
    );
}

/**
 * @brief Pretty Print
 *
 * @param prog Reference to the program to run.
 */
static void list_program(const Program *prog) {
    if (prog->length == 0) {
        printf("  (empty)\n");
        return;
    }
    printf("  Index  Word\n");
    printf("  -----  ----\n");
    for (int i = 0; i < prog->length; i++) {
        printf("  %5d  %d\n", i, prog->words[i]);
    }
}


/**
 * @brief Trim leading whitespace – returns pointer into the same buffer.
 *
 * @param s Reference to the character
 * @return Returns the pointer into the same buffer
 */
static char *ltrim(char *s) {
    while (*s && isspace((unsigned char)*s)) s++;
    return s;
}

/**
* @brief Extract the first word from src into dest (uppercased, NUL-terminated).
 * dest must be at least max_len bytes.
 *
 * @param src Character
 * @param dest Destination
 * @param max_len Maximum length of bytes
 */
static void first_word_upper(const char *src, char *dest, int max_len) {
    int i = 0;
    while (*src && !isspace((unsigned char)*src) && i < max_len - 1) {
        dest[i++] = (char)toupper((unsigned char)*src++);
    }
    dest[i] = '\0';
}

int main(void) {
    printf("Virtual Machine — interactive assembler\n");
    printf("Type HELP for usage, QUIT to exit.\n\n");

    Program prog = { .length = 0 };
    char line[LINE_BUF_SIZE];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            /* EOF (Ctrl-D / Ctrl-Z) */
            printf("\n");
            break;
        }

        char *trimmed = ltrim(line);

        /* ---- Blank line – run ---------------------------------------- */
        if (trimmed[0] == '\n' || trimmed[0] == '\r' || trimmed[0] == '\0') {
            goto do_run;
        }

        /* ---- Shell command check -------------------------------------- */
        {
            char cmd[16];
            first_word_upper(trimmed, cmd, (int)sizeof(cmd));

            if (strcmp(cmd, "QUIT") == 0 || strcmp(cmd, "EXIT") == 0) {
                printf("Goodbye.\n");
                break;
            }
            if (strcmp(cmd, "HELP") == 0) {
                print_help();
                continue;
            }
            if (strcmp(cmd, "RESET") == 0) {
                prog.length = 0;
                printf("  Program buffer cleared.\n");
                continue;
            }
            if (strcmp(cmd, "LIST") == 0) {
                list_program(&prog);
                continue;
            }
            if (strcmp(cmd, "RUN") == 0) {
                goto do_run;
            }
        }

        /* ---- Assemble instruction line -------------------------------- */
        {
            Token token;
            if (!lex_line(line, &token)) {
                /* Empty or comment-only — skip silently */
                continue;
            }

            /* Record the index of the opcode word about to be appended */
            int opcode_index = prog.length;

            if (!assemble_token(&prog, &token)) {
                /* assemble_token already printed the error */
                continue;
            }

            printf("  [@ word %d]\n", opcode_index);
        }
        continue;

        /* ---- Execute -------------------------------------------------- */
    do_run:
        if (prog.length == 0) {
            printf("  Nothing to run. Enter some instructions first.\n");
            continue;
        }

        printf("--- Running (%d word(s)) ---\n", prog.length);

        VM vm = {0};
        vm.program = prog.words;
        vm.running = 1;
        vm_run(&vm);

        printf("--- Done ---\n");

        /* Auto-reset so the user can type a fresh program immediately */
        prog.length = 0;
    }

    return 0;
}