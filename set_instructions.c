#include "instructions.h"

//=========================================================//
// 0x00
void cpu_set(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | ( *(cpu-> MemByte+*cpu->PC) & 0x0F);
}

void cpu_set_0(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x00;
}

void cpu_set_1(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x01;
}

void cpu_set_2(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x02;
}

void cpu_set_3(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x03;
}

void cpu_set_4(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x04;
}

void cpu_set_5(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x05;
}

void cpu_set_6(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x06;
}

void cpu_set_7(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x07;
}

void cpu_set_8(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x08;
}

void cpu_set_9(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x09;
}

void cpu_set_A(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x0A;
}

void cpu_set_B(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x0B;
}

void cpu_set_C(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x0C;
}

void cpu_set_D(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x0D;
}

void cpu_set_E(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x0E;
}

void cpu_set_F(Risc256* cpu) {
    *cpu->RR = (*cpu->RR << 4) | 0x0F;
}