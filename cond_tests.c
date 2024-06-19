#include "tests.h"


int test_set_t_flag_0_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RS = 0; // X=0, T=0
    set_t_flag(lCPU, 0);
    int passed = assert_int(*lCPU->RS, 0);

    print_flag_result("", "set_t_flag 0 0", *lCPU->RS, 0, passed);
    free(lCPU);
    return passed;
}

int test_set_t_flag_1_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RS = 0; // X=0, T=0
    set_t_flag(lCPU, 1);
    int passed = (*lCPU->RS & T_SET) != 0;

    print_flag_result("", "set_t_flag 1 1", *lCPU->RS, T_SET, passed);
    free(lCPU);
    return passed;
}

int test_cpu_fgt_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = float_to_cputype(2.5);
    *cpu->RB = float_to_cputype(1.5);
    cpu_fgt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x58", "test_cpu_fgt_ra_rb", 1, 1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_fgt_ra_rb_inf() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = float_to_cputype(100000);
    *cpu->RB = float_to_cputype(-100000);
    cpu_fgt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x58", "test_cpu_fgt_ra_rb_inf", 1, 1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_fgt_ra_rb_undef() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = float_to_cputype(100000);
    *cpu->RB = 128; //F2M_NAN
    cpu_fgt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x58", "test_cpu_fgt_ra_rb_und", 1, 1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

////

int test_cpu_gt_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 10;
    *cpu->RB = 5;
    cpu_gt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x50", "test_cpu_gt_ra_rb", 1,1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_lt_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 5;
    *cpu->RB = 10;
    cpu_lt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x51", "test_cpu_lt_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_eq_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 10;
    *cpu->RB = 10;
    cpu_eq_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x52", "test_cpu_eq_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_ge_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 10;
    *cpu->RB = 5;
    cpu_ge_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x53", "test_cpu_ge_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    *cpu->RA = 10;
    *cpu->RB = 10;
    cpu_ge_ra_rb(cpu);
    passed &= assert_int(*cpu->RS & T_SET, T_SET);
    print_int_result("0x53", "test_cpu_ge_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_le_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 5;
    *cpu->RB = 10;
    cpu_le_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = 0;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RS & T_SET, 0) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x54", "test_cpu_le_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    *cpu->RA = 10;
    *cpu->RB = 10;
    cpu_le_ra_rb(cpu);
    passed &= assert_int(*cpu->RS & T_SET, T_SET);
    print_int_result("0x54", "test_cpu_le_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_ne_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 10;
    *cpu->RB = 5;
    cpu_ne_ra_rb(cpu);


    int passed = assert_int(*cpu->RS & T_SET, T_SET) && assert_int(*cpu->RS, T_SET);
    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    
    print_int_result("0x55", "test_cpu_ne_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    *cpu->RA = 10;
    *cpu->RB = 10;
    cpu_ne_ra_rb(cpu);
    actualStatusFlags = *cpu->RS;
    expectedStatusFlags = 0;
    
    passed = assert_int(*cpu->RS, 0);
    print_int_result("0x55", "test_cpu_ne_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}