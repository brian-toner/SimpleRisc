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
    lRet->RA     = &lRet->Mem[0];
    lRet->RB     = &lRet->Mem[1];
    lRet->RC     = &lRet->Mem[2];
    lRet->RI     = &lRet->Mem[3];
    lRet->RD     = (AddressType*)&lRet->Mem[4];
    lRet->RE     = (AddressType*)&lRet->Mem[6];
    lRet->SP     = (AddressType*)&lRet->Mem[8];
    lRet->TP     = (AddressType*)&lRet->Mem[10];
    lRet->PC     = (AddressType*)&lRet->Mem[12];
    lRet->RF     = &lRet->Mem[14];
    lRet->RS     = &lRet->Mem[15];
    lRet->RR     = (AddressType*)&lRet->Mem[16];

    lRet->SSP = (AddressType*)&lRet->Mem[18];
    lRet->SEP = (AddressType*)&lRet->Mem[20];
    lRet->TSP = (AddressType*)&lRet->Mem[22];
    lRet->TEP = (AddressType*)&lRet->Mem[24];
    
    lRet->RING1Start = (AddressType*)&lRet->Mem[26];
    lRet->RING2Start = (AddressType*)&lRet->Mem[28];
    lRet->RING3Start = (AddressType*)&lRet->Mem[30];
    
    lRet->TR = &lRet->Mem[32];
    lRet->TC = &lRet->Mem[40];
    lRet->PL = &lRet->Mem[48];
    lRet->KC = &lRet->Mem[64];
    
    *lRet->PC = 240;
    *lRet->RD = 245;
    *lRet->RE = 245;
    
    *lRet->SP = 175;
    *lRet->TP = 207;
    
    *lRet->SSP = 175;
    *lRet->SEP = 206;
    *lRet->TSP = 207;
    *lRet->TEP = 239;
    
    
    lRet->SPAddr = lRet-> MemByte+(*lRet->SP);
    lRet->TPAddr = lRet-> MemByte+(*lRet->TP);
    

    *lRet->RING1Start = 256;
    *lRet->RING1Start = 512;            
    *lRet->RING1Start = 1024;
    
    return lRet;
}
