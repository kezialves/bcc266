#ifndef CPU_H
#define CPU_H

#include "instruction.h"
#include "memory.h"

// Machine's abstract data type
typedef struct {
    Instruction* instructions;
    RAM ram;
    Cache l1; // cache L1
    Cache l2; // cache L2
    Cache l3; // cache L3
    int hitL1, hitL2, hitL3, hitRAM;
    int missL1, missL2, missL3;
    int totalCost;
} Machine;

// Starts the machine
void start(Machine*, Instruction*, int*);

// Stops the machine
void stop(Machine*);

// Runs the machine
void run(Machine*);

// Prints the memories
void printMemories(Machine*);

#endif // !CPU_H