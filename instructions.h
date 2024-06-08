/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   instructions.h
 * Author: brian
 *
 * Created on June 4, 2021, 9:40 PM
 */

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "output.h"
#include "CPU.h"  
#include "minifloat.h"
#include "half.h"
#include <math.h>
    
#define M_E		2.7182818284590452354	/* e */
#define M_PI		3.14159265358979323846	/* pi */
    
void cpu_set_addr(Risc256* aCPUPt);
double logbn(double a, double b);

#if WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(CPUFloat aConv);
    
#elif WORDSIZE==2
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(float aConv);  
#elif WORDSIZE==4
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(float aConv);
#elif WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(double aConv); 
#endif

//Needs a home...
void cpu_qstf(Risc256* aCPUPt);
void cpu_qsti(Risc256* aCPUPt);
void cpu_uitf(Risc256* aCPUPt);
void cpu_uits(Risc256* aCPUPt);


//0x00
void cpu_set(Risc256* aCPUPt);
void cpu_set_0(Risc256* aCPUPt);
void cpu_set_1(Risc256* aCPUPt);
void cpu_set_2(Risc256* aCPUPt);
void cpu_set_3(Risc256* aCPUPt);
void cpu_set_4(Risc256* aCPUPt);
void cpu_set_5(Risc256* aCPUPt);
void cpu_set_6(Risc256* aCPUPt);
void cpu_set_7(Risc256* aCPUPt);
void cpu_set_8(Risc256* aCPUPt);
void cpu_set_9(Risc256* aCPUPt);
void cpu_set_A(Risc256* aCPUPt);
void cpu_set_B(Risc256* aCPUPt);
void cpu_set_C(Risc256* aCPUPt);
void cpu_set_D(Risc256* aCPUPt);
void cpu_set_E(Risc256* aCPUPt);
void cpu_set_F(Risc256* aCPUPt);

//0x1X
void cpu_nop(Risc256* aCPUPt);
void cpu_qadd(Risc256* aCPUPt);
void cpu_qsub(Risc256* aCPUPt);
void cpu_qmul(Risc256* aCPUPt);
void cpu_qdiv(Risc256* aCPUPt);
void cpu_qmod(Risc256* aCPUPt);
void cpu_stb(Risc256* aCPUPt);
void cpu_clb(Risc256* aCPUPt);
void cpu_qnot(Risc256* aCPUPt);
void cpu_qand(Risc256* aCPUPt);
void cpu_qor(Risc256* aCPUPt);
void cpu_qxor(Risc256* aCPUPt);
void cpu_qshl(Risc256* aCPUPt);
void cpu_qshr(Risc256* aCPUPt);
void cpu_its(Risc256* aCPUPt);
void cpu_itf(Risc256* aCPUPt);

//0x2X
void cpu_fexp(Risc256* aCPUPt);
void cpu_qfadd(Risc256* aCPUPt);
void cpu_qfsub(Risc256* aCPUPt);
void cpu_qfmul(Risc256* aCPUPt);
void cpu_qfdiv(Risc256* aCPUPt);
void cpu_qflogbn(Risc256* aCPUPt);
void cpu_qpi(Risc256* aCPUPt);
void cpu_qe(Risc256* aCPUPt);
void cpu_qsin(Risc256* aCPUPt);
void cpu_qcos(Risc256* aCPUPt);
void cpu_qtan(Risc256* aCPUPt);
void cpu_qasin(Risc256* aCPUPt);
void cpu_qacos(Risc256* aCPUPt);
void cpu_qatan2(Risc256* aCPUPt);
void cpu_qfts(Risc256* aCPUPt);
void cpu_qfti(Risc256* aCPUPt);



//=========================================================//
// 0x4X - CMP

void cpu_qgt(Risc256* aCPUPt);      //0x40
void cpu_qlt(Risc256* aCPUPt);      //0x41
void cpu_qeq(Risc256* aCPUPt);      //0x42
void cpu_qgeq(Risc256* aCPUPt);     //0x43
void cpu_qleq(Risc256* aCPUPt);     //0x44
void cpu_qneq(Risc256* aCPUPt);     //0x45
void cpu_qmaf(Risc256* aCPUPt);     //0x46
void cpu_qmbf(Risc256* aCPUPt);     //0x47
void cpu_qfgt(Risc256* aCPUPt);     //0x48
void cpu_qflt(Risc256* aCPUPt);     //0x49
void cpu_qfeq(Risc256* aCPUPt);     //0x4A
void cpu_qfgeq(Risc256* aCPUPt);    //0x4B
void cpu_qfleq(Risc256* aCPUPt);    //0x4C
void cpu_qfneq(Risc256* aCPUPt);    //0x4D




#ifdef __cplusplus
}
#endif

#endif /* INSTRUCTIONS_H */

