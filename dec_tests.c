#include "tests.h"

int test_cpu_dec_ra_zero() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 1;
    cpu_dec_ra(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = Z_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RA, 0) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_ra_zero", *cpu->RA, 0, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

// Test for negative result
int test_cpu_dec_ra_negative() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 0;
    cpu_dec_ra(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = S_SET | C_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RA, (CPUType)(-1)) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_ra_negative", *cpu->RA, (CPUType)(-1), actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

// Test for positive result
int test_cpu_dec_ra_positive() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 0x10;
    cpu_dec_ra(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = 0;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RA, 0x0F) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_ra_positive", *cpu->RA, 0x0F, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

// Test for underflow with overflow flag
int test_cpu_dec_ra_underflow() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RA = 0x80;
    cpu_dec_ra(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = O_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RA, 0x7F) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_ra_underflow", *cpu->RA, 0x7F, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}


// RB

 int test_cpu_dec_rb_zero() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RB = 1;
    cpu_dec_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = Z_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RB, 0) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_rb_zero", *cpu->RB, 0, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

// Test for negative result
int test_cpu_dec_rb_negative() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RB = 0;
    cpu_dec_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = S_SET | C_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RB, (CPUType)(-1)) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_rb_negative", *cpu->RB, (CPUType)(-1), actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

// Test for positive result
int test_cpu_dec_rb_positive() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RB = 0x10;
    cpu_dec_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = 0;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RB, 0x0F) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_rb_positive", *cpu->RB, 0x0F, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}

// Test for underflow with overflow flag
int test_cpu_dec_rb_underflow() {
    int memsize = 256;
    Risc256* cpu = cpu_init(memsize);

    *cpu->RB = 0x80;
    cpu_dec_rb(cpu);

    CPUType actualStatusFlags = *cpu->RS;
    CPUType expectedStatusFlags = O_SET;
    CPUType actualSystemFlags = *cpu->RF;
    CPUType expectedSystemFlags = 0;
    int passed = assert_int(*cpu->RB, 0x7F) && assert_int(actualStatusFlags, expectedStatusFlags) && assert_int(actualSystemFlags, expectedSystemFlags);
    print_int_result("0x40", "test_cpu_dec_rb_underflow", *cpu->RB, 0x7F, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed);
    
    free(cpu);
    return passed;
}