# Compiler Driver Design

## Background
Compiler driver is a software component that calls the preprocessor, compiler, assembler, and linker.

For this project, we will still use those components from gcc(or clang) to build an executable, but replace the compiler to Tompiler

## Requirements
The compiler driver convert the source file to an executable in 3 steps: 

- Preprocess: Produced preprocessed file. Use `-P` flag to to not emit linemarkers

- Compile: Compile preprocessed source file and output assembly file. Delete preprocessed file when done.

- Assemble & Link: Assemble and link the assembly file to produce an executable. Delete the assembly file when

The compiler driver accepts a path to a C source file as its only argument. If this command succeeds, it must produce an executable in the same directory as the input file, with the same name (minus the file extension)

The compiler driver should support the following options:
- `--lex`: Directs it to run the lexer, but stop before parsing
- `--parse`: Directs it to run the lexer and parser, but stop before assem-
bly generation
- `--codegen`: Directs it to perform lexing, parsing, and assembly genera-
tion, but stop before code emission
- `-S`: Directs it to produce an assembly file, but not assembly or link it
- `-h`: Print help menu

Possible commands:

```shell
./tpl -h
./tpl /path/to/file/prog.c
./tpl -S /path/to/file/prog.c
./tpl --lex /path/to/file/prog.c 
./tpl --parse /path/to/file/prog.c 
./tpl --codegen /path/to/file/prog.c 
```
