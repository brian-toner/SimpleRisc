#include "instructions.h"




void cpu_gt_ra_rb(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA > *aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_lt_ra_rb(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA < *aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_eq_ra_rb(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA == *aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_ge_ra_rb(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA >= *aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_le_ra_rb(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA <= *aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_ne_ra_rb(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA != *aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_ispos_ra(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRA & SIGNBIT) == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_isneg_ra(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRA & SIGNBIT) != 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_fgt_ra_rb(Risc256* aCPUPt) {
    bool condition = *(CPUFloat*)aCPUPt->vRA > *(CPUFloat*)aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_flt_ra_rb(Risc256* aCPUPt) {
    bool condition = *(CPUFloat*)aCPUPt->vRA < *(CPUFloat*)aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_feq_ra_rb(Risc256* aCPUPt) {
    bool condition = *(CPUFloat*)aCPUPt->vRA == *(CPUFloat*)aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_fge_ra_rb(Risc256* aCPUPt) {
    bool condition = *(CPUFloat*)aCPUPt->vRA >= *(CPUFloat*)aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_fle_ra_rb(Risc256* aCPUPt) {
    bool condition = *(CPUFloat*)aCPUPt->vRA <= *(CPUFloat*)aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_fne_ra_rb(Risc256* aCPUPt) {
    bool condition = *(CPUFloat*)aCPUPt->vRA != *(CPUFloat*)aCPUPt->vRB;
    set_t_flag(aCPUPt, condition);
}

void cpu_isnan_ra(Risc256* aCPUPt) {
    bool condition = isnan(*(CPUFloat*)aCPUPt->vRA);
    set_t_flag(aCPUPt, condition);
}

void cpu_isinf_ra(Risc256* aCPUPt) {
    bool condition = isinf(*(CPUFloat*)aCPUPt->vRA);
    set_t_flag(aCPUPt, condition);
}

void cpu_gt_ri_rc(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRI > *aCPUPt->vRC;
    set_t_flag(aCPUPt, condition);
}

void cpu_lt_ri_rc(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRI < *aCPUPt->vRC;
    set_t_flag(aCPUPt, condition);
}

void cpu_eq_ri_rc(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRI == *aCPUPt->vRC;
    set_t_flag(aCPUPt, condition);
}

void cpu_ge_ri_rc(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRI >= *aCPUPt->vRC;
    set_t_flag(aCPUPt, condition);
}

void cpu_le_ri_rc(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRI <= *aCPUPt->vRC;
    set_t_flag(aCPUPt, condition);
}

void cpu_ne_ri_rc(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRI != *aCPUPt->vRC;
    set_t_flag(aCPUPt, condition);
}

void cpu_isnull_rd(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_isnull_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRE == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_gt_rd_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD > *aCPUPt->vRE;
    set_t_flag(aCPUPt, condition);
}

void cpu_lt_rd_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD < *aCPUPt->vRE;
    set_t_flag(aCPUPt, condition);
}

void cpu_eq_rd_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD == *aCPUPt->vRE;
    set_t_flag(aCPUPt, condition);
}

void cpu_ge_rd_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD >= *aCPUPt->vRE;
    set_t_flag(aCPUPt, condition);
}

void cpu_le_rd_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD <= *aCPUPt->vRE;
    set_t_flag(aCPUPt, condition);
}

void cpu_ne_rd_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD != *aCPUPt->vRE;
    set_t_flag(aCPUPt, condition);
}

void cpu_inbound_re(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRE < aCPUPt->vMemSize;
    set_t_flag(aCPUPt, condition);
}

void cpu_inbound_rd(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRD < aCPUPt->vMemSize;
    set_t_flag(aCPUPt, condition);
}
