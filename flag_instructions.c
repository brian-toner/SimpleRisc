#include "instructions.h"
#include <string.h> // For memcmp



// Function implementations
void cpu_set_t(Risc256* cpu) {
    *cpu->RS |= T_SET;
}

void cpu_clr_f(Risc256* cpu) {
    *cpu->RS &= ~T_SET;
}

void cpu_not_t(Risc256* cpu) {
    *cpu->RS ^= T_SET;
}

void cpu_logical_or(Risc256* cpu) {
    *cpu->RS |= X_SET;
}

void cpu_logical_and(Risc256* cpu) {
    *cpu->RS &= ~X_SET;
}

void cpu_logical_not(Risc256* cpu) {
    *cpu->RS ^= X_SET;
}

void cpu_disable_nmi(Risc256* cpu) {
    *cpu->RF &= ~I_SET;
}

void cpu_enable_nmi(Risc256* cpu) {
    *cpu->RF |= I_SET;
}

void cpu_setbreak(Risc256* cpu) {
    *cpu->RF |= B_SET;
}

void cpu_clrbreak(Risc256* cpu) {
    *cpu->RF &= ~B_SET;
}

void cpu_lowmem(Risc256* cpu) {
    // Check if both P0 and P1 are 0 before enabling low memory mode
    if ((*cpu->RF & P0_SET) == 0 && (*cpu->RF & P1_SET) == 0) {
        *cpu->RF |= D_SET;
    }
}

void cpu_clr_error(Risc256* cpu) {
    *cpu->RF &= ~E_SET;
}

void cpu_clrrs(Risc256* cpu) {
    *cpu->RS = 0;
}

void cpu_clr_autherror(Risc256* cpu) {
    // Check if IOPL is 0 before clearing the authorization error flag
    if ((*cpu->RF & P0_SET) == 0 && (*cpu->RF & P1_SET) == 0) {
        *cpu->RF &= ~A_SET;
    } else {
        *cpu->RF |= (E_SET | A_SET); // Set error and authorization flags if not authorized
    }
}

void cpu_is_autherror(Risc256* cpu) {
    bool condition = (*cpu->RF & A_SET) != 0;
    set_t_flag(cpu, condition);
}

void cpu_set_iopl(Risc256* cpu) {
    // Determine the number of bytes to compare based on the word size
    size_t numBytes = WORDSIZE * 16; // 16 words, each WORDSIZE bytes

    // Assuming IOPL_KEY is stored in the first 16 words of PL (PL[0] to PL[15])
    CPUType* keyAddr = cpu->PL;
    CPUType* compAddr = cpu->Mem + *cpu->RE;

    // Compute current ring based on P0 and P1
    uint8_t currentRing = ((*cpu->RF & P1_SET) >> 1) | (*cpu->RF & P0_SET);
    uint8_t newRing = ((*cpu->RR & P1_SET) >> 1) | (*cpu->RR & P0_SET);

    // Compare memory blocks and check ring levels
    if ((memcmp(keyAddr, compAddr, numBytes) == 0) || (newRing >= currentRing)) {
        *cpu->RF = (*cpu->RF & ~(P0_SET | P1_SET)) | (*cpu->RR & (P0_SET | P1_SET));
    } else {
        *cpu->RF |= (E_SET | A_SET); // Set error and authorization error flags if not authorized
    }
    memset(compAddr, 0, numBytes); // Zero out RE for security
}
