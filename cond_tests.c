#include "tests.h"

// Test for set_t_flag: condition 000 0
int test_set_t_flag_000_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = 0; // X=0, T=0
    set_t_flag(lCPU, 0);
    int passed = (*lCPU->vRS & T_SET) == 0;

    print_flag_result("", "set_t_flag 000 0", *lCPU->vRS, 0, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 001 0
int test_set_t_flag_001_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = T_SET; // X=0, T=1
    set_t_flag(lCPU, 0);
    int passed = (*lCPU->vRS & T_SET) != 0;

    print_flag_result("", "set_t_flag 001 1", *lCPU->vRS, 0, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 010 0
int test_set_t_flag_010_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = X_SET; // X=1, T=0
    set_t_flag(lCPU, 0);
    int passed = (*lCPU->vRS & T_SET) == 0;

    print_flag_result("", "set_t_flag 010 0", *lCPU->vRS, 0, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 011 1
int test_set_t_flag_011_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = X_SET | T_SET; // X=1, T=1
    set_t_flag(lCPU, 0);
    int passed = (*lCPU->vRS & T_SET) == 0;

    print_flag_result("", "set_t_flag 011 0", *lCPU->vRS, T_SET, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 100 0
int test_set_t_flag_100_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = 0; 
    set_t_flag(lCPU, 1);
    int passed = (*lCPU->vRS & T_SET) != 0;

    print_flag_result("", "set_t_flag 100 1", *lCPU->vRS, 0, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 101 1
int test_set_t_flag_101_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = T_SET; 
    set_t_flag(lCPU, 1);
    int passed = (*lCPU->vRS & T_SET) != 0;

    print_flag_result("", "set_t_flag 101 1", *lCPU->vRS, T_SET, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 110 0
int test_set_t_flag_110_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = X_SET; 
    set_t_flag(lCPU, 1);
    int passed = (*lCPU->vRS & T_SET) == 0;

    print_flag_result("", "set_t_flag 110 0", *lCPU->vRS, T_SET, passed);
    free(lCPU);
    return passed;
}

// Test for set_t_flag: condition 111 1
int test_set_t_flag_111_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = X_SET | T_SET; // X=1 shifted to T position, X=1, T=1
    set_t_flag(lCPU, 1);
    int passed = (*lCPU->vRS & T_SET) != 0;

    print_flag_result("", "set_t_flag 111 1", *lCPU->vRS, T_SET, passed);
    free(lCPU);
    return passed;
}

int test_cpu_fgt_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = float_to_cputype(2.5);
    *cpu->vRB = float_to_cputype(1.5);
    cpu_fgt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x58", "test_cpu_fgt_ra_rb", 1, 1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_fgt_ra_rb_inf() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = float_to_cputype(100000);
    *cpu->vRB = float_to_cputype(-100000);
    cpu_fgt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET|N_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x58", "test_cpu_fgt_ra_rb_inf", 1, 1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_fgt_ra_rb_undef() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = float_to_cputype(100000);
    *cpu->vRB = 128; //F2M_NAN
    cpu_fgt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = N_SET|U_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x58", "test_cpu_fgt_ra_rb_und", 1, 1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}