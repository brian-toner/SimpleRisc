#include "instructions.h"



static inline void cpu_dec_doubleregister(Risc256* cpu, CPUType* regPtr, CPUType dec) {
    CPUPtrType reg = *regPtr;
    CPUPtrType result = reg - dec;

    // Calculate flags using bitwise operations to avoid conditionals
    CPUType flags = *cpu->RS & CZOS_MASK;

    flags |= (result == 0) * Z_SET;
    flags |= ((result & SIGNBIT) != 0) * S_SET;
    flags |= ((reg & SIGNBIT) && !(result & SIGNBIT)) * O_SET;
    flags |= (reg == 0) * C_SET;

    *cpu->RS = flags;
    *regPtr = result;
}

void cpu_dec_ra(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RA, 1);
}

void cpu_dec_rb(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RB, 1);
}

void cpu_dec_rc(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RC, 1);
}

void cpu_dec_rd_ws(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->RD, WORDSIZE);
}

void cpu_dec_rd_ds(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->RD, ADDRSIZE);
}

void cpu_dec_re_ws(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->RE, WORDSIZE);
}

void cpu_dec_re_ds(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->RE, ADDRSIZE);
}

void cpu_dec_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RI, 1);
}

void cpu_dec_ra_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RA, *cpu->RI);
}

void cpu_dec_rb_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RB, *cpu->RI);
}


void cpu_dec_rc_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RC, *cpu->RI);
}

void cpu_dec_rd_ri(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->RD, *cpu->RI);
}

void cpu_dec_re_ri(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->RE, *cpu->RI);
}

void cpu_dec_sp_ws(Risc256* cpu) {
    if ((*cpu->RF & P0_SET) == 0 && (*cpu->RF & P1_SET) == 0) {
        cpu_dec_doubleregister(cpu, cpu->SP, WORDSIZE);
    } else {
        *cpu->RF |= (E_SET | A_SET);
    }
}

void cpu_dec_tp_ws(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->TP, WORDSIZE);
}

void cpu_dec_rd_re_ws(Risc256* cpu) {
    *cpu->RD -= WORDSIZE;
    *cpu->RE -= WORDSIZE;
}