#include "tests.h"

// Test for basic increment RA
int test_cpu_inc_ra() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 0xFE; // Initial value close to overflow
    cpu_inc_ra(lCPU);
    
    int passed = (*lCPU->RA == 0xFF) && ((*lCPU->RS & Z_SET) == 0) && ((*lCPU->RS & S_SET) != 0);
    print_int_result("0x30", "inc_ra", *lCPU->RA, 0xFF, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RB with zero flag
int test_cpu_inc_rb_zero_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RB = 0xFF; // Initial value
    cpu_inc_rb(lCPU);
    
    int passed = (*lCPU->RB == 0x00) && ((*lCPU->RS & Z_SET) != 0) && ((*lCPU->RS & S_SET) == 0);
    print_int_result("0x31", "inc_rb_zero_flag", *lCPU->RB, 0x00, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RC with carry flag
int test_cpu_inc_rc_carry_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RC = 0xFF; // Initial value
    cpu_inc_rc(lCPU);
    
    int passed = (*lCPU->RC == 0x00) && ((*lCPU->RS & Z_SET) != 0) && ((*lCPU->RS & C_SET) != 0);
    print_int_result("0x32", "inc_rc_carry_flag", *lCPU->RS, Z_SET|C_SET, 0, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RD by WORDSIZE
int test_cpu_inc_rd_ws() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RD = 0xFE; // Initial value close to overflow
    cpu_inc_rd_ws(lCPU);
    
    AddressType expected = 0x00FE + WORDSIZE;
    
    int passed = assert_address(*lCPU->RD, expected );
    print_address_result("0x36", "inc_re_ds", *lCPU->RD, expected, *lCPU->RS, 0, 0, 0, passed);
    
    free(lCPU);
    return passed;
}

// Test for increment RE by ADDRSIZE
int test_cpu_inc_re_ds() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RE = 0xFE; // Initial value close to overflow
    cpu_inc_re_as(lCPU);
    
    AddressType expected = 0x00FE + ADDRSIZE;
    
    int passed = assert_address(*lCPU->RE, expected );
    print_address_result("0x36", "inc_re_ds", *lCPU->RE, expected, *lCPU->RS, 0, 0, 0, passed);

    
    free(lCPU);
    return passed;
}

// Add more tests as needed for other increment instructions...
