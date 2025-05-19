#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cpu.h"
#include "memory.h"
#include "sleep.h"

// Flag Masks
#define CarryFlag 0b00000001
#define ZeroFlag 0b00000010
#define InteruptFlag 0b00000100
#define DecimalFlag 0b00001000
#define BreakFlag 0b00010000
#define OverflowFlag 0b01000000
#define NegativeFlag 0b10000000

CPU* setupCPU() {
    CPU* cpu = (CPU*)malloc(sizeof(CPU));

    cpu->A = 0;
    cpu->X = 0;
    cpu->Y = 0;
    cpu->SP = 0;
    cpu->PC = 0;
    cpu->P = 0;

    return cpu;
}

bool negativeSet(uint8_t flags) {
    return (flags & 0b10000000) != 0;
}

bool overflowSet(uint8_t flags) {
    return (flags & 0b01000000) != 0;
}

bool breakSet(uint8_t flags) {
    return (flags & 0b00010000) != 0;
}

bool decimalSet(uint8_t flags) {
    return (flags & 0b00001000) != 0;
}

bool interruptSet(uint8_t flags) {
    return (flags & 0b00000100) != 0;
}

bool zeroSet(uint8_t flags) {
    return (flags & 0b00000010) != 0;
}

bool carrySet(uint8_t flags) {
    return (flags & 0b00000001) != 0;
}

void setFlag(uint8_t* flags, uint8_t mask, bool condition) {
    if(condition) {
        *flags |= mask;
    }
    else {
        *flags &= ~mask;
    }
}

void runCPU(CPU* cpu) {
    // Fetch, Decode, Execute loop
    uint8_t opcode = 0;
    uint8_t temp = 0;
    //uint16_t tempAdd = 0;
    while(true){
        for(uint16_t i = 0; i < 1000; i++) {
            opcode = memory[cpu->PC++];
            printf("opcode: %#02X\n", opcode);
            switch(opcode) {
                case 0x69: // ADC
                    // IMPLIMENT ME PLEASE
                    break;
                case 0x29: // AND
                    cpu->A = cpu->A & memory[cpu->PC++];
                    setFlag(&cpu->P, ZeroFlag, cpu->A == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->A & 0b10000000);
                    break;
                case 0x0A: // ASL
                    setFlag(&cpu->P, CarryFlag, cpu->A & 0b10000000);
                    cpu->A = cpu->A << 1;
                    setFlag(&cpu->P, NegativeFlag, cpu->A & 0b10000000);
                    break;
                case 0x2C: // BIT
                    temp = cpu->A & memory[cpu->PC];
                    setFlag(&cpu->P, ZeroFlag, temp == 0);
                    setFlag(&cpu->P, OverflowFlag, memory[cpu->PC] & 0b01000000);
                    setFlag(&cpu->P, NegativeFlag, memory[cpu->PC++] & 0b10000000);
                    break;
                case 0xD0: // BNE
                    if(!zeroSet(cpu->P)) {
                        cpu->PC += (int8_t)memory[cpu->PC];
                    }
                    cpu->PC++;
                    break;
                case 0x18: // CLC
                    setFlag(&cpu->P, CarryFlag, false);
                    break;
                case 0xD8: // CLD
                    setFlag(&cpu->P, DecimalFlag, false);
                    break;
                case 0x58: // CLI
                    setFlag(&cpu->P, InteruptFlag, false);
                    break;
                case 0xB8: // CLV
                    setFlag(&cpu->P, OverflowFlag, false);
                    break;
                case 0xC9: // CMP
                    temp = cpu->A - memory[cpu->PC];
                    setFlag(&cpu->P, CarryFlag, cpu->A >= memory[cpu->PC]);
                    setFlag(&cpu->P, ZeroFlag, temp == 0);
                    setFlag(&cpu->P, NegativeFlag, temp & 0b10000000);
                    break;
                case 0xE0: // CPX
                    temp = cpu->X - memory[cpu->PC];
                    setFlag(&cpu->P, CarryFlag, cpu->X >= memory[cpu->PC]);
                    setFlag(&cpu->P, ZeroFlag, cpu->X == memory[cpu->PC++]);
                    setFlag(&cpu->P, NegativeFlag, temp & 0b10000000);
                    break;
                case 0xC0: // CPY
                    temp = cpu->Y - memory[cpu->PC];
                    setFlag(&cpu->P, CarryFlag, cpu->Y >= memory[cpu->PC]);
                    setFlag(&cpu->P, ZeroFlag, cpu->Y == memory[cpu->PC++]);
                    setFlag(&cpu->P, NegativeFlag, temp & 0b10000000);
                    break;
                case 0xCA: // DEX
                    cpu->X--;
                    setFlag(&cpu->P, ZeroFlag, cpu->X == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->X & 0b10000000);
                    break;
                case 0x88: // DEY
                    cpu->Y--;
                    setFlag(&cpu->P, ZeroFlag, cpu->Y == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->Y & 0b10000000);
                    break;
                case 0x49: // EOR
                    cpu->A ^= memory[cpu->PC++];
                    setFlag(&cpu->P, ZeroFlag, cpu->A == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->A & 0b10000000);
                    break;
                case 0xE8: // INX
                    cpu->X++;
                    setFlag(&cpu->P, ZeroFlag, cpu->X == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->X & 0b10000000);
                    break;
                case 0xC8: // INY
                    cpu->Y++;
                    setFlag(&cpu->P, ZeroFlag, cpu->Y == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->Y & 0b10000000);
                    break;
                case 0x4C: // JMP
                    // Modifying PC more than once on the same line is undefined behavior, so I separtated them
                    temp = memory[cpu->PC++];
                    cpu->PC = ((uint16_t)temp << 8) | memory[cpu->PC];
                    cpu->PC++;
                    break;
                case 0xA9: // LDA
                    cpu->A = memory[cpu->PC++];
                    setFlag(&cpu->P, ZeroFlag, cpu->A == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->A & 0b10000000);
                    break;
                case 0xA2: // LDX
                    cpu->X = memory[cpu->PC++];
                    setFlag(&cpu->P, ZeroFlag, cpu->X == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->X & 0b10000000);
                    break;
                case 0xA0: // LDY
                    cpu->Y = memory[cpu->PC++];
                    setFlag(&cpu->P, ZeroFlag, cpu->Y == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->Y & 0b10000000);
                    break;
                case 0x4A: // LSR
                    setFlag(&cpu->P, CarryFlag, cpu->A & 0b00000001);
                    cpu->A = cpu->A >> 1;
                    setFlag(&cpu->P, ZeroFlag, cpu->A == 0);
                    setFlag(&cpu->P, NegativeFlag, 0);
                    break;
                case 0xEA: // NOP
                    cpu->PC++;
                    break;
                case 0x09: // ORA
                    cpu->A |= memory[cpu->PC++];
                    setFlag(&cpu->P, ZeroFlag, cpu->A == 0);
                    setFlag(&cpu->P, NegativeFlag, cpu->A & 0b10000000);
                    break;
                case 0x2A: // ROL
                    temp = cpu->A & 0b10000000;
                    cpu->A = cpu->A << 1;
                    setFlag(&cpu->P, CarryFlag, temp);
                    cpu->A += (temp >> 7);
                    break;
                case 0x6A:
                    break;
                case 0xFF: // THIS IS NOT REAL AND JUST FOR TESTING, CHANGE LATER
                    return;
                    break;
                default:
                    printf("Unhandled opcode: %#02X\n", opcode);
                    while(true) {
                        sleepMS(50);
                    }
                    break;
            }
        }
        sleepMS(1);
    }
}