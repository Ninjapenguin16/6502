#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct {
    uint8_t A, X, Y; // Registers
    uint8_t SP; // Stack Pointer
    uint16_t PC; // Program Counter
    uint8_t P; // Status Flags
} CPU;

CPU* setupCPU();

void runCPU(CPU* cpu);

#endif