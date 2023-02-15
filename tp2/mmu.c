#include "mmu.h"
#include "constants.h"
#include <stdio.h>

bool canOnlyReplaceBlock(Line line) {

    // Or the block is empty
    // or the block is equal to the one in memory RAM and can be replaced
    if(line.tag == INVALID_ADD || (line.tag != INVALID_ADD && !line.updated))
        return true;
    return false;
}

int memoryCacheMapping(int address, Cache* cache) {

    switch(MAPPING) {

        // Direct mapping
        case 1:
            return address % cache->size;
            break;

        // Least recently used
        case 2:

            int leastRecentlyUsed = 0;

            for(int i = 1; i < cache->size; i++) {
                if(cache->lines[i].timeInCache > cache->lines[leastRecentlyUsed].timeInCache) {
                    leastRecentlyUsed = i;
                }
            }

            return leastRecentlyUsed;
            break;

        // Least frequently used
        case 3:
            
            int leastFrequentlyUsed = 0;

            for(int i = 1; i < cache->size; i++) {
                if(cache->lines[i].timesUsed < cache->lines[leastFrequentlyUsed].timesUsed) {
                    leastFrequentlyUsed = i;
                }
            }

            return leastFrequentlyUsed;
            break;
    }
}

void updateMachineInfos(Machine* machine, Line* line) {

    switch(line->cacheHit) {

        case 1:
            machine->hitL1 += 1;
            break;

        case 2:
            machine->hitL2 += 1;
            machine->missL1 += 1;
            break;
        
        case 3:
            machine->hitL3 += 1;
            machine->missL1 += 1;
            machine->missL2 += 1;
            break;

        case 4:
            machine->hitRAM += 1;
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->missL3 += 1;
            break;
    }
    
    line->timeInCache = 0;
    line->timesUsed += 1;
    machine->totalCost += line->cost;
}

Line* MMUSearchOnMemorys(Address add, Machine* machine) {

    // Strategy => write back
    
    // Memory map
    int l1pos = memoryCacheMapping(add.block, &machine->l1);
    int l2pos = memoryCacheMapping(add.block, &machine->l2);    
    int l3pos = memoryCacheMapping(add.block, &machine->l3);

    Line* cache1 = machine->l1.lines;
    Line* cache2 = machine->l2.lines;
    Line* cache3 = machine->l3.lines;
    MemoryBlock* RAM = machine->ram.blocks;

    for(int i = 0; i < machine->l1.size; i++) {
        machine->l1.lines[i].timeInCache += 1;
    }

    for(int i = 0; i < machine->l2.size; i++) {
        machine->l2.lines[i].timeInCache += 1;
    }

    for(int i = 0; i < machine->l3.size; i++) {
        machine->l3.lines[i].timeInCache += 1;
    }

    // Block is in memory cache L1
    if(cache1[l1pos].tag == add.block) {

        cache1[l1pos].cost = COST_ACCESS_L1;
        cache1[l1pos].cacheHit = 1;
    }
    
    // Block is in memory cache L2
    else if(cache2[l2pos].tag == add.block) {

        cache2[l2pos].tag = add.block;
        cache2[l2pos].updated = false;
        cache2[l2pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2;
        cache2[l2pos].cacheHit = 2;

        // !Can be improved?
        updateMachineInfos(machine, &(cache2[l2pos]));
        return &(cache2[l2pos]);
    }
    
    // Block is in memory cache L3
    else if(cache3[l3pos].tag == add.block) {

        cache3[l3pos].tag = add.block;
        cache3[l3pos].updated = false;
        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3;
        cache3[l3pos].cacheHit = 3;

        // !Can be improved?
        updateMachineInfos(machine, &(cache3[l3pos]));
        return &(cache3[l3pos]);
    }
    
    // Block only in memory RAM, need to bring it to cache and manipulate the blocks
    else { 
        l3pos = memoryCacheMapping(cache2[l2pos].tag, &machine->l3);
        l2pos = memoryCacheMapping(cache1[l1pos].tag, &machine->l2); // Need to check the position of the block that will leave the L1
        
        if(!canOnlyReplaceBlock(cache1[l1pos])) { // The block on cache L1 cannot only be replaced, the memories must be updated
            if (!canOnlyReplaceBlock(cache2[l2pos])) {// The block on cache L2 cannot only be replaced, the memories must be updated
                if (!canOnlyReplaceBlock(cache3[l3pos])) { // The block on cache L3 cannot only be replaced, the memories must be updated
                    RAM[cache3[l3pos].tag] = cache3[l3pos].block;
                }
                cache3[l3pos] = cache2[l2pos];
                machine->l3.lines[l3pos].timeInCache = 0;
            }
            cache2[l2pos] = cache1[l1pos];
            machine->l2.lines[l2pos].timeInCache = 0;
        }
        cache1[l1pos].block = RAM[add.block];
        machine->l1.lines[l1pos].timeInCache = 0;
        cache1[l1pos].tag = add.block;
        cache1[l1pos].updated = false;
        cache1[l1pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM;
        cache1[l1pos].cacheHit = 4;
    }

    updateMachineInfos(machine, &(cache1[l1pos]));
    return &(cache1[l1pos]);
}