#include "instructions.h"

CPUType add_partial(CPUType* r, CPUType* m, CPUType ci, CPUType i, CPUPtrType b){
       
    CPUType co = (((CPUPtrType)r[i]+(CPUPtrType)m[i]+(CPUPtrType)ci)>=(CPUPtrType)b);
    r[i] = ((CPUPtrType)r[i]+(CPUPtrType)m[i]+(CPUPtrType)ci)-((co)*b);
            
    return co;

}

CPUType add_base(CPUType* r, CPUType* m, CPUPtrType b, CPUType k, CPUType cin){
    CPUType c = cin;

    for(int i = 0; i < k; i++){
        c = add_partial(r,m,c,i,b);
    }
    
    return c;
}

void cpu_func_call(Risc256* aCPUPt) {
    uint8_t new_ring = (*aCPUPt->vRF & (P0_SET | P1_SET)) >> 6;
    if (new_ring >= get_current_ring(aCPUPt)) {
        if (update_stack_pointer_push(aCPUPt, WORDSIZE * 14)) {
            memcpy(aCPUPt->vSPAddr, aCPUPt->vRA, WORDSIZE * 14);
            *aCPUPt->vPC = *aCPUPt->vRD;
            *aCPUPt->vRF = (*aCPUPt->vRF & ~(P0_SET | P1_SET)) | (new_ring << 6);
        }
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET); // Set error and authorization error flags if not authorized
    }
}

void cpu_swi(Risc256* aCPUPt) {
    if (update_stack_pointer_push(aCPUPt, WORDSIZE * 16)) {
        memcpy(aCPUPt->vSPAddr, aCPUPt->vRA, WORDSIZE * 16);
        *aCPUPt->vPC = *aCPUPt->vRR; // Start SW Interrupt
    }
}

void cpu_branch(Risc256* aCPUPt) {
    *aCPUPt->vPC = *aCPUPt->vRD;
}

void cpu_branch_t(Risc256* aCPUPt) {
    if (*aCPUPt->vRS & T_SET) {
        *aCPUPt->vPC = *aCPUPt->vRD;
    }
}

void cpu_branch_f(Risc256* aCPUPt) {
    if (!(*aCPUPt->vRS & T_SET)) {
        *aCPUPt->vPC = *aCPUPt->vRD;
    }
}

void cpu_ternary_ra_rb(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRS & T_SET) ? *aCPUPt->vRA : *aCPUPt->vRB;
}

void cpu_ternary_rd_re(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRS & T_SET) ? *aCPUPt->vRD : *aCPUPt->vRE;
}

void cpu_ternary_rd_re_mem(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRS & T_SET) ? *(aCPUPt->vMemByte + *aCPUPt->vRD) : *(aCPUPt->vMemByte + *aCPUPt->vRE);
}

void cpu_rfi(Risc256* aCPUPt) {
    if (update_stack_pointer_pop(aCPUPt, WORDSIZE * 16)) {
        memcpy(aCPUPt->vRA, aCPUPt->vSPAddr, WORDSIZE * 16);
    }
}

void cpu_ret(Risc256* aCPUPt){
    
}

void cpu_reset_sp(Risc256* aCPUPt) {
    *aCPUPt->vSP = *aCPUPt->vSSP;
}

void cpu_reset_tp(Risc256* aCPUPt) {
    *aCPUPt->vTP = *aCPUPt->vTSP;
}

void cpu_time(Risc256* aCPUPt) {
    memcpy(aCPUPt->vTC, aCPUPt->vTR, WORDSIZE * 8);
    add_base(aCPUPt->vTC, aCPUPt->vRE,PAGESIZE+1, 8, 0);
}

void cpu_jmp(Risc256* aCPUPt) {
    *aCPUPt->vPC += *aCPUPt->vRR;
}

void cpu_rjmp(Risc256* aCPUPt) {
    *aCPUPt->vPC -= *aCPUPt->vRR;
}

void cpu_hlt(Risc256* aCPUPt) {
    *aCPUPt->vRF |= H_SET; // Set halt flag
}

