#include "instructions.h"

// Individual POP instructions for SP (regular stack)
void cpu_pop_sp_ra(Risc256* cpu) { pop_register_from_stack(cpu, cpu->RA, WORDSIZE); }
void cpu_pop_sp_rb(Risc256* cpu) { pop_register_from_stack(cpu, cpu->RB, WORDSIZE); }
void cpu_pop_sp_rc(Risc256* cpu) { pop_register_from_stack(cpu, cpu->RC, WORDSIZE); }
void cpu_pop_sp_ri(Risc256* cpu) { pop_register_from_stack(cpu, cpu->RI, WORDSIZE); }
void cpu_pop_sp_rd(Risc256* cpu) { pop_register_from_stack(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_pop_sp_re(Risc256* cpu) { pop_register_from_stack(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_pop_sp_rr(Risc256* cpu) { pop_register_from_stack(cpu, (CPUType*)cpu->RR, ADDRSIZE); }
void cpu_pop_sp_rs(Risc256* cpu) { pop_register_from_stack(cpu, cpu->RS, WORDSIZE); }

// Individual POP instructions for TP (temporary stack)
void cpu_pop_tp_ra(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RA, WORDSIZE); }
void cpu_pop_tp_rb(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RB, WORDSIZE); }
void cpu_pop_tp_rc(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RC, WORDSIZE); }
void cpu_pop_tp_ri(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RI, WORDSIZE); }
void cpu_pop_tp_rd(Risc256* cpu) { pop_register_from_temp_stack(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_pop_tp_re(Risc256* cpu) { pop_register_from_temp_stack(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_pop_tp_rr(Risc256* cpu) { pop_register_from_temp_stack(cpu, (CPUType*)cpu->RR, ADDRSIZE); }

// POPALL instruction
void cpu_popall(Risc256* cpu) {
    if (update_stack_pointer_pop(cpu, WORDSIZE * 16)) {
        memcpy(cpu->RA, cpu->SPAddr, WORDSIZE * 16);
    }
}
