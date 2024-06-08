/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "CPU.h"
#include "instructions.h"
#include <string.h>
#include <math.h>
//#include <c++/10/complex>
//#define _GLIBCXX_COMPLEX 0

void cpu_set_addr(Risc256* aCPUPt){
    aCPUPt->vRDAddr = aCPUPt->vMemByte+(*aCPUPt->vRD);
    aCPUPt->vREAddr = aCPUPt->vMemByte+(*aCPUPt->vRE);
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);

}

double logbn(double a, double b){
    return log(a)/log(b);
}

#if WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv){

        CPUFloat lRet = mini_to_float(aConv);
        return lRet;
    }

    CPUType float_to_cputype(CPUFloat aConv){
        CPUType lRet = float_to_mini(aConv);
        return lRet;
    }
    
    bool cputype_is_nan(CPUType aConv){
        return isNan(aConv);
    }
    
    bool cputype_is_inf(CPUType aConv){
        return isInf(aConv);
    }
#elif WORDSIZE==2
    float cputype_to_float(CPUType aConv){

        float lRet = half_to_float(aConv);
        return lRet;
    }

    CPUType float_to_cputype(float aConv){
        CPUType lRet = half_from_float(*(uint32_t*)(&aConv) );
        return lRet;
    }
    
    
#elif WORDSIZE==4
    double cputype_to_float(CPUType aConv){

        float lRet = *(float*)(&aConv);
        return lRet;
    }

    CPUType float_to_cputype(float aConv){
        CPUType lRet = *(CPUType*)(&aConv);
        return lRet;
    }
#elif WORDSIZE==8
    double cputype_to_float(CPUType aConv){

        double lRet = *(double*)(&aConv);
        return lRet;
    }

    CPUType float_to_cputype(double aConv){
        CPUType lRet = *(CPUType*)(&aConv);
        return lRet;
    }    
#endif



void cpu_qstf(Risc256* aCPUPt){
    
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    CPUFloat lFVal = atof(lBuff);
    CPUType lVal = float_to_cputype(lFVal);
    *aCPUPt->vRA = lVal;
    
}

void cpu_qsti(Risc256* aCPUPt){
    
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    *aCPUPt->vRA  = atoi(lBuff);
    
}



void cpu_addc(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
    bool lBSign = (*aCPUPt->vRB & SIGNBIT)!=0;

    CPUType lRet = lVal1+lVal2;
    
    
    //Add with carry if we want to implement that
    if( (*aCPUPt->vRS*C_SET)!=0 ){
        lRet+=1;
    }
    *aCPUPt->vRA = lRet;

    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(
                Z_SET
            ):(
                0
            )) | 
            
        ((lSign)?(
                S_SET
            ):(
                0
            )) |
            
        ((lASign == lBSign && lSign != lASign)?(
                O_SET
            ):(
                0
            )) |
            
        ((lVal2 > lRet)?(
                C_SET
            ):(
                0
            )));

    *aCPUPt->vRS = lRFPt;
            
}

void cpu_subb(Risc256* aCPUPt){
    
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
    bool lBSign = (*aCPUPt->vRB & SIGNBIT)!=0;

    CPUType lRet = lVal1-lVal2;
    
    
    //Add with carry if we want to implement that
    if( (*aCPUPt->vRS*C_SET)!=0 ){
        lRet-=1;
    }
    *aCPUPt->vRA = lRet;

    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lASign == lBSign && lSign != lASign)?(O_SET):(0)) |
        ((lVal2 > lRet)?(C_SET):(0)));

    *aCPUPt->vRS = lRFPt;
    

}


void cpu_nop(Risc256* aCPUPt){
    return;
}


void cpu_qadd(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)+(*aCPUPt->vRB);
}

void cpu_qsub(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)-(*aCPUPt->vRB);
}

void cpu_qmul(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)*(*aCPUPt->vRB);
}

void cpu_qdiv(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)/(*aCPUPt->vRB);
}

void cpu_qmod(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)%(*aCPUPt->vRB);
}

void cpu_stb(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)|(1<<(*aCPUPt->vRB));
}

void cpu_clb(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)&(~(1<<(*aCPUPt->vRB)));
}

