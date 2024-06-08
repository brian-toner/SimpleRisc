#include "CPU.h"


Risc256* cpu_init(size_t aMemorySize){
    
    Risc256* lRet = malloc(sizeof(Risc256));

    lRet->vMemSize = aMemorySize;
    lRet->vMemByte = malloc(aMemorySize);
    lRet->vMem = (CPUType*)(lRet->vMemByte);
    lRet->vOperand = 0;
    lRet->vWordSize = sizeof(CPUType);    
    lRet->vExec = 1;
    
    size_t i = 0;
    for(i = 0; i < aMemorySize; i++){
        lRet->vMemByte[i] = 0;
    }
    
    lRet->vMemByte[aMemorySize-1] = 0xFF;
    
    int lRegCount = 0;
    lRet->vRA     = &lRet->vMem[lRegCount++];
    lRet->vRB     = &lRet->vMem[lRegCount++];
    lRet->vRC     = &lRet->vMem[lRegCount++];
    
    lRet->vRDH    = &lRet->vMem[lRegCount++];
    lRet->vRDL    = &lRet->vMem[lRegCount++];
    lRet->vREH    = &lRet->vMem[lRegCount++];
    lRet->vREL    = &lRet->vMem[lRegCount++];
    
    lRet->vRI     = &lRet->vMem[lRegCount++];
    
    lRet->vSP     = &lRet->vMem[lRegCount++];
    lRet->vTP     = &lRet->vMem[lRegCount++];
    
    lRet->vPCH    = &lRet->vMem[lRegCount++];
    lRet->vPCL    = &lRet->vMem[lRegCount++];
    lRet->vRF     = &lRet->vMem[lRegCount++];
    lRet->vRS     = &lRet->vMem[lRegCount++];
    
    lRet->vRRH    = &lRet->vMem[lRegCount++];
    lRet->vRRL    = &lRet->vMem[lRegCount++];
    
    lRet->vRD     = (CPUPtrType*)lRet->vRDH;
    lRet->vRE     = (CPUPtrType*)lRet->vREH;
    lRet->vPC     = (CPUPtrType*)lRet->vPCH;
    lRet->vRR     = (CPUPtrType*)lRet->vRRH;
    
    *lRet->vPC = 128;
    *lRet->vRD = 245;
    *lRet->vRE = 245;
    
    *lRet->vSP = 127;
    *lRet->vTP = 111;
    
    lRet->vSPAddr = lRet->vMemByte+(*lRet->vSP);
    lRet->vTPAddr = lRet->vMemByte+(*lRet->vTP);
    

    
    return lRet;
}