#include "instructions.h"

// Helper function to set flags
void set_flags(Risc256* cpu, CPUType value) {
    *cpu->RS &= ~(C_SET | Z_SET | S_SET); // Clear relevant flags
    if (value == 0) {
        *cpu->RS |= Z_SET; // Set Zero flag
    }
    if (value & SIGNBIT) {
        *cpu->RS |= S_SET; // Set Sign flag
    }
    if (value > value - 1) {
        *cpu->RS |= C_SET; // Set Carry flag (for overflow)
    }
}

void set_flags_addr(Risc256* cpu, CPUPtrType value) {
    *cpu->RS &= ~(C_SET | Z_SET ); // Clear relevant flags
    if (value == 0) {
        *cpu->RS |= Z_SET; // Set Zero flag
    }
    if (value > value - 1) {
        *cpu->RS |= C_SET; // Set Carry flag (for overflow)
    }
}


void cpu_inc_ra(Risc256* cpu) {
    CPUType result = *cpu->RA + 1;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

void cpu_inc_rb(Risc256* cpu) {
    CPUType result = *cpu->RB + 1;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RB) ? C_SET : 0);
    *cpu->RB = result;
}

void cpu_inc_rc(Risc256* cpu) {
    CPUType result = *cpu->RC + 1;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RC) ? C_SET : 0);
    *cpu->RC = result;
}

void cpu_inc_rd_ws(Risc256* cpu) {
    CPUType result = *cpu->RD + WORDSIZE;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RD) ? C_SET : 0);
    *cpu->RD = result;
}

void cpu_inc_rd_ds(Risc256* cpu) {
    CPUType result = *cpu->RD + ADDRSIZE;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RD) ? C_SET : 0);
    *cpu->RD = result;
}

void cpu_inc_re_ws(Risc256* cpu) {
    CPUType result = *cpu->RE + WORDSIZE;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RE) ? C_SET : 0);
    *cpu->RE = result;
}

void cpu_inc_re_ds(Risc256* cpu) {
    CPUType result = *cpu->RE + ADDRSIZE;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RE) ? C_SET : 0);
    *cpu->RE = result;
}

void cpu_inc_ri(Risc256* cpu) {
    CPUType result = *cpu->RI + 1;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RI) ? C_SET : 0);
    *cpu->RI = result;
}

void cpu_inc_ra_ri(Risc256* cpu) {
    CPUType result = *cpu->RA + *cpu->RI;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

void cpu_inc_rb_ri(Risc256* cpu) {
    CPUType result = *cpu->RB + *cpu->RI;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RB) ? C_SET : 0);
    *cpu->RB = result;
}

void cpu_inc_rc_ri(Risc256* cpu) {
    CPUType result = *cpu->RC + *cpu->RI;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RC) ? C_SET : 0);
    *cpu->RC = result;
}

void cpu_inc_rd_ri(Risc256* cpu) {
    CPUType result = *cpu->RD + *cpu->RI;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RD) ? C_SET : 0);
    *cpu->RD = result;
}

void cpu_inc_re_ri(Risc256* cpu) {
    CPUType result = *cpu->RE + *cpu->RI;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RE) ? C_SET : 0);
    *cpu->RE = result;
}

void cpu_inc_sp_ws(Risc256* cpu) {
    if ((*cpu->RF & P0_SET) == 0 && (*cpu->RF & P1_SET) == 0) {
        CPUType result = *cpu->SP + WORDSIZE;
        *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->SP) ? C_SET : 0);
        *cpu->SP = result;
    } else {
        *cpu->RF |= (E_SET | A_SET);
    }
}

void cpu_inc_tp_ws(Risc256* cpu) {
    CPUType result = *cpu->TP + WORDSIZE;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->TP) ? C_SET : 0);
    *cpu->TP = result;
}

void cpu_inc_rd_re_ws(Risc256* cpu) {
    *cpu->RD += WORDSIZE;
    *cpu->RE += WORDSIZE;
}