void cpu_qnot(Risc256* aCPUPt){
    *aCPUPt->vRA = ~(*aCPUPt->vRA);
}

void cpu_qand(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)&(*aCPUPt->vRB);
}

void cpu_qor(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)|(*aCPUPt->vRB);
}

void cpu_qxor(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)^(*aCPUPt->vRB);
}

void cpu_qshl(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)<<(*aCPUPt->vRB);
}

void cpu_qshr(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)>>(*aCPUPt->vRB);
}

//=========================================================//
// 0x00
void cpu_set(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | ( *(aCPUPt->vMemByte+*aCPUPt->vPC) & 0x0F);
}

void cpu_set_0(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x00;
}

void cpu_set_1(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x01;
}

void cpu_set_2(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x02;
}

void cpu_set_3(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x03;
}

void cpu_set_4(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x04;
}

void cpu_set_5(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x05;
}

void cpu_set_6(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x06;
}

void cpu_set_7(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x07;
}

void cpu_set_8(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x08;
}

void cpu_set_9(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x09;
}

void cpu_set_A(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x0A;
}

void cpu_set_B(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x0B;
}

void cpu_set_C(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x0C;
}

void cpu_set_D(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x0D;
}

void cpu_set_E(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x0E;
}

void cpu_set_F(Risc256* aCPUPt) {
    *aCPUPt->vRR = (*aCPUPt->vRR << 4) | 0x0F;
}


//=========================================================//
// 0x1X

// 0x10
void cpu_add(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
    bool lBSign = (*aCPUPt->vRB & SIGNBIT)!=0;

    CPUType lRet = lVal1+lVal2;
    *aCPUPt->vRA = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    // Set the flags based on the result
    lRFPt |= 
        ((lRet == 0) ? Z_SET : 0) | // Zero flag
        (lSign ? S_SET : 0) | // Sign flag
        ((lASign == lBSign && lSign != lASign) ? O_SET : 0) | // Overflow flag
        ((lRet < lVal1) ? C_SET : 0); // Carry flag (unsigned overflow)

    *aCPUPt->vRS = lRFPt;
            
}

//0x11
void cpu_sub(Risc256* aCPUPt) {
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    bool lASign = (lVal1 & SIGNBIT) != 0;
    bool lBSign = (lVal2 & SIGNBIT) != 0;

    CPUType lRet = lVal1 - lVal2;
    *aCPUPt->vRA = lRet;

    bool lSign = (lRet & SIGNBIT) != 0;

    /* Set flags */
    CPUType lRFPt = *aCPUPt->vRS & CZOS_MASK;

    lRFPt |= 
        ((lRet == 0 ? Z_SET : 0) | 
         (lSign ? S_SET : 0) |
         (lASign != lBSign && lSign != lASign ? O_SET : 0) |  // Adjusted overflow condition
         (lVal1 < lVal2 ? C_SET : 0));  // Correct carry flag calculation

    *aCPUPt->vRS = lRFPt;
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
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0)  // Sign Flag
                 |  (cputype_is_inf(lRet) ? N_SET : 0)     // Infinity Flag
                 |  (cputype_is_nan(lRet) ? U_SET : 0);   // Undefined Flag
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


// 0x15
void cpu_setbit(Risc256* aCPUPt) {
    CPUType bitPosition = *aCPUPt->vRB;
    *aCPUPt->vRA |= (ONEBIT << bitPosition);
}

// 0x16
void cpu_clrtbit(Risc256* aCPUPt) {
    CPUType bitPosition = *aCPUPt->vRB;
    *aCPUPt->vRA &= (ONEBIT << bitPosition);
}

// 0x17
void cpu_not(Risc256* aCPUPt) {
    // Perform bitwise NOT operation on the value in RA
    CPUType lRet = ~(*aCPUPt->vRA);
    *aCPUPt->vRA = lRet;

    // Resetting relevant flags initially
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0); // Sign Flag

    // The Not operation doesn't generate overflow, carry, infinity or undefined results
}

// 0x18
void cpu_and(Risc256* aCPUPt){
    
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    CPUType lRet = lVal1&lVal2;
    
    // Resetting relevant flags initially
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0); // Sign Flag


}

