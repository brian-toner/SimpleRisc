#include "instructions.h"
#include <string.h> // For memcpy

static inline void cpu_psh_data(Risc256* cpu, CPUType* reg, size_t size){
    
    if(!isRing0(cpu)){
        *cpu->RF |= E_SET | A_SET;
        return;
    }
    
    if(*cpu->SEP != 0 && *cpu->SP-WORDSIZE*size < *cpu->SEP ){   
        memcpy(cpu->SPAddr, reg, WORDSIZE*size);
        *cpu->SP += WORDSIZE*size;
        cpu->SPAddr = cpu->MemByte+(*cpu->SP);
    } else {
        //Throw interrupt.
        *cpu->RF |= E_SET;
    }
}

// Individual PUSH instructions for SP (regular stack)
void cpu_push_sp_ra(Risc256* cpu) { cpu_psh_data(cpu, cpu->RA, WORDSIZE); }
void cpu_push_sp_rb(Risc256* cpu) { cpu_psh_data(cpu, cpu->RB, WORDSIZE); }
void cpu_push_sp_rc(Risc256* cpu) { cpu_psh_data(cpu, cpu->RC, WORDSIZE); }
void cpu_push_sp_ri(Risc256* cpu) { cpu_psh_data(cpu, cpu->RI, WORDSIZE); }
void cpu_push_sp_rd(Risc256* cpu) { cpu_psh_data(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_push_sp_re(Risc256* cpu) { cpu_psh_data(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_push_sp_rr(Risc256* cpu) { cpu_psh_data(cpu, (CPUType*)cpu->RR, ADDRSIZE); }
void cpu_push_sp_rs(Risc256* cpu) { cpu_psh_data(cpu, cpu->RS, WORDSIZE); }

// Individual PUSH instructions for TP (temporary stack)
void cpu_push_tp_ra(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RA, WORDSIZE); }
void cpu_push_tp_rb(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RB, WORDSIZE); }
void cpu_push_tp_rc(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RC, WORDSIZE); }
void cpu_push_tp_ri(Risc256* cpu) { push_register_to_temp_stack(cpu, cpu->RI, WORDSIZE); }
void cpu_push_tp_rd(Risc256* cpu) { push_register_to_temp_stack(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_push_tp_re(Risc256* cpu) { push_register_to_temp_stack(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_push_tp_rr(Risc256* cpu) { push_register_to_temp_stack(cpu, (CPUType*)cpu->RR, ADDRSIZE); }

// PUSHALL instruction
void cpu_pushall(Risc256* cpu) { cpu_psh_data(cpu, cpu->RA, WORDSIZE*18); }
