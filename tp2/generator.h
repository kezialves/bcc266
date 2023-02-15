#ifndef GENERATOR_H
#define GENERATOR_H

#include "cpu.h"

// Generates random instructions for the machine
Instruction* generateRandomInstructions(int);

// Reads instructions from a input file
Instruction* readInstructions(char*, int*);

#endif // !GENERATOR_H