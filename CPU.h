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
#include <string.h>
    
#ifndef size_t
    typedef unsigned long size_t;
#endif

#ifndef int8_t
    typedef char int8_t;
#endif
    
#ifndef uint8_t
    typedef unsigned char uint8_t;
#endif
    
#ifndef uint16_t
    typedef unsigned short uint16_t;
#endif
    
#define M_E		2.7182818284590452354	/* e */
#define M_PI		3.14159265358979323846	/* pi */
    
#ifndef true
    #define true 1
#endif 

#ifndef false
    #define false 0
#endif


    
#define WORDSIZE 1
#if WORDSIZE == 1
    #define PAGESIZE 0xFF
    #define SIGNBIT  0x80
    #define ADDRSIGNBIT  0x8000
    #define ONEBIT 0x01
    #define ADDRSIZE 2
    #define WORDMASK 0xFF
    #define WORDSIZE_BITS 8
    #define DWORDSIZE_BITS 16
    #define MAX_VAL 256
    typedef unsigned char CPUType;
    typedef char CPUSWord;
    typedef unsigned short CPUPtrType;
    typedef uint8_t RegType;
    typedef int8_t SRegType;
    typedef uint16_t AddressType;
    
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
#define CZOS_MASK 0xF0
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
    unsigned char*  MemByte; // Memory array (byte-level access)
    CPUType* Mem;          // Memory array (CPUType-level access)

    size_t  MemByteSize;    // Size of memory in bytes
    size_t MemSize;        // Size of memory in CPUType units

    size_t Opcode;         // Current opcode
    size_t Operand;        // Current operand
    size_t WordSize;       // Word size of the CPU
    boolean Exec;          // Execution flag

    // General-Purpose Registers
    CPUType* RA;           // 0 Alpha Accumulator
    CPUType* RB;           // 1 Beta Accumulator
    CPUType* RC;           // 2 Counter Register

    // Increment Register
    CPUType* RI;           // 3 Increment Register

    // Address Registers
    CPUType* RDH;          // 4 Destination Address High
    CPUType* RDL;          // 5 Destination Address Low
    CPUType* REH;          // 6 Effective Address High
    CPUType* REL;          // 7 Effective Address Low

    // Stack Pointers
    CPUType* SPH;          // 8 Stack Pointer High
    CPUType* SPL;          // 9 Stack Pointer Low
    CPUType* TPH;          // A Temp Stack Pointer High
    CPUType* TPL;          // B Temp Stack Pointer Low

    // Full Pointers for Double Wide Registers
    CPUPtrType* SP;        // Full Stack Pointer (combination of SPH and SPL)
    CPUPtrType* TP;        // Full Temp Stack Pointer (combination of TPH and TPL)

    // System Control Registers
    CPUType* PCH;          // C Program Counter High
    CPUType* PCL;          // D Program Counter Low
    CPUType* RF;           // E Flag Register
    CPUType* RS;           // F Status Flags

    // Return Registers
    CPUType* RRH;          // 10 Return High
    CPUType* RRL;          // 11 Return Low
    CPUPtrType* RR;        // Full Return Register (combination of RRH and RRL)

    // Offset Registers
    CPUType* REOH;         // RE Offset Register High
    CPUType* REOL;         // RE Offset Register Low
    CPUType* RDOH;         // RD Offset Register High
    CPUType* RDOL;         // RD Offset Register Low
    CPUPtrType* REO;       // Full RE Offset Register (combination of REOH and REOL)
    CPUPtrType* RDO;       // Full RD Offset Register (combination of RDOH and RDOL)

    // Stack Boundaries
    CPUType* SSPH;         // 12 Stack Start Pointer High
    CPUType* SSPL;         // 13 Stack Start Pointer Low
    CPUType* SEPH;         // 14 Stack End Pointer High
    CPUType* SEPL;         // 15 Stack End Pointer Low
    CPUPtrType* SSP;       // Full Stack Start Pointer (combination of SSPH and SSPL)
    CPUPtrType* SEP;       // Full Stack End Pointer (combination of SEPH and SEPL)

    // Temp Stack Boundaries
    CPUType* TSPH;         // 16 Temp Stack Start Pointer High
    CPUType* TSPL;         // 17 Temp Stack Start Pointer Low
    CPUType* TEPH;         // 18 Temp Stack End Pointer High
    CPUType* TEPL;         // 19 Temp Stack End Pointer Low
    CPUPtrType* TSP;       // Full Temp Stack Start Pointer (combination of TSPH and TSPL)
    CPUPtrType* TEP;       // Full Temp Stack End Pointer (combination of TEPH and TEPL)

    // Ring Addresses
    CPUType* RING1StartH;  // 1A
    CPUType* RING1StartL;  // 1B
    CPUType* RING2StartH;  // 1C 
    CPUType* RING2StartL;  // 1D
    CPUType* RING3StartH;  // 1E
    CPUType* RING3StartL;  // 1F
    CPUPtrType* RING1Start; // Full Ring 1 Start Pointer
    CPUPtrType* RING2Start; // Full Ring 2 Start Pointer
    CPUPtrType* RING3Start; // Full Ring 3 Start Pointer

    // Time Registers
    CPUType* TR;        // 20-27 Time Registers TR0 - TR7

    // Time Comparison Registers
    CPUType* TC;        // 28-2F Time Comparison Registers TC0 - TC7

    // Key Registers
    RegType* PL; // Key Register - Used for elevating privilege level
    RegType* KC; // Key Cache Register - Used for caching user inputted key, when KC=PL admin elevation is enabled

    
    // Hardware Interrupt
    CPUType* HWIMaxH;      // 40
    CPUType* HWIMaxL;      // 41
    CPUType* HWIntFlagAddH;// 42
    CPUType* HWIntFlagAddL;// 43
    CPUType* HWIVTStH;     // 44
    CPUType* HWIVTStL;     // 45
    CPUType* HWIVTEndH;    // 46
    CPUType* HWIVTEndL;    // 47

    // Software Interrupt
    CPUType* SWIMaxH;      // 48
    CPUType* SWIMaxL;      // 49
    CPUType* SWIntFlagAddH;// 4A
    CPUType* SWIntFlagAddL;// 4B
    CPUType* SWIVTStH;     // 4C
    CPUType* SWIVTStL;     // 4D
    CPUType* SWIVTEndH;    // 4E
    CPUType* SWIVTEndL;    // 4F

    // Derived Pointers for Direct Memory Access
    CPUType* RDAddr;       // Pointer to RD (Destination Address)
    CPUType* REAddr;       // Pointer to RE (Effective Address)
    CPUType* SPAddr;       // Pointer to Stack Pointer address in memory
    CPUType* TPAddr;       // Pointer to Temp Stack Pointer address in memory
    unsigned char* PCAddr; // Pointer to Program Counter address in memory

    CPUPtrType* RD;        // Certain jumps use this register for their dest, also 
    CPUPtrType* RE;        // Effective Address
    CPUPtrType* PC;        // Program Counter
    CPUPtrType* RO;        // RRX+RTX form offset for RE (sometimes RD)

    // Status Arrays for Non-Maskable Interrupt (NMI), IRQ, and Halt Status (HS)
    CPUType* NMIStatus[4];
    CPUType* IRQStatus[4];
    CPUType* HSStatus[4];

} Risc256;




typedef void (*cpu_inst)(Risc256*);

extern cpu_inst OPCD8[256];


Risc256* cpu_init(size_t aMemorySize);
Risc256* cpu_init_rom(char* aRom, unsigned long aSize);

#ifdef __cplusplus
}
#endif

#endif /* CPU_H */

