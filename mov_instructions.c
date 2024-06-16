#include "CPU.h"

void cpu_mov_ra_rr(Risc256* cpu) {
    memcpy(cpu->RA, cpu->RR, ADDRSIZE);
    memset(cpu->RR, 0, ADDRSIZE);
}

void cpu_mov_rb_rr(Risc256* cpu) {
    memcpy(cpu->RB, cpu->RR, ADDRSIZE);
    memset(cpu->RR, 0, ADDRSIZE);
}

void cpu_mov_rc_rr(Risc256* cpu) {
    memcpy(cpu->RC, cpu->RR, ADDRSIZE);
    memset(cpu->RR, 0, ADDRSIZE);
}

void cpu_mov_rd_rr(Risc256* cpu) {
    memcpy((CPUType*)cpu->RD, (CPUType*)cpu->RR, ADDRSIZE);
    memset(cpu->RR, 0, ADDRSIZE);
}

void cpu_mov_re_rr(Risc256* cpu) {
    memcpy((CPUType*)cpu->RE, (CPUType*)cpu->RR, ADDRSIZE);
    memset(cpu->RR, 0, ADDRSIZE);
}

void cpu_mov_ri_rr(Risc256* cpu) {
    memcpy(cpu->RI, cpu->RR, ADDRSIZE);
    memset(cpu->RR, 0, ADDRSIZE);
}

void cpu_mov_rr_wordsize(Risc256* cpu) {
    *cpu->RR = WORDSIZE;
}

void cpu_mov_re_re(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RE)) {
        memcpy((CPUType*)cpu->RE, cpu-> MemByte + *cpu->RE, ADDRSIZE);
    }
}

void cpu_mov_rd_rd(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        memcpy((CPUType*)cpu->RD, cpu-> MemByte + *cpu->RD, ADDRSIZE);
    }
}

void cpu_mov_ra_0(Risc256* cpu) {
    memset(cpu->RA, 0, WORDSIZE);
}

void cpu_mov_rb_0(Risc256* cpu) {
    memset(cpu->RB, 0, WORDSIZE);
}

void cpu_mov_rc_0(Risc256* cpu) {
    memset(cpu->RC, 0, WORDSIZE);
}

void cpu_mov_rd_0(Risc256* cpu) {
    memset((CPUType*)cpu->RD, 0, ADDRSIZE);
}

void cpu_mov_re_0(Risc256* cpu) {
    memset((CPUType*)cpu->RE, 0, ADDRSIZE);
}

void cpu_mov_ri_0(Risc256* cpu) {
    memset(cpu->RI, 0, WORDSIZE);
}

void cpu_mov_rr_0(Risc256* cpu) {
    memset(cpu->RR, 0, ADDRSIZE);
}
