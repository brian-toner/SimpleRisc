#include "instructions.h"

// Helper function to set flags for decrement operations
void set_flags_decrement(Risc256* aCPUPt, CPUType value) {
    *aCPUPt->vRS &= ~(C_SET | Z_SET | S_SET); // Clear relevant flags
    if (value == 0) {
        *aCPUPt->vRS |= Z_SET; // Set Zero flag
    }
    if (value & SIGNBIT) {
        *aCPUPt->vRS |= S_SET; // Set Sign flag
    }
    if (value > value + 1) {
        *aCPUPt->vRS |= C_SET; // Set Carry flag (for underflow)
    }
}

void cpu_dec_ra(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA - 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((1 > *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

void cpu_dec_rb(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRB - 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((1 > *aCPUPt->vRB) ? C_SET : 0);
    *aCPUPt->vRB = result;
}

void cpu_dec_rc(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRC - 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((1 > *aCPUPt->vRC) ? C_SET : 0);
    *aCPUPt->vRC = result;
}

void cpu_dec_rd_ws(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRD - WORDSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((WORDSIZE > *aCPUPt->vRD) ? C_SET : 0);
    *aCPUPt->vRD = result;
}

void cpu_dec_rd_ds(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRD - ADDRSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((ADDRSIZE > *aCPUPt->vRD) ? C_SET : 0);
    *aCPUPt->vRD = result;
}

void cpu_dec_re_ws(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRE - WORDSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((WORDSIZE > *aCPUPt->vRE) ? C_SET : 0);
    *aCPUPt->vRE = result;
}

void cpu_dec_re_ds(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRE - ADDRSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((ADDRSIZE > *aCPUPt->vRE) ? C_SET : 0);
    *aCPUPt->vRE = result;
}

void cpu_dec_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRI - 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((1 > *aCPUPt->vRI) ? C_SET : 0);
    *aCPUPt->vRI = result;
}

void cpu_dec_ra_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA - *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRI > *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

void cpu_dec_rb_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRB - *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRI > *aCPUPt->vRB) ? C_SET : 0);
    *aCPUPt->vRB = result;
}

void cpu_dec_rc_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRC - *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRI > *aCPUPt->vRC) ? C_SET : 0);
    *aCPUPt->vRC = result;
}

void cpu_dec_rd_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRD - *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRI > *aCPUPt->vRD) ? C_SET : 0);
    *aCPUPt->vRD = result;
}

void cpu_dec_re_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRE - *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRI > *aCPUPt->vRE) ? C_SET : 0);
    *aCPUPt->vRE = result;
}

void cpu_dec_sp_ws(Risc256* aCPUPt) {
    if ((*aCPUPt->vRF & P0_SET) == 0 && (*aCPUPt->vRF & P1_SET) == 0) {
        CPUType result = *aCPUPt->vSP - WORDSIZE;
        *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((WORDSIZE > *aCPUPt->vSP) ? C_SET : 0);
        *aCPUPt->vSP = result;
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET);
    }
}

void cpu_dec_tp_ws(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vTP - WORDSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((WORDSIZE > *aCPUPt->vTP) ? C_SET : 0);
    *aCPUPt->vTP = result;
}

void cpu_dec_rd_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD -= WORDSIZE;
    *aCPUPt->vRE -= WORDSIZE;
}