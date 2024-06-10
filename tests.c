#include "tests.h"


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
    printf("|-------|----------------------------------------------------|---------|---------|---------|---------|---------|---------|---------|\n");
}


void labels(){
    hl();
    printf("| %-5s | %-50s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s |\n", "OP", "Test Name", "Act", "Exp", "RSAct", "RSExp" , "RFAct", "RFExp", "Pass");
    hl();
}

void header(char* testName){
    hl();
    printf("| %-5s | %-50s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s |\n", "", testName, "", "", "", "", "", "", "");
    hl();
}


// Print result functions for different data types
int print_float_result(const char* opcode, const char* testName, CPUFloat actual, CPUFloat expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed) {
    printf("| %-5s | %-50s | %-7.2f | %-7.2f | %-7X | %-7X | %-7X | %-7X | %-7s |\n", opcode, testName, actual, expected, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed ? "PASSED" : "FAILED");
    return passed;
}

int print_string_result(const char* opcode, const char* testName, const char* actual, const char* expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed) {
    printf("| %-5s | %-50s | %-7s | %-7s | %-7X | %-7X | %-7X | %-7X | %-7s |\n", opcode, testName, actual, expected, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed ? "PASSED" : "FAILED");
    return passed;
}

int print_int_result(const char* opcode, const char* testName, CPUType actual, CPUType expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed) {
    printf("| %-5s | %-50s | %-7d | %-7d | %-7X | %-7X | %-7X | %-7X | %-7s |\n", opcode, testName, actual, expected, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed ? "PASSED" : "FAILED");
    return passed;
}

int print_uint_result(const char* opcode, const char* testName, unsigned actual, unsigned expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed) {
    printf("| %-5s | %-50s | %-7u | %-7u | %-7X | %-7X | %-7X | %-7X | %-7s |\n", opcode, testName, actual, expected, actualStatusFlags, expectedStatusFlags, actualSystemFlags, expectedSystemFlags, passed ? "PASSED" : "FAILED");
    return passed;
}

int print_flag_result(const char* opcode, const char* testName, CPUType actual, CPUType expected, int passed) {
    printf("| %-5s | %-50s | %-7d | %-7d | %-7d |\n", opcode, testName, actual, expected, passed);
}



#if TESTING

test_func set_tests[] = {
    test_cpu_set_0,
    test_cpu_set_1,
    test_cpu_set_2,
    test_cpu_set_3,
    test_cpu_set_4,
    test_cpu_set_5,
    test_cpu_set_6,
    test_cpu_set_7,
    test_cpu_set_8,
    test_cpu_set_9,
    test_cpu_set_A,
    test_cpu_set_B,
    test_cpu_set_C,
    test_cpu_set_D,
    test_cpu_set_E,
    test_cpu_set_F,
    test_cpu_set_FFFF,
    test_cpu_set_ABCD,
    test_cpu_set_BCDE,
    test_cpu_set_alt_BCDE,
    test_cpu_set_0123,
    test_cpu_set_89AB,
    test_cpu_set_CDEF,
    test_cpu_set_0A0B
};


test_func iath_tests[] = {
//    test_cpu_add_basic,
//    test_cpu_add_zero_flag,
//    test_cpu_add_carry_flag,
//    test_cpu_add_overflow_flag,
//    test_cpu_sub_basic,
//    test_cpu_sub_zero_flag,
//    test_cpu_sub_carry_flag,
//    test_cpu_sub_overflow_flag,
//    test_cpu_qadd,
//    test_cpu_qsub,
//    test_cpu_qmul,
//    test_cpu_qdiv,
//    test_cpu_qmod,
//    test_cpu_stb,
//    test_cpu_clb,
//    test_cpu_qnot,
//    test_cpu_qand,
//    test_cpu_qor,
//    test_cpu_qxor,
//    test_cpu_qshl,
//    test_cpu_qshr,
//    test_cpu_its,
//    test_cpu_sti_its,
//    test_cpu_itf_fti,
            
    //New tests
        test_cpu_add_basic,
    test_cpu_add_zero_flag,
    test_cpu_add_carry_flag,
    test_cpu_add_overflow_flag,
    test_cpu_sub_basic,
    test_cpu_sub_zero_flag,
    test_cpu_sub_carry_flag,
    test_cpu_sub_overflow_flag,
    test_cpu_mul_basic,
    test_cpu_div_basic,
    test_cpu_div_by_zero,
    test_cpu_mod_basic,
    test_cpu_mod_by_zero,
    test_cpu_setb_basic,
    test_cpu_clrb_basic,
    test_cpu_not_basic,
    test_cpu_and_basic,
    test_cpu_or_basic,
    test_cpu_xor_basic,
    test_cpu_shl_basic,
    test_cpu_shr_basic,
    test_cpu_addc_basic,
    test_cpu_subb_basic,
    test_cpu_twos_basic,
};

test_func fath_tests[] = {
    test_cpu_qfpow,
    test_cpu_qfadd,
    test_cpu_qfsub,
    test_cpu_qfmul,
    test_cpu_qfdiv,
    test_cpu_qflogbn,
    test_cpu_qpi,
    test_cpu_qe,
    test_cpu_qsin,
    test_cpu_qcos,
    test_cpu_qtan,
    test_cpu_qasin,
    test_cpu_qacos,
    test_cpu_qatan2,
    test_cpu_stf_fts,
    test_cpu_fti_itf
};

test_func increment_tests[] = {
    test_cpu_inc_ra,
    test_cpu_inc_rb_zero_flag,
    test_cpu_inc_rc_carry_flag,
    test_cpu_inc_rd_ws,
    test_cpu_inc_re_ds,
    // Add other increment tests here...
};

test_func decrement_tests[] = {
    test_cpu_dec_ra_zero,
    test_cpu_dec_ra_negative,
    test_cpu_dec_ra_positive,
    test_cpu_dec_ra_underflow,
    // Add more decrement tests here...
};

void run_tests(test_func* tests, int num_tests, float* count, float* total, const char* header_name) {
    header(header_name);
    for (int i = 0; i < num_tests; i++) {
        (*total)++;
        *count += tests[i]();
    }
}

int check_flags(Risc256* cpu, CPUType expected_flags) {
    return (*cpu->vRS & expected_flags) == expected_flags;
}

int check_value(CPUType actual, CPUType expected) {
    return actual == expected;
}

int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t));

    float count = 0;
    float total = 0;

    labels();

    run_tests(set_tests, sizeof(set_tests) / sizeof(set_tests[0]), &count, &total, "set");
    run_tests(iath_tests, sizeof(iath_tests) / sizeof(iath_tests[0]), &count, &total, "iath");
    run_tests(fath_tests, sizeof(fath_tests) / sizeof(fath_tests[0]), &count, &total, "fath");
    run_tests(increment_tests, sizeof(increment_tests) / sizeof(increment_tests[0]), &count, &total, "inc");
    run_tests(decrement_tests, sizeof(decrement_tests) / sizeof(decrement_tests[0]), &count, &total, "dec");
    hl();

    printf("Total Passed: %d (%3.2f%%)\n", (int)count, count / total * 100);

    return 0;
}
#endif