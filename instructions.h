/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   instructions.h
 * Author: brian
 *
 * Created on June 4, 2021, 9:40 PM
 */

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "output.h"
#include "CPU.h"  
#include "minifloat.h"
#include "half.h"
#include <math.h>
#include <string.h>
    
typedef void (*InstructionHandler)(Risc256*);

extern InstructionHandler instructionHandlers[256];

void cpu_set_addr(Risc256* aCPUPt);
double logbn(double a, double b);
uint8_t get_current_ring(Risc256* aCPUPt);
bool is_in_ring_0(Risc256* aCPUPt);
bool is_iopl_authorized(Risc256* aCPUPt, CPUPtrType addr);
void set_t_flag(Risc256* aCPUPt, bool condition);

void pop_register_from_temp_stack(Risc256* aCPUPt, CPUType* reg, size_t size);
void push_register_to_temp_stack(Risc256* aCPUPt, CPUType* reg, size_t size);
bool update_temp_stack_pointer_pop(Risc256* aCPUPt, size_t decrement);
bool update_temp_stack_pointer_push(Risc256* aCPUPt, size_t increment);
void pop_register_from_stack(Risc256* aCPUPt, CPUType* reg, size_t size);
void push_register_to_stack(Risc256* aCPUPt, CPUType* reg, size_t size);
bool update_stack_pointer_pop(Risc256* aCPUPt, size_t decrement);
bool update_stack_pointer_push(Risc256* aCPUPt, size_t increment);


#if WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(CPUFloat aConv);
#elif WORDSIZE==2
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(float aConv);  
#elif WORDSIZE==4
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(float aConv);
#elif WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(double aConv); 
#endif

//Needs a home...
void cpu_qstf(Risc256* aCPUPt);
void cpu_qsti(Risc256* aCPUPt);
void cpu_uitf(Risc256* aCPUPt);
void cpu_uits(Risc256* aCPUPt);

// 0x00 - 0x0F: SET instructions
void cpu_set_0(Risc256* aCPUPt);
void cpu_set_1(Risc256* aCPUPt);
void cpu_set_2(Risc256* aCPUPt);
void cpu_set_3(Risc256* aCPUPt);
void cpu_set_4(Risc256* aCPUPt);
void cpu_set_5(Risc256* aCPUPt);
void cpu_set_6(Risc256* aCPUPt);
void cpu_set_7(Risc256* aCPUPt);
void cpu_set_8(Risc256* aCPUPt);
void cpu_set_9(Risc256* aCPUPt);
void cpu_set_A(Risc256* aCPUPt);
void cpu_set_B(Risc256* aCPUPt);
void cpu_set_C(Risc256* aCPUPt);
void cpu_set_D(Risc256* aCPUPt);
void cpu_set_E(Risc256* aCPUPt);
void cpu_set_F(Risc256* aCPUPt);

// 0x10 - 0x1F: Integer arithmetic instructions
static inline void cpu_add_register(Risc256* cpu, CPUType* regPtr, CPUType value) {
    CPUType reg = *regPtr;
    CPUType result = reg + value;

    CPUType flags = *cpu->vRS & CZOS_MASK;

    flags |= (result == 0) * Z_SET;
    flags |= ((result & SIGNBIT) != 0) * S_SET;
    flags |= (((reg & SIGNBIT) == (value & SIGNBIT)) && ((result & SIGNBIT) != (reg & SIGNBIT))) * O_SET;
    flags |= (result < reg) * C_SET;

    *cpu->vRS = flags;
    *regPtr = result;
}

static inline void cpu_sub_register(Risc256* cpu, CPUType* regPtr, CPUType value) {
    CPUType reg = *regPtr;
    CPUType result = reg - value;

    CPUType flags = *cpu->vRS & CZOS_MASK;

    flags |= (result == 0) * Z_SET;
    flags |= ((result & SIGNBIT) != 0) * S_SET;
    flags |= ((reg & SIGNBIT) != (value & SIGNBIT) && (result & SIGNBIT) != (reg & SIGNBIT)) * O_SET;
    flags |= (reg < value) * C_SET;

    *cpu->vRS = flags;
    *regPtr = result;
}

