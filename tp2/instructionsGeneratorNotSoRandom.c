//Gerador de instruções feito por Luísa Calegari, Thiago Cecote e Josué Vila Real
// Slightly modified
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_INST 10000 // Number of instructions
#define N_FOR 5     // Number of instructions to be repeated
#define N_MEM 1000  // Number of the memory for the block adress
#define N_PROB 50   // Repetition probability
#define N_OPCODE 3  // Max number of opcodes
#define N_WORD 4    // Number of words in block

void instGenerator(char*);

int main(int argc, char**argv) {

    if(argc != 2) {
        printf("Número de argumentos inválido! São 2.\n");
        printf("Linha de execução: ./exe \"path/nome arquivo.in\"\n");
        printf("\tExemplo de execução: ./exe instrucao.in\n");
        return 0;
    }

    instGenerator(argv[1]);
    return 0;
}

void instGenerator(char* fileName) {

    int rep[5][7];
    int inst[10000][7];
    FILE *arquivo = fopen(fileName, "w");
    int random;
    int instruc[8] = {6, 6, 6, 6, 6, 6, 6, 6};

    srand(time(NULL));

    for(int i = 0; i < N_FOR; i++) {

        random = rand() % N_OPCODE;
        rep[i][0] = random;

        for(int j = 1; j <= (instruc[random]); j += 2) {
            rep[i][j] = rand() % N_MEM;
            rep[i][j + 1] = rand() % N_WORD;
        }
    }

    for(int i = 0; i < N_INST;) {

        random = (rand() % 100) + 1;
        
        if(random <= N_PROB && i + N_FOR < N_INST) {
            for(int j = 0; j < N_FOR; j++) {
                for(int k = 0; k < 7; k++) {
                    inst[i + j][k] = rep[j][k];
                }
            }

            i += N_FOR;
        }
        
        else {
            random = rand() % N_OPCODE;
            inst[i][0] = random;

            for(int j = 1; j <= instruc[random]; j += 2) {
                inst[i][j] = rand() % N_MEM;
                inst[i][j + 1] = rand() % N_WORD;
            }

            i++;
        }
    }

    fprintf(arquivo, "%d %d\n", N_INST, N_MEM);
    
    for(int i = 0; i < N_INST - 1; i++) {
        for(int k = 0; k < 6; k++) {
            fprintf(arquivo, "%d ", inst[i][k]);
        }
        
        fprintf(arquivo, "%d\n", inst[i][6]);
    }

    fprintf(arquivo, "-1 -1 -1 -1 -1 -1 -1");

    fclose(arquivo);
}