#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CPU.h"
#include "output.h"
#include "instructions.h"
#include "tests.h"
#include <string.h>


int assert_float(CPUFloat actual, CPUFloat expected, CPUFloat tolerance){
    return (actual<=(expected+tolerance))&&(actual>=(expected-tolerance));
}

int assert_int(CPUType actual, CPUType expected){
    return (actual==expected);
}

int assert_uint(CPUSWord actual, CPUSWord expected){
    return (actual==expected);
}

void hl(){
    printf("|-------|----------------------|---------|---------|---------|\n");
}


void labels(){
    hl();
    printf("| %-5s | %-20s | %-7s | %-7s | %-7s |\n", "OP", "Test Name", "Act", "Exp", "Pass");
    hl();
}

void header(char* testName){
    hl();
    printf("| %-5s | %-20s | %-7s | %-7s | %-7s |\n", "", testName, "", "", "");
    hl();
}


int print_float_result(const char* opcode, const char* testName, CPUFloat actual, CPUFloat expected, int passed){
    printf("| %-5s | %-20s | %-7.2f | %-7.2f | %-7d |\n", opcode, testName, actual, expected, passed);
}

int print_string_result(const char* opcode, const char* testName, char* actual, char* expected, int passed){
    printf("| %-5s | %-20s | %-7s | %-7s | %-7d |\n", opcode, testName, actual, expected, passed);
}

int print_int_result(const char* opcode, const char* testName, CPUType* actual, CPUType* expected, int passed){
    printf("| %-5s | %-20s | %-7d | %-7d | %-7d |\n", opcode, testName, actual, expected, passed);
}

int print_uint_result(const char* opcode, const char* testName, char* actual, char* expected, int passed){
    printf("| %-5s | %-20s | %-7u | %-7u | %-7d |\n", opcode, testName, actual, expected, passed);
}

int print_flag_result(const char* opcode, const char* testName, CPUType actual, CPUType expected, int passed) {
    printf("| %-5s | %-20s | %-7d | %-7d | %-7d |\n", opcode, testName, actual, expected, passed);
}

