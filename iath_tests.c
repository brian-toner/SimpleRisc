#include "tests.h"




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