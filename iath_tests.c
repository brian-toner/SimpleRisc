#include "tests.h"




// Test for basic addition
int test_cpu_add_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->RA = 10;
    *lCPU->RB = 20;
    
    cpu_add(lCPU);
    int passed = *lCPU->RA == 30;
    
    print_int_result("0x01", "add", *lCPU->RA, 30, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for unsigned overflow and CF flag
// Assuming CPUType is an unsigned 8-bit type for this test
int test_cpu_add_zero_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 25;
    *lCPU->RB = -25; // Assuming CPUType supports negative values

    cpu_add(lCPU);
    CPUType actualFlags = *lCPU->RS & Z_SET;
    CPUType expectedFlags = Z_SET; // Expecting Zero Flag to be set
    int passed = (*lCPU->RA == 0) && (actualFlags & Z_SET);

    print_int_result("0x01", "add_zero", *lCPU->RA, 0, actualFlags, expectedFlags,0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_add_carry_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 200;
    *lCPU->RB = 100;

    cpu_add(lCPU);
    
    CPUType actualFlags = *lCPU->RS & C_SET;
    CPUType expectedFlags = C_SET; // Expecting Carry Flag to be set
    int passed = actualFlags != 0;

    print_int_result("0x01", "add_carry", *lCPU->RA, 44, actualFlags, expectedFlags, 0, 0, passed);
    free(lCPU);
    return passed;
}


// Test for signed overflow and OF flag
// This test assumes CPUType is an 8-bit signed integer
int test_cpu_add_overflow_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;  // Close to the max value of a signed 8-bit int
    *lCPU->RB = 50;

    cpu_add(lCPU);
    
    CPUType actualFlags = *lCPU->RS ;
    CPUType expectedFlags = S_SET|O_SET; // Expecting Overflow Flag to be set
    int passed = actualFlags != 0;

    print_int_result("0x01", "add_overflow", *lCPU->RA, 150, actualFlags, expectedFlags, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 50;
    *lCPU->RB = 20;
    
    cpu_sub(lCPU);
    int passed = *lCPU->RA == 30;

    print_int_result("0x02", "sub_basic", *lCPU->RA, 30, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_zero_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 20;
    *lCPU->RB = 20;

    cpu_sub(lCPU);
    
    CPUType actualFlags = *lCPU->RS & Z_SET;
    CPUType expectedFlags = Z_SET;
    int passed = (*lCPU->RA == 0) && (actualFlags == expectedFlags);

    print_int_result("0x02", "sub_zero", *lCPU->RA, 0, actualFlags, expectedFlags, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_carry_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 20;
    *lCPU->RB = 50;

    cpu_sub(lCPU);
    
    CPUType actualFlags = *lCPU->RS & C_SET;
    CPUType expectedFlags = C_SET;
    int passed = (actualFlags == expectedFlags);

    print_int_result("0x02", "sub_carry", *lCPU->RA, -30, actualFlags, expectedFlags, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_overflow_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 50; // Close to the max value of a signed 8-bit int
    *lCPU->RB = -100;

    cpu_sub(lCPU);
    
    CPUType actualFlags = *lCPU->RS & O_SET;
    CPUType expectedFlags = O_SET;
    int passed = (actualFlags == expectedFlags);

    print_int_result("0x02", "sub_overflow", *lCPU->RA, 150, actualFlags, expectedFlags, 0, 0, passed);
    free(lCPU);
    return passed;
}


int test_cpu_qadd(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 50;
    CPUType v2 = rand() % 50;
    CPUType res = v1+v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qadd(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qadd", *lCPU->RA, res, passed);
    print_int_result("0x00", "qadd", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
    
}

int test_cpu_qsub(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 50;
    CPUType v2 = rand() % 50;
    CPUType res = v1-v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qsub(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qsub", *lCPU->RA, res, passed);
    print_int_result("0x01", "qsub", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}

int test_cpu_qmul(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 15;
    CPUType v2 = rand() % 15;
    CPUType res = v1*v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qmul(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qmul", *lCPU->RA, res, passed);
    print_int_result("0x02", "qmul", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}


int test_cpu_qdiv(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = rand() % 15+1;
    CPUType res = v1/v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qdiv(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qdiv", *lCPU->RA, res, passed);
    print_int_result("0x03", "qdiv", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}


int test_cpu_qmod(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = (rand() % 254)+1;
    CPUType res = v1%v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qmod(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qmod", *lCPU->RA, res, passed);
    print_int_result("0x04", "qmod", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}

int test_cpu_stb(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = 0;
    CPUType v2 = (rand() % (sizeof(CPUType)*8) );
    CPUType res = (v1)|(1<<v2);
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_stb(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_stb", *lCPU->RA, res, passed);
    print_int_result("0x05", "stb", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}


int test_cpu_clb(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = ~0;
    CPUType v2 = (rand() % (sizeof(CPUType)*8) );
    CPUType res = (v1)&(~(1<<(v2)));
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_clb(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_clb", *lCPU->RA, res, passed);
    print_int_result("0x06", "clb", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}


int test_cpu_qnot(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = (rand() % 255);
    CPUType res = ~v1;
    
    *lCPU->RA = v1;
    
    cpu_qnot(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qnot", *lCPU->RA, res, passed);
    print_int_result("0x07", "qnot", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}

int test_cpu_qand(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = (rand() % 255);
    CPUType res = v1&v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qand(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qand", *lCPU->RA, res, passed);
    print_int_result("0x08", "qand", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}

int test_cpu_qor(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = (rand() % 255);
    CPUType res = v1|v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qor(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qor", *lCPU->RA, res, passed);
    print_int_result("0x09", "qor", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}

int test_cpu_qxor(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = (rand() % 255);
    CPUType res = v1^v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qxor(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qxor", *lCPU->RA, res, passed);
    print_int_result("0x0A", "qxor", *lCPU->RA, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
}

int test_cpu_qshl(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = (rand() % (sizeof(CPUType)*8));
    CPUType res = v1<<v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qshl(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qshl", *lCPU->RA, res, passed);
    print_int_result("0x0B", "qshl", *lCPU->RA, res, 0, 0, 0, 0, passed); 
    
    free(lCPU);
    
    return passed;
}

int test_cpu_qshr(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 255;
    CPUType v2 = (rand() % (sizeof(CPUType)*8));
    CPUType res = v1>>v2;
    
    *lCPU->RA = v1;
    *lCPU->RB = v2;
    
    cpu_qshr(lCPU);
    int passed = *lCPU->RA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qshr", *lCPU->RA, res, passed);
    print_int_result("0x0C", "qshr", *lCPU->RA, res, 0, 0, 0, 0, passed); 
    
    free(lCPU);
    
    return passed;
}

/////////

// Test for multiplication
int test_cpu_mul_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 6;
    *lCPU->RB = 7;

    cpu_mul(lCPU);
    int passed = (*lCPU->RA == 42) && ((*lCPU->RS & CZOS_MASK) == 0);

    print_int_result("0x12", "mul_basic", *lCPU->RA, 42, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for division
int test_cpu_div_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;
    *lCPU->RB = 4;

    cpu_div(lCPU);
    int passed = (*lCPU->RA == 25) && ((*lCPU->RS & CZOS_MASK) == 0);

    print_int_result("0x13", "div_basic", *lCPU->RA, 25, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for division by zero
int test_cpu_div_by_zero() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;
    *lCPU->RB = 0;

    cpu_div(lCPU);
    CPUType actualFlags = *lCPU->RS & U_SET;
    CPUType expectedFlags = U_SET; // Undefined flag expected
    int passed = (actualFlags == expectedFlags);

    print_int_result("0x13", "div_by_zero", *lCPU->RA, 100, actualFlags, expectedFlags, 0, 0, passed);

    free(lCPU);
    return passed;
}

// Test for modulus
int test_cpu_mod_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;
    *lCPU->RB = 30;

    cpu_mod(lCPU);
    int passed = (*lCPU->RA == 10) && ((*lCPU->RS & CZOS_MASK) == 0);

    print_int_result("0x14", "mod_basic", *lCPU->RA, 10, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for modulus by zero
int test_cpu_mod_by_zero() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;
    *lCPU->RB = 0;

    cpu_mod(lCPU);
    CPUType actualFlags = *lCPU->RS & U_SET;
    CPUType expectedFlags = U_SET; // Undefined flag expected
    int passed = (actualFlags == expectedFlags);

    print_int_result("0x14", "mod_by_zero", *lCPU->RA, 100, actualFlags, expectedFlags, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for bit set
int test_cpu_setb_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 0;
    *lCPU->RB = 3; // Set the 3rd bit

    cpu_setb(lCPU);
    int passed = (*lCPU->RA == 8); // 8 is 2^3

    print_int_result("0x15", "setb_basic", *lCPU->RA, 8, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for bit clear
int test_cpu_clrb_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 15; // 1111 in binary
    *lCPU->RB = 2; // Clear the 2nd bit

    cpu_clrb(lCPU);
    int passed = (*lCPU->RA == 0b1011); // 1011 in binary

    print_int_result("0x16", "clrb_basic", *lCPU->RA, 0b1011, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for bitwise NOT
int test_cpu_not_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 0xF0; // Some arbitrary value

    cpu_not(lCPU);
    int passed = (*lCPU->RA == 0x0F); // Complement of 0xF0

    print_int_result("0x17", "not_basic", *lCPU->RA, 0x0F, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for bitwise AND
int test_cpu_and_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 0xF0;
    *lCPU->RB = 0x0F;

    cpu_and(lCPU);
    int passed = (*lCPU->RA == 0x00);

    print_int_result("0x18", "and_basic", *lCPU->RA, 0x00, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for bitwise OR
int test_cpu_or_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 0xF0;
    *lCPU->RB = 0x0F;

    cpu_or(lCPU);
    int passed = (*lCPU->RA == 0xFF);

    print_int_result("0x19", "or_basic", *lCPU->RA, 0xFF, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for bitwise XOR
int test_cpu_xor_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 0xF0;
    *lCPU->RB = 0x0F;

    cpu_xor(lCPU);
    int passed = (*lCPU->RA == 0xFF);

    print_int_result("0x1A", "xor_basic", *lCPU->RA, 0xFF, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for shift left
int test_cpu_shl_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 1;
    *lCPU->RB = 3; // Shift left by 3 bits

    cpu_shl(lCPU);
    int passed = (*lCPU->RA == 8); // 1 << 3 is 8

    print_int_result("0x1B", "shl_basic", *lCPU->RA, 8, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for shift right
int test_cpu_shr_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 8;
    *lCPU->RB = 3; // Shift right by 3 bits

    cpu_shr(lCPU);
    int passed = (*lCPU->RA == 1); // 8 >> 3 is 1

    print_int_result("0x1C", "shr_basic", *lCPU->RA, 1, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for add with carry
// Test for add with carry
int test_cpu_addc_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;
    *lCPU->RB = 55;
    *lCPU->RS = C_SET; // Set carry flag

    cpu_adc(lCPU);
    int passed = assert_int(*lCPU->RA,156) && assert_int(*lCPU->RS, O_SET|S_SET ) ;

    print_int_result("0x1D", "addc_basic", *lCPU->RA, 156, *lCPU->RS, O_SET|S_SET, 0, 0, passed);
    free(lCPU);
    return passed;
}


// Test for subtract with borrow
int test_cpu_subb_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 100;
    *lCPU->RB = 55;
    *lCPU->RS = C_SET; // Set carry flag

    cpu_sbb(lCPU);
    int passed = assert_int(*lCPU->RA, 44) && assert_int(*lCPU->RS, 0);

    print_int_result("0x1E", "subb_basic", *lCPU->RA, 44, *lCPU->RS, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

// Test for two's complement
int test_cpu_twos_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->RA = 50;

    cpu_twos(lCPU);
    int passed = (*lCPU->RA == (CPUType)-50); // Two's complement of 50

    print_int_result("0x1F", "twos_basic", *lCPU->RA, (CPUType)-50, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}