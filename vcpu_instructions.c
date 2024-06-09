#include "instructions.h"

void cpu_vinit(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        // Initialize the virtual CPU at the address pointed to by RD
        memset(vCPU, 0, sizeof(Risc256));
    }
}

void cpu_vstart(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        // Start execution of the virtual CPU at the address pointed to by RD
        while (vCPU->vExec) {
            executeInstruction(vCPU); // Assuming executeInstruction is reentrant
        }
    }
}

void cpu_vstop(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        vCPU->vExec = 0; // Halt execution of the virtual CPU at the address pointed to by RD
    }
}

void cpu_vstep(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        executeInstruction(vCPU); // Execute a single instruction on the virtual CPU at the address pointed to by RD
    }
}

void cpu_vsave(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD) && is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        memcpy(aCPUPt->vMemByte + *aCPUPt->vRE, vCPU, sizeof(Risc256));
    }
}

void cpu_vload(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD) && is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        memcpy(vCPU, aCPUPt->vMemByte + *aCPUPt->vRE, sizeof(Risc256));
    }
}

void cpu_vrsave(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD) && is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        for (CPUPtrType i = 0; i < *aCPUPt->vRI; ++i) {
            memcpy((CPUType*)(vCPU->vMemByte + *aCPUPt->vRE + i), aCPUPt->vMemByte + *aCPUPt->vRE + *aCPUPt->vRR + i, WORDSIZE);
        }
    }
}

void cpu_vrload(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD) && is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        for (CPUPtrType i = 0; i < *aCPUPt->vRI; ++i) {
            memcpy(aCPUPt->vMemByte + *aCPUPt->vRE + i, (CPUType*)(vCPU->vMemByte + *aCPUPt->vRE + *aCPUPt->vRR + i), WORDSIZE);
        }
    }
}

void cpu_vbegin(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        // Push VCPU's registers to the stack
        memcpy(aCPUPt->vSPAddr, vCPU, sizeof(Risc256));
        *aCPUPt->vSP += sizeof(Risc256);
    }
}

void cpu_vend(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        // Pop VCPU's registers from the stack
        *aCPUPt->vSP -= sizeof(Risc256);
        memcpy(vCPU, aCPUPt->vSPAddr, sizeof(Risc256));
    }
}

void cpu_vrssetre(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        vCPU->vRE = aCPUPt->vRR; // Sets the virtual CPU’s RE register
    }
}

void cpu_vcopy(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD) && is_iopl_authorized(aCPUPt, *aCPUPt->vRE)) {
        Risc256* vCPUDest = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRE);
        Risc256* vCPUSrc = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        memcpy(vCPUDest, vCPUSrc, sizeof(Risc256));
    }
}

void cpu_viserror(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        if (*vCPU->vRF & E_SET) {
            *aCPUPt->vRS |= T_SET;
        } else {
            *aCPUPt->vRS &= ~T_SET;
        }
    }
}

void cpu_vishlt(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        if (*vCPU->vRF & H_SET) {
            *aCPUPt->vRS |= T_SET;
        } else {
            *aCPUPt->vRS &= ~T_SET;
        }
    }
}

void cpu_vswinterrupt(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        // Send software interrupt to the virtual CPU
        // Assuming a function handle_interrupt is defined
        //handle_interrupt(vCPU, SOFTWARE_INTERRUPT);
    }
}

void cpu_vhwinterrupt(Risc256* aCPUPt) {
    if (is_iopl_authorized(aCPUPt, *aCPUPt->vRD)) {
        Risc256* vCPU = (Risc256*)(aCPUPt->vMemByte + *aCPUPt->vRD);
        // Send hardware interrupt to the virtual CPU
        // Assuming a function handle_interrupt is defined
        //handle_interrupt(vCPU, HARDWARE_INTERRUPT);
    }
}