// 0x19
void cpu_or(Risc256* aCPUPt){
    
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    CPUType lRet = lVal1&lVal2;
    
    // Resetting relevant flags initially
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0); // Sign Flag

}

// 0x1A
void cpu_xor(Risc256* aCPUPt){
    
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRB;

    CPUType lRet = lVal1&lVal2;
    
    // Resetting relevant flags initially
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Setting flags based on the result
    *aCPUPt->vRS |= ((lRet == 0) ? Z_SET : 0)          // Zero Flag
                 |  (((lRet & SIGNBIT) != 0) ? S_SET : 0); // Sign Flag

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


//=========================================================//
// 0x2X


// 0x20
void cpu_qfadd(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d+lVal2d;
    *aCPUPt->vRA = float_to_cputype(lRet);

    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x21
void cpu_qfsub(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d-lVal2d;
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x22
void cpu_qfmul(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d*lVal2d;
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x23
void cpu_qfdiv(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d/lVal2d;
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}




// 0x24
void cpu_qflogbn(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);

    double lRet = logbn(lVal1d,lVal2d);
    *aCPUPt->vRA = float_to_cputype(lRet);

    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
    
}


// 0x25
void cpu_fexp(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    CPUFloat lVal1d = cputype_to_float(lVal1);
    CPUFloat lVal2d = cputype_to_float(lVal2);
    
    CPUFloat lRet = pow(lVal1d,lVal2d);
    
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

void cpu_qpi(Risc256* aCPUPt){
    *aCPUPt->vRB = float_to_cputype(M_PI);
}

void cpu_qe(Risc256* aCPUPt){
    *aCPUPt->vRB = float_to_cputype(M_E);
}

// 0x26
void cpu_qsin(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = sin(lVal1d);
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x27
void cpu_qcos(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = cos(lVal1d);
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x28
void cpu_qtan(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = tan(lVal1d);
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x29
void cpu_qasin(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = asin(lVal1d);
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x2A
void cpu_qacos(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = acos(lVal1d);
    *aCPUPt->vRA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x2B
void cpu_qatan2(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);

    double lRet = atan2(lVal1d,lVal2d);

    // Reset relevant flags
    *aCPUPt->vRS &= CZOSNU_MASK;

    // Set flags based on the result
    *aCPUPt->vRS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}


// 0x2C
void cpu_its(Risc256* aCPUPt){
    //int to string
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    sprintf(lBuff,"%d", (CPUSWord)*aCPUPt->vRA);
    
}

void cpu_uits(Risc256* aCPUPt){
    
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    sprintf(lBuff,"%d", (CPUType)*aCPUPt->vRA);
    
}

// 0x2D
void cpu_itf(Risc256* aCPUPt){  
    //int to float
    *aCPUPt->vRA = float_to_cputype((CPUSWord)*aCPUPt->vRA);
}

void cpu_uitf(Risc256* aCPUPt){    
    *aCPUPt->vRA = float_to_cputype(*aCPUPt->vRA);
}

// 0x2E
void cpu_qfts(Risc256* aCPUPt){
    
    //char* lBuff = (char*)aCPUPt->vREAddr;
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    CPUFloat lVal1 = cputype_to_float(*aCPUPt->vRA);
    sprintf(lBuff,"%g", lVal1);    
    
}

// 0x2F
void cpu_qfti(Risc256* aCPUPt){
    
    CPUFloat lFRet = cputype_to_float(*aCPUPt->vRA);
    CPUType lRet = lFRet;
    *aCPUPt->vRA = lRet;

}


//=========================================================//
// 0x01



//
//void cpu_qsin(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*sin(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qcos(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*cos(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qtan(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*tan(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qasin(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*asin(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qacos(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*acos(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qatan2(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = atan2(lVal1d,lVal2d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}

//=========================================================//
// 0x3 - INC


void cpu_inc_ra(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRA;

    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;

    CPUType lRet = lVal1+1;
    *aCPUPt->vRA = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET|C_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lSign != lASign)?(O_SET):(0)));

    *aCPUPt->vRS = lRFPt;
            
}

void cpu_inc_rb(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRB;

    bool lASign = (*aCPUPt->vRB & SIGNBIT)!=0;

    CPUType lRet = lVal1+1;
    *aCPUPt->vRB = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET|C_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lSign != lASign)?(O_SET):(0)));

    *aCPUPt->vRS = lRFPt;
            
}

void cpu_inc_rc(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRC;

    bool lASign = (*aCPUPt->vRC & SIGNBIT)!=0;

    CPUType lRet = lVal1+1;
    *aCPUPt->vRC = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET|C_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lSign != lASign)?(O_SET):(0)));

    *aCPUPt->vRS = lRFPt;
            
}


