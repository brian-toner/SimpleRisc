/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: brian
 *
 * Created on September 17, 2020, 5:01 PM
 */

#ifndef CPU_H
#define CPU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
    
#ifndef size_t
    typedef unsigned long size_t;
#endif
    

#define CZOS_MASK 0x0F
#define CZOSNU_MASK 0x3F

typedef unsigned char uint8_t;
    
#define WORDSIZE 1
#if WORDSIZE == 1
    #define PAGESIZE 0xFF
    #define SIGNBIT  0x80
    #define ONEBIT 0x01
    #define ADDRSIZE 2
    #define WORDMASK 0xFF
    #define WORDSIZE_BITS 8
    #define DWORDSIZE_BITS 16
    typedef unsigned char CPUType;
    typedef char CPUSWord;
    typedef unsigned short CPUPtrType;
    typedef float CPUFloat;
#elif WORDSIZE == 2
    #define PAGESIZE 0xFFFF
    #define SIGNBIT  0x8000
    #define ADDRSIZE 4
    typedef unsigned short CPUType;
    typedef unsigned int CPUPtrType;
    typedef float CPUFloat;
#elif WORDSIZE == 4
    #define PAGESIZE 0xFFFFFFFF
    #define SIGNBIT  0x80000000
    #define ADDRSIZE 8
    typedef unsigned int CPUType;
    typedef unsigned long CPUPtrType;
    typedef double CPUFloat;
#elif WORDSIZE == 8
    #define PAGESIZE 0xFFFFFFFFFFFFFFFF
    #define SIGNBIT  0x8000000000000000
    #define ADDRSIZE 8
    typedef unsigned long CPUType;
    typedef unsigned long CPUPtrType;
    typedef double CPUFloat;
#endif

#define WORDSIZE_8  1
#define WORDSIZE_16 2
#define WORDSIZE_32 4
#define WORDSIZE_64 8

#define SIGN_64 0x8000000000000000
#define SIGN_32 0x0000000080000000
#define SIGN_16 0x0000000000008000
#define SIGN_8  0x0000000000000080

#define MASK_64 0xFFFFFFFFFFFFFFFF
#define MASK_32 0x00000000FFFFFFFF
#define MASK_16 0x000000000000FFFF
#define MASK_8  0x00000000000000FF
        
#define C_CLR 0b11111110 // Clear Carry flag
#define Z_CLR 0b11111101 // Clear Zero flag
#define O_CLR 0b11111011 // Clear Overflow flag
#define S_CLR 0b11110111 // Clear Sign flag
#define N_CLR 0b11101111 // Clear Infinity flag
#define U_CLR 0b11011111 // Clear Undefined flag
#define T_CLR 0b10111111 // Clear True flag
#define X_CLR 0b01111111 // Clear bitwise multiplication flag

#define C_SET 0b00000001 // Set Carry flag
#define Z_SET 0b00000010 // Set Zero flag
#define O_SET 0b00000100 // Set Overflow flag
#define S_SET 0b00001000 // Set Sign flag
#define N_SET 0b00010000 // Set Infinity flag
#define U_SET 0b00100000 // Set Undefined flag
#define T_SET 0b01000000 // Set True flag
#define X_SET 0b10000000 // Set bitwise multiplication flag


#define P0_CLR 0b11111110 // Clear IO Privilege Level 0
#define P1_CLR 0b11111101 // Clear IO Privilege Level 1
#define A_CLR  0b11111011 // Clear Authorized flag
#define I_CLR  0b11110111 // Clear IRQ flag
#define D_CLR  0b11101111 // Clear Disable flag
#define B_CLR  0b11011111 // Clear Break flag
#define E_CLR  0b10111111 // Clear Error flag
#define H_CLR  0b01111111 // Clear Halt flag

#define P0_SET 0b00000001 // Set IO Privilege Level 0
#define P1_SET 0b00000010 // Set IO Privilege Level 1
#define A_SET  0b00000100 // Set Authorized flag
#define I_SET  0b00001000 // Set IRQ flag
#define D_SET  0b00010000 // Set Disable flag
#define B_SET  0b00100000 // Set Break flag
#define E_SET  0b01000000 // Set Error flag
#define H_SET  0b10000000 // Set Halt flag

 

#ifndef bool
typedef unsigned char boolean;
typedef unsigned char bool;
#endif


typedef struct {
    unsigned char* vMemByte; // Memory array (byte-level access)
    CPUType* vMem;          // Memory array (CPUType-level access)

    size_t vMemByteSize;    // Size of memory in bytes
    size_t vMemSize;        // Size of memory in CPUType units

    size_t vOpcode;         // Current opcode
    size_t vOperand;        // Current operand
    size_t vWordSize;       // Word size of the CPU
    boolean vExec;          // Execution flag

    // General-Purpose Registers
    CPUType* vRA;           // Alpha Accumulator
    CPUType* vRB;           // Beta Accumulator
    CPUType* vRC;           // Counter Register

    // Address Registers
    CPUType* vRDH;          // Destination Address High
    CPUType* vRDL;          // Destination Address Low
    CPUType* vREH;          // Effective Address High
    CPUType* vREL;          // Effective Address Low

    // Increment Register
    CPUType* vRI;           // Increment Register

    // Stack Pointers
    CPUType* vSP;           // Stack Pointer
    CPUType* vTP;           // Temp Stack Pointer

    // System Control Registers
    CPUType* vPCH;          // Program Counter High
    CPUType* vPCL;          // Program Counter Low
    CPUType* vRF;           // Flag Register
    CPUType* vRS;           // Status Flags

    // Return Registers
    CPUType* vRRH;          // Return High
    CPUType* vRRL;          // Return Low

    // Derived Pointers for Direct Memory Access
    CPUType* vRDAddr;       // Pointer to RD (Destination Address)
    CPUType* vREAddr;       // Pointer to RE (Effective Address)
    CPUType* vSPAddr;       // Pointer to Stack Pointer address in memory
    CPUType* vTPAddr;       // Pointer to Temp Stack Pointer address in memory
    unsigned char* vPCAddr; // Pointer to Program Counter address in memory


    CPUPtrType* vRD;    // Certain jumps use this register for their dest, also 
    CPUPtrType* vRE;    // Effective Address
    CPUPtrType* vPC;    // 
    CPUPtrType* vRO;    // RRX+RTX form offset for RE (sometimes RD)

    
    // Status Arrays for Non-Maskable Interrupt (NMI), IRQ, and Halt Status (HS)
    CPUType* vNMIStatus[4];
    CPUType* vIRQStatus[4];
    CPUType* vHSStatus[4];
    
} Risc256;

typedef void (*cpu_inst)(Risc256*);

extern cpu_inst OPCD8[256];


Risc256* cpu_init(size_t aMemorySize);
Risc256* cpu_init_rom(char* aRom, unsigned long aSize);

#ifdef __cplusplus
}
#endif

#endif /* CPU_H */

