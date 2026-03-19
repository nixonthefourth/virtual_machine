//
// lexer.c
//

#include "io/lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Trim a trailing newline or carriage-return in place. */
static void strip_newline(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
}

/** Truncate at the first ';' comment character. */
static void strip_comment(char *s) {
    char *p = strchr(s, ';');
    if (p) *p = '\0';
}

/** Advance *p past any ASCII whitespace. */
static void skip_ws(char **p) {
    while (**p && isspace((unsigned char)**p) ) (*p)++;
}

/** Convert a NUL-terminated string to uppercase in place. */
static void to_upper(char *s) {
    for (; *s; s++) *s = (char)toupper((unsigned char)*s);
}

// Public API

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
int lex_line(char *line, Token *out) {
    strip_newline(line);
    strip_comment(line);

    char *p = line;
    skip_ws(&p);

    /* Empty line after stripping */
    if (*p == '\0') return 0;

    /* ---- mnemonic ---- */
    int mi = 0;
    while (*p && !isspace((unsigned char)*p) && mi < 31) {
        out->mnemonic[mi++] = *p++;
    }
    out->mnemonic[mi] = '\0';
    to_upper(out->mnemonic);

    /* ---- operands ---- */
    out->operand_count = 0;
    while (out->operand_count < MAX_OPERANDS) {
        skip_ws(&p);
        if (*p == '\0') break;

        char *end;
        long val = strtol(p, &end, 0); /* base 0: handles 0x… and decimal */
        if (end == p) break;           /* no valid integer found           */

        out->operands[out->operand_count++] = (int)val;
        p = end;
    }

    return 1;
}
