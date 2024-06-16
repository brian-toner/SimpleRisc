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
#include <math.h>
#include <string.h>
    
typedef void (*InstructionHandler)(Risc256*);

extern InstructionHandler instructionHandlers[256];

void cpu_set_addr(Risc256* cpu);
double logbn(double a, double b);
uint8_t get_current_ring(Risc256* cpu);
bool is_in_ring_0(Risc256* cpu);
bool is_iopl_authorized(Risc256* cpu, CPUPtrType addr);


static inline void set_t_flag(Risc256* cpu, CPUType cv) {
    *cpu->RS = (cv * T_SET);
}

void pop_register_from_temp_stack(Risc256* cpu, CPUType* reg, size_t size);
void push_register_to_temp_stack(Risc256* cpu, CPUType* reg, size_t size);
bool update_temp_stack_pointer_pop(Risc256* cpu, size_t decrement);
bool update_temp_stack_pointer_push(Risc256* cpu, size_t increment);
void pop_register_from_stack(Risc256* cpu, CPUType* reg, size_t size);
void push_register_to_stack(Risc256* cpu, CPUType* reg, size_t size);
bool update_stack_pointer_pop(Risc256* cpu, size_t decrement);
bool update_stack_pointer_push(Risc256* cpu, size_t increment);


#if WORDSIZE==1

#elif WORDSIZE==2
    float cputype_to_float(CPUType aConv){

        float lRet = half_to_float(aConv);
        return lRet;
    }

    CPUType float_to_cputype(float aConv){
        CPUType lRet = half_from_float(*(uint32_t*)(&aConv) );
        return lRet;
    }
    
       bool cputype_is_nan(CPUType aConv){
        return isnan(*(float*)half_to_float(aConv));
    }
    
    bool cputype_is_inf(CPUType aConv){
        return isinf(*(float*)half_to_float(aConv));
    } 
#elif WORDSIZE==4
    double cputype_to_float(CPUType aConv){

        float lRet = *(float*)(&aConv);
        return lRet;
    }

    CPUType float_to_cputype(float aConv){
        CPUType lRet = *(CPUType*)(&aConv);
        return lRet;
    }
#elif WORDSIZE==8
    double cputype_to_float(CPUType aConv){

        double lRet = *(double*)(&aConv);
        return lRet;
    }

    CPUType float_to_cputype(double aConv){
        CPUType lRet = *(CPUType*)(&aConv);
        return lRet;
    }    
#endif
    
#if WORDSIZE==1
    #include "minifloat.h"

    
    static inline int compare_float(CPUSWord a, CPUSWord b) {
        // Handle NaN separately
        if (a == F2M_NAN || b == F2M_NAN) {
            return (a == F2M_NAN && b == F2M_NAN) ? 0 : (a == F2M_NAN ? -1 : 1);
        }

        // Direct comparison for non-special values
        return (a == b) ? 0 : (a < b ? -1 : 1);
    }

    static inline CPUFloat cputype_to_float(CPUType aConv){

        CPUFloat lRet = mini_to_float(aConv);
        return lRet;
    }

    static inline CPUType float_to_cputype(CPUFloat aConv){
        CPUType lRet = float_to_mini(aConv);
        return lRet;
    }
    
    static inline bool cputype_is_nan(CPUType aConv){
        return isNan(aConv);
    }
    
    static inline bool cputype_is_inf(CPUType aConv){
        return isInf(aConv);
    }    
#elif WORDSIZE==2
    #include "half.h"

    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(float aConv);  
    
    static inline int compare_float(CPUSWord a, CPUSWord b) {
        CPUFloat fa = cputype_to_float(a);
        CPUFloat fb = cputype_to_float(b);

        // Direct comparison for non-special values
        return (fa == fb) ? 0 : (fa < fb ? -1 : 1);
    }
        
#elif WORDSIZE==4
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(float aConv);
    
    static inline int compare_float(CPUSWord a, CPUSWord b) {
        CPUFloat fa = cputype_to_float(a);
        CPUFloat fb = cputype_to_float(b);

        // Direct comparison for non-special values
        return (fa == fb) ? 0 : (fa < fb ? -1 : 1);
    }
