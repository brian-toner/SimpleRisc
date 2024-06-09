#include "CPU.h"

void cpu_push_re_ra(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRA, WORDSIZE);
        *aCPUPt->vRE += WORDSIZE;
    }
}

void cpu_push_re_rb(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRB, WORDSIZE);
        *aCPUPt->vRE += WORDSIZE;
    }
}

void cpu_push_re_rc(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRC, WORDSIZE);
        *aCPUPt->vRE += WORDSIZE;
    }
}

void cpu_push_re_ri(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRI, WORDSIZE);
        *aCPUPt->vRE += WORDSIZE;
    }
}

void cpu_push_re_rd(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, (CPUType*)aCPUPt->vRD, ADDRSIZE);
        *aCPUPt->vRE += ADDRSIZE;
    }
}

void cpu_push_re_rr(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, (CPUType*)aCPUPt->vRR, ADDRSIZE);
        *aCPUPt->vRE += ADDRSIZE;
    }
}

void cpu_cpy_re_ra(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRA, WORDSIZE);
    }
}

void cpu_cpy_re_rb(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRB, WORDSIZE);
    }
}

void cpu_cpy_re_rc(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRC, WORDSIZE);
    }
}

void cpu_cpy_re_ri(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, aCPUPt->vRI, WORDSIZE);
    }
}

void cpu_cpy_re_rd(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, (CPUType*)aCPUPt->vRD, ADDRSIZE);
    }
}

void cpu_cpy_re_rr(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, (CPUType*)aCPUPt->vRR, ADDRSIZE);
    }
}

void cpu_cpy_re_rr_ra(Risc256* aCPUPt) {
    CPUPtrType effective_addr = *aCPUPt->vRE + *aCPUPt->vRR;
    if (is_iopl_authorized(aCPUPt, effective_addr)) {
        memcpy(aCPUPt->vMemByte + effective_addr, aCPUPt->vRA, WORDSIZE);
    }
}

void cpu_cpy_re_rr_ri_ra(Risc256* aCPUPt) {
    CPUPtrType effective_addr = *aCPUPt->vRE + *aCPUPt->vRR + *aCPUPt->vRI;
    if (is_iopl_authorized(aCPUPt, effective_addr)) {
        memcpy(aCPUPt->vMemByte + effective_addr, aCPUPt->vRA, WORDSIZE);
    }
}

void cpu_cpyblk_re_rd_rc(Risc256* aCPUPt) {
    for (CPUPtrType i = 0; i < *aCPUPt->vRC; ++i) {
        CPUPtrType dest_addr = *aCPUPt->vRE + i;
        CPUPtrType src_addr = *aCPUPt->vRD + i;
        if (is_iopl_authorized(aCPUPt, dest_addr) && is_iopl_authorized(aCPUPt, src_addr)) {
            *(aCPUPt->vMemByte + dest_addr) = *(aCPUPt->vMemByte + src_addr);
        } else {
            break;
        }
    }
}