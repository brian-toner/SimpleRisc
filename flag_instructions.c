#include "instructions.h"
#include <string.h> // For memcmp



// Function implementations
void cpu_set_t(Risc256* aCPUPt) {
    *aCPUPt->vRS |= T_SET;
}

void cpu_clr_f(Risc256* aCPUPt) {
    *aCPUPt->vRS &= ~T_SET;
}

void cpu_not_t(Risc256* aCPUPt) {
    *aCPUPt->vRS ^= T_SET;
}

void cpu_logical_or(Risc256* aCPUPt) {
    *aCPUPt->vRS |= X_SET;
}

void cpu_logical_and(Risc256* aCPUPt) {
    *aCPUPt->vRS &= ~X_SET;
}

void cpu_logical_not(Risc256* aCPUPt) {
    *aCPUPt->vRS ^= X_SET;
}

void cpu_disable_nmi(Risc256* aCPUPt) {
    *aCPUPt->vRF &= ~I_SET;
}

void cpu_enable_nmi(Risc256* aCPUPt) {
    *aCPUPt->vRF |= I_SET;
}

void cpu_setbreak(Risc256* aCPUPt) {
    *aCPUPt->vRF |= B_SET;
}

void cpu_clrbreak(Risc256* aCPUPt) {
    *aCPUPt->vRF &= ~B_SET;
}

void cpu_lowmem(Risc256* aCPUPt) {
    // Check if both P0 and P1 are 0 before enabling low memory mode
    if ((*aCPUPt->vRF & P0_SET) == 0 && (*aCPUPt->vRF & P1_SET) == 0) {
        *aCPUPt->vRF |= D_SET;
    }
}

void cpu_clr_error(Risc256* aCPUPt) {
    *aCPUPt->vRF &= ~E_SET;
}

void cpu_clrrs(Risc256* aCPUPt) {
    *aCPUPt->vRS = 0;
}

void cpu_clr_autherror(Risc256* aCPUPt) {
    // Check if IOPL is 0 before clearing the authorization error flag
    if ((*aCPUPt->vRF & P0_SET) == 0 && (*aCPUPt->vRF & P1_SET) == 0) {
        *aCPUPt->vRF &= ~A_SET;
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET); // Set error and authorization flags if not authorized
    }
}

void cpu_is_autherror(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRF & A_SET) != 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_set_iopl(Risc256* aCPUPt) {
    // Determine the number of bytes to compare based on the word size
    size_t numBytes = WORDSIZE * 16; // 16 words, each WORDSIZE bytes

    // Assuming IOPL_KEY is stored in the first 16 words of vPL (vPL[0] to vPL[15])
    CPUType* keyAddr = aCPUPt->vPL;
    CPUType* compAddr = aCPUPt->vMem + *aCPUPt->vRE;

    // Compute current ring based on P0 and P1
    uint8_t currentRing = ((*aCPUPt->vRF & P1_SET) >> 1) | (*aCPUPt->vRF & P0_SET);
    uint8_t newRing = ((*aCPUPt->vRR & P1_SET) >> 1) | (*aCPUPt->vRR & P0_SET);

    // Compare memory blocks and check ring levels
    if ((memcmp(keyAddr, compAddr, numBytes) == 0) || (newRing >= currentRing)) {
        *aCPUPt->vRF = (*aCPUPt->vRF & ~(P0_SET | P1_SET)) | (*aCPUPt->vRR & (P0_SET | P1_SET));
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET); // Set error and authorization error flags if not authorized
    }
    memset(compAddr, 0, numBytes); // Zero out RE for security
}
