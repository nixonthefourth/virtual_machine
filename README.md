# C Virtual Machine

A lightweight stack-based virtual machine written in C (C11 standard).

## Project Structure
```
vm/
├── src/
│   ├── main.c
│   └── vm.c
│
├── include/
│   └── vm.h
│
├── README.md
│
└── .gitignore
```

## Getting Started

### Prerequisites
- GCC or Clang with C11 support

### Build
```bash
gcc -std=c11 -Wall -Wextra -o vm main.c vm.c
```

### Run
```bash
./vm
```

## Features

- [ ] Custom instruction set
- [ ] Stack-based execution model
- [ ] Bytecode interpreter