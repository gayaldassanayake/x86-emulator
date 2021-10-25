# x86-emulator
Developing an x86 Processor Instruction Emulator

## Goal
Goal of this programming assignment is to get a first-hand experience about the
nature of real-world complex instruction set computers (CISC) and their instruction decoding
process.

## Task
Write a program (preferably in C/C++) that emulates the instruction decoding of an x86
processor.

## Build

```$ make```

C++ 11 is required.

## Run

```$ ./emulator.out [path to input file]```

eg:- ```$ ./emulator.out sample_inputs/add/add03.in```

## File and Folders

- ```Makefile``` - Scipts to build the program
- ```main.cpp``` - Main driver program
- ```memory.hpp``` - Declarations of the Memory module
- ```memory.cpp``` - Implementation of the memory moduel
- ```register.hpp``` - Declarations of the Register Bank
- ```register.cpp``` - Implementation of the Register Bank
- ```reader.hpp``` - Declarations of the Input Reader module
- ```reader.cpp``` - Implementation of the Input Reader moduel
- ```modmr.hpp``` - Declarations of the ModR/M decode module
- ```modmr.cpp``` - Implementation of the ModR/M docode moduel
- ```sib.hpp``` - Declarations of the SIB decode module
- ```sib.cpp``` - Implementation of the SIB decode moduel
- ```utility_flag_set.hpp``` - Declarations of the utility functions to set flags
- ```utility_flag_set.cpp``` - Implementation of the utility functions to set flags
- ```utility_functions.hpp``` - Declarations of the utility functions
- ```utility_functions.cpp``` - Implementation of the utility functions
- ```util.hpp``` - Declaration of utility data structures
- ```opcode_extension.hpp``` - Declarations of the opcode extension handling functions
- ```opcode_extension.cpp``` - Implementation of the opcode extension handling functions

- ```opcodes/opcodes.hpp``` - Header file include of supported opcodes

- ```opcodes/[ opcode ].hpp``` - Declaration of the decode and excution functions of the respective opcode

- ```opcodes/[ opcode ].cpp``` - Implementaion of the decode and excution functions of the respective opcode

- ```sample_inputs/[ opcode ]/ [ Input File Name ].in``` - Sample inputs

- ```sample_inputs/[ opcode ]/ [ Input File Name ].out.txt``` - Corresponding outputs of the sample inputs

## Resources

- [Intel® 64 and IA-32 Architectures Developer's Manual: Vol. 2](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
## Contributers
- Damika Gamlath
- Gayal Dassanayake
