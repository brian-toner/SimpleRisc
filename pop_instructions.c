#include "instructions.h"

// Individual POP instructions for SP (regular stack)
void cpu_pop_sp_ra(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, aCPUPt->vRA, WORDSIZE); }
void cpu_pop_sp_rb(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, aCPUPt->vRB, WORDSIZE); }
void cpu_pop_sp_rc(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, aCPUPt->vRC, WORDSIZE); }
void cpu_pop_sp_ri(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, aCPUPt->vRI, WORDSIZE); }
void cpu_pop_sp_rd(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, (CPUType*)aCPUPt->vRD, ADDRSIZE); }
void cpu_pop_sp_re(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, (CPUType*)aCPUPt->vRE, ADDRSIZE); }
void cpu_pop_sp_rr(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, (CPUType*)aCPUPt->vRR, ADDRSIZE); }
void cpu_pop_sp_rs(Risc256* aCPUPt) { pop_register_from_stack(aCPUPt, aCPUPt->vRS, WORDSIZE); }

// Individual POP instructions for TP (temporary stack)
void cpu_pop_tp_ra(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, aCPUPt->vRA, WORDSIZE); }
void cpu_pop_tp_rb(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, aCPUPt->vRB, WORDSIZE); }
void cpu_pop_tp_rc(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, aCPUPt->vRC, WORDSIZE); }
void cpu_pop_tp_ri(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, aCPUPt->vRI, WORDSIZE); }
void cpu_pop_tp_rd(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, (CPUType*)aCPUPt->vRD, ADDRSIZE); }
void cpu_pop_tp_re(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, (CPUType*)aCPUPt->vRE, ADDRSIZE); }
void cpu_pop_tp_rr(Risc256* aCPUPt) { pop_register_from_temp_stack(aCPUPt, (CPUType*)aCPUPt->vRR, ADDRSIZE); }

// POPALL instruction
void cpu_popall(Risc256* aCPUPt) {
    if (update_stack_pointer_pop(aCPUPt, WORDSIZE * 16)) {
        memcpy(aCPUPt->vRA, aCPUPt->vSPAddr, WORDSIZE * 16);
    }
}