int test_cpu_set_FFFF() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->vPC = 128;
    lCPU->vMemByte[128] = 0x0F; // SET 0
    
    cpu_set(lCPU);
    cpu_set(lCPU);
    cpu_set(lCPU);
    cpu_set(lCPU);
    
    int passed = *lCPU->vRR == 65535;
    
    //print_mem(lCPU->vMemByte, memsize);
    
    print_uint_result("0x00", "set_0f0f0f0f", *lCPU->vRR, 65535, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_ABCD() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->vPC = 128;
    lCPU->vMemByte[128] = 0x0A; // SET 0
    cpu_set(lCPU);
    
    lCPU->vMemByte[128] = 0x0B; // SET 0
    cpu_set(lCPU);
    
    lCPU->vMemByte[128] = 0x0C; // SET 0
    cpu_set(lCPU);
    
    lCPU->vMemByte[128] = 0x0D; // SET 0
    cpu_set(lCPU);
    
    int passed = *lCPU->vRR == 0xABCD;
    
    //print_mem(lCPU->vMemByte, memsize);
    
    print_uint_result("0x00", "set_0a0b0c0d", *lCPU->vRR, 0xABCD, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_BCDE() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->vPC = 128;
    lCPU->vMemByte[128] = 0x0A; // SET 0
    cpu_set(lCPU);
    
    lCPU->vMemByte[128] = 0x0B; // SET 0
    cpu_set(lCPU);
    
    lCPU->vMemByte[128] = 0x0C; // SET 0
    cpu_set(lCPU);
    
    lCPU->vMemByte[128] = 0x0D; // SET 0
    cpu_set(lCPU);

    lCPU->vMemByte[128] = 0x0E; // SET 0
    cpu_set(lCPU);
    
    int passed = *lCPU->vRR == 0xBCDE;
    
    //print_mem(lCPU->vMemByte, memsize);
    
    print_uint_result("0x00", "set_0a0b0c0d0e", *lCPU->vRR, 0xBCDE, passed);
    free(lCPU);
    return passed;
}


int test_cpu_set_alt_BCDE() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_A(lCPU);
    cpu_set_B(lCPU);
    cpu_set_C(lCPU);
    cpu_set_D(lCPU);
    cpu_set_E(lCPU);
    
    int passed = *lCPU->vRR == 0xBCDE;
    
    //print_mem(lCPU->vMemByte, memsize);
    
    print_uint_result("0x00", "set_0a0b0c0d0e", *lCPU->vRR, 0xBCDE, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_0123() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_0(lCPU);
    cpu_set_1(lCPU);
    cpu_set_2(lCPU);
    cpu_set_3(lCPU);
    
    int passed = *lCPU->vRR == 0x0123;
    
    print_uint_result("0x00", "set_010203", *lCPU->vRR, 0x0123, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_89AB() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_8(lCPU);
    cpu_set_9(lCPU);
    cpu_set_A(lCPU);
    cpu_set_B(lCPU);
    
    int passed = *lCPU->vRR == 0x89AB;
    
    print_uint_result("0x00", "set_08090a0b", *lCPU->vRR, 0x89AB, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_CDEF() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_C(lCPU);
    cpu_set_D(lCPU);
    cpu_set_E(lCPU);
    cpu_set_F(lCPU);
    
    int passed = *lCPU->vRR == 0xCDEF;
    
    print_uint_result("0x00", "set_0c0d0e0f", *lCPU->vRR, 0xCDEF, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_0A0B() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_0(lCPU);
    cpu_set_A(lCPU);
    cpu_set_0(lCPU);
    cpu_set_B(lCPU);
    
    int passed = *lCPU->vRR == 0x0A0B;
    
    print_uint_result("0x00", "set_000a000b", *lCPU->vRR, 0x0A0B, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_0(lCPU);
    
    int passed = *lCPU->vRR == 0x0;
    
    print_uint_result("0x0", "set_0", *lCPU->vRR, 0x0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_1(lCPU);
    
    int passed = *lCPU->vRR == 0x1;
    
    print_uint_result("0x1", "set_1", *lCPU->vRR, 0x1, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_2() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_2(lCPU);
    
    int passed = *lCPU->vRR == 0x2;
    
    print_uint_result("0x2", "set_2", *lCPU->vRR, 0x2, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_3() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_3(lCPU);
    
    int passed = *lCPU->vRR == 0x3;
    
    print_uint_result("0x3", "set_3", *lCPU->vRR, 0x3, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_4() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_4(lCPU);
    
    int passed = *lCPU->vRR == 0x4;
    
    print_uint_result("0x4", "set_4", *lCPU->vRR, 0x4, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_5() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_5(lCPU);
    
    int passed = *lCPU->vRR == 0x5;
    
    print_uint_result("0x5", "set_5", *lCPU->vRR, 0x5, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_6() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_6(lCPU);
    
    int passed = *lCPU->vRR == 0x6;
    
    print_uint_result("0x6", "set_6", *lCPU->vRR, 0x6, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_7() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_7(lCPU);
    
    int passed = *lCPU->vRR == 0x7;
    
    print_uint_result("0x7", "set_7", *lCPU->vRR, 0x7, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_8() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_8(lCPU);
    
    int passed = *lCPU->vRR == 0x8;
    
    print_uint_result("0x8", "set_8", *lCPU->vRR, 0x8, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_9() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_9(lCPU);
    
    int passed = *lCPU->vRR == 0x9;
    
    print_uint_result("0x9", "set_9", *lCPU->vRR, 0x9, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_A() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_A(lCPU);
    
    int passed = *lCPU->vRR == 0xA;
    
    print_uint_result("0xA", "set_A", *lCPU->vRR, 0xA, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_B() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_B(lCPU);
    
    int passed = *lCPU->vRR == 0xB;
    
    print_uint_result("0xB", "set_B", *lCPU->vRR, 0xB, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_C() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_C(lCPU);
    
    int passed = *lCPU->vRR == 0xC;
    
    print_uint_result("0xC", "set_C", *lCPU->vRR, 0xC, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_D() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_D(lCPU);
    
    int passed = *lCPU->vRR == 0xD;
    
    print_uint_result("0xD", "set_D", *lCPU->vRR, 0xD, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_E() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_E(lCPU);
    
    int passed = *lCPU->vRR == 0xE;
    
    print_uint_result("0xE", "set_E", *lCPU->vRR, 0xE, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_F() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_F(lCPU);
    
    int passed = *lCPU->vRR == 0xF;
    
    print_uint_result("0xF", "set_F", *lCPU->vRR, 0xF, passed);
    free(lCPU);
    return passed;
}

// Test for basic addition
int test_cpu_add_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->vRA = 10;
    *lCPU->vRB = 20;
    
    cpu_add(lCPU);
    int passed = *lCPU->vRA == 30;
    
    print_int_result("0x01", "add", *lCPU->vRA, 30, passed);
    free(lCPU);
    return passed;
}

// Test for unsigned overflow and CF flag
// Assuming CPUType is an unsigned 8-bit type for this test
int test_cpu_add_zero_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 25;
    *lCPU->vRB = -25; // Assuming CPUType supports negative values

    cpu_add(lCPU);
    CPUType actualFlags = *lCPU->vRS & Z_SET;
    CPUType expectedFlags = Z_SET; // Expecting Zero Flag to be set
    int passed = (*lCPU->vRA == 0) && (actualFlags & Z_SET);

    print_int_result("0x01", "add_zero", actualFlags, expectedFlags, passed);
    free(lCPU);
    return passed;
}

int test_cpu_add_carry_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 200;
    *lCPU->vRB = 100;

    cpu_add(lCPU);
    
    CPUType actualFlags = *lCPU->vRS & C_SET;
    CPUType expectedFlags = C_SET; // Expecting Carry Flag to be set
    int passed = actualFlags != 0;

    print_int_result("0x01", "add_carry", actualFlags, expectedFlags, passed);
    free(lCPU);
    return passed;
}


// Test for signed overflow and OF flag
// This test assumes CPUType is an 8-bit signed integer
int test_cpu_add_overflow_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 100;  // Close to the max value of a signed 8-bit int
    *lCPU->vRB = 50;

    cpu_add(lCPU);
    
    CPUType actualFlags = *lCPU->vRS & O_SET;
    CPUType expectedFlags = O_SET; // Expecting Overflow Flag to be set
    int passed = actualFlags != 0;

    print_int_result("0x01", "add_overflow", actualFlags, expectedFlags, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_basic() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 50;
    *lCPU->vRB = 20;
    
    cpu_sub(lCPU);
    int passed = *lCPU->vRA == 30;

    print_int_result("0x02", "sub_basic", *lCPU->vRA, 30, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_zero_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 20;
    *lCPU->vRB = 20;

    cpu_sub(lCPU);
    
    CPUType actualFlags = *lCPU->vRS & Z_SET;
    CPUType expectedFlags = Z_SET;
    int passed = (*lCPU->vRA == 0) && (actualFlags == expectedFlags);

    print_flag_result("0x02", "sub_zero", actualFlags, expectedFlags, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_carry_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 20;
    *lCPU->vRB = 50;

    cpu_sub(lCPU);
    
    CPUType actualFlags = *lCPU->vRS & C_SET;
    CPUType expectedFlags = C_SET;
    int passed = (actualFlags == expectedFlags);

    print_flag_result("0x02", "sub_carry", actualFlags, expectedFlags, passed);
    free(lCPU);
    return passed;
}

int test_cpu_sub_overflow_flag() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0;

    *lCPU->vRA = 50; // Close to the max value of a signed 8-bit int
    *lCPU->vRB = -100;

    cpu_sub(lCPU);
    
    CPUType actualFlags = *lCPU->vRS & O_SET;
    CPUType expectedFlags = O_SET;
    int passed = (actualFlags == expectedFlags);

    print_flag_result("0x02", "sub_overflow", actualFlags, expectedFlags, passed);
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qadd(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qadd", *lCPU->vRA, res, passed);
    print_int_result("0x00", "qadd", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qsub(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qsub", *lCPU->vRA, res, passed);
    print_int_result("0x01", "qsub", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qmul(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qmul", *lCPU->vRA, res, passed);
    print_int_result("0x02", "qmul", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qdiv(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qdiv", *lCPU->vRA, res, passed);
    print_int_result("0x03", "qdiv", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qmod(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qmod", *lCPU->vRA, res, passed);
    print_int_result("0x04", "qmod", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_stb(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_stb", *lCPU->vRA, res, passed);
    print_int_result("0x05", "stb", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_clb(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_clb", *lCPU->vRA, res, passed);
    print_int_result("0x06", "clb", *lCPU->vRA, res, passed);
    
    free(lCPU);
    
    return passed;
}


int test_cpu_qnot(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = (rand() % 255);
    CPUType res = ~v1;
    
    *lCPU->vRA = v1;
    
    cpu_qnot(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qnot", *lCPU->vRA, res, passed);
    print_int_result("0x07", "qnot", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qand(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qand", *lCPU->vRA, res, passed);
    print_int_result("0x08", "qand", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qor(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qor", *lCPU->vRA, res, passed);
    print_int_result("0x09", "qor", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qxor(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qxor", *lCPU->vRA, res, passed);
    print_int_result("0x0A", "qxor", *lCPU->vRA, res, passed);
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qshl(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qshl", *lCPU->vRA, res, passed);
    print_int_result("0x0B", "qshl", *lCPU->vRA, res, passed); 
    
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
    
    *lCPU->vRA = v1;
    *lCPU->vRB = v2;
    
    cpu_qshr(lCPU);
    int passed = *lCPU->vRA==res;

    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_qshr", *lCPU->vRA, res, passed);
    print_int_result("0x0C", "qshr", *lCPU->vRA, res, passed); 
    
    free(lCPU);
    
    return passed;
}

int test_cpu_its(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    CPUType v1 = sign*(rand() % 50);
    
    *lCPU->vRA = v1;
    *lCPU->vRE = 50;
    char lBuff[100];
    sprintf(lBuff,"%d", (CPUSWord)v1);
    
    cpu_set_addr(lCPU);
    
    cpu_its(lCPU);
        
    //print_mem(lCPU->vMemByte, memsize);
    int passed = strcmp((char*)lCPU->vREAddr, lBuff)==0;//*lCPU->vRA==res;

    //printf("%-20s | %-7s | %-7s | %-7d |\n", "test_cpu_its", (char*)lCPU->vREAddr, lBuff, passed);
    print_string_result("0x0D", "its", (char*)lCPU->vREAddr, lBuff, passed); 
    
    //printf("P: %d\n", passed);
    free(lCPU);
    
    return passed;
}

int test_cpu_sti_its(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    CPUSWord v1 = sign*(rand() % 128);
    
    char lBuff[10];
    sprintf(lBuff,"%d", v1);
    
    *lCPU->vRA = v1;
    *lCPU->vRE = 50;
    cpu_set_addr(lCPU);
    
    
    char* strval = lBuff;
    
    strcpy(lCPU->vREAddr, strval);
    cpu_qsti(lCPU);
    
    for(int i = 0; i < strlen(strval); i++){
        lCPU->vREAddr[i] = 0;
    }
    
    cpu_its(lCPU);
    
    
    //print_mem(lCPU->vMemByte, memsize);
    int passed = strcmp((char*)lCPU->vREAddr, strval)==0;//*lCPU->vRA==res;

    //printf("%-20s | %-7s | %-7s | %-7d |\n", "test_cpu_sti_its", (char*)lCPU->vREAddr, strval, passed);
    print_string_result("0x0E", "sti_its", (char*)lCPU->vREAddr, strval, passed); 
    
    //printf("P: %d\n", passed);
    free(lCPU);
    
    return passed;
}

int test_cpu_itf_fti(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    CPUSWord v1 = sign*(rand()%50)+5;
    *lCPU->vRA = v1;
    
    cpu_itf(lCPU);
    cpu_qfti(lCPU);
    CPUSWord ret = *lCPU->vRA;
    int passed = (ret<=v1+3) && (ret>=v1-3);
    
    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_itf_fti", ret, v1, passed);
    print_int_result("0x0F", "itf_fti", ret, v1, passed); 
    
    free(lCPU);
    
    return passed;    
}

//============================================================================//
// fath                                                                       //
//============================================================================//

int test_cpu_qfpow(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 7+1);
    CPUFloat v2 = (sign)*(rand() % 7+1);
    CPUFloat res = pow(v1,v2);
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_fexp(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 20);
    print_float_result("0x10", "fpow", ret, res, passed);

    free(lCPU);
    
    return passed;
    
}


int test_cpu_qfadd(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat sign2 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (sign1)*(rand() % 7+1);
    CPUFloat v2 = (sign2)*(rand() % 7+1);
    CPUFloat res = v1+v2;
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_qfadd(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x11", "fadd", ret, res, passed);

    free(lCPU);
    
    return passed;
    
}

int test_cpu_qfsub(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat sign2 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (sign1)*(rand() % 7+1);
    CPUFloat v2 = (sign2)*(rand() % 7+1);
    CPUFloat res = v1-v2;
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_qfsub(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x12", "fsub", ret, res, passed);

    free(lCPU);
    
    return passed;
    
}


int test_cpu_qfmul(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat sign2 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (sign1)*(rand() % 25+1);
    CPUFloat v2 = (sign2)*(rand() % 25+1);
    CPUFloat res = v1*v2;
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_qfmul(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 15);
    print_float_result("0x13", "fmul", ret, res, passed);

    free(lCPU);
    
    return passed;
    
}


int test_cpu_qfdiv(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat sign2 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (sign1)*(rand() % 5000);
    CPUFloat v2 = (sign2)*(rand() % 9999+1);
    CPUFloat res = v1/v2;
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_qfdiv(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x14", "fdiv", ret, res, passed);

    free(lCPU);
    
    return passed;
    
}

int test_cpu_qflogbn(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat sign2 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 9999+1);
    CPUFloat v2 = (rand() % 10+1);
    CPUFloat res = logbn(v1,v2);
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_qflogbn(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x15", "flogbn", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}


int test_cpu_qpi(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(sign*M_PI);
    //lCPU->vRB = float_to_cputype(4.0);

    cpu_qpi(lCPU);
    //cpu_qfmul(lCPU);
    //cpu_qfmul(lCPU);
    
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    
    int passed = assert_float(ret, sign*M_PI, 3);
    print_float_result("0x16", "pi", ret, sign*M_PI, passed);
    //printf("%-20s | %-7.3f | %-7.3f | %-7d |\n", "test_cpu_qpi", ret, sign*M_PI, passed);

    free(lCPU);
    
    return passed;
    
}


int test_cpu_qe(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->vRA = float_to_cputype(sign*M_E);
    //lCPU->vRB = float_to_cputype(4.0);

    cpu_qpi(lCPU);
    //cpu_qfmul(lCPU);
    //cpu_qfmul(lCPU);
    
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    
    int passed = assert_float(ret, sign*M_E, 3);
    print_float_result("0x17", "e", ret, sign*M_E, passed);
    //printf("%-20s | %-7.3f | %-7.3f | %-7d |\n", "test_cpu_qpi", ret, sign*M_PI, passed);

    free(lCPU);
    
    return passed;
    
}

int test_cpu_qsin(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 10000)/(10000.0);
    CPUFloat res = sin(v1);
    
    *lCPU->vRA = float_to_cputype(v1);

    cpu_qsin(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x18", "sin", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}

int test_cpu_qcos(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 10000)/(10000.0);
    CPUFloat res = cos(v1);
    
    *lCPU->vRA = float_to_cputype(v1);

    cpu_qcos(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x19", "cos", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}

int test_cpu_qtan(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 10000)/(10000.0);
    CPUFloat res = tan(v1);
    
    *lCPU->vRA = float_to_cputype(v1);

    cpu_qcos(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1A", "tan", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}


int test_cpu_qasin(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 10000)/(10000.0);
    CPUFloat res = asin(v1);
    
    *lCPU->vRA = float_to_cputype(v1);

    cpu_qsin(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1B", "asin", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}

int test_cpu_qacos(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = (rand() % 10000)/(10000.0);
    CPUFloat res = acos(v1);
    
    *lCPU->vRA = float_to_cputype(v1);

    cpu_qacos(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1C", "acos", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}


int test_cpu_qatan2(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign1 = (rand()%2?-1.0:1.0);
    CPUFloat sign2 = (rand()%2?-1.0:1.0);
    CPUFloat v1 = sign1*(rand() % 10000)/(10000.0);
    CPUFloat v2 = sign2*(rand() % 10000)/(10000.0);
    CPUFloat res = atan2(v1,v2);
    
    *lCPU->vRA = float_to_cputype(v1);
    *lCPU->vRB = float_to_cputype(v2);

    cpu_qatan2(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1D", "atan2", ret, res, passed);
    
    free(lCPU);
    
    return passed;
    
}

//cpu_qatan2

int test_cpu_stf_fts(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 50;
    
    *lCPU->vRA = v1;
    *lCPU->vRE = 50;
    cpu_set_addr(lCPU);
    char* strval = "-0.025";
    
    strcpy(lCPU->vREAddr, strval);
    cpu_qstf(lCPU);
    
    for(int i = 0; i < strlen(strval); i++){
        lCPU->vREAddr[i] = 0;
    }
    
    cpu_qfts(lCPU);
    
    
    //print_mem(lCPU->vMemByte, memsize);
    int passed = strcmp((char*)lCPU->vREAddr, strval)==0;//*lCPU->vRA==res;

    //printf("%-20s | %-7s | %-7s | %-7d |\n", "test_cpu_stf_fts", (char*)lCPU->vREAddr, strval, passed);
    print_string_result("0x1E", "test_cpu_stf_fts", (char*)lCPU->vREAddr, strval, passed);
    
    //printf("P: %d\n", passed);
    free(lCPU);
    
    return passed;
}

int test_cpu_fti_itf(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    CPUFloat v1 = sign*(CPUFloat)(rand()%255)/(CPUFloat)(rand()%64+1);
    CPUType v1f = float_to_cputype(v1);
    *lCPU->vRA = v1f;
    
    cpu_qfti(lCPU);
    cpu_itf(lCPU);
    
    CPUFloat ret = cputype_to_float(*lCPU->vRA);
    int passed = (ret<=(int)v1+3) && (ret>=(int)v1-3);
    
    print_float_result("0x1F", "test_cpu_fti_itf", ret, (int)v1, passed);
    
    
    free(lCPU);
    
    return passed;    
}



#if TESTING

/*
 * 
 */
int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t));
    
    float count = 0;
    float total = 0;
    
    //printf("Starting Tests\n");
    //printf("---------------------|---------|---------|---------|\n");
    //printf("%-20s | %-7s | %-7s | %-7s |\n", "Test Name", "Act", "Exp", "Pass");
    //printf("---------------------|---------|---------|---------|\n");
    //printf("%-20s | %-7s | %-7s | %-7s |\n", "iath", "", "", "");
    //printf("---------------------|---------|---------|---------|\n");
    
    
    labels();
    header("set");
    
    total++;
    count += test_cpu_set_0();

    total++;
    count += test_cpu_set_1();

    total++;
    count += test_cpu_set_2();

    total++;
    count += test_cpu_set_3();

    total++;
    count += test_cpu_set_4();

    total++;
    count += test_cpu_set_5();

    total++;
    count += test_cpu_set_6();

    total++;
    count += test_cpu_set_7();

    total++;
    count += test_cpu_set_8();

    total++;
    count += test_cpu_set_9();

    total++;
    count += test_cpu_set_A();

    total++;
    count += test_cpu_set_B();

    total++;
    count += test_cpu_set_C();

    total++;
    count += test_cpu_set_D();

    total++;
    count += test_cpu_set_E();

    total++;
    count += test_cpu_set_F();
    
    total++;
    count += test_cpu_set_FFFF();
    total++;
    count += test_cpu_set_ABCD();
    total++;
    count += test_cpu_set_BCDE();
    total++;
    count += test_cpu_set_alt_BCDE();
    total++;
    count += test_cpu_set_0123();

    total++;
    count += test_cpu_set_89AB();

    total++;
    count += test_cpu_set_CDEF();

    total++;
    count += test_cpu_set_0A0B();      
    
    header("iath");
    
    total++;
    count += test_cpu_add_basic();
    total++;
    count += test_cpu_add_zero_flag();
    total++;
    count += test_cpu_add_carry_flag();
    total++;
    count += test_cpu_add_overflow_flag();

    total++;
    count += test_cpu_sub_basic();
    total++;
    count += test_cpu_sub_zero_flag();
    total++;
    count += test_cpu_sub_carry_flag();
    total++;
    count += test_cpu_sub_overflow_flag();    
    
    total++;
    count += test_cpu_qadd();
    
    total++;
    count += test_cpu_qsub();
 
    total++;
    count += test_cpu_qmul();
    
    total++;
    count += test_cpu_qdiv();
    
    total++;
    count += test_cpu_qmod();
    
    total++;
    count += test_cpu_stb();

    total++;
    count += test_cpu_clb();
    
    total++;
    count += test_cpu_qnot();

    total++;
    count += test_cpu_qand();
    
    total++;
    count += test_cpu_qor();
    
    total++;
    count += test_cpu_qxor();
    
    total++;
    count += test_cpu_qshl();

    total++;
    count += test_cpu_qshr();

    total++;
    count += test_cpu_its();
    
    total++;
    count += test_cpu_sti_its();

    
    total++;
    count += test_cpu_itf_fti();
    

    
    //printf("---------------------|---------|---------|---------|\n");
    //print_string_result("","fath", "", "", 0);
    header("fath");
    
    total++;
    count += test_cpu_qfpow();
    
    total++;
    count += test_cpu_qfadd();
    
    total++;
    count += test_cpu_qfsub();
    
    total++;
    count += test_cpu_qfmul();
    
    total++;
    count += test_cpu_qfdiv();
    
    total++;
    count += test_cpu_qflogbn();
    
    total++;
    count += test_cpu_qpi();
    
    total++;
    count += test_cpu_qe();

    total++;
    count += test_cpu_qsin();
    
    total++;
    count += test_cpu_qcos();

    total++;
    count += test_cpu_qtan();
    
    total++;
    count += test_cpu_qasin();
    
    total++;
    count += test_cpu_qacos();    
    
    total++;
    count += test_cpu_qatan2();
            
    total++;
    count += test_cpu_stf_fts();
    
    total++;
    count += test_cpu_fti_itf();
    
    hl();
    
    printf("Total Passed: %d (%3.2f%%)", (int)count, count/total*100);
    
}


#endif