#elif WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv);
    CPUType float_to_cputype(double aConv); 
    
    static inline int compare_float(CPUSWord a, CPUSWord b) {
        CPUFloat fa = cputype_to_float(a);
        CPUFloat fb = cputype_to_float(b);

        // Direct comparison for non-special values
        return (fa == fb) ? 0 : (fa < fb ? -1 : 1);
    }
#endif

//Needs a home...
void cpu_qstf(Risc256* cpu);
void cpu_qsti(Risc256* cpu);
void cpu_uitf(Risc256* cpu);
void cpu_uits(Risc256* cpu);

// 0x00 - 0x0F: SET instructions
void cpu_set_0(Risc256* cpu);
void cpu_set_1(Risc256* cpu);
void cpu_set_2(Risc256* cpu);
void cpu_set_3(Risc256* cpu);
void cpu_set_4(Risc256* cpu);
void cpu_set_5(Risc256* cpu);
void cpu_set_6(Risc256* cpu);
void cpu_set_7(Risc256* cpu);
void cpu_set_8(Risc256* cpu);
void cpu_set_9(Risc256* cpu);
void cpu_set_A(Risc256* cpu);
void cpu_set_B(Risc256* cpu);
void cpu_set_C(Risc256* cpu);
void cpu_set_D(Risc256* cpu);
void cpu_set_E(Risc256* cpu);
void cpu_set_F(Risc256* cpu);

// 0x10 - 0x1F: Integer arithmetic instructions
static inline void cpu_add_register(Risc256* cpu, CPUType* regPtr, CPUType value) {
    CPUType reg = *regPtr;
    CPUType result = reg + value;

    CPUType flags = *cpu->RS & CZOS_MASK;

    flags |= (result == 0) * Z_SET;
    flags |= ((result & SIGNBIT) != 0) * S_SET;
    flags |= (((reg & SIGNBIT) == (value & SIGNBIT)) && ((result & SIGNBIT) != (reg & SIGNBIT))) * O_SET;
    flags |= (result < reg) * C_SET;

    *cpu->RS = flags;
    *regPtr = result;
}

static inline void cpu_sub_register(Risc256* cpu, CPUType* regPtr, CPUType value) {
    CPUType reg = *regPtr;
    CPUType result = reg - value;

    CPUType flags = *cpu->RS & CZOS_MASK;

    flags |= (result == 0) * Z_SET;
    flags |= ((result & SIGNBIT) != 0) * S_SET;
    flags |= ((reg & SIGNBIT) != (value & SIGNBIT) && (result & SIGNBIT) != (reg & SIGNBIT)) * O_SET;
    flags |= (reg < value) * C_SET;

    *cpu->RS = flags;
    *regPtr = result;
}

void cpu_add(Risc256* cpu);
void cpu_sub(Risc256* cpu);
void cpu_mul(Risc256* cpu);
void cpu_div(Risc256* cpu);
void cpu_mod(Risc256* cpu);
void cpu_setb(Risc256* cpu);
void cpu_clrb(Risc256* cpu);
void cpu_not(Risc256* cpu);
void cpu_and(Risc256* cpu);
void cpu_or(Risc256* cpu);
void cpu_xor(Risc256* cpu);
void cpu_shl(Risc256* cpu);
void cpu_shr(Risc256* cpu);
void cpu_adc(Risc256* cpu);
void cpu_sbb(Risc256* cpu);
void cpu_twos(Risc256* cpu);

// 0x20 - 0x2F: Floating-point instructions
void cpu_qfadd(Risc256* cpu);
void cpu_qfsub(Risc256* cpu);
void cpu_qfmul(Risc256* cpu);
void cpu_qfdiv(Risc256* cpu);
void cpu_qflogbn(Risc256* cpu);
void cpu_fexp(Risc256* cpu);
void cpu_qsin(Risc256* cpu);
void cpu_qcos(Risc256* cpu);
void cpu_qtan(Risc256* cpu);
void cpu_qasin(Risc256* cpu);
void cpu_qacos(Risc256* cpu);
void cpu_qatan2(Risc256* cpu);
void cpu_its(Risc256* cpu);
void cpu_uits(Risc256* cpu);
void cpu_itf(Risc256* cpu);
void cpu_uitf(Risc256* cpu);
void cpu_qfts(Risc256* cpu);
void cpu_qfti(Risc256* cpu);

