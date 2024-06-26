/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   tests.h
 * Author: brian
 *
 * Created on July 24, 2022, 7:37 PM
 */

#ifndef TESTS_H
#define TESTS_H

#define TESTING 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CPU.h"
#include "output.h"
#include "instructions.h"
#include <string.h>

typedef int (*test_func)();

// Function Prototypes
int assert_float(CPUFloat actual, CPUFloat expected, CPUFloat tolerance);
int assert_int(CPUType actual, CPUType expected);
int assert_uint(CPUSWord actual, CPUSWord expected);
void hl();
void labels();
void header(char* testName);
int print_int_result(const char* opcode, const char* testName, CPUType actual, CPUType expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed);
int print_uint_result(const char* opcode, const char* testName, unsigned actual, unsigned expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed);
int print_string_result(const char* opcode, const char* testName, const char* actual, const char* expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed);
int print_float_result(const char* opcode, const char* testName, CPUFloat actual, CPUFloat expected, CPUType actualStatusFlags, CPUType expectedStatusFlags, CPUType actualSystemFlags, CPUType expectedSystemFlags, int passed);

int print_flag_result(const char* opcode, const char* testName, CPUType actual, CPUType expected, int passed);
int check_value(CPUType actual, CPUType expected);
int check_flags(Risc256* cpu, CPUType expected_flags);


int test_cpu_set_FFFF();
int test_cpu_set_ABCD();
int test_cpu_set_BCDE();
int test_cpu_set_alt_BCDE();
int test_cpu_set_0123();
int test_cpu_set_89AB();
int test_cpu_set_CDEF();
int test_cpu_set_0A0B();
int test_cpu_set_0();
int test_cpu_set_1();
int test_cpu_set_2();
int test_cpu_set_3();
int test_cpu_set_4();
int test_cpu_set_5();
int test_cpu_set_6();
int test_cpu_set_7();
int test_cpu_set_8();
int test_cpu_set_9();
int test_cpu_set_A();
int test_cpu_set_B();
int test_cpu_set_C();
int test_cpu_set_D();
int test_cpu_set_E();
int test_cpu_set_F();


int test_cpu_add_basic();
int test_cpu_add_zero_flag();
int test_cpu_add_carry_flag();
int test_cpu_add_overflow_flag();
int test_cpu_sub_basic();
int test_cpu_sub_zero_flag();
int test_cpu_sub_carry_flag();
int test_cpu_sub_overflow_flag();
int test_cpu_mul_basic();
int test_cpu_div_basic();
int test_cpu_div_by_zero();
int test_cpu_mod_basic();
int test_cpu_mod_by_zero();
int test_cpu_setb_basic();
int test_cpu_clrb_basic();
int test_cpu_not_basic();
int test_cpu_and_basic();
int test_cpu_or_basic();
int test_cpu_xor_basic();
int test_cpu_shl_basic();
int test_cpu_shr_basic();
int test_cpu_addc_basic();
int test_cpu_subb_basic();
int test_cpu_twos_basic();
int test_cpu_add_basic();
int test_cpu_add_zero_flag();
int test_cpu_add_carry_flag();
int test_cpu_add_overflow_flag();
int test_cpu_sub_basic();
int test_cpu_sub_zero_flag();
int test_cpu_sub_carry_flag();
int test_cpu_sub_overflow_flag();
int test_cpu_qadd();
int test_cpu_qsub();
int test_cpu_qmul();
int test_cpu_qdiv();
int test_cpu_qmod();
int test_cpu_stb();
int test_cpu_clb();
int test_cpu_qnot();
int test_cpu_qand();
int test_cpu_qor();
int test_cpu_qxor();
int test_cpu_qshl();
int test_cpu_qshr();

int test_cpu_its();
int test_cpu_sti_its();
int test_cpu_itf_fti();
int test_cpu_qfpow();
int test_cpu_qfadd();
int test_cpu_qfsub();
int test_cpu_qfmul();
int test_cpu_qfdiv();
int test_cpu_qflogbn();
int test_cpu_qpi();
int test_cpu_qe();
int test_cpu_qsin();
int test_cpu_qcos();
int test_cpu_qtan();
int test_cpu_qasin();
int test_cpu_qacos();
int test_cpu_qatan2();
int test_cpu_stf_fts();
int test_cpu_fti_itf();


int test_cpu_inc_ra();
int test_cpu_inc_rb_zero_flag();
int test_cpu_inc_rc_carry_flag();
int test_cpu_inc_rd_ws();
int test_cpu_inc_re_ds();

int test_cpu_dec_ra_underflow();
int test_cpu_dec_ra_positive();
int test_cpu_dec_ra_negative();
int test_cpu_dec_ra_zero();
int test_cpu_dec_rb_underflow();
int test_cpu_dec_rb_positive();
int test_cpu_dec_rb_negative();
int test_cpu_dec_rb_zero();

int test_set_t_flag_0_0();
int test_set_t_flag_1_1();

int test_cpu_gt_ra_rb();
int test_cpu_lt_ra_rb();
int test_cpu_eq_ra_rb();
int test_cpu_ge_ra_rb();
int test_cpu_le_ra_rb();
int test_cpu_ne_ra_rb();
        
int test_cpu_fgt_ra_rb();
int test_cpu_fgt_ra_rb_inf();
int test_cpu_fgt_ra_rb_undef();



int test_cpu_push();

#endif /* TESTS_H */

