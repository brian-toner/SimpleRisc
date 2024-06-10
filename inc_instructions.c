#include "instructions.h"

// Helper function to set flags
void set_flags(Risc256* aCPUPt, CPUType value) {
    *aCPUPt->vRS &= ~(C_SET | Z_SET | S_SET); // Clear relevant flags
    if (value == 0) {
        *aCPUPt->vRS |= Z_SET; // Set Zero flag
    }
    if (value & SIGNBIT) {
        *aCPUPt->vRS |= S_SET; // Set Sign flag
    }
    if (value > value - 1) {
        *aCPUPt->vRS |= C_SET; // Set Carry flag (for overflow)
    }
}

void set_flags_addr(Risc256* aCPUPt, CPUPtrType value) {
    *aCPUPt->vRS &= ~(C_SET | Z_SET ); // Clear relevant flags
    if (value == 0) {
        *aCPUPt->vRS |= Z_SET; // Set Zero flag
    }
    if (value > value - 1) {
        *aCPUPt->vRS |= C_SET; // Set Carry flag (for overflow)
    }
}


void cpu_inc_ra(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA + 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

void cpu_inc_rb(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRB + 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRB) ? C_SET : 0);
    *aCPUPt->vRB = result;
}

void cpu_inc_rc(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRC + 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRC) ? C_SET : 0);
    *aCPUPt->vRC = result;
}

void cpu_inc_rd_ws(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRD + WORDSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRD) ? C_SET : 0);
    *aCPUPt->vRD = result;
}

void cpu_inc_rd_ds(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRD + ADDRSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRD) ? C_SET : 0);
    *aCPUPt->vRD = result;
}

void cpu_inc_re_ws(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRE + WORDSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRE) ? C_SET : 0);
    *aCPUPt->vRE = result;
}

void cpu_inc_re_ds(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRE + ADDRSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRE) ? C_SET : 0);
    *aCPUPt->vRE = result;
}

void cpu_inc_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRI + 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRI) ? C_SET : 0);
    *aCPUPt->vRI = result;
}

void cpu_inc_ra_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA + *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

void cpu_inc_rb_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRB + *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRB) ? C_SET : 0);
    *aCPUPt->vRB = result;
}

void cpu_inc_rc_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRC + *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRC) ? C_SET : 0);
    *aCPUPt->vRC = result;
}

void cpu_inc_rd_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRD + *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRD) ? C_SET : 0);
    *aCPUPt->vRD = result;
}

void cpu_inc_re_ri(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRE + *aCPUPt->vRI;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRE) ? C_SET : 0);
    *aCPUPt->vRE = result;
}

void cpu_inc_sp_ws(Risc256* aCPUPt) {
    if ((*aCPUPt->vRF & P0_SET) == 0 && (*aCPUPt->vRF & P1_SET) == 0) {
        CPUType result = *aCPUPt->vSP + WORDSIZE;
        *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vSP) ? C_SET : 0);
        *aCPUPt->vSP = result;
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET);
    }
}

void cpu_inc_tp_ws(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vTP + WORDSIZE;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vTP) ? C_SET : 0);
    *aCPUPt->vTP = result;
}

void cpu_inc_rd_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD += WORDSIZE;
    *aCPUPt->vRE += WORDSIZE;
}
