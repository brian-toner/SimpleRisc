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
    if (value < value - 1) {
        *aCPUPt->vRS |= C_SET; // Set Carry flag (for overflow)
    }
}

void cpu_inc_ra(Risc256* aCPUPt) {
    *aCPUPt->vRA += 1;
    set_flags(aCPUPt, *aCPUPt->vRA);
}

void cpu_inc_rb(Risc256* aCPUPt) {
    *aCPUPt->vRB += 1;
    set_flags(aCPUPt, *aCPUPt->vRB);
}

void cpu_inc_rc(Risc256* aCPUPt) {
    *aCPUPt->vRC += 1;
    set_flags(aCPUPt, *aCPUPt->vRC);
}

void cpu_inc_rd_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD += WORDSIZE;
    set_flags(aCPUPt, *aCPUPt->vRD);
}

void cpu_inc_rd_ds(Risc256* aCPUPt) {
    *aCPUPt->vRD += ADDRSIZE;
    set_flags(aCPUPt, *aCPUPt->vRD);
}

void cpu_inc_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRE += WORDSIZE;
    set_flags(aCPUPt, *aCPUPt->vRE);
}

void cpu_inc_re_ds(Risc256* aCPUPt) {
    *aCPUPt->vRE += ADDRSIZE;
    set_flags(aCPUPt, *aCPUPt->vRE);
}

void cpu_inc_ri(Risc256* aCPUPt) {
    *aCPUPt->vRI += 1;
    set_flags(aCPUPt, *aCPUPt->vRI);
}

void cpu_inc_ra_ri(Risc256* aCPUPt) {
    *aCPUPt->vRA += *aCPUPt->vRI;
    set_flags(aCPUPt, *aCPUPt->vRA);
}

void cpu_inc_rb_ri(Risc256* aCPUPt) {
    *aCPUPt->vRB += *aCPUPt->vRI;
    set_flags(aCPUPt, *aCPUPt->vRB);
}

void cpu_inc_rc_ri(Risc256* aCPUPt) {
    *aCPUPt->vRC += *aCPUPt->vRI;
    set_flags(aCPUPt, *aCPUPt->vRC);
}

void cpu_inc_rd_ri(Risc256* aCPUPt) {
    *aCPUPt->vRD += *aCPUPt->vRI;
    set_flags(aCPUPt, *aCPUPt->vRD);
}

void cpu_inc_re_ri(Risc256* aCPUPt) {
    *aCPUPt->vRE += *aCPUPt->vRI;
    set_flags(aCPUPt, *aCPUPt->vRE);
}

void cpu_inc_sp_ws(Risc256* aCPUPt) {
    if ((*aCPUPt->vRF & P0_SET) == 0 && (*aCPUPt->vRF & P1_SET) == 0) {
        *aCPUPt->vSP += WORDSIZE;
        set_flags(aCPUPt, *aCPUPt->vSP);
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET);
    }
}

void cpu_inc_tp_ws(Risc256* aCPUPt) {
    *aCPUPt->vTP += WORDSIZE;
    set_flags(aCPUPt, *aCPUPt->vTP);
}

void cpu_inc_rd_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD += WORDSIZE;
    *aCPUPt->vRE += WORDSIZE;
    set_flags(aCPUPt, *aCPUPt->vRD); // Assuming we set flags based on RD
    set_flags(aCPUPt, *aCPUPt->vRE); // Ensure flags reflect both RD and RE
}