// 0x30 - 0x3F: Increment instructions
void cpu_inc_ra(Risc256* cpu);
void cpu_inc_rb(Risc256* cpu);
void cpu_inc_rc(Risc256* cpu);
void cpu_inc_rd_ws(Risc256* cpu);
void cpu_inc_rd_ds(Risc256* cpu);
void cpu_inc_re_ws(Risc256* cpu);
void cpu_inc_re_ds(Risc256* cpu);
void cpu_inc_ri(Risc256* cpu);
void cpu_inc_ra_ri(Risc256* cpu);
void cpu_inc_rb_ri(Risc256* cpu);
void cpu_inc_rc_ri(Risc256* cpu);
void cpu_inc_rd_ri(Risc256* cpu);
void cpu_inc_re_ri(Risc256* cpu);
void cpu_inc_sp_ws(Risc256* cpu);
void cpu_inc_tp_ws(Risc256* cpu);
void cpu_inc_rd_re_ws(Risc256* cpu);

// 0x40 - 0x4F: Decrement instructions
static inline void cpu_dec_register(Risc256* cpu, CPUType* regPtr, CPUType dec);
static inline void cpu_dec_doubleregister(Risc256* cpu, CPUType* regPtr, CPUType dec);

void cpu_dec_ra(Risc256* cpu);
void cpu_dec_rb(Risc256* cpu);
void cpu_dec_rc(Risc256* cpu);
void cpu_dec_rd_ws(Risc256* cpu);
void cpu_dec_rd_ds(Risc256* cpu);
void cpu_dec_re_ws(Risc256* cpu);
void cpu_dec_re_ds(Risc256* cpu);
void cpu_dec_ri(Risc256* cpu);
void cpu_dec_ra_ri(Risc256* cpu);
void cpu_dec_rb_ri(Risc256* cpu);
void cpu_dec_rc_ri(Risc256* cpu);
void cpu_dec_rd_ri(Risc256* cpu);
void cpu_dec_re_ri(Risc256* cpu);
void cpu_dec_sp_ws(Risc256* cpu);
void cpu_dec_tp_ws(Risc256* cpu);
void cpu_dec_rd_re_ws(Risc256* cpu);

// 0x50 - 0x5F: Comparison instructions
void cpu_gt_ra_rb(Risc256* cpu);
void cpu_lt_ra_rb(Risc256* cpu);
void cpu_eq_ra_rb(Risc256* cpu);
void cpu_ge_ra_rb(Risc256* cpu);
void cpu_le_ra_rb(Risc256* cpu);
void cpu_ne_ra_rb(Risc256* cpu);
void cpu_ispos_ra(Risc256* cpu);
void cpu_isneg_ra(Risc256* cpu);
void cpu_fgt_ra_rb(Risc256* cpu);
void cpu_flt_ra_rb(Risc256* cpu);
void cpu_feq_ra_rb(Risc256* cpu);
void cpu_fge_ra_rb(Risc256* cpu);
void cpu_fle_ra_rb(Risc256* cpu);
void cpu_fne_ra_rb(Risc256* cpu);
void cpu_isnan_ra(Risc256* cpu);
void cpu_isinf_ra(Risc256* cpu);

// 0x60 - 0x6F: Comparison instructions
void cpu_gt_ri_rc(Risc256* cpu);
void cpu_lt_ri_rc(Risc256* cpu);
void cpu_eq_ri_rc(Risc256* cpu);
void cpu_ge_ri_rc(Risc256* cpu);
void cpu_le_ri_rc(Risc256* cpu);
void cpu_ne_ri_rc(Risc256* cpu);
void cpu_isnull_rd(Risc256* cpu);
void cpu_isnull_re(Risc256* cpu);
void cpu_gt_rd_re(Risc256* cpu);
void cpu_lt_rd_re(Risc256* cpu);
void cpu_eq_rd_re(Risc256* cpu);
void cpu_ge_rd_re(Risc256* cpu);
void cpu_le_rd_re(Risc256* cpu);
void cpu_ne_rd_re(Risc256* cpu);
void cpu_inbound_re(Risc256* cpu);
void cpu_inbound_rd(Risc256* cpu);