void cpu_add(Risc256* aCPUPt);
void cpu_sub(Risc256* aCPUPt);
void cpu_mul(Risc256* aCPUPt);
void cpu_div(Risc256* aCPUPt);
void cpu_mod(Risc256* aCPUPt);
void cpu_setb(Risc256* aCPUPt);
void cpu_clrb(Risc256* aCPUPt);
void cpu_not(Risc256* aCPUPt);
void cpu_and(Risc256* aCPUPt);
void cpu_or(Risc256* aCPUPt);
void cpu_xor(Risc256* aCPUPt);
void cpu_shl(Risc256* aCPUPt);
void cpu_shr(Risc256* aCPUPt);
void cpu_adc(Risc256* aCPUPt);
void cpu_sbb(Risc256* aCPUPt);
void cpu_twos(Risc256* aCPUPt);

// 0x20 - 0x2F: Floating-point instructions
void cpu_qfadd(Risc256* aCPUPt);
void cpu_qfsub(Risc256* aCPUPt);
void cpu_qfmul(Risc256* aCPUPt);
void cpu_qfdiv(Risc256* aCPUPt);
void cpu_qflogbn(Risc256* aCPUPt);
void cpu_fexp(Risc256* aCPUPt);
void cpu_qsin(Risc256* aCPUPt);
void cpu_qcos(Risc256* aCPUPt);
void cpu_qtan(Risc256* aCPUPt);
void cpu_qasin(Risc256* aCPUPt);
void cpu_qacos(Risc256* aCPUPt);
void cpu_qatan2(Risc256* aCPUPt);
void cpu_its(Risc256* aCPUPt);
void cpu_uits(Risc256* aCPUPt);
void cpu_itf(Risc256* aCPUPt);
void cpu_uitf(Risc256* aCPUPt);
void cpu_qfts(Risc256* aCPUPt);
void cpu_qfti(Risc256* aCPUPt);

// 0x30 - 0x3F: Increment instructions
void cpu_inc_ra(Risc256* aCPUPt);
void cpu_inc_rb(Risc256* aCPUPt);
void cpu_inc_rc(Risc256* aCPUPt);
void cpu_inc_rd_ws(Risc256* aCPUPt);
void cpu_inc_rd_ds(Risc256* aCPUPt);
void cpu_inc_re_ws(Risc256* aCPUPt);
void cpu_inc_re_ds(Risc256* aCPUPt);
void cpu_inc_ri(Risc256* aCPUPt);
void cpu_inc_ra_ri(Risc256* aCPUPt);
void cpu_inc_rb_ri(Risc256* aCPUPt);
void cpu_inc_rc_ri(Risc256* aCPUPt);
void cpu_inc_rd_ri(Risc256* aCPUPt);
void cpu_inc_re_ri(Risc256* aCPUPt);
void cpu_inc_sp_ws(Risc256* aCPUPt);
void cpu_inc_tp_ws(Risc256* aCPUPt);
void cpu_inc_rd_re_ws(Risc256* aCPUPt);

// 0x40 - 0x4F: Decrement instructions
static inline void cpu_dec_register(Risc256* cpu, CPUType* regPtr, CPUType dec);
static inline void cpu_dec_doubleregister(Risc256* cpu, CPUType* regPtr, CPUType dec);

void cpu_dec_ra(Risc256* aCPUPt);
void cpu_dec_rb(Risc256* aCPUPt);
void cpu_dec_rc(Risc256* aCPUPt);
void cpu_dec_rd_ws(Risc256* aCPUPt);
void cpu_dec_rd_ds(Risc256* aCPUPt);
void cpu_dec_re_ws(Risc256* aCPUPt);
void cpu_dec_re_ds(Risc256* aCPUPt);
void cpu_dec_ri(Risc256* aCPUPt);
void cpu_dec_ra_ri(Risc256* aCPUPt);
void cpu_dec_rb_ri(Risc256* aCPUPt);
void cpu_dec_rc_ri(Risc256* aCPUPt);
void cpu_dec_rd_ri(Risc256* aCPUPt);
void cpu_dec_re_ri(Risc256* aCPUPt);
void cpu_dec_sp_ws(Risc256* aCPUPt);
void cpu_dec_tp_ws(Risc256* aCPUPt);
void cpu_dec_rd_re_ws(Risc256* aCPUPt);

