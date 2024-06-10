#include "tests.h"

// Test for basic increment RA
int test_cpu_inc_ra() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 0xFE; // Initial value close to overflow
    cpu_inc_ra(lCPU);
    
    int passed = (*lCPU->vRA == 0xFF) && ((*lCPU->vRS & Z_SET) == 0) && ((*lCPU->vRS & S_SET) != 0);
    print_int_result("0x30", "inc_ra", *lCPU->vRA, 0xFF, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RB with zero flag
int test_cpu_inc_rb_zero_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRB = 0xFF; // Initial value
    cpu_inc_rb(lCPU);
    
    int passed = (*lCPU->vRB == 0x00) && ((*lCPU->vRS & Z_SET) != 0) && ((*lCPU->vRS & S_SET) == 0);
    print_int_result("0x31", "inc_rb_zero_flag", *lCPU->vRB, 0x00, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RC with carry flag
int test_cpu_inc_rc_carry_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRC = 0xFF; // Initial value
    cpu_inc_rc(lCPU);
    
    int passed = (*lCPU->vRC == 0x00) && ((*lCPU->vRS & Z_SET) != 0) && ((*lCPU->vRS & C_SET) != 0);
    print_int_result("0x32", "inc_rc_carry_flag", *lCPU->vRS, Z_SET|C_SET, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RD by WORDSIZE
int test_cpu_inc_rd_ws() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRD = 0xFE; // Initial value close to overflow
    cpu_inc_rd_ws(lCPU);
    
    int passed = (*lCPU->vRD == 0xFE + WORDSIZE) && ((*lCPU->vRS & S_SET) != 0);
    print_int_result("0x33", "inc_rd_ws", *lCPU->vRD, 0xFE + WORDSIZE, 0, 0, 0, 0, passed);
    print_int_result("0x33", "inc_rd_ws (flags)", *lCPU->vRS, S_SET, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RE by ADDRSIZE
int test_cpu_inc_re_ds() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRE = 0xFE; // Initial value close to overflow
    cpu_inc_re_ds(lCPU);
    
    CPUType expected = 0xFE + ADDRSIZE;
    
    int passed = (*lCPU->vRE == expected ) && ((*lCPU->vRS & Z_SET) != 0) && ((*lCPU->vRS & C_SET) != 0);
    print_int_result("0x36", "inc_re_ds", *lCPU->vRE, expected, 0, 0, 0, 0, passed);
    print_int_result("0x36", "inc_re_ds (flags)", *lCPU->vRS, Z_SET|C_SET + ADDRSIZE, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Add more tests as needed for other increment instructions...
