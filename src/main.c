#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "cpu.h"
#include "memory.h"

int main(int argc, char** argv) {

    if(argc < 2) {
        printf("Provide the binary file to execute as an argument\n");
        return 0;
    }

    FILE* ProgBin = fopen(argv[1], "rb");
    if(!ProgBin) {
        printf("Error opening provided file\n");
        return -1;
    }

    fread(memory, sizeof(uint8_t), sizeof(memory) / sizeof(uint8_t), ProgBin);

    fclose(ProgBin);
    
    CPU* cpu = setupCPU();

    /*
    memory[0] = 0xA2; // LDX
    memory[1] = (uint8_t)5; // Number
    memory[2] = 0xA0; // LDY
    memory[3] = (uint8_t)0; // Number
    memory[4] = 0xE8; // INX
    memory[5] = 0xC8; // INY
    memory[6] = 0xC0; // CPY
    memory[7] = (uint8_t)5; // Number
    memory[8] = 0xD0; // BNE
    memory[9] = (uint8_t)-6; // -6
    memory[10] = 0xFF; // EXIT
    */

    runCPU(cpu);

    printf("%u", cpu->X);

    free(cpu);

}