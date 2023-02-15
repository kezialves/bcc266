#ifndef MMU_H
#define MMU_H

#include "memory.h"
#include "instruction.h"
#include "cpu.h"

// Search info on memory
Line* MMUSearchOnMemorys(Address, Machine*); // Order of complexity: O(n);

#endif // !MMU_H