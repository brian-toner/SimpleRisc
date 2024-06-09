#include "instructions.h"


void cpu_qpi(Risc256* aCPUPt){
    *aCPUPt->vRB = float_to_cputype(M_PI);
}

void cpu_qe(Risc256* aCPUPt){
    *aCPUPt->vRB = float_to_cputype(M_E);
}

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