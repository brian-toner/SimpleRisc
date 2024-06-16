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

void cpu_func_call(Risc256* cpu) {
    uint8_t new_ring = (*cpu->RF & (P0_SET | P1_SET)) >> 6;
    if (new_ring >= get_current_ring(cpu)) {
        if (update_stack_pointer_push(cpu, WORDSIZE * 14)) {
            memcpy(cpu->SPAddr, cpu->RA, WORDSIZE * 14);
            *cpu->PC = *cpu->RD;
            *cpu->RF = (*cpu->RF & ~(P0_SET | P1_SET)) | (new_ring << 6);
        }
    } else {
        *cpu->RF |= (E_SET | A_SET); // Set error and authorization error flags if not authorized
    }
}

void cpu_swi(Risc256* cpu) {
    if (update_stack_pointer_push(cpu, WORDSIZE * 16)) {
        memcpy(cpu->SPAddr, cpu->RA, WORDSIZE * 16);
        *cpu->PC = *cpu->RR; // Start SW Interrupt
    }
}

void cpu_branch(Risc256* cpu) {
    *cpu->PC = *cpu->RD;
}

void cpu_branch_t(Risc256* cpu) {
    if (*cpu->RS & T_SET) {
        *cpu->PC = *cpu->RD;
    }
}

void cpu_branch_f(Risc256* cpu) {
    if (!(*cpu->RS & T_SET)) {
        *cpu->PC = *cpu->RD;
    }
}

void cpu_ternary_ra_rb(Risc256* cpu) {
    *cpu->RR = (*cpu->RS & T_SET) ? *cpu->RA : *cpu->RB;
}

void cpu_ternary_rd_re(Risc256* cpu) {
    *cpu->RR = (*cpu->RS & T_SET) ? *cpu->RD : *cpu->RE;
}

void cpu_ternary_rd_re_mem(Risc256* cpu) {
    *cpu->RR = (*cpu->RS & T_SET) ? *(cpu-> MemByte + *cpu->RD) : *(cpu-> MemByte + *cpu->RE);
}

void cpu_rfi(Risc256* cpu) {
    if (update_stack_pointer_pop(cpu, WORDSIZE * 16)) {
        memcpy(cpu->RA, cpu->SPAddr, WORDSIZE * 16);
    }
}

void cpu_ret(Risc256* cpu){
    
}

void cpu_reset_sp(Risc256* cpu) {
    *cpu->SP = *cpu->SSP;
}

void cpu_reset_tp(Risc256* cpu) {
    *cpu->TP = *cpu->TSP;
}

void cpu_time(Risc256* cpu) {
    memcpy(cpu->TC, cpu->TR, WORDSIZE * 8);
    add_base(cpu->TC, cpu->RE,PAGESIZE+1, 8, 0);
}

void cpu_jmp(Risc256* cpu) {
    *cpu->PC += *cpu->RR;
}

void cpu_rjmp(Risc256* cpu) {
    *cpu->PC -= *cpu->RR;
}

void cpu_hlt(Risc256* cpu) {
    *cpu->RF |= H_SET; // Set halt flag
}

