#include "CPU2.h"
#include <stdlib.h>
#include <string.h>

CPU_Architecture* cpu2_init(size_t aMemorySize) {
    // Allocate memory for the CPU structure
    CPU_Architecture* cpu = malloc(sizeof(CPU_Architecture));

    // Initialize memory sizes
    cpu->MemoryByteSize = aMemorySize;
    cpu->MemoryByteArray = malloc(aMemorySize);
    cpu->MemorySize = aMemorySize / sizeof(RegType);
    cpu->MemoryArray = (RegType*)cpu->MemoryByteArray;
    cpu->ExecutionFlag = 1;

    // Clear memory
    memset(cpu->MemoryByteArray, 0, aMemorySize);
    cpu->MemoryByteArray[aMemorySize - 1] = 0xFF;

    // Initialize registers
    int regCount = 0;
    cpu->RA = &cpu->MemoryArray[regCount++];
    cpu->RB = &cpu->MemoryArray[regCount++];
    cpu->RC = &cpu->MemoryArray[regCount++];
    cpu->RI = &cpu->MemoryArray[regCount++];

    // Handle Destination and Effective Address Registers as PtrType
    cpu->RD = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->RE = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]

    // Initialize other registers
    cpu->SP = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->TP = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]

    cpu->PC = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->RF = &cpu->MemoryArray[regCount++];
    cpu->RS = &cpu->MemoryArray[regCount++];

    cpu->RR = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->StackStartRegister = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->StackEndRegister = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->TempStackStartRegister = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->TempStackEndRegister = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]

    cpu->Ring1StartAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->Ring2StartAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->Ring3StartAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]

    // Initialize time and key registers
    for (int i = 0; i < 8; ++i) {
        cpu->TimeRegister[i] = &cpu->MemoryArray[regCount++];
        cpu->TimeComparisonRegister[i] = &cpu->MemoryArray[regCount++];
    }

    for (int i = 0; i < 16; ++i) {
        cpu->PrivilegeKeyRegister[i] = &cpu->MemoryArray[regCount++];
        cpu->KeyCacheRegister[i] = &cpu->MemoryArray[regCount++];
    }

    // Initialize hardware interrupt registers
    cpu->HardwareInterruptFlags = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt1Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt2Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt3Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt4Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt5Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt6Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt7Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt8Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterrupt9Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterruptAAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterruptBAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterruptCAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterruptDAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterruptEAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->HardwareInterruptFAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]

    // Initialize software interrupt registers
    cpu->SoftwareInterruptFlags = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt1Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt2Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt3Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt4Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt5Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt6Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt7Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt8Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterrupt9Address = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterruptAAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterruptBAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterruptCAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterruptDAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterruptEAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]
    cpu->SoftwareInterruptFAddress = (AddressType*)&cpu->MemoryArray[regCount];
    regCount += 2; // Increment by 2 because PtrType is RegType[2]

    // Initialize default values
    *cpu->PC = 128;
    *cpu->RD = 245;
    *cpu->RE = 245;

    *cpu->SP = 127;
    *cpu->TP = 111;

    return cpu;
}
