// 0x70 - 0x7F: Check instructions
void cpu_getstatus(Risc256* cpu);
void cpu_getflags(Risc256* cpu);
void cpu_isset(Risc256* cpu);
void cpu_isclear(Risc256* cpu);
void cpu_istrue(Risc256* cpu);
void cpu_isfalse(Risc256* cpu);
void cpu_iscset(Risc256* cpu);
void cpu_iscclear(Risc256* cpu);
void cpu_isoset(Risc256* cpu);
void cpu_isoclear(Risc256* cpu);
void cpu_istime(Risc256* cpu);
void cpu_tpsh_t(Risc256* cpu);
void cpu_and_tpop_t(Risc256* cpu);
void cpu_or_tpop_t(Risc256* cpu);
void cpu_nand_tpop_t(Risc256* cpu);
void cpu_nor_tpop_t(Risc256* cpu);

// 0x80 - 0x8F: Flag instructions
void cpu_set_t(Risc256* cpu);
void cpu_clr_f(Risc256* cpu);
void cpu_not_t(Risc256* cpu);
void cpu_logical_or(Risc256* cpu);
void cpu_logical_and(Risc256* cpu);
void cpu_logical_not(Risc256* cpu);
void cpu_disable_nmi(Risc256* cpu);
void cpu_enable_nmi(Risc256* cpu);
void cpu_setbreak(Risc256* cpu);
void cpu_clrbreak(Risc256* cpu);
void cpu_lowmem(Risc256* cpu);
void cpu_clr_error(Risc256* cpu);
void cpu_clrrs(Risc256* cpu);
void cpu_clr_autherror(Risc256* cpu);
void cpu_is_autherror(Risc256* cpu);
void cpu_set_iopl(Risc256* cpu);

// 0x90 - 0x9F: Stack push instructions
void cpu_push_sp_ra(Risc256* cpu);
void cpu_push_sp_rb(Risc256* cpu);
void cpu_push_sp_rc(Risc256* cpu);
void cpu_push_sp_ri(Risc256* cpu);
void cpu_push_sp_rd(Risc256* cpu);
void cpu_push_sp_re(Risc256* cpu);
void cpu_push_sp_rr(Risc256* cpu);
void cpu_push_sp_rs(Risc256* cpu);
void cpu_push_tp_ra(Risc256* cpu);
void cpu_push_tp_rb(Risc256* cpu);
void cpu_push_tp_rc(Risc256* cpu);
void cpu_push_tp_ri(Risc256* cpu);
void cpu_push_tp_rd(Risc256* cpu);
void cpu_push_tp_re(Risc256* cpu);
void cpu_push_tp_rr(Risc256* cpu);
void cpu_pushall(Risc256* cpu);

// 0xA0 - 0xAF: Stack pop instructions
void cpu_pop_sp_ra(Risc256* cpu);
void cpu_pop_sp_rb(Risc256* cpu);
void cpu_pop_sp_rc(Risc256* cpu);
void cpu_pop_sp_ri(Risc256* cpu);
void cpu_pop_sp_rd(Risc256* cpu);
void cpu_pop_sp_re(Risc256* cpu);
void cpu_pop_sp_rr(Risc256* cpu);
void cpu_pop_sp_rs(Risc256* cpu);
void cpu_pop_tp_ra(Risc256* cpu);
void cpu_pop_tp_rb(Risc256* cpu);
void cpu_pop_tp_rc(Risc256* cpu);
void cpu_pop_tp_ri(Risc256* cpu);
void cpu_pop_tp_rd(Risc256* cpu);
void cpu_pop_tp_re(Risc256* cpu);
void cpu_pop_tp_rr(Risc256* cpu);
void cpu_popall(Risc256* cpu);

// 0xB0 - 0xBF: Extended save instructions
void cpu_push_re_ra(Risc256* cpu);
void cpu_push_re_rb(Risc256* cpu);
void cpu_push_re_rc(Risc256* cpu);
void cpu_push_re_ri(Risc256* cpu);
void cpu_push_re_rd(Risc256* cpu);
void cpu_push_re_rr(Risc256* cpu);
void cpu_cpy_re_ra(Risc256* cpu);
void cpu_cpy_re_rb(Risc256* cpu);
void cpu_cpy_re_rc(Risc256* cpu);
void cpu_cpy_re_ri(Risc256* cpu);
void cpu_cpy_re_rd(Risc256* cpu);
void cpu_cpy_re_rr(Risc256* cpu);
void cpu_cpy_re_rr_ra(Risc256* cpu);
void cpu_cpy_re_rr_ri_ra(Risc256* cpu);
void cpu_cpyblk_re_rd_rc(Risc256* cpu);