void cpu_inc_ri(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRI;

    bool lASign = (*aCPUPt->vRI & SIGNBIT)!=0;

    CPUType lRet = lVal1+1;
    *aCPUPt->vRI = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET|C_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lSign != lASign)?(O_SET):(0)));

    *aCPUPt->vRS = lRFPt;
            
}

void cpu_inci(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRA;
    CPUType lVal2 = *aCPUPt->vRI;

    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
    bool lBSign = (*aCPUPt->vRI & SIGNBIT)!=0;

    CPUType lRet = lVal1+lVal2;
    *aCPUPt->vRA = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lASign == lBSign && lSign != lASign)?(O_SET):(0)) |
        ((lVal2 > lRet)?(C_SET):(0)));

    *aCPUPt->vRS = lRFPt;
            
}

void cpu_incdws(Risc256* aCPUPt){
        
    CPUType lVal1 = *aCPUPt->vRA;

    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
    CPUType lRet = lVal1+WORDSIZE;
    *aCPUPt->vRA = lRet;
    
    bool lSign = (lRet & SIGNBIT)!=0;

    /*Set flags*/
    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;

    lRFPt |= 
        (((lRet==0)?(Z_SET):(0)) | 
        ((lSign)?(S_SET):(0)) |
        ((lSign != lASign)?(O_SET):(0)) |
        ((lVal1 > lRet)?(C_SET):(0)));

    *aCPUPt->vRS = lRFPt;
            
}


void cpu_qinc(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)+1;
}

void cpu_qinci(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)+(*aCPUPt->vRI);
}

void cpu_qincaddr(Risc256* aCPUPt, CPUType* aRetH, CPUType* aRetL){
    *aRetL = (*aRetL)+1;
    *aRetH = (*aRetH)+(*aRetL==0)*1;
}

//0x30
void cpu_qira(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRA);
}

//0x31
void cpu_qirb(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRB);
}

//0x32
void cpu_qirc(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRC);
}

//0x33
void cpu_qird(Risc256* aCPUPt){
    cpu_qincaddr(aCPUPt,aCPUPt->vRDH,aCPUPt->vRDL);
}

//0x24
void cpu_qire(Risc256* aCPUPt){
    cpu_qincaddr(aCPUPt,aCPUPt->vREH,aCPUPt->vREL);
}

//0x25
void cpu_qirrh(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRRH);
}

//0x26
void cpu_qirrl(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRRL);
}

//0x27
void cpu_qirai(Risc256* aCPUPt){
    cpu_qinci(aCPUPt,aCPUPt->vRA);
}

//0x28
void cpu_qirbi(Risc256* aCPUPt){
    cpu_qinci(aCPUPt,aCPUPt->vRB);
}

//0x29
void cpu_qirci(Risc256* aCPUPt){
    cpu_qinci(aCPUPt,aCPUPt->vRC);
}

//=========================================================//
// 0x4 - COND



//=========================================================//
// 0x5 - INC



//0x2A
//0x2B
//0x2C
//0x2D
//0x2E
//0x2F

//=========================================================//
// 0x03 - DEC

void cpu_qdec(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)-1;
}

void cpu_qdeci(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)-(*aCPUPt->vRI);
}

void cpu_qdecaddr(Risc256* aCPUPt, CPUType* aRetH, CPUType* aRetL){
    *aRetL = (*aRetL)-1;
    *aRetH = (*aRetH)-(*aRetL==0)*1;
}

void cpu_qdra(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRA);
}

void cpu_qdrb(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRB);
}

void cpu_qdrc(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRC);
}

void cpu_qdrd(Risc256* aCPUPt){
    cpu_qdecaddr(aCPUPt,aCPUPt->vRDH,aCPUPt->vRDL);
}

