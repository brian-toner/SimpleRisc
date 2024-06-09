#include "CPU.h"

void cpu_pop_re_ra(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRA, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
        *aCPUPt->vRE -= WORDSIZE;
    }
}

void cpu_pop_re_rb(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRB, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
        *aCPUPt->vRE -= WORDSIZE;
    }
}

void cpu_pop_re_rc(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRC, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
        *aCPUPt->vRE -= WORDSIZE;
    }
}

void cpu_pop_re_ri(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRI, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
        *aCPUPt->vRE -= WORDSIZE;
    }
}

void cpu_pop_re_rd(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy((CPUType*)aCPUPt->vRD, aCPUPt->vMemByte + *aCPUPt->vRE, ADDRSIZE);
        *aCPUPt->vRE -= ADDRSIZE;
    }
}

void cpu_pop_re_rr(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy((CPUType*)aCPUPt->vRR, aCPUPt->vMemByte + *aCPUPt->vRE, ADDRSIZE);
        *aCPUPt->vRE -= ADDRSIZE;
    }
}

void cpu_cpy_ra_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRA, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
    }
}

void cpu_cpy_rb_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRB, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
    }
}

void cpu_cpy_rc_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRC, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
    }
}

void cpu_cpy_ri_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vRI, aCPUPt->vMemByte + *aCPUPt->vRE, WORDSIZE);
    }
}

void cpu_cpy_rd_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy((CPUType*)aCPUPt->vRD, aCPUPt->vMemByte + *aCPUPt->vRE, ADDRSIZE);
    }
}

void cpu_cpy_rr_re(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy((CPUType*)aCPUPt->vRR, aCPUPt->vMemByte + *aCPUPt->vRE, ADDRSIZE);
    }
}

void cpu_cpy_ra_re_rr(Risc256* aCPUPt) {
    CPUPtrType effective_addr = *aCPUPt->vRE + *aCPUPt->vRR;
    if (is_iopl_authorized(aCPUPt, effective_addr)) {
        memcpy(aCPUPt->vRA, aCPUPt->vMemByte + effective_addr, WORDSIZE);
    }
}

void cpu_cpy_ra_re_rr_ri(Risc256* aCPUPt) {
    CPUPtrType effective_addr = *aCPUPt->vRE + *aCPUPt->vRR + *aCPUPt->vRI;
    if (is_iopl_authorized(aCPUPt, effective_addr)) {
        memcpy(aCPUPt->vRA, aCPUPt->vMemByte + effective_addr, WORDSIZE);
    }
}

void cpu_cpyblk_rd_re_rc(Risc256* aCPUPt) {
    for (CPUPtrType i = 0; i < *aCPUPt->vRC; ++i) {
        CPUPtrType dest_addr = *aCPUPt->vRD + i;
        CPUPtrType src_addr = *aCPUPt->vRE + i;
        if (is_iopl_authorized(aCPUPt, dest_addr) && is_iopl_authorized(aCPUPt, src_addr)) {
            *(aCPUPt->vMemByte + dest_addr) = *(aCPUPt->vMemByte + src_addr);
        } else {
            break;
        }
    }
}