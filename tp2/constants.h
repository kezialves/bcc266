#include <stdbool.h>

#define WORDS_SIZE 4
#define INVALID_ADD -1
#define COST_ACCESS_L1 1
#define COST_ACCESS_L2 10
#define COST_ACCESS_L3 100
#define COST_ACCESS_RAM 1000

#define MAPPING 2
// Set to:
// 1 for direct mapping
// 2 for LRU mapping
// 3 for LFU mapping

// #define PRINT_INTERMEDIATE_RAM
#define PRINT_LOG