void cpu_qdre(Risc256* aCPUPt){
    cpu_qdecaddr(aCPUPt,aCPUPt->vREH,aCPUPt->vREL);
}

void cpu_qdrrh(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRRH);
}

void cpu_qdrrl(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRRL);
}

void cpu_qdrai(Risc256* aCPUPt){
    cpu_qdeci(aCPUPt,aCPUPt->vRA);
}

void cpu_qdrbi(Risc256* aCPUPt){
    cpu_qdeci(aCPUPt,aCPUPt->vRB);
}

void cpu_qdrci(Risc256* aCPUPt){
    cpu_qdeci(aCPUPt,aCPUPt->vRC);
}

//=========================================================//
// 0x04 - CMP

//40
void cpu_qgt(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)>(*aCPUPt->vRB);
}

//41
void cpu_qlt(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)<(*aCPUPt->vRB);
}

//42
void cpu_qeq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)==(*aCPUPt->vRB);
}

//43
void cpu_qgeq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)>=(*aCPUPt->vRB);
}

//44
void cpu_qleq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)<=(*aCPUPt->vRB);
}

//45
void cpu_qneq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)!=(*aCPUPt->vRB);
}

//46
void cpu_qmaf(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)*(*aCPUPt->vRF);
}

//47
void cpu_qmbf(Risc256* aCPUPt){
    *aCPUPt->vRB = (*aCPUPt->vRB)*(*aCPUPt->vRF);
}

//48
void cpu_qfgt(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d>lVal2d;
    
}

//49
void cpu_qflt(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d<lVal2d;
    
}

//4A
void cpu_qfeq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d==lVal2d;
    
}

//4B
void cpu_qfgeq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d>=lVal2d;
    
}

//4C
void cpu_qfleq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d<=lVal2d;
    
}

//4D
void cpu_qfneq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d!=lVal2d;
    
}

//4E


//4F

//=========================================================//
// 0x06 - BR/JMP

//=========================================================//
// 0xAX - Temp Push
void cpu_tps_all(Risc256* aCPUPt){
    *aCPUPt->vTP -= WORDSIZE*16;    //16 Registers
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);
    memcpy(aCPUPt->vSPAddr+1, aCPUPt->vRA, WORDSIZE*16);    
}

void cpu_tps(Risc256* aCPUPt, CPUType* aReg){
    *(aCPUPt->vSPAddr) = (*aReg);
    *aCPUPt->vSP -= WORDSIZE;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
}


void cpu_tpsa(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRA);
}

void cpu_tpsb(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRB);
}

void cpu_tpsc(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRC);
}

void cpu_tpsdh(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRDH);
}

void cpu_tpsdl(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRDL);
}

void cpu_tpseh(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vREH);
}

void cpu_tpsel(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vREL);
}

void cpu_tpstp(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vTP);
}

void cpu_tpssp(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vSP);
}

void cpu_tpsi(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRI);
}

void cpu_tpspch(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vPCH);
}

void cpu_tpspcl(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vPCL);
}

void cpu_tpsf(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRF);
}

void cpu_tpss(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRS);
}

void cpu_tpsrh(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRRH);
}

void cpu_tpsrl(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRRL);
}

//=========================================================//
// 0xBX - Temp Pop

//Pop all registers from temp stack
void cpu_tpp_all(Risc256* aCPUPt){
    memcpy(aCPUPt->vRA, aCPUPt->vTPAddr+1, WORDSIZE*16);
    *aCPUPt->vTP += WORDSIZE*16;
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);
    
}

//Pop single register from temp stack
void cpu_tpp(Risc256* aCPUPt, CPUType *aReg){
    *aCPUPt->vTP += WORDSIZE;
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);
    *(aReg) = *(aCPUPt->vTPAddr);
    
}

void cpu_tppa(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRA);
}

void cpu_tppb(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRB);
}

void cpu_tppc(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRC);
}

void cpu_tppdh(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRDH);
}

void cpu_tppdl(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRDL);
}

void cpu_tppeh(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vREH);
}

void cpu_tppel(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vREL);
}

void cpu_tpptp(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vTP);
}

void cpu_tppsp(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vSP);
}

