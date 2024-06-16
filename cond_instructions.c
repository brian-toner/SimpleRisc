#include "instructions.h"




void cpu_gt_ra_rb(Risc256* cpu) {
    bool condition = *cpu->RA > *cpu->RB;
    set_t_flag(cpu, condition);
}

void cpu_lt_ra_rb(Risc256* cpu) {
    bool condition = *cpu->RA < *cpu->RB;
    set_t_flag(cpu, condition);
}

void cpu_eq_ra_rb(Risc256* cpu) {
    bool condition = *cpu->RA == *cpu->RB;
    set_t_flag(cpu, condition);
}

void cpu_ge_ra_rb(Risc256* cpu) {
    bool condition = *cpu->RA >= *cpu->RB;
    set_t_flag(cpu, condition);
}

void cpu_le_ra_rb(Risc256* cpu) {
    bool condition = *cpu->RA <= *cpu->RB;
    set_t_flag(cpu, condition);
}

void cpu_ne_ra_rb(Risc256* cpu) {
    bool condition = *cpu->RA != *cpu->RB;
    set_t_flag(cpu, condition);
}

void cpu_ispos_ra(Risc256* cpu) {
    bool condition = (*cpu->RA & SIGNBIT) == 0;
    set_t_flag(cpu, condition);
}

void cpu_isneg_ra(Risc256* cpu) {
    bool condition = (*cpu->RA & SIGNBIT) != 0;
    set_t_flag(cpu, condition);
}


static inline bool fcomp_gt(float v1, float v2){
    return v1>v2;
}

static inline void float_comp(Risc256* cpu, CPUType* v1, CPUType* v2) {
    float reg1 = cputype_to_float(*v1);
    float reg2 = cputype_to_float(*v2);
    
    *cpu->RS |= ( isnan(reg1) || isnan(reg2))?U_SET:0;
    *cpu->RS |= ( isinf(reg1) || isinf(reg2) )?N_SET:0;
   
    bool condition = reg1 > reg2;

    set_t_flag(cpu, condition);
            
}

void cpu_fgt_ra_rb(Risc256* cpu) {
    bool condition = compare_float(*cpu->RA, *cpu->RB) == 1;
    set_t_flag(cpu, condition);
}

void cpu_flt_ra_rb(Risc256* cpu) {
    bool condition = compare_float(*cpu->RA, *cpu->RB) == -1;
    set_t_flag(cpu, condition);
}

void cpu_feq_ra_rb(Risc256* cpu) {
    bool condition = compare_float(*cpu->RA, *cpu->RB) == 0;
    set_t_flag(cpu, condition);
}

void cpu_fge_ra_rb(Risc256* cpu) {
    int comp = compare_float(*cpu->RA, *cpu->RB);
    bool condition = (comp == 1 || comp == 0);
    set_t_flag(cpu, condition);
}

void cpu_fle_ra_rb(Risc256* cpu) {
    int comp = compare_float(*cpu->RA, *cpu->RB);
    bool condition = (comp == 0 || comp == -1);
    set_t_flag(cpu, condition);
}

void cpu_fne_ra_rb(Risc256* cpu) {
    bool condition = compare_float(*cpu->RA, *cpu->RB) != 0;
    set_t_flag(cpu, condition);
}

void cpu_isnan_ra(Risc256* cpu) {
    bool condition = cputype_is_nan(*cpu->RA);
    set_t_flag(cpu, condition);
}

void cpu_isinf_ra(Risc256* cpu) {
    bool condition = cputype_is_inf(*cpu->RA);
    set_t_flag(cpu, condition);
}

void cpu_gt_ri_rc(Risc256* cpu) {
    bool condition = *cpu->RI > *cpu->RC;
    set_t_flag(cpu, condition);
}

void cpu_lt_ri_rc(Risc256* cpu) {
    bool condition = *cpu->RI < *cpu->RC;
    set_t_flag(cpu, condition);
}

void cpu_eq_ri_rc(Risc256* cpu) {
    bool condition = *cpu->RI == *cpu->RC;
    set_t_flag(cpu, condition);
}

void cpu_ge_ri_rc(Risc256* cpu) {
    bool condition = *cpu->RI >= *cpu->RC;
    set_t_flag(cpu, condition);
}

void cpu_le_ri_rc(Risc256* cpu) {
    bool condition = *cpu->RI <= *cpu->RC;
    set_t_flag(cpu, condition);
}

void cpu_ne_ri_rc(Risc256* cpu) {
    bool condition = *cpu->RI != *cpu->RC;
    set_t_flag(cpu, condition);
}

void cpu_isnull_rd(Risc256* cpu) {
    bool condition = *cpu->RD == 0;
    set_t_flag(cpu, condition);
}

void cpu_isnull_re(Risc256* cpu) {
    bool condition = *cpu->RE == 0;
    set_t_flag(cpu, condition);
}

void cpu_gt_rd_re(Risc256* cpu) {
    bool condition = *cpu->RD > *cpu->RE;
    set_t_flag(cpu, condition);
}

void cpu_lt_rd_re(Risc256* cpu) {
    bool condition = *cpu->RD < *cpu->RE;
    set_t_flag(cpu, condition);
}

void cpu_eq_rd_re(Risc256* cpu) {
    bool condition = *cpu->RD == *cpu->RE;
    set_t_flag(cpu, condition);
}

void cpu_ge_rd_re(Risc256* cpu) {
    bool condition = *cpu->RD >= *cpu->RE;
    set_t_flag(cpu, condition);
}

void cpu_le_rd_re(Risc256* cpu) {
    bool condition = *cpu->RD <= *cpu->RE;
    set_t_flag(cpu, condition);
}

void cpu_ne_rd_re(Risc256* cpu) {
    bool condition = *cpu->RD != *cpu->RE;
    set_t_flag(cpu, condition);
}

void cpu_inbound_re(Risc256* cpu) {
    bool condition = *cpu->RE < cpu->MemSize;
    set_t_flag(cpu, condition);
}

void cpu_inbound_rd(Risc256* cpu) {
    bool condition = *cpu->RD < cpu->MemSize;
    set_t_flag(cpu, condition);
}
