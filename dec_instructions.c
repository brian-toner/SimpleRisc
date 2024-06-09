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
    *aCPUPt->vRA -= 1;
    set_flags_decrement(aCPUPt, *aCPUPt->vRA);
}

void cpu_dec_rb(Risc256* aCPUPt) {
    *aCPUPt->vRB -= 1;
    set_flags_decrement(aCPUPt, *aCPUPt->vRB);
}

void cpu_dec_rc(Risc256* aCPUPt) {
    *aCPUPt->vRC -= 1;
    set_flags_decrement(aCPUPt, *aCPUPt->vRC);
}

void cpu_dec_rd_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD -= WORDSIZE;
    set_flags_decrement(aCPUPt, *aCPUPt->vRD);
}

void cpu_dec_rd_ds(Risc256* aCPUPt) {
    *aCPUPt->vRD -= ADDRSIZE;
    set_flags_decrement(aCPUPt, *aCPUPt->vRD);
}

void cpu_dec_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRE -= WORDSIZE;
    set_flags_decrement(aCPUPt, *aCPUPt->vRE);
}

void cpu_dec_re_ds(Risc256* aCPUPt) {
    *aCPUPt->vRE -= ADDRSIZE;
    set_flags_decrement(aCPUPt, *aCPUPt->vRE);
}

void cpu_dec_ri(Risc256* aCPUPt) {
    *aCPUPt->vRI -= 1;
    set_flags_decrement(aCPUPt, *aCPUPt->vRI);
}

void cpu_dec_ra_ri(Risc256* aCPUPt) {
    *aCPUPt->vRA -= *aCPUPt->vRI;
    set_flags_decrement(aCPUPt, *aCPUPt->vRA);
}

void cpu_dec_rb_ri(Risc256* aCPUPt) {
    *aCPUPt->vRB -= *aCPUPt->vRI;
    set_flags_decrement(aCPUPt, *aCPUPt->vRB);
}

void cpu_dec_rc_ri(Risc256* aCPUPt) {
    *aCPUPt->vRC -= *aCPUPt->vRI;
    set_flags_decrement(aCPUPt, *aCPUPt->vRC);
}

void cpu_dec_rd_ri(Risc256* aCPUPt) {
    *aCPUPt->vRD -= *aCPUPt->vRI;
    set_flags_decrement(aCPUPt, *aCPUPt->vRD);
}

void cpu_dec_re_ri(Risc256* aCPUPt) {
    *aCPUPt->vRE -= *aCPUPt->vRI;
    set_flags_decrement(aCPUPt, *aCPUPt->vRE);
}

void cpu_dec_sp_ws(Risc256* aCPUPt) {
    if ((*aCPUPt->vRF & P0_SET) == 0 && (*aCPUPt->vRF & P1_SET) == 0) {
        *aCPUPt->vSP -= WORDSIZE;
        set_flags_decrement(aCPUPt, *aCPUPt->vSP);
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET);
    }
}

void cpu_dec_tp_ws(Risc256* aCPUPt) {
    *aCPUPt->vTP -= WORDSIZE;
    set_flags_decrement(aCPUPt, *aCPUPt->vTP);
}

void cpu_dec_rd_re_ws(Risc256* aCPUPt) {
    *aCPUPt->vRD -= WORDSIZE;
    *aCPUPt->vRE -= WORDSIZE;
    set_flags_decrement(aCPUPt, *aCPUPt->vRD); // Assuming we set flags based on RD
    set_flags_decrement(aCPUPt, *aCPUPt->vRE); // Ensure flags reflect both RD and RE
}