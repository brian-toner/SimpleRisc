#include "instructions.h"

#if 1
// 0x10
void cpu_add(Risc256* cpu){
    cpu_add_register(cpu, cpu->vRA, *cpu->vRB);
}

//0x11
void cpu_sub(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->vRA, *cpu->vRB);
}

// 0x12
void cpu_mul(Risc256* aCPUPt) {
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    bool lASign = (*aCPUPt->vRA & SIGNBIT) != 0;
    bool lBSign = (*aCPUPt->vRB & SIGNBIT) != 0;

    CPUType lRet = lVal1 * lVal2;
    *aCPUPt->vRA = lRet;

    bool lSign = (lRet & SIGNBIT) != 0;

    /* Set flags */
    CPUType lRFPt = *aCPUPt->vRS & CZOS_MASK;

    lRFPt |=
        ((lRet == 0) ? (Z_SET) : (0)) | // Zero Flag
        ((lSign) ? (S_SET) : (0)) |     // Sign Flag
        (((lASign != lBSign) && lSign != lASign) ? (O_SET) : (0)); // Overflow Flag


    *aCPUPt->vRS = lRFPt;
}

// 0x13
void cpu_div(Risc256* aCPUPt) {
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    // Resetting all relevant flags initially
    *aCPUPt->vRF &= E_CLR;
    *aCPUPt->vRS &= CZOSNU_MASK;
    // Check for division by zero
    if (lVal2 == 0) {
        *aCPUPt->vRF |= E_SET; // Set Undefined Flag and Error Flag
        *aCPUPt->vRS |= U_SET;
        return;
    }

    CPUType lRet = lVal1 / lVal2;
    *aCPUPt->vRA = lRet;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0);  // Sign Flag
}

// 0x14
void cpu_mod(Risc256* aCPUPt) {
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    // Resetting all relevant flags initially
    *aCPUPt->vRF &= E_CLR;
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Check for division by zero
    if (lVal2 == 0) {
        *aCPUPt->vRF |= E_SET; // Set Undefined Flag and Error Flag
        *aCPUPt->vRS |= U_SET;
        return;
    }

    CPUType lRet = lVal1 % lVal2;
    *aCPUPt->vRA = lRet;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0)  // Sign Flag
                 |  (cputype_is_inf(lRet) ? N_SET : 0)     // Infinity Flag
                 |  (cputype_is_nan(lRet) ? U_SET : 0);   // Undefined Flag
}


