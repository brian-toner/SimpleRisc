#include "instructions.h"

void cpu_vinit(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        // Initialize the virtual CPU at the address pointed to by RD
        memset(vCPU, 0, sizeof(Risc256));
    }
}

void cpu_start(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        // Start execution of the virtual CPU at the address pointed to by RD
        while (vCPU->Exec) {
            executeInstruction(vCPU); // Assuming executeInstruction is reentrant
        }
    }
}

void cpu_stop(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        vCPU->Exec = 0; // Halt execution of the virtual CPU at the address pointed to by RD
    }
}

void cpu_step(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        executeInstruction(vCPU); // Execute a single instruction on the virtual CPU at the address pointed to by RD
    }
}

void cpu_save(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD) && is_iopl_authorized(cpu, *cpu->RE)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        memcpy(cpu-> MemByte + *cpu->RE, vCPU, sizeof(Risc256));
    }
}

void cpu_vload(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD) && is_iopl_authorized(cpu, *cpu->RE)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        memcpy(vCPU, cpu-> MemByte + *cpu->RE, sizeof(Risc256));
    }
}

void cpu_RSave(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD) && is_iopl_authorized(cpu, *cpu->RE)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        for (CPUPtrType i = 0; i < *cpu->RI; ++i) {
            memcpy((CPUType*)(vCPU-> MemByte + *cpu->RE + i), cpu-> MemByte + *cpu->RE + *cpu->RR + i, WORDSIZE);
        }
    }
}

void cpu_vrload(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD) && is_iopl_authorized(cpu, *cpu->RE)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        for (CPUPtrType i = 0; i < *cpu->RI; ++i) {
            memcpy(cpu-> MemByte + *cpu->RE + i, (CPUType*)(vCPU-> MemByte + *cpu->RE + *cpu->RR + i), WORDSIZE);
        }
    }
}

void cpu_vbegin(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        // Push VCPU's registers to the stack
        memcpy(cpu->SPAddr, vCPU, sizeof(Risc256));
        *cpu->SP += sizeof(Risc256);
    }
}

void cpu_vend(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        // Pop VCPU's registers from the stack
        *cpu->SP -= sizeof(Risc256);
        memcpy(vCPU, cpu->SPAddr, sizeof(Risc256));
    }
}

void cpu_RSsetre(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        vCPU->RE = cpu->RR; // Sets the virtual CPU’s RE register
    }
}

void cpu_vcopy(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD) && is_iopl_authorized(cpu, *cpu->RE)) {
        Risc256* vCPUDest = (Risc256*)(cpu-> MemByte + *cpu->RE);
        Risc256* vCPUSrc = (Risc256*)(cpu-> MemByte + *cpu->RD);
        memcpy(vCPUDest, vCPUSrc, sizeof(Risc256));
    }
}

void cpu_viserror(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        if (*vCPU->RF & E_SET) {
            *cpu->RS |= T_SET;
        } else {
            *cpu->RS &= ~T_SET;
        }
    }
}

void cpu_vishlt(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        if (*vCPU->RF & H_SET) {
            *cpu->RS |= T_SET;
        } else {
            *cpu->RS &= ~T_SET;
        }
    }
}

void cpu_SWInterrupt(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        // Send software interrupt to the virtual CPU
        // Assuming a function handle_interrupt is defined
        //handle_interrupt(vCPU, SOFTWARE_INTERRUPT);
    }
}

void cpu_HWInterrupt(Risc256* cpu) {
    if (is_iopl_authorized(cpu, *cpu->RD)) {
        Risc256* vCPU = (Risc256*)(cpu-> MemByte + *cpu->RD);
        // Send hardware interrupt to the virtual CPU
        // Assuming a function handle_interrupt is defined
        //handle_interrupt(vCPU, HARDWARE_INTERRUPT);
    }
}


