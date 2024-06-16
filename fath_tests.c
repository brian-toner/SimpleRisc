#include "tests.h"



int test_cpu_its(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    CPUType v1 = sign*(rand() % 50);
    
    *lCPU->RA = v1;
    *lCPU->RE = 50;
    char lBuff[100];
    sprintf(lBuff,"%d", (CPUSWord)v1);
    
    cpu_set_addr(lCPU);
    
    cpu_its(lCPU);
        
    //print_mem(lCPU-> MemByte, memsize);
    int passed = strcmp((char*)lCPU->REAddr, lBuff)==0;//*lCPU->RA==res;

    //printf("%-20s | %-7s | %-7s | %-7d |\n", "test_cpu_its", (char*)lCPU->REAddr, lBuff, passed);
    print_string_result("0x0D", "its", (char*)lCPU->REAddr, lBuff, 0, 0, 0, 0, passed); 
    
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
    
    *lCPU->RA = v1;
    *lCPU->RE = 50;
    cpu_set_addr(lCPU);
    
    
    char* strval = lBuff;
    
    strcpy(lCPU->REAddr, strval);
    cpu_qsti(lCPU);
    
    for(int i = 0; i < strlen(strval); i++){
        lCPU->REAddr[i] = 0;
    }
    
    cpu_its(lCPU);
    
    
    //print_mem(lCPU-> MemByte, memsize);
    int passed = strcmp((char*)lCPU->REAddr, strval)==0;//*lCPU->RA==res;

    //printf("%-20s | %-7s | %-7s | %-7d |\n", "test_cpu_sti_its", (char*)lCPU->REAddr, strval, passed);
    print_string_result("0x0E", "sti_its", (char*)lCPU->REAddr, strval, 0, 0, 0, 0, passed); 
    
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
    *lCPU->RA = v1;
    
    cpu_itf(lCPU);
    cpu_qfti(lCPU);
    CPUSWord ret = *lCPU->RA;
    int passed = (ret<=v1+3) && (ret>=v1-3);
    
    //printf("%-20s | %-7d | %-7d | %-7d |\n", "test_cpu_itf_fti", ret, v1, passed);
    print_int_result("0x0F", "itf_fti", ret, v1, 0, 0, 0, 0, passed); 
    
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
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_fexp(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 20);
    print_float_result("0x10", "fpow", ret, res, 0, 0, 0, 0, passed);

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
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_qfadd(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x11", "fadd", ret, res, 0, 0, 0, 0, passed);

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
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_qfsub(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x12", "fsub", ret, res, 0, 0, 0, 0, passed);

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
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_qfmul(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 15);
    print_float_result("0x13", "fmul", ret, res, 0, 0, 0, 0, passed);

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
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_qfdiv(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x14", "fdiv", ret, res, 0, 0, 0, 0, passed);

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
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_qflogbn(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x15", "flogbn", ret, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
    
}


int test_cpu_qpi(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUFloat sign = (rand()%2?-1.0:1.0);
    
    //printf("\n%f %f\n",v1,v2);
    *lCPU->RA = float_to_cputype(sign*M_PI);
    //lCPU->RB = float_to_cputype(4.0);

    cpu_qpi(lCPU);
    //cpu_qfmul(lCPU);
    //cpu_qfmul(lCPU);
    
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    
    int passed = assert_float(ret, sign*M_PI, 3);
    print_float_result("0x16", "pi", ret, sign*M_PI, 0, 0, 0, 0, passed);
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
    *lCPU->RA = float_to_cputype(sign*M_E);
    //lCPU->RB = float_to_cputype(4.0);

    cpu_qe(lCPU);
    //cpu_qfmul(lCPU);
    //cpu_qfmul(lCPU);
    
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    
    int passed = assert_float(ret, sign*M_E, 3);
    print_float_result("0x17", "e", ret, sign*M_E, 0, 0, 0, 0, passed);
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
    
    *lCPU->RA = float_to_cputype(v1);

    cpu_qsin(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x18", "sin", ret, res, 0, 0, 0, 0, passed);
    
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
    
    *lCPU->RA = float_to_cputype(v1);

    cpu_qcos(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x19", "cos", ret, res, 0, 0, 0, 0, passed);
    
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
    
    *lCPU->RA = float_to_cputype(v1);

    cpu_qcos(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1A", "tan", ret, res, 0, 0, 0, 0, passed);
    
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
    
    *lCPU->RA = float_to_cputype(v1);

    cpu_qsin(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1B", "asin", ret, res, 0, 0, 0, 0, passed);
    
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
    
    *lCPU->RA = float_to_cputype(v1);

    cpu_qacos(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1C", "acos", ret, res, 0, 0, 0, 0, passed);
    
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
    
    *lCPU->RA = float_to_cputype(v1);
    *lCPU->RB = float_to_cputype(v2);

    cpu_qatan2(lCPU);
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    
    
    int passed = assert_float(ret, res, 3);
    print_float_result("0x1D", "atan2", ret, res, 0, 0, 0, 0, passed);
    
    free(lCPU);
    
    return passed;
    
}

//cpu_qatan2

int test_cpu_stf_fts(){
    int memsize = 256;
    Risc256* lCPU;
    lCPU = cpu_init(memsize);
    
    CPUType v1 = rand() % 50;
    
    *lCPU->RA = v1;
    *lCPU->RE = 50;
    cpu_set_addr(lCPU);
    char* strval = "-0.025";
    
    strcpy(lCPU->REAddr, strval);
    cpu_qstf(lCPU);
    
    for(int i = 0; i < strlen(strval); i++){
        lCPU->REAddr[i] = 0;
    }
    
    cpu_qfts(lCPU);
    
    
    //print_mem(lCPU-> MemByte, memsize);
    int passed = strcmp((char*)lCPU->REAddr, strval)==0;//*lCPU->RA==res;

    //printf("%-20s | %-7s | %-7s | %-7d |\n", "test_cpu_stf_fts", (char*)lCPU->REAddr, strval, passed);
    print_string_result("0x1E", "test_cpu_stf_fts", (char*)lCPU->REAddr, strval, 0, 0, 0, 0, passed);
    
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
    *lCPU->RA = v1f;
    
    cpu_qfti(lCPU);
    cpu_itf(lCPU);
    
    CPUFloat ret = cputype_to_float(*lCPU->RA);
    int passed = (ret<=(int)v1+3) && (ret>=(int)v1-3);
    
    print_float_result("0x1F", "test_cpu_fti_itf", ret, (int)v1, 0, 0, 0, 0, passed);
    
    
    free(lCPU);
    
    return passed;    
}
