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
    

#define M_E		2.7182818284590452354	/* e */
#define M_PI		3.14159265358979323846	/* pi */
    
#ifndef true
    #define true 1
#endif 

#ifndef false
    #define false 0
#endif

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
    #define MAX_VAL 256
    typedef unsigned char CPUType;
    typedef char CPUSWord;
    typedef unsigned short CPUPtrType;
    typedef float CPUFloat;
#elif WORDSIZE == 2
    #define PAGESIZE 0xFFFF
    #define SIGNBIT  0x8000
    #define ADDRSIZE 4
    #define WORDMASK 0xFFFF
    #define WORDSIZE_BITS 16
    #define DWORDSIZE_BITS 32
    #define MAX_VAL 65536
    typedef unsigned short CPUType;
    typedef short CPUSWord;
    typedef unsigned int CPUPtrType;
    typedef float CPUFloat;
#elif WORDSIZE == 4
    #define PAGESIZE 0xFFFFFFFF
    #define SIGNBIT  0x80000000
    #define ADDRSIZE 8
    #define MAX_VAL 4294967296
    typedef unsigned int CPUType;
    typedef int CPUSWord;
    typedef unsigned long CPUPtrType;
    typedef double CPUFloat;
#elif WORDSIZE == 8
    #define PAGESIZE 0xFFFFFFFFFFFFFFFF
    #define SIGNBIT  0x8000000000000000
    #define ADDRSIZE 8
    #define MAX_VAL 18446744073709551616
    typedef unsigned long CPUType;
    typedef long CPUSWord;
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

// RS Flags
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

// Special clear constants
#define CZOS_MASK 0x0F
#define CZOSNU_MASK 0x3F
#define CZ_S_MASK 0x0B
#define Z_S_MASK 0x0A
    
// RF Flags
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
    CPUType* vRA;           // 0 Alpha Accumulator
    CPUType* vRB;           // 1 Beta Accumulator
    CPUType* vRC;           // 2 Counter Register

    // Increment Register
    CPUType* vRI;           // 3 Increment Register

    // Address Registers
    CPUType* vRDH;          // 4 Destination Address High
    CPUType* vRDL;          // 5 Destination Address Low
    CPUType* vREH;          // 6 Effective Address High
    CPUType* vREL;          // 7 Effective Address Low

    // Stack Pointers
    CPUType* vSPH;          // 8 Stack Pointer High
    CPUType* vSPL;          // 9 Stack Pointer Low
    CPUType* vTPH;          // A Temp Stack Pointer High
    CPUType* vTPL;          // B Temp Stack Pointer Low

    // Full Pointers for Double Wide Registers
    CPUPtrType* vSP;        // Full Stack Pointer (combination of vSPH and vSPL)
    CPUPtrType* vTP;        // Full Temp Stack Pointer (combination of vTPH and vTPL)

    // System Control Registers
    CPUType* vPCH;          // C Program Counter High
    CPUType* vPCL;          // D Program Counter Low
    CPUType* vRF;           // E Flag Register
    CPUType* vRS;           // F Status Flags

    // Return Registers
    CPUType* vRRH;          // 10 Return High
    CPUType* vRRL;          // 11 Return Low
    CPUPtrType* vRR;        // Full Return Register (combination of vRRH and vRRL)

    // Offset Registers
    CPUType* vREOH;         // RE Offset Register High
    CPUType* vREOL;         // RE Offset Register Low
    CPUType* vRDOH;         // RD Offset Register High
    CPUType* vRDOL;         // RD Offset Register Low
    CPUPtrType* vREO;       // Full RE Offset Register (combination of vREOH and vREOL)
    CPUPtrType* vRDO;       // Full RD Offset Register (combination of vRDOH and vRDOL)

    // Stack Boundaries
    CPUType* vSSPH;         // 12 Stack Start Pointer High
    CPUType* vSSPL;         // 13 Stack Start Pointer Low
    CPUType* vSEPH;         // 14 Stack End Pointer High
    CPUType* vSEPL;         // 15 Stack End Pointer Low
    CPUPtrType* vSSP;       // Full Stack Start Pointer (combination of vSSPH and vSSPL)
    CPUPtrType* vSEP;       // Full Stack End Pointer (combination of vSEPH and vSEPL)

    // Temp Stack Boundaries
    CPUType* vTSPH;         // 16 Temp Stack Start Pointer High
    CPUType* vTSPL;         // 17 Temp Stack Start Pointer Low
    CPUType* vTEPH;         // 18 Temp Stack End Pointer High
    CPUType* vTEPL;         // 19 Temp Stack End Pointer Low
    CPUPtrType* vTSP;       // Full Temp Stack Start Pointer (combination of vTSPH and vTSPL)
    CPUPtrType* vTEP;       // Full Temp Stack End Pointer (combination of vTEPH and vTEPL)

    // Ring Addresses
    CPUType* vRING1StartH;  // 1A
    CPUType* vRING1StartL;  // 1B
    CPUType* vRING2StartH;  // 1C 
    CPUType* vRING2StartL;  // 1D
    CPUType* vRING3StartH;  // 1E
    CPUType* vRING3StartL;  // 1F
    CPUPtrType* vRING1Start; // Full Ring 1 Start Pointer
    CPUPtrType* vRING2Start; // Full Ring 2 Start Pointer
    CPUPtrType* vRING3Start; // Full Ring 3 Start Pointer

    // Time Registers
    CPUType* vTR[8];        // 20-27 Time Registers TR0 - TR7

    // Time Comparison Registers
    CPUType* vTC[8];        // 28-2F Time Comparison Registers TC0 - TC7

    // Key Registers
    CPUType* vPL[16];       // 30-3F Key Registers PL0 - PL15

    // Hardware Interrupt
    CPUType* vHWIMaxH;      // 40
    CPUType* vHWIMaxL;      // 41
    CPUType* vHwintFlagAddH;// 42
    CPUType* vHWIntFlagAddL;// 43
    CPUType* vHWIVTStH;     // 44
    CPUType* vHWIVTStL;     // 45
    CPUType* vHWIVTEndH;    // 46
    CPUType* vHWIVTEndL;    // 47

    // Software Interrupt
    CPUType* vSWIMaxH;      // 48
    CPUType* vSWIMaxL;      // 49
    CPUType* vSWIntFlagAddH;// 4A
    CPUType* vSWIntFlagAddL;// 4B
    CPUType* vSWIVTStH;     // 4C
    CPUType* vSWIVTStL;     // 4D
    CPUType* vSWIVTEndH;    // 4E
    CPUType* vSWIVTEndL;    // 4F

    // Derived Pointers for Direct Memory Access
    CPUType* vRDAddr;       // Pointer to RD (Destination Address)
    CPUType* vREAddr;       // Pointer to RE (Effective Address)
    CPUType* vSPAddr;       // Pointer to Stack Pointer address in memory
    CPUType* vTPAddr;       // Pointer to Temp Stack Pointer address in memory
    unsigned char* vPCAddr; // Pointer to Program Counter address in memory

    CPUPtrType* vRD;        // Certain jumps use this register for their dest, also 
    CPUPtrType* vRE;        // Effective Address
    CPUPtrType* vPC;        // Program Counter
    CPUPtrType* vRO;        // RRX+RTX form offset for RE (sometimes RD)

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

