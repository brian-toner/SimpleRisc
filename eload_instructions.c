#include "CPU.h"

void cpu_pop_re_ra(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RA, cpu-> MemByte + *cpu->RE, WORDSIZE);
        *cpu->RE -= WORDSIZE;
    }
}

void cpu_pop_re_rb(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RB, cpu-> MemByte + *cpu->RE, WORDSIZE);
        *cpu->RE -= WORDSIZE;
    }
}

void cpu_pop_re_rc(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RC, cpu-> MemByte + *cpu->RE, WORDSIZE);
        *cpu->RE -= WORDSIZE;
    }
}

void cpu_pop_re_ri(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RI, cpu-> MemByte + *cpu->RE, WORDSIZE);
        *cpu->RE -= WORDSIZE;
    }
}

void cpu_pop_re_rd(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy((CPUType*)cpu->RD, cpu-> MemByte + *cpu->RE, ADDRSIZE);
        *cpu->RE -= ADDRSIZE;
    }
}

void cpu_pop_re_rr(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy((CPUType*)cpu->RR, cpu-> MemByte + *cpu->RE, ADDRSIZE);
        *cpu->RE -= ADDRSIZE;
    }
}

void cpu_cpy_ra_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RA, cpu-> MemByte + *cpu->RE, WORDSIZE);
    }
}

void cpu_cpy_rb_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RB, cpu-> MemByte + *cpu->RE, WORDSIZE);
    }
}

void cpu_cpy_rc_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RC, cpu-> MemByte + *cpu->RE, WORDSIZE);
    }
}

void cpu_cpy_ri_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy(cpu->RI, cpu-> MemByte + *cpu->RE, WORDSIZE);
    }
}

void cpu_cpy_rd_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy((CPUType*)cpu->RD, cpu-> MemByte + *cpu->RE, ADDRSIZE);
    }
}

void cpu_cpy_rr_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy((CPUType*)cpu->RR, cpu-> MemByte + *cpu->RE, ADDRSIZE);
    }
}

void cpu_cpy_ra_re_rr(Risc256* cpu) {
    CPUPtrType effective_addr = *cpu->RE + *cpu->RR;
    if (is_iopl_authorized(cpu, effective_addr)) {
        memcpy(cpu->RA, cpu-> MemByte + effective_addr, WORDSIZE);
    }
}

void cpu_cpy_ra_re_rr_ri(Risc256* cpu) {
    CPUPtrType effective_addr = *cpu->RE + *cpu->RR + *cpu->RI;
    if (is_iopl_authorized(cpu, effective_addr)) {
        memcpy(cpu->RA, cpu-> MemByte + effective_addr, WORDSIZE);
    }
}

void cpu_cpyblk_rd_re_rc(Risc256* cpu) {
    for (CPUPtrType i = 0; i < *cpu->RC; ++i) {
        CPUPtrType dest_addr = *cpu->RD + i;
        CPUPtrType src_addr = *cpu->RE + i;
        if (is_iopl_authorized(cpu, dest_addr) && is_iopl_authorized(cpu, src_addr)) {
            *(cpu-> MemByte + dest_addr) = *(cpu-> MemByte + src_addr);
        } else {
            break;
        }
    }
}