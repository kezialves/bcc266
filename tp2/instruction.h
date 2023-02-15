#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Adress' abstract data type
typedef struct {
    int block;
    int word;
} Address;

// Instruction's abstract data type
typedef struct {
    Address add1;
    Address add2;
    Address add3;
    int opcode;
} Instruction;

// Gets and sets adress 1
Address getAdd1(Instruction* instruction);
void setAdd1(Instruction* instruction, Address add);

// Gets and sets adress 2
Address getAdd2(Instruction* instruction);
void setAdd2(Instruction* instruction, Address add);

// Gets and sets adress 3
Address getAdd3(Instruction* instruction);
void setAdd3(Instruction* instruction, Address add);

// Gets and sets opcode
int getOpcode(Instruction* instruction);
void setOpcode(Instruction* instruction, int opcode);

#endif // !INSTRUCTION_H