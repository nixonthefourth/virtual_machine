# C Virtual Machine

A lightweight, stack-based virtual machine written in C (C11 standard), featuring a custom instruction set, arithmetic operations, control flow, and stack manipulation.

---

## Project Structure

```
vm/
├── src/
│   ├── main.c          # Entry point & example program
│   ├── vm.c            # Core VM runtime (push, pop, vm_run)
│   └── operations.c    # Opcode implementations
│
├── include/
│   ├── vm.h            # VM struct, opcodes, core function declarations
│   └── operations.h    # Operation function declarations
│
├── README.md
└── .gitignore
```

---

## How It Works

The VM is a classic **fetch-decode-execute** loop operating on an integer array as bytecode.

```
┌─────────────┐     ┌──────────────┐     ┌─────────────────┐
│  FETCH      │ ──▶ │  DECODE      │ ──▶ │  EXECUTE        │
│  Read next  │     │  Match to    │     │  Run opcode     │
│  opcode     │     │  opcode enum │     │  handler        │
└─────────────┘     └──────────────┘     └─────────────────┘
        ▲                                        │
        └────────────────────────────────────────┘
                      (loop until HALT)
```

The VM state is held in a single `VM` struct:

```c
typedef struct {
    int stack[256];     // Stack memory
    int registers[16];  // General purpose registers
    int sp;             // Stack pointer
    int ip;             // Instruction pointer
    int running;        // Execution state flag
    int *program;       // Pointer to bytecode
} VM;
```

---

## Instruction Set

| Opcode   | Description                                                 | Stack Effect      |
|----------|-------------------------------------------------------------|-------------------|
| `PUSH n` | Push value `n` onto the stack                               | `→ [n]`           |
| `POP`    | Discard the top value                                       | `[a] →`           |
| `ADD`    | Add top two values                                          | `[a, b] → [a+b]`  |
| `SUB`    | Subtract top two values                                     | `[a, b] → [a-b]`  |
| `MULT`   | Multiply top two values                                     | `[a, b] → [a*b]`  |
| `DIV`    | Divide top two values (checks ÷0)                           | `[a, b] → [a/b]`  |
| `MOD`    | Modulo of top two values                                    | `[a, b] → [a%b]`  |
| `PRINT`  | Print and pop top value                                     | `[a] →`           |
| `HALT`   | Stop execution                                              | —                 |
| `JMP n`  | Unconditional jump to address `n`                           | —                 |
| `JZ n`   | Jump to `n` if top of stack is zero                         | `[a] →`           |
| `DUP`    | Duplicate top of stack                                      | `[a] → [a, a]`    |
| `SWAP`   | Swap top two values                                         | `[a, b] → [b, a]` |
| `EQ`     | Push `1` if equal, else `0`                                 | `[a, b] → [a==b]` |
| `LT`     | Push `1` if `a < b`, else `0`                               | `[a, b] → [a<b]`  |
| `GT`     | Push `1` if `a > b`, else `0`                               | `[a, b] → [a>b]`  |
| `ST`     | Store value from the stack into the next availible register.| `[a] →`           |
| `LD`     | Load value from the register to the stack.                  | `→ [a]`           |

---

## Getting Started

### Prerequisites

- GCC or Clang with C11 support

### Build

```bash
gcc -std=c11 -Wall -Wextra -o vm src/main.c src/vm.c src/operations.c -Iinclude
```

### Run

```bash
./vm
```

---

## Writing Programs

For now, the programs are just integer arrays. Here's the example from `main.c` — computing `8 + 5` and printing the result:

```c
int program[] = {
    PUSH, 8,
    PUSH, 5,
    ADD,
    PRINT,
    HALT
};

VM vm = {0};
vm.program = program;
vm.running = 1;
vm_run(&vm);
// Output: 13
```

### More Examples

**Countdown loop using `JZ` and `DUP`:**
```c
int program[] = {
    PUSH, 3,   // Start counter at 3
    DUP,       // Duplicate top for PRINT (preserves counter)
    PRINT,     // Print current value
    PUSH, 1,
    SUB,       // Decrement counter
    DUP,       // Duplicate for JZ check
    JZ, 10,    // If counter == 0, jump to HALT (index 10)
    JMP, 1,    // Otherwise loop back to DUP at index 1
    HALT       // index 10
};
```

**Comparing two values:**
```c
int program[] = {
    PUSH, 10,
    PUSH, 20,
    LT,        // Is 10 < 20?
    PRINT,     // Prints 1 (true)
    HALT
};
```

---

## Error Handling

The VM handles runtime errors gracefully by printing a message and halting:

| Error              | Trigger Condition                         |
|--------------------|-------------------------------------------|
| `Stack overflow`   | Pushing to a full stack (>256 items)      |
| `Stack underflow`  | Popping from / operating on an empty stack|
| `Division by zero` | `DIV` with `0` as divisor                 |

---

## Extending the VM

To add a new opcode:

1. **Declare it** in the `enum` in `include/vm.h`
2. **Implement it** as `op_yourname(VM *vm)` in `src/operations.c`
3. **Declare it** in `include/operations.h`
4. **Register it** with a `case` in the `switch` inside `vm_run()` in `src/vm.c`

---

## Features

- [x] Custom instruction set (16 opcodes)
- [x] Stack-based execution model
- [x] Bytecode interpreter
- [x] Arithmetic: `ADD`, `SUB`, `MULT`, `DIV`, `MOD`
- [x] Control flow: `JMP`, `JZ`
- [x] Stack manipulation: `DUP`, `SWAP`, `POP`
- [x] Comparison operators: `EQ`, `LT`, `GT`
- [x] Runtime error detection (overflow, underflow, division by zero)
- [x] Local variable support via registers: `LD`, `ST`
- [ ] Function calls / call stack
- [ ] Test programs at launch
- [ ] Console I/O to both code and output the program
- [ ] SFML interface
- [ ] Storing files as .txt
- [ ] LaTeX paper
---

## License

This project is open source. Feel free to fork, extend, and experiment!