#include "tests.h"



int test_cpu_set_FFFF() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->PC = 128;
    lCPU-> MemByte[128] = 0x0F; // SET 0
    
    cpu_set(lCPU);
    cpu_set(lCPU);
    cpu_set(lCPU);
    cpu_set(lCPU);
    
    int passed = *lCPU->RR == 65535;
    
    //print_mem(lCPU-> MemByte, memsize);
    
    print_uint_result("0x00", "set_0f0f0f0f", *lCPU->RR, 65535, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_ABCD() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->PC = 128;
    lCPU-> MemByte[128] = 0x0A; // SET 0
    cpu_set(lCPU);
    
    lCPU-> MemByte[128] = 0x0B; // SET 0
    cpu_set(lCPU);
    
    lCPU-> MemByte[128] = 0x0C; // SET 0
    cpu_set(lCPU);
    
    lCPU-> MemByte[128] = 0x0D; // SET 0
    cpu_set(lCPU);
    
    int passed = *lCPU->RR == 0xABCD;
    
    //print_mem(lCPU-> MemByte, memsize);
    
    print_uint_result("0x00", "set_0a0b0c0d", *lCPU->RR, 0xABCD, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_BCDE() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    *lCPU->PC = 128;
    lCPU-> MemByte[128] = 0x0A; // SET 0
    cpu_set(lCPU);
    
    lCPU-> MemByte[128] = 0x0B; // SET 0
    cpu_set(lCPU);
    
    lCPU-> MemByte[128] = 0x0C; // SET 0
    cpu_set(lCPU);
    
    lCPU-> MemByte[128] = 0x0D; // SET 0
    cpu_set(lCPU);

    lCPU-> MemByte[128] = 0x0E; // SET 0
    cpu_set(lCPU);
    
    int passed = *lCPU->RR == 0xBCDE;
    
    //print_mem(lCPU-> MemByte, memsize);
    
    print_uint_result("0x00", "set_0a0b0c0d0e", *lCPU->RR, 0xBCDE, 0, 0, 0, 0, passed);
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
    
    int passed = *lCPU->RR == 0xBCDE;
    
    //print_mem(lCPU-> MemByte, memsize);
    
    print_uint_result("0x00", "set_0a0b0c0d0e", *lCPU->RR, 0xBCDE, 0, 0, 0, 0, passed);
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
    
    int passed = *lCPU->RR == 0x0123;
    
    print_uint_result("0x00", "set_010203", *lCPU->RR, 0x0123, 0, 0, 0, 0, passed);
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
    
    int passed = *lCPU->RR == 0x89AB;
    
    print_uint_result("0x00", "set_08090a0b", *lCPU->RR, 0x89AB, 0, 0, 0, 0, passed);
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
    
    int passed = *lCPU->RR == 0xCDEF;
    
    print_uint_result("0x00", "set_0c0d0e0f", *lCPU->RR, 0xCDEF, 0, 0, 0, 0, passed);
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
    
    int passed = *lCPU->RR == 0x0A0B;
    
    print_uint_result("0x00", "set_000a000b", *lCPU->RR, 0x0A0B, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_0() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_0(lCPU);
    
    int passed = *lCPU->RR == 0x0;
    
    print_uint_result("0x0", "set_0", *lCPU->RR, 0x0, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_1() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_1(lCPU);
    
    int passed = *lCPU->RR == 0x1;
    
    print_uint_result("0x1", "set_1", *lCPU->RR, 0x1, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_2() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_2(lCPU);
    
    int passed = *lCPU->RR == 0x2;
    
    print_uint_result("0x2", "set_2", *lCPU->RR, 0x2, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_3() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_3(lCPU);
    
    int passed = *lCPU->RR == 0x3;
    
    print_uint_result("0x3", "set_3", *lCPU->RR, 0x3, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_4() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_4(lCPU);
    
    int passed = *lCPU->RR == 0x4;
    
    print_uint_result("0x4", "set_4", *lCPU->RR, 0x4, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_5() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_5(lCPU);
    
    int passed = *lCPU->RR == 0x5;
    
    print_uint_result("0x5", "set_5", *lCPU->RR, 0x5, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_6() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_6(lCPU);
    
    int passed = *lCPU->RR == 0x6;
    
    print_uint_result("0x6", "set_6", *lCPU->RR, 0x6, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_7() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_7(lCPU);
    
    int passed = *lCPU->RR == 0x7;
    
    print_uint_result("0x7", "set_7", *lCPU->RR, 0x7, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_8() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_8(lCPU);
    
    int passed = *lCPU->RR == 0x8;
    
    print_uint_result("0x8", "set_8", *lCPU->RR, 0x8, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_9() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_9(lCPU);
    
    int passed = *lCPU->RR == 0x9;
    
    print_uint_result("0x9", "set_9", *lCPU->RR, 0x9, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_A() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_A(lCPU);
    
    int passed = *lCPU->RR == 0xA;
    
    print_uint_result("0xA", "set_A", *lCPU->RR, 0xA, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_B() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_B(lCPU);
    
    int passed = *lCPU->RR == 0xB;
    
    print_uint_result("0xB", "set_B", *lCPU->RR, 0xB, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_C() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_C(lCPU);
    
    int passed = *lCPU->RR == 0xC;
    
    print_uint_result("0xC", "set_C", *lCPU->RR, 0xC, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_D() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_D(lCPU);
    
    int passed = *lCPU->RR == 0xD;
    
    print_uint_result("0xD", "set_D", *lCPU->RR, 0xD, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_E() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_E(lCPU);
    
    int passed = *lCPU->RR == 0xE;
    
    print_uint_result("0xE", "set_E", *lCPU->RR, 0xE, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}

int test_cpu_set_F() {
    int memsize = 256;
    Risc256* lCPU = cpu_init(memsize);
    if (!lCPU) return 0; // Initialization failed

    cpu_set_F(lCPU);
    
    int passed = *lCPU->RR == 0xF;
    
    print_uint_result("0xF", "set_F", *lCPU->RR, 0xF, 0, 0, 0, 0, passed);
    free(lCPU);
    return passed;
}