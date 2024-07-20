#include "instructions.h"

static inline void cpu_psh_re_data(Risc256* cpu, CPUType* reg, size_t size, bool incrment){
    // Check ring permissions
    if(getRing(cpu) < getRingFromAddress(cpu, *cpu->RE)){
        *cpu->RF |= E_SET | A_SET;
        //Throw interrupt
        return;
    }
    
    // Check memory boundary and copy data
    if(*cpu->RE + WORDSIZE*size <= cpu->MemSize ){  
        CPUType* REAddr = cpu->MemByte+(*cpu->RE);
        memcpy(REAddr, reg, WORDSIZE*size);
        *cpu->RE += WORDSIZE * size * (incrment?1:0);
    } else {
        //Throw interrupt.
        *cpu->RF |= E_SET;
    }
        
}




void cpu_push_re_ra(Risc256* cpu) { cpu_psh_re_data(cpu, cpu->RA, WORDSIZE, true); }
void cpu_push_re_rb(Risc256* cpu) { cpu_psh_re_data(cpu, cpu->RB, WORDSIZE, true); }
void cpu_push_re_rc(Risc256* cpu) { cpu_psh_re_data(cpu, cpu->RC, WORDSIZE, true); }
void cpu_push_re_ri(Risc256* cpu) { cpu_psh_re_data(cpu, cpu->RI, WORDSIZE, true); }
void cpu_push_re_rd(Risc256* cpu) { cpu_psh_re_data(cpu, (CPUType*)cpu->RD, ADDRSIZE, true); }
void cpu_push_re_rr(Risc256* cpu) { cpu_psh_re_data(cpu, (CPUType*)cpu->RR, ADDRSIZE, true); }


void cpu_cpy_re_ra(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu-> MemByte + *cpu->RE, cpu->RA, WORDSIZE);
    }
}

void cpu_cpy_re_rb(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu-> MemByte + *cpu->RE, cpu->RB, WORDSIZE);
    }
}

void cpu_cpy_re_rc(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu-> MemByte + *cpu->RE, cpu->RC, WORDSIZE);
    }
}

void cpu_cpy_re_ri(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu-> MemByte + *cpu->RE, cpu->RI, WORDSIZE);
    }
}

void cpu_cpy_re_rd(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu-> MemByte + *cpu->RE, (CPUType*)cpu->RD, ADDRSIZE);
    }
}

void cpu_cpy_re_rr(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu-> MemByte + *cpu->RE, (CPUType*)cpu->RR, ADDRSIZE);
    }
}

void cpu_cpy_re_rr_ra(Risc256* cpu) {
    CPUPtrType effective_addr = *cpu->RE + *cpu->RR;
    if (is_iopl_authorized(cpu, effective_addr)) {
        memcpy(cpu-> MemByte + effective_addr, cpu->RA, WORDSIZE);
    }
}

void cpu_cpy_re_rr_ri_ra(Risc256* cpu) {
    CPUPtrType effective_addr = *cpu->RE + *cpu->RR + *cpu->RI;
    if (is_iopl_authorized(cpu, effective_addr)) {
        memcpy(cpu-> MemByte + effective_addr, cpu->RA, WORDSIZE);
    }
}

void cpu_cpyblk_re_rd_rc(Risc256* cpu) {
    for (CPUPtrType i = 0; i < *cpu->RC; ++i) {
        CPUPtrType dest_addr = *cpu->RE + i;
        CPUPtrType src_addr = *cpu->RD + i;
        if (is_iopl_authorized(cpu, dest_addr) && is_iopl_authorized(cpu, src_addr)) {
            *(cpu-> MemByte + dest_addr) = *(cpu-> MemByte + src_addr);
        } else {
            break;
        }
    }
}