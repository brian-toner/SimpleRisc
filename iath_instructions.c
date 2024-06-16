#include "instructions.h"

#if 1
// 0x10
void cpu_add(Risc256* cpu){
    cpu_add_register(cpu, cpu->RA, *cpu->RB);
}

//0x11
void cpu_sub(Risc256* cpu) {
    cpu_sub_register(cpu, cpu->RA, *cpu->RB);
}

// 0x12
void cpu_mul(Risc256* cpu) {
    CPUType lVal1 = *cpu->RA;
    CPUType lVal2 = *cpu->RB;

    bool lASign = (*cpu->RA & SIGNBIT) != 0;
    bool lBSign = (*cpu->RB & SIGNBIT) != 0;

    CPUType lRet = lVal1 * lVal2;
    *cpu->RA = lRet;

    bool lSign = (lRet & SIGNBIT) != 0;

    /* Set flags */
    CPUType lRFPt = *cpu->RS & CZOS_MASK;

    lRFPt |=
        ((lRet == 0) ? (Z_SET) : (0)) | // Zero Flag
        ((lSign) ? (S_SET) : (0)) |     // Sign Flag
        (((lASign != lBSign) && lSign != lASign) ? (O_SET) : (0)); // Overflow Flag


    *cpu->RS = lRFPt;
}

// 0x13
void cpu_div(Risc256* cpu) {
    CPUType lVal1 = *cpu->RA;
    CPUType lVal2 = *cpu->RB;

    // Resetting all relevant flags initially
    *cpu->RF &= E_CLR;
    *cpu->RS &= CZOSNU_MASK;
    // Check for division by zero
    if (lVal2 == 0) {
        *cpu->RF |= E_SET; // Set Undefined Flag and Error Flag
        *cpu->RS |= U_SET;
        return;
    }

    CPUType lRet = lVal1 / lVal2;
    *cpu->RA = lRet;

    // Setting flags based on the result
    *cpu->RS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0);  // Sign Flag
}

// 0x14
void cpu_mod(Risc256* cpu) {
    CPUType lVal1 = *cpu->RA;
    CPUType lVal2 = *cpu->RB;

    // Resetting all relevant flags initially
    *cpu->RF &= E_CLR;
    *cpu->RS &= CZOSNU_MASK;

    // Check for division by zero
    if (lVal2 == 0) {
        *cpu->RF |= E_SET; // Set Undefined Flag and Error Flag
        *cpu->RS |= U_SET;
        return;
    }

    CPUType lRet = lVal1 % lVal2;
    *cpu->RA = lRet;

    // Setting flags based on the result
    *cpu->RS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0)  // Sign Flag
                 |  (cputype_is_inf(lRet) ? N_SET : 0)     // Infinity Flag
                 |  (cputype_is_nan(lRet) ? U_SET : 0);   // Undefined Flag
}