// 0x50 - 0x5F: Comparison instructions
void cpu_gt_ra_rb(Risc256* aCPUPt);
void cpu_lt_ra_rb(Risc256* aCPUPt);
void cpu_eq_ra_rb(Risc256* aCPUPt);
void cpu_ge_ra_rb(Risc256* aCPUPt);
void cpu_le_ra_rb(Risc256* aCPUPt);
void cpu_ne_ra_rb(Risc256* aCPUPt);
void cpu_ispos_ra(Risc256* aCPUPt);
void cpu_isneg_ra(Risc256* aCPUPt);
void cpu_fgt_ra_rb(Risc256* aCPUPt);
void cpu_flt_ra_rb(Risc256* aCPUPt);
void cpu_feq_ra_rb(Risc256* aCPUPt);
void cpu_fge_ra_rb(Risc256* aCPUPt);
void cpu_fle_ra_rb(Risc256* aCPUPt);
void cpu_fne_ra_rb(Risc256* aCPUPt);
void cpu_isnan_ra(Risc256* aCPUPt);
void cpu_isinf_ra(Risc256* aCPUPt);

// 0x60 - 0x6F: Comparison instructions
void cpu_gt_ri_rc(Risc256* aCPUPt);
void cpu_lt_ri_rc(Risc256* aCPUPt);
void cpu_eq_ri_rc(Risc256* aCPUPt);
void cpu_ge_ri_rc(Risc256* aCPUPt);
void cpu_le_ri_rc(Risc256* aCPUPt);
void cpu_ne_ri_rc(Risc256* aCPUPt);
void cpu_isnull_rd(Risc256* aCPUPt);
void cpu_isnull_re(Risc256* aCPUPt);
void cpu_gt_rd_re(Risc256* aCPUPt);
void cpu_lt_rd_re(Risc256* aCPUPt);
void cpu_eq_rd_re(Risc256* aCPUPt);
void cpu_ge_rd_re(Risc256* aCPUPt);
void cpu_le_rd_re(Risc256* aCPUPt);
void cpu_ne_rd_re(Risc256* aCPUPt);
void cpu_inbound_re(Risc256* aCPUPt);
void cpu_inbound_rd(Risc256* aCPUPt);

// 0x70 - 0x7F: Check instructions
void cpu_getstatus(Risc256* aCPUPt);
void cpu_getflags(Risc256* aCPUPt);
void cpu_isset(Risc256* aCPUPt);
void cpu_isclear(Risc256* aCPUPt);
void cpu_istrue(Risc256* aCPUPt);
void cpu_isfalse(Risc256* aCPUPt);
void cpu_iscset(Risc256* aCPUPt);
void cpu_iscclear(Risc256* aCPUPt);
void cpu_isoset(Risc256* aCPUPt);
void cpu_isoclear(Risc256* aCPUPt);
void cpu_istime(Risc256* aCPUPt);
void cpu_tpsh_t(Risc256* aCPUPt);
void cpu_and_tpop_t(Risc256* aCPUPt);
void cpu_or_tpop_t(Risc256* aCPUPt);
void cpu_nand_tpop_t(Risc256* aCPUPt);
void cpu_nor_tpop_t(Risc256* aCPUPt);

