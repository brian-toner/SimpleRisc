#include "instructions.h"

static inline void cpu_pop_data(Risc256* cpu, CPUType *reg, size_t size){
    if(!isRing0(cpu)){
        *cpu->RF |= E_SET | A_SET;
        //Throw Interrupt;
        return;
    }
      
    if(*cpu->SSP == 0 || *cpu->SP-WORDSIZE*size >= *cpu->SSP ){   
        *cpu->SP -= WORDSIZE*size;
        cpu->SPAddr = cpu->MemByte+(*cpu->SP);
        memcpy(reg, cpu->SPAddr, WORDSIZE*size);
    } else {
        //Throw interrupt.
        *cpu->RF |= E_SET;
    }
    
}

static inline void cpu_pop_data_reg(Risc256* cpu, CPUType *reg, size_t size, AddressType* stack, AddressType* stackStart, RegType** stackAddress){
    if(*stackStart == 0 || *stack - WORDSIZE * size >= *stackStart ){   
        *stack -= WORDSIZE * size;
        *stackAddress = cpu->MemByte + (*stack);
        memcpy(reg, *stackAddress, WORDSIZE * size);
    } else {
        //Throw interrupt.
        *cpu->RF |= E_SET;
    }
}

static inline void cpu_pop_sp(Risc256* cpu, CPUType *reg, size_t size){
    if(!isRing0(cpu)){
        *cpu->RF |= E_SET | A_SET;
        //Throw Interrupt;
        return;
    }
    
    cpu_pop_data_reg(cpu, reg, size, cpu->SP, cpu->SSP, &(cpu->SPAddr));
}

static inline void cpu_pop_tp(Risc256* cpu, CPUType *reg, size_t size){
    cpu_pop_data_reg(cpu, reg, size, cpu->TP, cpu->TSP, &(cpu->TPAddr));
}

// Individual POP instructions for SP (regular stack)
void cpu_pop_sp_ra(Risc256* cpu) { cpu_pop_sp(cpu, cpu->RA, WORDSIZE); }
void cpu_pop_sp_rb(Risc256* cpu) { cpu_pop_sp(cpu, cpu->RB, WORDSIZE); }
void cpu_pop_sp_rc(Risc256* cpu) { cpu_pop_sp(cpu, cpu->RC, WORDSIZE); }
void cpu_pop_sp_ri(Risc256* cpu) { cpu_pop_sp(cpu, cpu->RI, WORDSIZE); }
void cpu_pop_sp_rd(Risc256* cpu) { cpu_pop_sp(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_pop_sp_re(Risc256* cpu) { cpu_pop_sp(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_pop_sp_rr(Risc256* cpu) { cpu_pop_sp(cpu, (CPUType*)cpu->RR, ADDRSIZE); }
void cpu_pop_sp_rs(Risc256* cpu) { cpu_pop_sp(cpu, cpu->RS, WORDSIZE); }

// Individual POP instructions for TP (temporary stack)
void cpu_pop_tp_ra(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RA, WORDSIZE); }
void cpu_pop_tp_rb(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RB, WORDSIZE); }
void cpu_pop_tp_rc(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RC, WORDSIZE); }
void cpu_pop_tp_ri(Risc256* cpu) { pop_register_from_temp_stack(cpu, cpu->RI, WORDSIZE); }
void cpu_pop_tp_rd(Risc256* cpu) { pop_register_from_temp_stack(cpu, (CPUType*)cpu->RD, ADDRSIZE); }
void cpu_pop_tp_re(Risc256* cpu) { pop_register_from_temp_stack(cpu, (CPUType*)cpu->RE, ADDRSIZE); }
void cpu_pop_tp_rr(Risc256* cpu) { pop_register_from_temp_stack(cpu, (CPUType*)cpu->RR, ADDRSIZE); }

// POPALL instruction
void cpu_popall(Risc256* cpu) { cpu_pop_sp(cpu, cpu->RA, WORDSIZE*18); }
