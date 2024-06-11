#include "instructions.h"



static inline void cpu_dec_doubleregister(Risc256* cpu, CPUType* regPtr, CPUType dec) {
    CPUPtrType reg = *regPtr;
    CPUPtrType result = reg - dec;

    // Calculate flags using bitwise operations to avoid conditionals
    CPUType flags = *cpu->vRS & CZOS_MASK;

    flags |= (result == 0) * Z_SET;
    flags |= ((result & SIGNBIT) != 0) * S_SET;
    flags |= ((reg & SIGNBIT) && !(result & SIGNBIT)) * O_SET;
    flags |= (reg == 0) * C_SET;

    *cpu->vRS = flags;
    *regPtr = result;
}

void cpu_dec_ra(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRA, 1);
}

void cpu_dec_rb(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRB, 1);
}

void cpu_dec_rc(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRC, 1);
}

void cpu_dec_rd_ws(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vRD, WORDSIZE);
}

void cpu_dec_rd_ds(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vRD, ADDRSIZE);
}

void cpu_dec_re_ws(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vRE, WORDSIZE);
}

void cpu_dec_re_ds(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vRE, ADDRSIZE);
}

void cpu_dec_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRI, 1);
}

void cpu_dec_ra_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRA, *cpu->vRI);
}

void cpu_dec_rb_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRB, *cpu->vRI);
}


void cpu_dec_rc_ri(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRC, *cpu->vRI);
}

void cpu_dec_rd_ri(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vRD, *cpu->vRI);
}

void cpu_dec_re_ri(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vRE, *cpu->vRI);
}

void cpu_dec_sp_ws(Risc256* cpu) {
    if ((*cpu->vRF & P0_SET) == 0 && (*cpu->vRF & P1_SET) == 0) {
        cpu_dec_doubleregister(cpu, cpu->vSP, WORDSIZE);
    } else {
        *cpu->vRF |= (E_SET | A_SET);
    }
}

void cpu_dec_tp_ws(Risc256* cpu) {
    cpu_dec_doubleregister(cpu, cpu->vTP, WORDSIZE);
}

void cpu_dec_rd_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD -= WORDSIZE;
    *aCPUPt->vRE -= WORDSIZE;
}