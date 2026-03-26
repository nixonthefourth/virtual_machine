# C Virtual Machine

A lightweight, stack-based virtual machine written in C (C11), featuring a custom instruction set, an interactive assembler, arithmetic, logic, control flow, registers, and a call stack – all built from scratch.

Please look into `docs/main.pdf` for the paper explaining the reasoning behind this project in more detail.

---

## Table of Contents

- [Why a Stack-Based Architecture?](#why-a-stack-based-architecture)
- [Features](#features)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Interactive Assembler](#interactive-assembler)
- [Instruction Set Reference](#instruction-set-reference)
- [Example Programs](#example-programs)
- [Error Handling](#error-handling)
- [Extending the VM](#extending-the-vm)
- [Roadmap](#roadmap)
- [License](#license)

---

## Why a Stack-Based Architecture?

Most CPUs you interact with every day are register-based: they shuffle values between a fixed set of named registers (like `eax`, `rbx`, etc.) before operating on them. A stack-based VM takes a different approach: operands are implicitly the top values on a stack, and instructions consume and produce values there.

This design was chosen deliberately for several reasons:

**Simplicity of implementation.** There is no register-allocation problem to solve. Every opcode knows exactly where its inputs are (the top of the stack) and where to leave its output (back on the stack). The interpreter loop is a clean `switch` over a flat integer array, hence no complex decode stage needed.

**Simplicity of the instruction encoding.** Because operands are implicit, most instructions are a single word (one integer). Only instructions that need a literal value — `PUSH`, `JMP`, `LD`, `ST`, `CALL` carry an extra word. This keeps bytecode compact and the assembler trivial to write.

**Portability.** The entire VM state is a single `VM` struct holding plain `int` arrays. There are no platform-specific register intrinsics, no inline assembly, and no OS dependencies. The same code compiles and runs identically on Linux, macOS, and Windows thanks to CMake.

**Pedagogical clarity.** Stack machines map directly onto how many high-level language expressions are naturally evaluated (postfix / reverse-Polish notation). The execution model is easy to reason about step-by-step, making this a good platform for learning how interpreters and compilers work.

The trade-off is that stack machines can require more instructions than a register machine to express the same computation (e.g., `DUP` and `SWAP` are needed to reorder operands). For this project, which is a teaching and experimentation, that is an acceptable cost.

---

## Features

- [x] Interactive REPL assembler — type instructions, run instantly
- [x] Stack-based execution model with 256-slot stack
- [x] 25 opcodes across five categories
- [x] Arithmetic: `ADD`, `SUB`, `MULT`, `DIV`, `MOD`
- [x] Logic & comparison: `AND`, `OR`, `NOT`, `EQ`, `LT`, `GT`
- [x] Control flow: `JMP`, `JZ`, `JNZ`, `CALL`, `RET`
- [x] Stack manipulation: `PUSH`, `POP`, `DUP`, `SWAP`, `PEEK`
- [x] 16 general-purpose registers: `LD`, `ST`
- [x] Call stack with 128-frame depth (`CALL` / `RET`)
- [x] Runtime error detection: overflow, underflow, division by zero, invalid register
- [ ] Save/load programs as `.txt` files
- [x] Accompanying LaTeX paper
- [ ] SFML visual interface

---

## Project Structure

```
vm/
├── docs/
│   ├── assets/
│   │   └── directory.png
│   │
│   ├── sections/
│   │   ├── conclusions.tex
│   │   ├── implementation_notes.tex
│   │   ├── instruction_set.tex
│   │   ├── machines.tex
│   │   ├── abstract.tex
│   │   └── project_setup.tex
│   │
│   ├── main.tex
│   └── main.pdf
│
├── src/
│   ├── main.c                 # Interactive REPL entry point
│   ├── vm.c                   # Fetch-decode-execute loop; push/pop primitives
│   ├── io/
│   │   ├── lexer.c            # Tokenises a line of source text
│   │   └── assembler.c        # Translates tokens into bytecode words
│   └── operations/
│       ├── flow.c             # JMP, JZ, JNZ, CALL, RET
│       ├── logic.c            # EQ, LT, GT, AND, OR, NOT
│       ├── maths.c            # ADD, SUB, MULT, DIV, MOD
│       ├── registers.c        # LD, ST
│       └── stack.c            # PUSH, POP, DUP, SWAP, PEEK, PRINT, HALT
│
├── include/
│   ├── vm.h                   # VM struct, opcode enum, push/pop declarations
│   ├── io/
│   │   ├── lexer.h
│   │   └── assembler.h
│   └── operations/
│       ├── flow.h
│       ├── logic.h
│       ├── maths.h
│       ├── registers.h
│       └── stack.h
│
├── README.md
└── .gitignore
```

Each operation category lives in its own translation unit. Adding a new opcode means touching only the relevant file plus a single `case` in `vm.c` – the rest of the codebase is unaffected. This was achieved via a divide and conquer approach, where modules that don't have to know about each other – don't know about each other. This separation of concerns allows for a simplified scalable design.

---

## How It Works

### The Pipeline

Source text typed at the prompt travels through three stages before execution:

```
  Raw text line
       │
       ▼
  ┌─────────┐
  │  Lexer  │  Strip comments, uppercase mnemonic, parse integer operands → Token
  └─────────┘
       │
       ▼
  ┌───────────┐
  │ Assembler │  Look up mnemonic in table, emit opcode word + operand words → Program
  └───────────┘
       │
       ▼
  ┌─────────────────────────────────────────────┐
  │               VM — fetch / decode / execute │
  │                                             │
  │  ┌─────────┐   ┌──────────┐   ┌──────────┐  │
  │  │  FETCH  │──▶│  DECODE  │──▶│ EXECUTE  │  │
  │  │ ip++    │   │ switch() │   │ op_*()   │  │
  │  └─────────┘   └──────────┘   └──────────┘  │
  │        ▲                            │       │
  │        └────────────────────────────┘       │
  │                (loop until HALT)            │
  └─────────────────────────────────────────────┘
```

### VM State

The complete runtime state is a single struct; no globals, no hidden singletons:

```c
typedef struct {
    int  stack[256];      // Operand stack
    int  registers[16];   // General-purpose registers (R0–R15)
    int  sp;              // Stack pointer (index of next free slot)
    int  ip;              // Instruction pointer (index into program[])
    int  running;         // 1 = executing, 0 = halted
    int *program;         // Pointer to the flat bytecode array
    int  call_stack[128]; // Return addresses for CALL/RET
    int  csp;             // Call stack pointer
} VM;
```

### Bytecode Format

Programs are flat integer arrays. Instructions that need a literal argument are followed immediately by that value:

```
Index:  0     1     2     3    4      5     6
        PUSH  10    PUSH  32   ADD    PRINT HALT
```

`ip` starts at 0. After fetching the opcode at `program[ip]`, ip is incremented. Instructions like `PUSH` then read `program[ip++]` again to consume their operand.

---

## Getting Started

### Prerequisites

- GCC or Clang with C11 support (`-std=c11`)
- GNU Make (optional, for a Makefile-based build)

### Build

```bash
# Example — adjust paths to match your layout
gcc -std=c11 -Wall -Wextra -Iinclude \
    src/main.c src/vm.c \
    src/io/lexer.c src/io/assembler.c \
    src/operations/maths.c src/operations/stack.c \
    src/operations/flow.c src/operations/logic.c \
    src/operations/registers.c \
    -o vm
```

### Run

```bash
./vm
```

---

## Interactive Assembler

The program launches an interactive REPL. Type one instruction per line; a blank line (or the `RUN` command) assembles and executes everything entered so far.

```
Virtual Machine — interactive assembler
Type HELP for usage, QUIT to exit.

> PUSH 10
  [@ word 0]
> PUSH 32
  [@ word 2]
> ADD
  [@ word 4]
> PRINT
  [@ word 5]
> HALT
  [@ word 6]
>
--- Running (7 word(s)) ---
42
--- Done ---
```

### Shell Commands

These are interpreted by the REPL and never assembled into the program:

| Command | Effect |
|---------|--------|
| `RUN`   | Assemble and execute the current buffer |
| `LIST`  | Print the assembled word array with indices |
| `RESET` | Clear the program buffer |
| `HELP`  | Show opcode reference |
| `QUIT` / `EXIT` | Exit the program |

Comments begin with `;` and are stripped before assembly.

---

## Instruction Set Reference

### Stack

| Instruction | Stack Effect | Description |
|-------------|-------------|-------------|
| `PUSH n`    | `→ n` | Push the integer literal `n` |
| `POP`       | `a →` | Discard the top value |
| `DUP`       | `a → a a` | Duplicate the top value |
| `SWAP`      | `a b → b a` | Swap the top two values |
| `PEEK`      | `a → a` | Print the top value without consuming it |

### Arithmetic

| Instruction | Stack Effect | Description |
|-------------|-------------|-------------|
| `ADD`  | `a b → (a+b)` | Addition |
| `SUB`  | `a b → (a-b)` | Subtraction |
| `MULT` | `a b → (a*b)` | Multiplication |
| `DIV`  | `a b → (a/b)` | Integer division (halts on ÷0) |
| `MOD`  | `a b → (a%b)` | Remainder |

### Comparison & Logic

| Instruction | Stack Effect | Description |
|-------------|-------------|-------------|
| `EQ`  | `a b → (a==b)` | Push 1 if equal, else 0 |
| `LT`  | `a b → (a<b)`  | Push 1 if a < b, else 0 |
| `GT`  | `a b → (a>b)`  | Push 1 if a > b, else 0 |
| `AND` | `a b → (a&&b)` | Logical AND (non-zero = true) |
| `OR`  | `a b → (a\|\|b)` | Logical OR |
| `NOT` | `a → (!a)`     | Logical NOT |

### Control Flow

| Instruction  | Description |
|--------------|-------------|
| `JMP addr`   | Unconditional jump to word index `addr` |
| `JZ  addr`   | Pop top; jump if it was 0 |
| `JNZ addr`   | Pop top; jump if it was non-zero |
| `CALL addr`  | Push return address onto call stack, jump to `addr` |
| `RET`        | Pop return address from call stack, resume there |

### Registers

16 general-purpose integer registers, addressed 0–15.

| Instruction | Stack Effect | Description |
|-------------|-------------|-------------|
| `ST reg`    | `a →`  | Pop top of stack, store in register `reg` |
| `LD reg`    | `→ a`  | Push the value of register `reg` |

### I/O & Control

| Instruction | Description |
|-------------|-------------|
| `PRINT`     | Pop and print the top value |
| `HALT`      | Stop execution |

---

## Example Programs

### Adding two numbers

```
PUSH 8
PUSH 5
ADD
PRINT
HALT
```
Output: `13`

### Countdown loop

```
PUSH 3      ; starting counter — word index 0
DUP         ; duplicate for PRINT              2
PRINT       ; print current value              3
PUSH 1      ; load decrement amount            4
SUB         ; counter - 1                      6
DUP         ; duplicate for JZ check           7
JZ 10       ; if counter == 0, jump to HALT    8
JMP 2       ; otherwise loop back to DUP       10
HALT        ; word index 12
```
Output: `3`, `2`, `1`

### Storing and loading a register

```
PUSH 42
ST 0        ; store 42 in register 0
PUSH 10     ; do other work...
POP
LD 0        ; reload 42 from register 0
PRINT
HALT
```
Output: `42`

### Function call with CALL / RET

```
CALL 4      ; call the function at word 4; return address = word 2
HALT        ; word 2 — execution resumes here after RET

; --- function body starts at word 4 ---
PUSH 99
PRINT
RET         ; return to caller
```
Output: `99`

---

## Error Handling

The VM detects runtime errors, prints a message, and halts cleanly — it never crashes silently.

| Error | Trigger |
|-------|---------|
| `Stack overflow`       | Pushing to a full stack (>256 items) |
| `Stack underflow`      | Popping from or operating on an empty/insufficient stack |
| `Division by zero`     | `DIV` with 0 as divisor |
| `Invalid register`     | `LD` or `ST` with a register index outside 0–15 |
| `Call stack overflow`  | `CALL` nested more than 128 frames deep |
| `Call stack underflow` | `RET` with no matching `CALL` |

---

## Extending the VM

To add a new opcode, follow these five steps:

1. **Declare the opcode** – add a constant to the `enum` in `include/vm.h`.
2. **Implement the handler** – write `void op_yourname(VM *vm)` in the appropriate file under `src/operations/`, or create a new one.
3. **Declare the handler** – add the prototype to the corresponding header in `include/operations/`.
4. **Register it** – add a `case YOUR_OPCODE: { op_yourname(vm); break; }` to the `switch` in `src/vm.c`.
5. **Expose it to the assembler** – add a `{ "YOURNAME", YOUR_OPCODE, operand_count }` row to `MNEMONIC_TABLE` in `src/io/assembler.c`.

The REPL and assembler will pick it up automatically — no other changes required.

---

## Roadmap

- [ ] Save and load programs as `.txt` files
- [ ] SFML visual interface
- [x] LaTeX paper documenting the architecture

---

## License

This project is open source. Feel free to fork, extend, and experiment!