#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdbool.h>
#include "constants.h"

// Memory blocks' abstract data type
typedef struct {
    int words[WORDS_SIZE];
} MemoryBlock;

// RAM's abstract data type
typedef struct {
    MemoryBlock* blocks;
    int size;
} RAM;

// Line's abstract data type
typedef struct {
    MemoryBlock block;
    int tag; // Address of the block in memory RAM
    bool updated;
    int cost;
    int cacheHit;
    int timesUsed; // Tracks how many times the line has been used
    int timeInCache; // Tracks how long the line has remained unchanged
} Line;

// Cache's abstract data type
typedef struct {
    Line* lines;
    int size;
} Cache;

// Starts cache memory
void startCache(Cache*, int);
void stopCache(Cache*);

// Starts RAM memory
void startRAM(RAM*, int);
void stopRAM(RAM*);

#endif // !MEMORY_H