// 15 - SETB
void cpu_setb(Risc256* aCPUPt) {
    *aCPUPt->vRA |= (1 << *aCPUPt->vRB);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 16 - CLRB
void cpu_clrb(Risc256* aCPUPt) {
    *aCPUPt->vRA &= ~(1 << *aCPUPt->vRB);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}


// 17 - NOT
void cpu_not(Risc256* aCPUPt) {
    *aCPUPt->vRA = ~(*aCPUPt->vRA);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 18 - AND
void cpu_and(Risc256* aCPUPt) {
    *aCPUPt->vRA &= *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 19 - OR
void cpu_or(Risc256* aCPUPt) {
    *aCPUPt->vRA |= *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}


// 0x1A
void cpu_xor(Risc256* aCPUPt) {
    *aCPUPt->vRA ^= *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}


// 0x1B
void cpu_shl(Risc256* aCPUPt) {
    CPUType lVal = *aCPUPt->vRA;
    CPUType lShift = *aCPUPt->vRB;

    // Reset the carry flag
    *aCPUPt->vRS &= C_CLR;

    // Check and set the carry flag if any of the shifted out bits are 1
    if (lVal & (WORDMASK << (WORDSIZE_BITS - lShift))) {
        *aCPUPt->vRS |= C_SET;
    }

    // Perform the left shift operation
    lVal <<= lShift;

    // Store the result back in RA
    *aCPUPt->vRA = lVal;
}

// 0x1C
void cpu_shr(Risc256* aCPUPt) {
    CPUType lVal = *aCPUPt->vRA;
    CPUType lShift = *aCPUPt->vRB;

    // Reset the carry flag
    *aCPUPt->vRS &= C_CLR;

    // Check and set the carry flag if any of the rightmost bits that are shifted out are 1
    if (lVal & ((1 << lShift) - 1)) {
        *aCPUPt->vRS |= C_SET;
    }

    // Perform the right shift operation
    lVal >>= lShift;

    // Store the result back in RA
    *aCPUPt->vRA = lVal;
}

// 0x1D - ADC: Add with Carry
void cpu_adc(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA + *aCPUPt->vRB + ((*aCPUPt->vRS & C_SET) ? 1 : 0);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

//// 0x1E - SBB: Subtract with Borrow
void cpu_sbb(Risc256* aCPUPt) {
    CPUType borrow = (*aCPUPt->vRS & C_SET) ? 1 : 0;
    CPUType result = *aCPUPt->vRA - *aCPUPt->vRB - borrow;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRB + borrow > *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}


// 0x1F
void cpu_twos(Risc256* aCPUPt) {
    // Perform Two's Complement operation on the value in RA
    CPUType lRet = ~(*aCPUPt->vRA) + 1;
    *aCPUPt->vRA = lRet;

    // Resetting relevant flags initially
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0); // Sign Flag

    // The Two's Complement operation doesn't generate overflow, carry, infinity or undefined results
}

#elif

// 10 - ADC: Add with Carry
void cpu_add(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA + *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

// 11 - SUB
void cpu_sub(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA - *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRB > *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

// 12 - MUL
void cpu_mul(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA * *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0);
    *aCPUPt->vRA = result;
}

// 13 - DIV: Integer Division
void cpu_div(Risc256* aCPUPt) {
    if (*aCPUPt->vRB == 0) {
        *aCPUPt->vRS |= U_SET; // Set Undefined flag
        *aCPUPt->vRF |= E_SET; // Set Error flag
        return;
    }
    CPUType result = *aCPUPt->vRA / *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~(Z_SET | S_SET | U_SET)) | 
                   (result == 0 ? Z_SET : 0) | 
                   ((result & SIGNBIT) ? S_SET : 0);
    *aCPUPt->vRA = result;
}

// 14 - MOD: Integer Modulus
void cpu_mod(Risc256* aCPUPt) {
    if (*aCPUPt->vRB == 0) {
        *aCPUPt->vRS |= U_SET; // Set Undefined flag
        *aCPUPt->vRF |= E_SET; // Set Error flag
        return;
    }
    CPUType result = *aCPUPt->vRA % *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~(Z_SET | S_SET | U_SET)) | 
                   (result == 0 ? Z_SET : 0) | 
                   ((result & SIGNBIT) ? S_SET : 0);
    *aCPUPt->vRA = result;
}

// 15 - SETB
void cpu_setb(Risc256* aCPUPt) {
    *aCPUPt->vRA |= (1 << *aCPUPt->vRB);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 16 - CLRB
void cpu_clrb(Risc256* aCPUPt) {
    *aCPUPt->vRA &= ~(1 << *aCPUPt->vRB);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 17 - NOT
void cpu_not(Risc256* aCPUPt) {
    *aCPUPt->vRA = ~(*aCPUPt->vRA);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 18 - AND
void cpu_and(Risc256* aCPUPt) {
    *aCPUPt->vRA &= *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 19 - OR
void cpu_or(Risc256* aCPUPt) {
    *aCPUPt->vRA |= *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 1A - XOR
void cpu_xor(Risc256* aCPUPt) {
    *aCPUPt->vRA ^= *aCPUPt->vRB;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 1B - SHL
void cpu_shl(Risc256* aCPUPt) {
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZ_S_MASK) | ((*aCPUPt->vRA & (1 << (WORDSIZE_BITS - 1))) ? C_SET : 0);
    *aCPUPt->vRA <<= *aCPUPt->vRB;
    *aCPUPt->vRS |= (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 1C - SHR
void cpu_shr(Risc256* aCPUPt) {
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZ_S_MASK) | ((*aCPUPt->vRA & 1) ? C_SET : 0);
    *aCPUPt->vRA >>= *aCPUPt->vRB;
    *aCPUPt->vRS |= (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

// 1D - ADC: Add with Carry
void cpu_adc(Risc256* aCPUPt) {
    CPUType result = *aCPUPt->vRA + *aCPUPt->vRB + ((*aCPUPt->vRS & C_SET) ? 1 : 0);
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

// 1E - SBB: Subtract with Borrow
void cpu_sbb(Risc256* aCPUPt) {
    CPUType borrow = (*aCPUPt->vRS & C_SET) ? 1 : 0;
    CPUType result = *aCPUPt->vRA - *aCPUPt->vRB - borrow;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*aCPUPt->vRB + borrow > *aCPUPt->vRA) ? C_SET : 0);
    *aCPUPt->vRA = result;
}

// 1F - TWOS
void cpu_twos(Risc256* aCPUPt) {
    *aCPUPt->vRA = ~(*aCPUPt->vRA) + 1;
    *aCPUPt->vRS = (*aCPUPt->vRS & ~Z_S_MASK) | (*aCPUPt->vRA == 0 ? Z_SET : 0) | ((*aCPUPt->vRA & SIGNBIT) ? S_SET : 0);
}

#endif