// 0x80 - 0x8F: Flag instructions
void cpu_set_t(Risc256* aCPUPt);
void cpu_clr_f(Risc256* aCPUPt);
void cpu_not_t(Risc256* aCPUPt);
void cpu_logical_or(Risc256* aCPUPt);
void cpu_logical_and(Risc256* aCPUPt);
void cpu_logical_not(Risc256* aCPUPt);
void cpu_disable_nmi(Risc256* aCPUPt);
void cpu_enable_nmi(Risc256* aCPUPt);
void cpu_setbreak(Risc256* aCPUPt);
void cpu_clrbreak(Risc256* aCPUPt);
void cpu_lowmem(Risc256* aCPUPt);
void cpu_clr_error(Risc256* aCPUPt);
void cpu_clrrs(Risc256* aCPUPt);
void cpu_clr_autherror(Risc256* aCPUPt);
void cpu_is_autherror(Risc256* aCPUPt);
void cpu_set_iopl(Risc256* aCPUPt);

// 0x90 - 0x9F: Stack push instructions
void cpu_push_sp_ra(Risc256* aCPUPt);
void cpu_push_sp_rb(Risc256* aCPUPt);
void cpu_push_sp_rc(Risc256* aCPUPt);
void cpu_push_sp_ri(Risc256* aCPUPt);
void cpu_push_sp_rd(Risc256* aCPUPt);
void cpu_push_sp_re(Risc256* aCPUPt);
void cpu_push_sp_rr(Risc256* aCPUPt);
void cpu_push_sp_rs(Risc256* aCPUPt);
void cpu_push_tp_ra(Risc256* aCPUPt);
void cpu_push_tp_rb(Risc256* aCPUPt);
void cpu_push_tp_rc(Risc256* aCPUPt);
void cpu_push_tp_ri(Risc256* aCPUPt);
void cpu_push_tp_rd(Risc256* aCPUPt);
void cpu_push_tp_re(Risc256* aCPUPt);
void cpu_push_tp_rr(Risc256* aCPUPt);
void cpu_pushall(Risc256* aCPUPt);

// 0xA0 - 0xAF: Stack pop instructions
void cpu_pop_sp_ra(Risc256* aCPUPt);
void cpu_pop_sp_rb(Risc256* aCPUPt);
void cpu_pop_sp_rc(Risc256* aCPUPt);
void cpu_pop_sp_ri(Risc256* aCPUPt);
void cpu_pop_sp_rd(Risc256* aCPUPt);
void cpu_pop_sp_re(Risc256* aCPUPt);
void cpu_pop_sp_rr(Risc256* aCPUPt);
void cpu_pop_sp_rs(Risc256* aCPUPt);
void cpu_pop_tp_ra(Risc256* aCPUPt);
void cpu_pop_tp_rb(Risc256* aCPUPt);
void cpu_pop_tp_rc(Risc256* aCPUPt);
void cpu_pop_tp_ri(Risc256* aCPUPt);
void cpu_pop_tp_rd(Risc256* aCPUPt);
void cpu_pop_tp_re(Risc256* aCPUPt);
void cpu_pop_tp_rr(Risc256* aCPUPt);
void cpu_popall(Risc256* aCPUPt);

// 0xB0 - 0xBF: Extended save instructions
void cpu_push_re_ra(Risc256* aCPUPt);
void cpu_push_re_rb(Risc256* aCPUPt);
void cpu_push_re_rc(Risc256* aCPUPt);
void cpu_push_re_ri(Risc256* aCPUPt);
void cpu_push_re_rd(Risc256* aCPUPt);
void cpu_push_re_rr(Risc256* aCPUPt);
void cpu_cpy_re_ra(Risc256* aCPUPt);
void cpu_cpy_re_rb(Risc256* aCPUPt);
void cpu_cpy_re_rc(Risc256* aCPUPt);
void cpu_cpy_re_ri(Risc256* aCPUPt);
void cpu_cpy_re_rd(Risc256* aCPUPt);
void cpu_cpy_re_rr(Risc256* aCPUPt);
void cpu_cpy_re_rr_ra(Risc256* aCPUPt);
void cpu_cpy_re_rr_ri_ra(Risc256* aCPUPt);
void cpu_cpyblk_re_rd_rc(Risc256* aCPUPt);

