/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   CPU2.h
 * Author: brian
 *
 * Created on June 15, 2024, 10:55 PM
 */

#ifndef CPU2_H
#define CPU2_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

// Define the mode
// Uncomment the desired mode or define it in the compiler settings
#define MODE_8_BIT
// #define MODE_16_BIT
// #define MODE_32_BIT
// #define MODE_64_BIT

// Define data types based on the mode
#ifdef MODE_8_BIT
    #define WORDSIZE 1
    #define PAGESIZE 0xFF
    #define SIGNBIT  0x80
    #define ADDRSIZE 2
    #define WORDMASK 0xFF
    #define WORDSIZE_BITS 8
    #define DWORDSIZE_BITS 16
    #define MAX_VAL 256
    typedef uint8_t RegType;
    typedef int8_t SRegType;
    typedef uint16_t PtrType;
    typedef float FloatType;
#elif defined(MODE_16_BIT)
    #define WORDSIZE 2
    #define PAGESIZE 0xFFFF
    #define SIGNBIT  0x8000
    #define ADDRSIZE 4
    #define WORDMASK 0xFFFF
    #define WORDSIZE_BITS 16
    #define DWORDSIZE_BITS 32
    #define MAX_VAL 65536
    typedef uint16_t RegType;
    typedef int16_t SRegType;
    typedef uint32_t PtrType;
    typedef float FloatType;
#elif defined(MODE_32_BIT)
    #define WORDSIZE 4
    #define PAGESIZE 0xFFFFFFFF
    #define SIGNBIT  0x80000000
    #define ADDRSIZE 8
    #define WORDMASK 0xFFFFFFFF
    #define WORDSIZE_BITS 32
    #define DWORDSIZE_BITS 64
    #define MAX_VAL 4294967296
    typedef uint32_t RegType;
    typedef int32_t SRegType;
    typedef uint64_t PtrType;
    typedef float FloatType;
#elif defined(MODE_64_BIT)
    #define WORDSIZE 8
    #define PAGESIZE 0xFFFFFFFFFFFFFFFF
    #define SIGNBIT  0x8000000000000000
    #define ADDRSIZE 8
    #define WORDMASK 0xFFFFFFFFFFFFFFFF
    #define WORDSIZE_BITS 64
    #define DWORDSIZE_BITS 128
    #define MAX_VAL 18446744073709551616ULL
    typedef uint64_t RegType;
    typedef int64_t SRegType;
    typedef uint64_t PtrType;
    typedef double FloatType;
#else
    #error "Please define a mode: MODE_8_BIT, MODE_16_BIT, MODE_32_BIT, or MODE_64_BIT"
#endif

#define WORDSIZE_8  1
#define WORDSIZE_16 2
#define WORDSIZE_32 4
#define WORDSIZE_64 8

// Define the structure for the CPU architecture
typedef struct {
    unsigned char*  MemByte; // Memory array (byte-level access)
    CPUType* Mem;          // Memory array (CPUType-level access)
    size_t MemByteSize;    // Size of memory in bytes
    size_t MemSize;        // Size of memory in CPUType units
    int Exec;          // Execution flag
    
    // Accumulator Registers
    RegType* RA; // Alpha Accumulator - Used in mathematical operations
    RegType* RB; // Beta Accumulator - Used in mathematical operations

    // Counter and Index Registers
    RegType* RC; // Counter Register
    RegType* RI; // Increment Register - Used as an index for C, incrementing GP Registers and Address Register

    // Destination and Effective Address Registers
    PtrType* RD; // Destination Register - Used in function calls and jumps
    PtrType* RE; // Effective Address Register - Used for referencing memory, also can be used as a stack pointer

    // Stack Pointers
    PtrType* SP; // Stack Pointer - Used during interrupts and function calls to keep track of stack. Elevated permissions required to directly push and pop from this stack
    PtrType* TP; // Temp Stack Pointer - General purpose stack

    // Program Control Registers
    PtrType* PC; // Program Counter - Points to current instruction being executed
    RegType* RF;  // Flag Register - Flags for keeping track of the state of the machine
    RegType* RS;  // Status Flag - Used to keep track of the state of arithmetic operations

    // Return and Stack Boundary Registers
    PtrType* RR; // Return Register - Used to store results of function calls, used for building data
    PtrType* SS; // Stack Start Register - Used for stack resets and keeping track of stack boundaries
    PtrType* SE; // Stack End Register - Used to keep track of stack end
    PtrType* TS; // Temp Stack Start Register - Used to reset stack and keep track of stack boundaries
    PtrType* TE; // Temp Stack End Register - Used to keep track of temp stack end

    // Ring Start Address Registers
    PtrType* R1; // Ring 1 Start Address
    PtrType* R2; // Ring 2 Start Address
    PtrType* R3; // Ring 3 Start Address

    // Time Registers
    RegType* TR[8]; // Time Register - Updated with current time after each instruction
    RegType* TC[8]; // Time Comparison - Used for setting alarms and triggering timer interrupt

    // Key Registers
    RegType* PL[16]; // Key Register - Used for elevating privilege level
    RegType* KC[16]; // Key Cache Register - Used for caching user inputted key, when KC=PL admin elevation is enabled

    // Hardware Interrupt Registers
    PtrType* IF; // Hardware Interrupt Flags - Used to indicate when a non-maskable interrupt has occurred
    PtrType* H1; // Hardware Interrupt 1 Address
    PtrType* H2; // Hardware Interrupt 2 Address
    PtrType* H3; // Hardware Interrupt 3 Address
    PtrType* H4; // Hardware Interrupt 4 Address
    PtrType* H5; // Hardware Interrupt 5 Address
    PtrType* H6; // Hardware Interrupt 6 Address
    PtrType* H7; // Hardware Interrupt 7 Address
    PtrType* H8; // Hardware Interrupt 8 Address
    PtrType* H9; // Hardware Interrupt 9 Address
    PtrType* HA; // Hardware Interrupt A Address
    PtrType* HB; // Hardware Interrupt B Address
    PtrType* HC; // Hardware Interrupt C Address
    PtrType* HD; // Hardware Interrupt D Address
    PtrType* HE; // Hardware Interrupt E Address
    PtrType* HF; // Hardware Interrupt F Address

    // Software Interrupt Registers
    PtrType* IS; // Software Interrupt Flags - Used to indicate when a maskable interrupt has occurred
    PtrType* S1; // Software Interrupt 1 Address
    PtrType* S2; // Software Interrupt 2 Address
    PtrType* S3; // Software Interrupt 3 Address
    PtrType* S4; // Software Interrupt 4 Address
    PtrType* S5; // Software Interrupt 5 Address
    PtrType* S6; // Software Interrupt 6 Address
    PtrType* S7; // Software Interrupt 7 Address
    PtrType* S8; // Software Interrupt 8 Address
    PtrType* S9; // Software Interrupt 9 Address
    PtrType* SA; // Software Interrupt A Address
    PtrType* SB; // Software Interrupt B Address
    PtrType* SC; // Software Interrupt C Address
    PtrType* SD; // Software Interrupt D Address
    PtrType* SE; // Software Interrupt E Address
    PtrType* SF; // Software Interrupt F Address
} CPU_Architecture;


#ifdef __cplusplus
}
#endif

#endif /* CPU2_H */

