#include "CPU.h"


Risc256* cpu_init(size_t aMemorySize){
    
    Risc256* lRet = malloc(sizeof(Risc256));

    lRet->MemSize = aMemorySize;
    lRet-> MemByte = malloc(aMemorySize);
    lRet->Mem = (CPUType*)(lRet-> MemByte);
    lRet->Operand = 0;
    lRet->WordSize = sizeof(CPUType);    
    lRet->Exec = 1;
    
    size_t i = 0;
    for(i = 0; i < aMemorySize; i++){
        lRet-> MemByte[i] = 0;
    }
    
    lRet-> MemByte[aMemorySize-1] = 0xFF;
    
    int lRegCount = 0;
    lRet->RA     = &lRet->Mem[lRegCount++];
    lRet->RB     = &lRet->Mem[lRegCount++];
    lRet->RC     = &lRet->Mem[lRegCount++];
    
    lRet->RDH    = &lRet->Mem[lRegCount++];
    lRet->RDL    = &lRet->Mem[lRegCount++];
    lRet->REH    = &lRet->Mem[lRegCount++];
    lRet->REL    = &lRet->Mem[lRegCount++];
    
    lRet->RI     = &lRet->Mem[lRegCount++];
    
    lRet->SP     = &lRet->Mem[lRegCount++];
    lRet->TP     = &lRet->Mem[lRegCount++];
    
    lRet->PCH    = &lRet->Mem[lRegCount++];
    lRet->PCL    = &lRet->Mem[lRegCount++];
    lRet->RF     = &lRet->Mem[lRegCount++];
    lRet->RS     = &lRet->Mem[lRegCount++];
    
    lRet->RRH    = &lRet->Mem[lRegCount++];
    lRet->RRL    = &lRet->Mem[lRegCount++];
    
    lRet->RD     = (CPUPtrType*)lRet->RDH;
    lRet->RE     = (CPUPtrType*)lRet->REH;
    lRet->PC     = (CPUPtrType*)lRet->PCH;
    lRet->RR     = (CPUPtrType*)lRet->RRH;
    
    *lRet->PC = 128;
    *lRet->RD = 245;
    *lRet->RE = 245;
    
    *lRet->SP = 127;
    *lRet->TP = 111;
    
    lRet->SPAddr = lRet-> MemByte+(*lRet->SP);
    lRet->TPAddr = lRet-> MemByte+(*lRet->TP);
    

    
    return lRet;
}