// 0xC0 - 0xCF: Extended load instructions
void cpu_pop_re_ra(Risc256* aCPUPt);
void cpu_pop_re_rb(Risc256* aCPUPt);
void cpu_pop_re_rc(Risc256* aCPUPt);
void cpu_pop_re_ri(Risc256* aCPUPt);
void cpu_pop_re_rd(Risc256* aCPUPt);
void cpu_pop_re_rr(Risc256* aCPUPt);
void cpu_cpy_ra_re(Risc256* aCPUPt);
void cpu_cpy_rb_re(Risc256* aCPUPt);
void cpu_cpy_rc_re(Risc256* aCPUPt);
void cpu_cpy_ri_re(Risc256* aCPUPt);
void cpu_cpy_rd_re(Risc256* aCPUPt);
void cpu_cpy_rr_re(Risc256* aCPUPt);
void cpu_cpy_ra_re_rr(Risc256* aCPUPt);
void cpu_cpy_ra_re_rr_ri(Risc256* aCPUPt);
void cpu_cpyblk_rd_re_rc(Risc256* aCPUPt);

// 0xD0 - 0xDF: Move instructions
void cpu_mov_ra_rr(Risc256* aCPUPt);
void cpu_mov_rb_rr(Risc256* aCPUPt);
void cpu_mov_rc_rr(Risc256* aCPUPt);
void cpu_mov_rd_rr(Risc256* aCPUPt);
void cpu_mov_re_rr(Risc256* aCPUPt);
void cpu_mov_ri_rr(Risc256* aCPUPt);
void cpu_mov_rr_wordsize(Risc256* aCPUPt);
void cpu_mov_re_re(Risc256* aCPUPt);
void cpu_mov_rd_rd(Risc256* aCPUPt);
void cpu_mov_ra_0(Risc256* aCPUPt);
void cpu_mov_rb_0(Risc256* aCPUPt);
void cpu_mov_rc_0(Risc256* aCPUPt);
void cpu_mov_rd_0(Risc256* aCPUPt);
void cpu_mov_re_0(Risc256* aCPUPt);
void cpu_mov_ri_0(Risc256* aCPUPt);
void cpu_mov_rr_0(Risc256* aCPUPt);

// 0xE0 - 0xEF: VCPU instructions
void cpu_vinit(Risc256* aCPUPt);
void cpu_vstart(Risc256* aCPUPt);
void cpu_vstop(Risc256* aCPUPt);
void cpu_vstep(Risc256* aCPUPt);
void cpu_vsave(Risc256* aCPUPt);
void cpu_vload(Risc256* aCPUPt);
void cpu_vrsave(Risc256* aCPUPt);
void cpu_vrload(Risc256* aCPUPt);
void cpu_vbegin(Risc256* aCPUPt);
void cpu_vend(Risc256* aCPUPt);
void cpu_vrssetre(Risc256* aCPUPt);
void cpu_vcopy(Risc256* aCPUPt);
void cpu_viserror(Risc256* aCPUPt);
void cpu_vishlt(Risc256* aCPUPt);
void cpu_vswinterrupt(Risc256* aCPUPt);
void cpu_vhwinterrupt(Risc256* aCPUPt);

// 0xF0 - 0xFF: Control instructions
void cpu_func_call(Risc256* aCPUPt);
void cpu_swi(Risc256* aCPUPt);
void cpu_branch(Risc256* aCPUPt);
void cpu_branch_t(Risc256* aCPUPt);
void cpu_branch_f(Risc256* aCPUPt);
void cpu_ternary_ra_rb(Risc256* aCPUPt);
void cpu_ternary_rd_re(Risc256* aCPUPt);
void cpu_ternary_rd_re_mem(Risc256* aCPUPt);
void cpu_rfi(Risc256* aCPUPt);
void cpu_ret(Risc256* aCPUPt);
void cpu_reset_sp(Risc256* aCPUPt);
void cpu_reset_tp(Risc256* aCPUPt);
void cpu_time(Risc256* aCPUPt);
void cpu_jmp(Risc256* aCPUPt);
void cpu_rjmp(Risc256* aCPUPt);
void cpu_hlt(Risc256* aCPUPt);





#ifdef __cplusplus
}
#endif

#endif /* INSTRUCTIONS_H */

