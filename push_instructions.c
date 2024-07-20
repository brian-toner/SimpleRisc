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



static inline void cpu_psh_data_reg(Risc256* cpu, CPUType* reg, size_t size, AddressType* stack, AddressType* stackEnd, RegType** stackAddress){
    if(*stackEnd != 0 && *stack - WORDSIZE * size < *stackEnd ){   
        memcpy(*stackAddress, reg, WORDSIZE * size);
        *stack += WORDSIZE * size;
        *stackAddress = cpu->MemByte + (*stack);
    } else {
        //Throw interrupt.
        *cpu->RF |= E_SET;
    }
}

static inline void cpu_psh_sp(Risc256* cpu, CPUType* reg, size_t size){
    if(!isRing0(cpu)){
        *cpu->RF |= E_SET | A_SET;
        return;
    }
    
    cpu_psh_data_reg(cpu, reg, size, cpu->SP, cpu->SEP, &(cpu->SPAddr));
}

static inline void cpu_psh_tp(Risc256* cpu, CPUType* reg, size_t size){
    cpu_psh_data_reg(cpu, reg, size, cpu->TP, cpu->TEP, &(cpu->TPAddr));
}

// Individual PUSH instructions for SP (regular stack)
void cpu_push_sp_ra(Risc256* cpu) { cpu_psh_sp(cpu, cpu->RA, WORDSIZE); }
void cpu_push_sp_rb(Risc256* cpu) { cpu_psh_sp(cpu, cpu->RB, WORDSIZE); }
void cpu_push_sp_rc(Risc256* cpu) { cpu_psh_sp(cpu, cpu->RC, WORDSIZE); }
void cpu_push_sp_ri(Risc256* cpu) { cpu_psh_sp(cpu, cpu->RI, WORDSIZE); }
void cpu_push_sp_rd(Risc256* cpu) { cpu_psh_sp(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_push_sp_re(Risc256* cpu) { cpu_psh_sp(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_push_sp_rr(Risc256* cpu) { cpu_psh_sp(cpu, (CPUType*)cpu->RR, ADDRSIZE); }
void cpu_push_sp_rs(Risc256* cpu) { cpu_psh_sp(cpu, cpu->RS, WORDSIZE); }

// Individual PUSH instructions for TP (temporary stack)
void cpu_push_tp_ra(Risc256* cpu) { cpu_psh_tp(cpu, cpu->RA, WORDSIZE); }
void cpu_push_tp_rb(Risc256* cpu) { cpu_psh_tp(cpu, cpu->RB, WORDSIZE); }
void cpu_push_tp_rc(Risc256* cpu) { cpu_psh_tp(cpu, cpu->RC, WORDSIZE); }
void cpu_push_tp_ri(Risc256* cpu) { cpu_psh_tp(cpu, cpu->RI, WORDSIZE); }
void cpu_push_tp_rd(Risc256* cpu) { cpu_psh_tp(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_push_tp_re(Risc256* cpu) { cpu_psh_tp(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_push_tp_rr(Risc256* cpu) { cpu_psh_tp(cpu, (CPUType*)cpu->RR, ADDRSIZE); }

// PUSHALL instruction
void cpu_pushall(Risc256* cpu) { cpu_psh_sp(cpu, cpu->RA, WORDSIZE*18); }
