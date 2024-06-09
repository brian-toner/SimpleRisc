#include "instructions.h"
#include <string.h> // For memcpy

// Individual PUSH instructions for SP (regular stack)
void cpu_push_sp_ra(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, aCPUPt->vRA, WORDSIZE); }
void cpu_push_sp_rb(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, aCPUPt->vRB, WORDSIZE); }
void cpu_push_sp_rc(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, aCPUPt->vRC, WORDSIZE); }
void cpu_push_sp_ri(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, aCPUPt->vRI, WORDSIZE); }
void cpu_push_sp_rd(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, (CPUType*)aCPUPt->vRD, ADDRSIZE); }
void cpu_push_sp_re(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, (CPUType*)aCPUPt->vRE, ADDRSIZE); }
void cpu_push_sp_rr(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, (CPUType*)aCPUPt->vRR, ADDRSIZE); }
void cpu_push_sp_rs(Risc256* aCPUPt) { push_register_to_stack(aCPUPt, aCPUPt->vRS, WORDSIZE); }

// Individual PUSH instructions for TP (temporary stack)
void cpu_push_tp_ra(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, aCPUPt->vRA, WORDSIZE); }
void cpu_push_tp_rb(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, aCPUPt->vRB, WORDSIZE); }
void cpu_push_tp_rc(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, aCPUPt->vRC, WORDSIZE); }
void cpu_push_tp_ri(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, aCPUPt->vRI, WORDSIZE); }
void cpu_push_tp_rd(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, (CPUType*)aCPUPt->vRD, ADDRSIZE); }
void cpu_push_tp_re(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, (CPUType*)aCPUPt->vRE, ADDRSIZE); }
void cpu_push_tp_rr(Risc256* aCPUPt) { push_register_to_temp_stack(aCPUPt, (CPUType*)aCPUPt->vRR, ADDRSIZE); }

// PUSHALL instruction
void cpu_pushall(Risc256* aCPUPt) {
    if (update_stack_pointer_push(aCPUPt, WORDSIZE * 16)) {
        memcpy(aCPUPt->vSPAddr, aCPUPt->vRA, WORDSIZE * 16);
    }
}
