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

#ifndef size_t
    typedef unsigned long size_t;
#endif

#ifndef bool
    typedef unsigned char boolean;
    typedef unsigned char bool;
#endif

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
    #define ADDRSIGNBIT  0x8000
    #define ADDRSIZE 2
    #define WORDMASK 0xFF
    #define WORDSIZE_BITS 8
    #define DWORDSIZE_BITS 16
    #define MAX_VAL 256
    typedef uint8_t RegType;
    typedef int8_t SRegType;
    typedef uint16_t AddressType;
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
    typedef uint32_t AddressType;
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
    typedef uint64_t AddressType;
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
    typedef uint64_t AddressType;
    typedef double FloatType;
#else
    #error "Please define a mode: MODE_8_BIT, MODE_16_BIT, MODE_32_BIT, or MODE_64_BIT"
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
    
// Define the structure for the CPU architecture
typedef struct {
    unsigned char*  MemoryByteArray; // Memory array (byte-level access)
    RegType* MemoryArray;           // Memory array (RegType-level access)
    size_t MemoryByteSize;          // Size of memory in bytes
    size_t MemorySize;              // Size of memory in RegType units
    int ExecutionFlag;              // Execution flag
    
    // Accumulator Registers
    RegType* RA; // Alpha Accumulator - Used in mathematical operations
    RegType* RB;  // Beta Accumulator - Used in mathematical operations

    // Counter and Index Registers
    RegType* RC; // Counter Register
    RegType* RI;   // Increment Register - Used as an index for C, incrementing GP Registers and Address Register

    // Destination and Effective Address Registers
    AddressType* RD;    // Destination Register - Used in function calls and jumps
    AddressType* RE; // Effective Address Register - Used for referencing memory, also can be used as a stack pointer

    // Stack Pointers
    AddressType* SP; // Stack Pointer - Used during interrupts and function calls to keep track of stack. Elevated permissions required to directly push and pop from this stack
    AddressType* TP; // Temp Stack Pointer - General purpose stack

    // Program Control Registers
    AddressType* PC; // Program Counter - Points to current instruction being executed
    RegType* RF;    // Flag Register - Flags for keeping track of the state of the machine
    RegType* RS;      // Status Flag - Used to keep track of the state of arithmetic operations

    // Return and Stack Boundary Registers
    AddressType* RR;   // Return Register - Used to store results of function calls, used for building data
    AddressType* StackStartRegister; // Stack Start Register - Used for stack resets and keeping track of stack boundaries
    AddressType* StackEndRegister;   // Stack End Register - Used to keep track of stack end
    AddressType* TempStackStartRegister; // Temp Stack Start Register - Used to reset stack and keep track of stack boundaries
    AddressType* TempStackEndRegister;   // Temp Stack End Register - Used to keep track of temp stack end

    // Ring Start Address Registers
    AddressType* Ring1StartAddress; // Ring 1 Start Address
    AddressType* Ring2StartAddress; // Ring 2 Start Address
    AddressType* Ring3StartAddress; // Ring 3 Start Address

    // Time Registers
    RegType* TimeRegister[8]; // Time Register - Updated with current time after each instruction
    RegType* TimeComparisonRegister[8]; // Time Comparison - Used for setting alarms and triggering timer interrupt

    // Key Registers
    RegType* PrivilegeKeyRegister[16]; // Key Register - Used for elevating privilege level
    RegType* KeyCacheRegister[16]; // Key Cache Register - Used for caching user inputted key, when KC=PL admin elevation is enabled

    // Hardware Interrupt Registers
    AddressType* HardwareInterruptFlags; // Hardware Interrupt Flags - Used to indicate when a non-maskable interrupt has occurred
    AddressType* HardwareInterrupt1Address; // Hardware Interrupt 1 Address
    AddressType* HardwareInterrupt2Address; // Hardware Interrupt 2 Address
    AddressType* HardwareInterrupt3Address; // Hardware Interrupt 3 Address
    AddressType* HardwareInterrupt4Address; // Hardware Interrupt 4 Address
    AddressType* HardwareInterrupt5Address; // Hardware Interrupt 5 Address
    AddressType* HardwareInterrupt6Address; // Hardware Interrupt 6 Address
    AddressType* HardwareInterrupt7Address; // Hardware Interrupt 7 Address
    AddressType* HardwareInterrupt8Address; // Hardware Interrupt 8 Address
    AddressType* HardwareInterrupt9Address; // Hardware Interrupt 9 Address
    AddressType* HardwareInterruptAAddress; // Hardware Interrupt A Address
    AddressType* HardwareInterruptBAddress; // Hardware Interrupt B Address
    AddressType* HardwareInterruptCAddress; // Hardware Interrupt C Address
    AddressType* HardwareInterruptDAddress; // Hardware Interrupt D Address
    AddressType* HardwareInterruptEAddress; // Hardware Interrupt E Address
    AddressType* HardwareInterruptFAddress; // Hardware Interrupt F Address

    // Software Interrupt Registers
    AddressType* SoftwareInterruptFlags; // Software Interrupt Flags - Used to indicate when a maskable interrupt has occurred
    AddressType* SoftwareInterrupt1Address; // Software Interrupt 1 Address
    AddressType* SoftwareInterrupt2Address; // Software Interrupt 2 Address
    AddressType* SoftwareInterrupt3Address; // Software Interrupt 3 Address
    AddressType* SoftwareInterrupt4Address; // Software Interrupt 4 Address
    AddressType* SoftwareInterrupt5Address; // Software Interrupt 5 Address
    AddressType* SoftwareInterrupt6Address; // Software Interrupt 6 Address
    AddressType* SoftwareInterrupt7Address; // Software Interrupt 7 Address
    AddressType* SoftwareInterrupt8Address; // Software Interrupt 8 Address
    AddressType* SoftwareInterrupt9Address; // Software Interrupt 9 Address
    AddressType* SoftwareInterruptAAddress; // Software Interrupt A Address
    AddressType* SoftwareInterruptBAddress; // Software Interrupt B Address
    AddressType* SoftwareInterruptCAddress; // Software Interrupt C Address
    AddressType* SoftwareInterruptDAddress; // Software Interrupt D Address
    AddressType* SoftwareInterruptEAddress; // Software Interrupt E Address
    AddressType* SoftwareInterruptFAddress; // Software Interrupt F Address
} CPU_Architecture;

#ifdef __cplusplus
}
#endif

#endif /* CPU2_H */
