#include "tests.h"

int test_cpu_push() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->PC = 2048;
    //*lCPU->RF = P0_SET|P1_SET;
    
    *lCPU->RA = 0xAA;
    *lCPU->RR = 0xFFFF;
    cpu_pushall(lCPU);
     *lCPU->RA = 0x00;
    *lCPU->RR = 0x0000;
    
    cpu_popall(lCPU);
    //*lCPU->RA = 0xBB;
    //cpu_push_sp_ra(lCPU);
    //*lCPU->RA = 0xCC;
    //cpu_push_sp_ra(lCPU);
    
    //cpu_pop_sp_rb(lCPU);
    //cpu_pop_sp_rc(lCPU);
    //cpu_pop_sp_ri(lCPU);
    //cpu_pop_sp_re(lCPU);
    
    for(int i = 0; i < 32; i++){
        cpu_push_sp_ra(lCPU);
        cpu_inc_ra(lCPU);
    }
    
    print_mem(lCPU->MemByte,256);
    
    printf("%u\n", *lCPU->RF);
    
    
    //int passed = assert_address(*lCPU->RE, expected );
    //print_address_result("0x36", "inc_re_ds", *lCPU->RE, expected, *lCPU->RS, 0, 0, 0, passed);
    int passed = 1;
    
    free(lCPU);
    return passed;
}

int test_cpu_re_push() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->PC = 2048;
    //*lCPU->RF = P0_SET|P1_SET;
    
    *lCPU->RA = 0xAA;

    
    *lCPU->RA = 0x00;
    *lCPU->RE = 0x00EF;
        
     print_mem(lCPU->MemByte,256);
    
    for(int i = 0; i < 32; i++){
        printf("Pushing: %u \n", *lCPU->RA);
        cpu_push_re_ra(lCPU);

        if((*lCPU->RF&E_SET)==0){
            cpu_inc_ra(lCPU);
        }
    }
    
    print_mem(lCPU->MemByte,256);
    
    printf("%u\n", *lCPU->RA);
    printf("%u\n", *lCPU->RF);
    
    *lCPU->RA = 0xAA;
    *lCPU->RB = 0xBB;
    *lCPU->RC = 0xCC;
    *lCPU->RI = 0xDD;
    *lCPU->RD = 0xEEFF;
    
    *lCPU->RE = 0x0005;
    
    for(int i = 0; i < 4; i++){
        cpu_pop_re_rr(lCPU);
        print_mem(lCPU->MemByte,256);
    }
    
    
    
    //int passed = assert_address(*lCPU->RE, expected );
    //print_address_result("0x36", "inc_re_ds", *lCPU->RE, expected, *lCPU->RS, 0, 0, 0, passed);
    int passed = 1;
    
    free(lCPU);
    return passed;
}