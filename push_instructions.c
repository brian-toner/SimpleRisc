#include "instructions.h"
#include <string.h> // For memcpy

// Individual PUSH instructions for SP (regular stack)
void cpu_push_sp_ra(Risc256* cpu) { push_register_to_stack(cpu, cpu->RA, WORDSIZE); }
void cpu_push_sp_rb(Risc256* cpu) { push_register_to_stack(cpu, cpu->RB, WORDSIZE); }
void cpu_push_sp_rc(Risc256* cpu) { push_register_to_stack(cpu, cpu->RC, WORDSIZE); }
void cpu_push_sp_ri(Risc256* cpu) { push_register_to_stack(cpu, cpu->RI, WORDSIZE); }
void cpu_push_sp_rd(Risc256* cpu) { push_register_to_stack(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_push_sp_re(Risc256* cpu) { push_register_to_stack(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_push_sp_rr(Risc256* cpu) { push_register_to_stack(cpu, (CPUType*)cpu->RR, ADDRSIZE); }
void cpu_push_sp_rs(Risc256* cpu) { push_register_to_stack(cpu, cpu->RS, WORDSIZE); }

// Individual PUSH instructions for TP (temporary stack)
void cpu_push_tp_ra(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RA, WORDSIZE); }
void cpu_push_tp_rb(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RB, WORDSIZE); }
void cpu_push_tp_rc(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RC, WORDSIZE); }
void cpu_push_tp_ri(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RI, WORDSIZE); }
void cpu_push_tp_rd(Risc256* cpu) { push_register_to_temp_stack(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_push_tp_re(Risc256* cpu) { push_register_to_temp_stack(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_push_tp_rr(Risc256* cpu) { push_register_to_temp_stack(cpu, (CPUType*)cpu->RR, ADDRSIZE); }

// PUSHALL instruction
void cpu_pushall(Risc256* cpu) {
    if (update_stack_pointer_push(cpu, WORDSIZE * 16)) {
        memcpy(cpu->SPAddr, cpu->RA, WORDSIZE * 16);
    }
}