void cpu_tppi(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRI);
}

void cpu_tpppch(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vPCH);
}

void cpu_tpppcl(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vPCL);
}

void cpu_tppf(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRF);
}

void cpu_tpps(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRS);
}

void cpu_tpprh(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRRH);
}

void cpu_tpprl(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRRL);
}


//=========================================================//
// 0xCX - Push
void cpu_psh_int(Risc256* aCPUPt){
    *aCPUPt->vSP -= WORDSIZE*16;    //16 Registers
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    memcpy(aCPUPt->vSPAddr+1, aCPUPt->vRA, WORDSIZE*16);
    
}

void cpu_psh_call(Risc256* aCPUPt){
    *aCPUPt->vSP -= WORDSIZE*14;    //16 Registers
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    memcpy(aCPUPt->vSPAddr+1, aCPUPt->vRA, WORDSIZE*14);
    
}

void cpu_psh(Risc256* aCPUPt, CPUType* aReg){
    *(aCPUPt->vSPAddr) = (*aReg);
    *aCPUPt->vSP -= WORDSIZE;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
}

void cpu_psha(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRA);
}

void cpu_pshb(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRB);
}

void cpu_pshc(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRC);
}

void cpu_pshdh(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRDH);
}

void cpu_pshdl(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRDL);
}

void cpu_psheh(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vREH);
}

void cpu_pshel(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vREL);
}

void cpu_pshtp(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vTP);
}

void cpu_pshsp(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vSP);
}

void cpu_pshi(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRI);
}

void cpu_pshpch(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vPCH);
}

void cpu_pshpcl(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vPCL);
}

void cpu_pshf(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRF);
}

void cpu_pshs(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRS);
}

void cpu_pshrh(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRRH);
}

void cpu_pshrl(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRRL);
}

//=========================================================//
// 0xDX - Pop

void cpu_pop_int(Risc256* aCPUPt){
    memcpy(aCPUPt->vRA, aCPUPt->vSPAddr+1, WORDSIZE*16);
    *aCPUPt->vSP += WORDSIZE*16;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    
}

void cpu_pop_call(Risc256* aCPUPt){
    memcpy(aCPUPt->vRA, aCPUPt->vSPAddr+1, WORDSIZE*14);
    *aCPUPt->vSP += WORDSIZE*14;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    
}

void cpu_pop(Risc256* aCPUPt, CPUType *aReg){
    *aCPUPt->vSP += WORDSIZE;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    *(aReg) = *(aCPUPt->vSPAddr);
    
}

void cpu_popa(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRA);
}

void cpu_popb(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRB);
}

void cpu_popc(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRC);
}

void cpu_popdh(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRDH);
}

void cpu_popdl(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRDL);
}

void cpu_popeh(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vREH);
}

void cpu_popel(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vREL);
}

void cpu_poptp(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vTP);
}

void cpu_popsp(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vSP);
}

void cpu_popi(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRI);
}

void cpu_poppch(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vPCH);
}

void cpu_poppcl(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vPCL);
}

void cpu_popf(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRF);
}

void cpu_pops(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRS);
}

void cpu_poprh(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRRH);
}

void cpu_poprl(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRRL);
}



//=========================================================//
// 0xEX - Relative push


//=========================================================//
// 0xFX - Set/clear flags

void push_registers(Risc256* aCPUPt){
    
    
    
}

//
//void cpu_clrIF(Risc256* cpu){
//    
//    if((*cpu->vRS & IF_SET)!=0){
//
//        //printf("Before POP: %lu %lu\n",*aCPUPt->vRegisters->vRF, *aCPUPt->vRegisters->vPC);
//        *cpu->vSP += cpu->vMemSize;
//        *cpu->vRF = *((CPUType*)(cpu->vMemByte+*cpu->vSP));
//
//        *cpu->vSP += cpu->vMemSize;
//        *cpu->vPC = *((CPUType*)(cpu->vMemByte+*cpu->vSP));
//        (*cpu->vPC)--;
//
//        *cpu->vRS &= IF_CLR;
//
//        //printf("After POP: %lu %lu\n",*aCPUPt->vRegisters->vRF, *aCPUPt->vRegisters->vPC);
//    }
//}