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
    
    //for(int i = 0; i < 32; i++){
    //    cpu_push_sp_ra(lCPU);
    //}
    
    print_mem(lCPU->MemByte,256);
    
    printf("%u", *lCPU->RF);
    
    
    //int passed = assert_address(*lCPU->RE, expected );
    //print_address_result("0x36", "inc_re_ds", *lCPU->RE, expected, *lCPU->RS, 0, 0, 0, passed);
    int passed = 1;
    
    free(lCPU);
    return passed;
}