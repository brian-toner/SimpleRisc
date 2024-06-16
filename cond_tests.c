#include "tests.h"


int test_set_t_flag_0_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = 0; // X=0, T=0
    set_t_flag(lCPU, 0);
    int passed = (*lCPU->vRS & T_SET) == 0;

    print_flag_result("", "set_t_flag 0 0", *lCPU->vRS, 0, passed);
    free(lCPU);
    return passed;
}

int test_set_t_flag_1_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRS = 0; // X=0, T=0
    set_t_flag(lCPU, 1);
    int passed = (*lCPU->vRS & T_SET) != 0;

    print_flag_result("", "set_t_flag 1 1", *lCPU->vRS, T_SET, passed);
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
    CPUType expectedStatusFlags = T_SET;
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
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
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

    *cpu->vRA = 10;
    *cpu->vRB = 5;
    cpu_gt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->vRS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x50", "test_cpu_gt_ra_rb", 1,1, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_lt_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = 5;
    *cpu->vRB = 10;
    cpu_lt_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->vRS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x51", "test_cpu_lt_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_eq_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = 10;
    *cpu->vRB = 10;
    cpu_eq_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->vRS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x52", "test_cpu_eq_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_ge_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = 10;
    *cpu->vRB = 5;
    cpu_ge_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->vRS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x53", "test_cpu_ge_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    *cpu->vRA = 10;
    *cpu->vRB = 10;
    cpu_ge_ra_rb(cpu);
    passed &= assert_int(*cpu->vRS & T_SET, T_SET);
    print_int_result("0x53", "test_cpu_ge_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_le_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = 5;
    *cpu->vRB = 10;
    cpu_le_ra_rb(cpu);

    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->vRS & T_SET, T_SET) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x54", "test_cpu_le_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    *cpu->vRA = 10;
    *cpu->vRB = 10;
    cpu_le_ra_rb(cpu);
    passed &= assert_int(*cpu->vRS & T_SET, T_SET);
    print_int_result("0x54", "test_cpu_le_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

int test_cpu_ne_ra_rb() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->vRA = 10;
    *cpu->vRB = 5;
    cpu_ne_ra_rb(cpu);


    int passed = assert_int(*cpu->vRS & T_SET, T_SET) && assert_int(*cpu->vRS, T_SET);
    CPUType actualStatusFlags = *cpu->vRS;
    CPUType expectedStatusFlags = T_SET;
    CPUType actualSystemFlags = *cpu->vRF;
    CPUType expectedSystemFlags = 0;
    
    print_int_result("0x55", "test_cpu_ne_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    *cpu->vRA = 10;
    *cpu->vRB = 10;
    cpu_ne_ra_rb(cpu);
    actualStatusFlags = *cpu->vRS;// & T_CLR;
    expectedStatusFlags = 0;
    
    passed = assert_int(*cpu->vRS, 0);
    print_int_result("0x55", "test_cpu_ne_ra_rb", 1,1,actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}