// 0xC0 - 0xCF: Extended load instructions
void cpu_pop_re_ra(Risc256* cpu);
void cpu_pop_re_rb(Risc256* cpu);
void cpu_pop_re_rc(Risc256* cpu);
void cpu_pop_re_ri(Risc256* cpu);
void cpu_pop_re_rd(Risc256* cpu);
void cpu_pop_re_rr(Risc256* cpu);
void cpu_cpy_ra_re(Risc256* cpu);
void cpu_cpy_rb_re(Risc256* cpu);
void cpu_cpy_rc_re(Risc256* cpu);
void cpu_cpy_ri_re(Risc256* cpu);
void cpu_cpy_rd_re(Risc256* cpu);
void cpu_cpy_rr_re(Risc256* cpu);
void cpu_cpy_ra_re_rr(Risc256* cpu);
void cpu_cpy_ra_re_rr_ri(Risc256* cpu);
void cpu_cpyblk_rd_re_rc(Risc256* cpu);

// 0xD0 - 0xDF: Move instructions
void cpu_mov_ra_rr(Risc256* cpu);
void cpu_mov_rb_rr(Risc256* cpu);
void cpu_mov_rc_rr(Risc256* cpu);
void cpu_mov_rd_rr(Risc256* cpu);
void cpu_mov_re_rr(Risc256* cpu);
void cpu_mov_ri_rr(Risc256* cpu);
void cpu_mov_rr_wordsize(Risc256* cpu);
void cpu_mov_re_re(Risc256* cpu);
void cpu_mov_rd_rd(Risc256* cpu);
void cpu_mov_ra_0(Risc256* cpu);
void cpu_mov_rb_0(Risc256* cpu);
void cpu_mov_rc_0(Risc256* cpu);
void cpu_mov_rd_0(Risc256* cpu);
void cpu_mov_re_0(Risc256* cpu);
void cpu_mov_ri_0(Risc256* cpu);
void cpu_mov_rr_0(Risc256* cpu);

// 0xE0 - 0xEF: VCPU instructions
void cpu_vinit(Risc256* cpu);
void cpu_start(Risc256* cpu);
void cpu_stop(Risc256* cpu);
void cpu_step(Risc256* cpu);
void cpu_save(Risc256* cpu);
void cpu_vload(Risc256* cpu);
void cpu_RSave(Risc256* cpu);
void cpu_vrload(Risc256* cpu);
void cpu_vbegin(Risc256* cpu);
void cpu_vend(Risc256* cpu);
void cpu_RSsetre(Risc256* cpu);
void cpu_vcopy(Risc256* cpu);
void cpu_viserror(Risc256* cpu);
void cpu_vishlt(Risc256* cpu);
void cpu_SWInterrupt(Risc256* cpu);
void cpu_HWInterrupt(Risc256* cpu);

// 0xF0 - 0xFF: Control instructions
void cpu_func_call(Risc256* cpu);
void cpu_swi(Risc256* cpu);
void cpu_branch(Risc256* cpu);
void cpu_branch_t(Risc256* cpu);
void cpu_branch_f(Risc256* cpu);
void cpu_ternary_ra_rb(Risc256* cpu);
void cpu_ternary_rd_re(Risc256* cpu);
void cpu_ternary_rd_re_mem(Risc256* cpu);
void cpu_rfi(Risc256* cpu);
void cpu_ret(Risc256* cpu);
void cpu_reset_sp(Risc256* cpu);
void cpu_reset_tp(Risc256* cpu);
void cpu_time(Risc256* cpu);
void cpu_jmp(Risc256* cpu);
void cpu_rjmp(Risc256* cpu);
void cpu_hlt(Risc256* cpu);





#ifdef __cplusplus
}
#endif

#endif /* INSTRUCTIONS_H */