// 15 - SETB
void cpu_setb(Risc256* cpu) {
    *cpu->RA |= (1 << *cpu->RB);
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 16 - CLRB
void cpu_clrb(Risc256* cpu) {
    *cpu->RA &= ~(1 << *cpu->RB);
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}


// 17 - NOT
void cpu_not(Risc256* cpu) {
    *cpu->RA = ~(*cpu->RA);
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 18 - AND
void cpu_and(Risc256* cpu) {
    *cpu->RA &= *cpu->RB;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 19 - OR
void cpu_or(Risc256* cpu) {
    *cpu->RA |= *cpu->RB;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}


// 0x1A
void cpu_xor(Risc256* cpu) {
    *cpu->RA ^= *cpu->RB;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}


// 0x1B
void cpu_shl(Risc256* cpu) {
    CPUType lVal = *cpu->RA;
    CPUType lShift = *cpu->RB;

    // Reset the carry flag
    *cpu->RS &= C_CLR;

    // Check and set the carry flag if any of the shifted out bits are 1
    if (lVal & (WORDMASK << (WORDSIZE_BITS - lShift))) {
        *cpu->RS |= C_SET;
    }

    // Perform the left shift operation
    lVal <<= lShift;

    // Store the result back in RA
    *cpu->RA = lVal;
}

// 0x1C
void cpu_shr(Risc256* cpu) {
    CPUType lVal = *cpu->RA;
    CPUType lShift = *cpu->RB;

    // Reset the carry flag
    *cpu->RS &= C_CLR;

    // Check and set the carry flag if any of the rightmost bits that are shifted out are 1
    if (lVal & ((1 << lShift) - 1)) {
        *cpu->RS |= C_SET;
    }

    // Perform the right shift operation
    lVal >>= lShift;

    // Store the result back in RA
    *cpu->RA = lVal;
}

// 0x1D - ADC: Add with Carry
void cpu_adc(Risc256* cpu) {
    CPUType result = *cpu->RA + *cpu->RB + ((*cpu->RS & C_SET) ? 1 : 0);
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

//// 0x1E - SBB: Subtract with Borrow
void cpu_sbb(Risc256* cpu) {
    CPUType borrow = (*cpu->RS & C_SET) ? 1 : 0;
    CPUType result = *cpu->RA - *cpu->RB - borrow;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*cpu->RB + borrow > *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}


// 0x1F
void cpu_twos(Risc256* cpu) {
    // Perform Two's Complement operation on the value in RA
    CPUType lRet = ~(*cpu->RA) + 1;
    *cpu->RA = lRet;

    // Resetting relevant flags initially
    *cpu->RS &= CZOSNU_MASK;

    // Setting flags based on the result
    *cpu->RS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0); // Sign Flag

    // The Two's Complement operation doesn't generate overflow, carry, infinity or undefined results
}

#elif

// 10 - ADC: Add with Carry
void cpu_add(Risc256* cpu) {
    CPUType result = *cpu->RA + *cpu->RB;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

// 11 - SUB
void cpu_sub(Risc256* cpu) {
    CPUType result = *cpu->RA - *cpu->RB;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*cpu->RB > *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

// 12 - MUL
void cpu_mul(Risc256* cpu) {
    CPUType result = *cpu->RA * *cpu->RB;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0);
    *cpu->RA = result;
}

// 13 - DIV: Integer Division
void cpu_div(Risc256* cpu) {
    if (*cpu->RB == 0) {
        *cpu->RS |= U_SET; // Set Undefined flag
        *cpu->RF |= E_SET; // Set Error flag
        return;
    }
    CPUType result = *cpu->RA / *cpu->RB;
    *cpu->RS = (*cpu->RS & ~(Z_SET | S_SET | U_SET)) | 
                   (result == 0 ? Z_SET : 0) | 
                   ((result & SIGNBIT) ? S_SET : 0);
    *cpu->RA = result;
}

// 14 - MOD: Integer Modulus
void cpu_mod(Risc256* cpu) {
    if (*cpu->RB == 0) {
        *cpu->RS |= U_SET; // Set Undefined flag
        *cpu->RF |= E_SET; // Set Error flag
        return;
    }
    CPUType result = *cpu->RA % *cpu->RB;
    *cpu->RS = (*cpu->RS & ~(Z_SET | S_SET | U_SET)) | 
                   (result == 0 ? Z_SET : 0) | 
                   ((result & SIGNBIT) ? S_SET : 0);
    *cpu->RA = result;
}

// 15 - SETB
void cpu_setb(Risc256* cpu) {
    *cpu->RA |= (1 << *cpu->RB);
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 16 - CLRB
void cpu_clrb(Risc256* cpu) {
    *cpu->RA &= ~(1 << *cpu->RB);
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 17 - NOT
void cpu_not(Risc256* cpu) {
    *cpu->RA = ~(*cpu->RA);
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 18 - AND
void cpu_and(Risc256* cpu) {
    *cpu->RA &= *cpu->RB;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 19 - OR
void cpu_or(Risc256* cpu) {
    *cpu->RA |= *cpu->RB;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 1A - XOR
void cpu_xor(Risc256* cpu) {
    *cpu->RA ^= *cpu->RB;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 1B - SHL
void cpu_shl(Risc256* cpu) {
    *cpu->RS = (*cpu->RS & ~CZ_S_MASK) | ((*cpu->RA & (1 << (WORDSIZE_BITS - 1))) ? C_SET : 0);
    *cpu->RA <<= *cpu->RB;
    *cpu->RS |= (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 1C - SHR
void cpu_shr(Risc256* cpu) {
    *cpu->RS = (*cpu->RS & ~CZ_S_MASK) | ((*cpu->RA & 1) ? C_SET : 0);
    *cpu->RA >>= *cpu->RB;
    *cpu->RS |= (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

// 1D - ADC: Add with Carry
void cpu_adc(Risc256* cpu) {
    CPUType result = *cpu->RA + *cpu->RB + ((*cpu->RS & C_SET) ? 1 : 0);
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((result < *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

// 1E - SBB: Subtract with Borrow
void cpu_sbb(Risc256* cpu) {
    CPUType borrow = (*cpu->RS & C_SET) ? 1 : 0;
    CPUType result = *cpu->RA - *cpu->RB - borrow;
    *cpu->RS = (*cpu->RS & ~CZOS_MASK) | (result == 0 ? Z_SET : 0) | ((result & SIGNBIT) ? S_SET : 0) | ((*cpu->RB + borrow > *cpu->RA) ? C_SET : 0);
    *cpu->RA = result;
}

// 1F - TWOS
void cpu_twos(Risc256* cpu) {
    *cpu->RA = ~(*cpu->RA) + 1;
    *cpu->RS = (*cpu->RS & ~Z_S_MASK) | (*cpu->RA == 0 ? Z_SET : 0) | ((*cpu->RA & SIGNBIT) ? S_SET : 0);
}

#endif