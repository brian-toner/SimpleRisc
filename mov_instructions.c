#include "CPU.h"

void cpu_mov_ra_rr(Risc256* aCPUPt) {
    memcpy(aCPUPt->vRA, aCPUPt->vRR, ADDRSIZE);
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}

void cpu_mov_rb_rr(Risc256* aCPUPt) {
    memcpy(aCPUPt->vRB, aCPUPt->vRR, ADDRSIZE);
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}

void cpu_mov_rc_rr(Risc256* aCPUPt) {
    memcpy(aCPUPt->vRC, aCPUPt->vRR, ADDRSIZE);
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}

void cpu_mov_rd_rr(Risc256* aCPUPt) {
    memcpy((CPUType*)aCPUPt->vRD, (CPUType*)aCPUPt->vRR, ADDRSIZE);
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}

void cpu_mov_re_rr(Risc256* aCPUPt) {
    memcpy((CPUType*)aCPUPt->vRE, (CPUType*)aCPUPt->vRR, ADDRSIZE);
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}

void cpu_mov_ri_rr(Risc256* aCPUPt) {
    memcpy(aCPUPt->vRI, aCPUPt->vRR, ADDRSIZE);
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}

void cpu_mov_rr_wordsize(Risc256* aCPUPt) {
    *aCPUPt->vRR = WORDSIZE;
}

void cpu_mov_re_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy((CPUType*)aCPUPt->vRE, aCPUPt->vMemByte + *aCPUPt->vRE, ADDRSIZE);
    }
}

void cpu_mov_rd_rd(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        memcpy((CPUType*)aCPUPt->vRD, aCPUPt->vMemByte + *aCPUPt->vRD, ADDRSIZE);
    }
}

void cpu_mov_ra_0(Risc256* aCPUPt) {
    memset(aCPUPt->vRA, 0, WORDSIZE);
}

void cpu_mov_rb_0(Risc256* aCPUPt) {
    memset(aCPUPt->vRB, 0, WORDSIZE);
}

void cpu_mov_rc_0(Risc256* aCPUPt) {
    memset(aCPUPt->vRC, 0, WORDSIZE);
}

void cpu_mov_rd_0(Risc256* aCPUPt) {
    memset((CPUType*)aCPUPt->vRD, 0, ADDRSIZE);
}

void cpu_mov_re_0(Risc256* aCPUPt) {
    memset((CPUType*)aCPUPt->vRE, 0, ADDRSIZE);
}

void cpu_mov_ri_0(Risc256* aCPUPt) {
    memset(aCPUPt->vRI, 0, WORDSIZE);
}

void cpu_mov_rr_0(Risc256* aCPUPt) {
    memset(aCPUPt->vRR, 0, ADDRSIZE);
}
