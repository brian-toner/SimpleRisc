#include "instructions.h"


void cpu_qpi(Risc256* cpu){
    *cpu->RB = float_to_cputype(M_PI);
}

void cpu_qe(Risc256* cpu){
    *cpu->RB = float_to_cputype(M_E);
}

// 0x20
void cpu_qfadd(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d+lVal2d;
    *cpu->RA = float_to_cputype(lRet);

    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x21
void cpu_qfsub(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d-lVal2d;
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x22
void cpu_qfmul(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d*lVal2d;
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x23
void cpu_qfdiv(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    double lRet = lVal1d/lVal2d;
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}




// 0x24
void cpu_qflogbn(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);

    double lRet = logbn(lVal1d,lVal2d);
    *cpu->RA = float_to_cputype(lRet);

    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
    
}


// 0x25
void cpu_fexp(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    CPUFloat lVal1d = cputype_to_float(lVal1);
    CPUFloat lVal2d = cputype_to_float(lVal2);
    
    CPUFloat lRet = pow(lVal1d,lVal2d);
    
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}



// 0x26
void cpu_qsin(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = sin(lVal1d);
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x27
void cpu_qcos(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = cos(lVal1d);
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x28
void cpu_qtan(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = tan(lVal1d);
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x29
void cpu_qasin(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = asin(lVal1d);
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x2A
void cpu_qacos(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    double lVal1d = cputype_to_float(lVal1);
    double lRet = acos(lVal1d);
    *cpu->RA = float_to_cputype(lRet);
    
    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}

// 0x2B
void cpu_qatan2(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);

    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);

    double lRet = atan2(lVal1d,lVal2d);

    // Reset relevant flags
    *cpu->RS &= CZOSNU_MASK;

    // Set flags based on the result
    *cpu->RS |= (isnan(lRet) ? U_SET : 0)    // Undefined flag for NaN
                 | (isinf(lRet) ? N_SET : 0)    // Infinity flag for infinity
                 | ((lRet == 0.0) ? Z_SET : 0)  // Zero flag for zero result
                 | ((lRet < 0.0) ? S_SET : 0);  // Sign flag for negative result
}


// 0x2C
void cpu_its(Risc256* cpu){
    //int to string
    char* lBuff = (char*)(cpu->RA+*cpu->RE);
    sprintf(lBuff,"%d", (CPUSWord)*cpu->RA);
    
}

void cpu_uits(Risc256* cpu){
    
    char* lBuff = (char*)(cpu->RA+*cpu->RE);
    sprintf(lBuff,"%d", (CPUType)*cpu->RA);
    
}

// 0x2D
void cpu_itf(Risc256* cpu){  
    //int to float
    *cpu->RA = float_to_cputype((CPUSWord)*cpu->RA);
}

void cpu_uitf(Risc256* cpu){    
    *cpu->RA = float_to_cputype(*cpu->RA);
}

// 0x2E
void cpu_qfts(Risc256* cpu){
    
    //char* lBuff = (char*)cpu->REAddr;
    char* lBuff = (char*)(cpu->RA+*cpu->RE);
    CPUFloat lVal1 = cputype_to_float(*cpu->RA);
    sprintf(lBuff,"%g", lVal1);    
    
}

// 0x2F
void cpu_qfti(Risc256* cpu){
    
    CPUFloat lFRet = cputype_to_float(*cpu->RA);
    CPUType lRet = lFRet;
    *cpu->RA = lRet;

}