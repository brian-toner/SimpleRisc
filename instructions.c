/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "CPU.h"
#include "instructions.h"
#include <string.h>
#include <math.h>
//#include <c++/10/complex>
//#define _GLIBCXX_COMPLEX 0

uint8_t get_iopl(Risc256* aCPUPt){
    CPUType IOPL = *aCPUPt->vRF & (P0_SET | P1_SET);
    return IOPL;
}

uint8_t get_current_ring(Risc256* aCPUPt) {
    CPUPtrType pc = *aCPUPt->vPC;
    if (pc < *aCPUPt->vRING1Start) {
        return 0; // Ring 0
    } else if (pc < *aCPUPt->vRING2Start) {
        return 1; // Ring 1
    } else if (pc < *aCPUPt->vRING3Start) {
        return 2; // Ring 2
    } else {
        return 3; // Ring 3
    }
}

void cpu_set_addr(Risc256* aCPUPt){
    aCPUPt->vRDAddr = aCPUPt->vMemByte+(*aCPUPt->vRD);
    aCPUPt->vREAddr = aCPUPt->vMemByte+(*aCPUPt->vRE);
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);

}

// Helper function to check if we are in ring 0
bool is_in_ring_0(Risc256* aCPUPt) {
    return !(*aCPUPt->vRF & (P0_SET | P1_SET));
}

bool is_iopl_authorized(Risc256* aCPUPt, CPUPtrType addr) {
    uint8_t current_ring = get_current_ring(aCPUPt);
    if (current_ring <= (*aCPUPt->vRF & (P0_SET | P1_SET))) {
        return true; // Authorized if current ring is within IOPL
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET); // Set error and authorization error flags if not authorized
        return false;
    }
}

// Helper function to set the T flag
void set_t_flag(Risc256* aCPUPt, bool condition) {
    if (*aCPUPt->vRS & X_SET) {
        *aCPUPt->vRS = (*aCPUPt->vRS & ~T_SET) | (condition ? T_SET : 0);
    } else {
        *aCPUPt->vRS = (*aCPUPt->vRS & ~T_SET) | (condition ? T_SET : 0);
    }
}


InstructionHandler instructionHandlers[256] = {
    // 0x00 - 0x0F: SET instructions
    cpu_set_0, cpu_set_1, cpu_set_2, cpu_set_3, cpu_set_4, cpu_set_5, cpu_set_6, cpu_set_7,
    cpu_set_8, cpu_set_9, cpu_set_A, cpu_set_B, cpu_set_C, cpu_set_D, cpu_set_E, cpu_set_F,
    
    // 0x10 - 0x1F: Integer arithmetic instructions
    cpu_add, cpu_sub, cpu_mul, cpu_div, cpu_mod, cpu_setb, cpu_clrb, cpu_not,
    cpu_and, cpu_or, cpu_xor, cpu_shl, cpu_shr, cpu_adc, cpu_sbb, cpu_twos,
    
    // 0x20 - 0x2F: Floating-point instructions
    cpu_qfadd, cpu_qfsub, cpu_qfmul, cpu_qfdiv, cpu_qflogbn, cpu_fexp, cpu_qsin, cpu_qcos,
    cpu_qtan, cpu_qasin, cpu_qacos, cpu_qatan2, cpu_its, cpu_uits, cpu_itf, cpu_uitf, cpu_qfts, cpu_qfti,
    
    //0x30-0x3F: Increment instructions
    cpu_inc_ra, cpu_inc_rb, cpu_inc_rc, cpu_inc_rd_ws, cpu_inc_rd_ds, cpu_inc_re_ws, cpu_inc_re_ds, cpu_inc_ri, 
    cpu_inc_ra_ri, cpu_inc_rb_ri,  cpu_inc_rc_ri, cpu_inc_rd_ri, cpu_inc_re_ri, cpu_inc_sp_ws, cpu_inc_tp_ws, cpu_inc_rd_re_ws,
    
    //0x40-0x4F: Decrement instructions
    cpu_dec_ra, cpu_dec_rb, cpu_dec_rc, cpu_dec_rd_ws, cpu_dec_rd_ds, cpu_dec_re_ws, cpu_dec_re_ds, cpu_dec_ri, 
    cpu_dec_ra_ri, cpu_dec_rb_ri, cpu_dec_rc_ri, cpu_dec_rd_ri, cpu_dec_re_ri, cpu_dec_sp_ws, cpu_dec_tp_ws, cpu_dec_rd_re_ws,
    
    //0x50-0x5F: Comparison instructions
    cpu_gt_ra_rb, cpu_lt_ra_rb, cpu_eq_ra_rb, cpu_ge_ra_rb, cpu_le_ra_rb, cpu_ne_ra_rb, cpu_ispos_ra, cpu_isneg_ra, 
    cpu_fgt_ra_rb, cpu_flt_ra_rb, cpu_feq_ra_rb, cpu_fge_ra_rb, cpu_fle_ra_rb, cpu_fne_ra_rb, cpu_isnan_ra, cpu_isinf_ra,
    
    //0x60-0x6F: Comparison instructions
    cpu_gt_ri_rc, cpu_lt_ri_rc, cpu_eq_ri_rc, cpu_ge_ri_rc, cpu_le_ri_rc, cpu_ne_ri_rc, cpu_isnull_rd, cpu_isnull_re, 
    cpu_gt_rd_re, cpu_lt_rd_re, cpu_eq_rd_re, cpu_ge_rd_re, cpu_le_rd_re, cpu_ne_rd_re, cpu_inbound_re, cpu_inbound_rd,
    
    //0x70-0x7F: Check instructions
    cpu_getstatus, cpu_getflags, cpu_isset, cpu_isclear, cpu_istrue, cpu_isfalse, cpu_iscset, cpu_iscclear, 
    cpu_isoset, cpu_isoclear, cpu_istime, cpu_tpsh_t, cpu_and_tpop_t, cpu_or_tpop_t, cpu_nand_tpop_t, cpu_nor_tpop_t,
    
    //0x80-0x8F: Flag instructions
    cpu_set_t, cpu_clr_f, cpu_not_t, cpu_logical_or, cpu_logical_and, cpu_logical_not, cpu_disable_nmi, 
    cpu_enable_nmi, cpu_setbreak, cpu_clrbreak, cpu_lowmem, cpu_clr_error, cpu_clrrs, cpu_clr_autherror, cpu_is_autherror, cpu_set_iopl,
    
    //0x90-0x9F: Stack push instructions
    cpu_push_sp_ra, cpu_push_sp_rb, cpu_push_sp_rc, cpu_push_sp_ri, cpu_push_sp_rd, cpu_push_sp_re, cpu_push_sp_rr, cpu_push_sp_rs,
    cpu_push_tp_ra, cpu_push_tp_rb, cpu_push_tp_rc, cpu_push_tp_ri, cpu_push_tp_rd, cpu_push_tp_re, cpu_push_tp_rr, cpu_pushall,
    
    //0xA0-0xAF: Stack pop instructions
    cpu_pop_sp_ra, cpu_pop_sp_rb, cpu_pop_sp_rc, cpu_pop_sp_ri, cpu_pop_sp_rd, cpu_pop_sp_re, cpu_pop_sp_rr, cpu_pop_sp_rs,
    cpu_pop_tp_ra, cpu_pop_tp_rb, cpu_pop_tp_rc, cpu_pop_tp_ri, cpu_pop_tp_rd, cpu_pop_tp_re, cpu_pop_tp_rr, cpu_popall,
    
    //0xB0-0xBF: Extended save instructions
    cpu_push_re_ra, cpu_push_re_rb, cpu_push_re_rc, cpu_push_re_ri, cpu_push_re_rd, cpu_push_re_rr, cpu_cpy_re_ra, cpu_cpy_re_rb,
    cpu_cpy_re_rc, cpu_cpy_re_ri, cpu_cpy_re_rd, cpu_cpy_re_rr, cpu_cpy_re_rr_ra, cpu_cpy_re_rr_ri_ra, cpu_cpyblk_re_rd_rc,
    
    //0xC0-0xCF: Extended load instructions
    cpu_pop_re_ra, cpu_pop_re_rb, cpu_pop_re_rc, cpu_pop_re_ri, cpu_pop_re_rd, cpu_pop_re_rr, cpu_cpy_ra_re, cpu_cpy_rb_re,
    cpu_cpy_rc_re, cpu_cpy_ri_re, cpu_cpy_rd_re, cpu_cpy_rr_re, cpu_cpy_ra_re_rr, cpu_cpy_ra_re_rr_ri, cpu_cpyblk_rd_re_rc,
    
    //0xD0-0xDF: Move instructions
    cpu_mov_ra_rr, cpu_mov_rb_rr, cpu_mov_rc_rr, cpu_mov_rd_rr, cpu_mov_re_rr, cpu_mov_ri_rr, cpu_mov_rr_wordsize, cpu_mov_re_re,
    cpu_mov_rd_rd, cpu_mov_ra_0, cpu_mov_rb_0, cpu_mov_rc_0, cpu_mov_rd_0, cpu_mov_re_0, cpu_mov_ri_0, cpu_mov_rr_0,
    
    //0xE0-0xEF: VCPU instructions
    cpu_vinit, cpu_vstart, cpu_vstop, cpu_vstep,  cpu_vsave, cpu_vload, cpu_vrsave, cpu_vrload,
    cpu_vbegin, cpu_vend, cpu_vrssetre, cpu_vcopy, cpu_viserror, cpu_vishlt, cpu_vswinterrupt, cpu_vhwinterrupt,
        
    //0xF0-0xFF: Control instructions
    cpu_func_call, cpu_swi, cpu_branch, cpu_branch_t, cpu_branch_f, cpu_ternary_ra_rb, cpu_ternary_rd_re, cpu_ternary_rd_re_mem, 
    cpu_rfi, cpu_ret, cpu_reset_sp, cpu_reset_tp, cpu_time, cpu_jmp, cpu_rjmp, cpu_hlt
    
};

void executeInstruction(Risc256* cpu) {
    uint8_t opcode = *(cpu->vMemByte + *(cpu->vPC));
    instructionHandlers[opcode](cpu);
    (*(cpu->vPC))++; // Increment the program counter after executing the instruction
}



// Helper function to update stack pointer for push operations with boundary and ring 0 check for the regular stack
bool update_stack_pointer_push(Risc256* aCPUPt, size_t increment) {
    if (is_in_ring_0(aCPUPt)) {
        if (*aCPUPt->vSP + increment <= *aCPUPt->vSEP) {
            *aCPUPt->vSP += increment;
            return true;
        } else {
            *aCPUPt->vRF |= E_SET; // Set error flag if stack overflow
        }
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET); // Set error and authorization error flags if not in ring 0
    }
    return false;
}

// Helper function to update stack pointer for pop operations with boundary and ring 0 check for the regular stack
bool update_stack_pointer_pop(Risc256* aCPUPt, size_t decrement) {
    if (is_in_ring_0(aCPUPt)) {
        if (*aCPUPt->vSP >= *aCPUPt->vSSP + decrement) {
            *aCPUPt->vSP -= decrement;
            return true;
        } else {
            *aCPUPt->vRF |= E_SET; // Set error flag if stack underflow
        }
    } else {
        *aCPUPt->vRF |= (E_SET | A_SET); // Set error and authorization error flags if not in ring 0
    }
    return false;
}

// Helper function to push a register onto the regular stack
void push_register_to_stack(Risc256* aCPUPt, CPUType* reg, size_t size) {
    if (update_stack_pointer_push(aCPUPt, size)) {
        unsigned char* spAddr = aCPUPt->vMemByte + (*aCPUPt->vSP - size);
        memcpy(spAddr, reg, size);
    }
}

// Helper function to pop a register from the regular stack
void pop_register_from_stack(Risc256* aCPUPt, CPUType* reg, size_t size) {
    if (update_stack_pointer_pop(aCPUPt, size)) {
        unsigned char* spAddr = aCPUPt->vMemByte + *aCPUPt->vSP;
        memcpy(reg, spAddr, size);
    }
}


// Helper function to update stack pointer for push operations with boundary check for the temporary stack
bool update_temp_stack_pointer_push(Risc256* aCPUPt, size_t increment) {
    if (*aCPUPt->vTP + increment <= *aCPUPt->vTEP) {
        *aCPUPt->vTP += increment;
        return true;
    } else {
        *aCPUPt->vRF |= E_SET; // Set error flag if stack overflow
    }
    return false;
}

// Helper function to update stack pointer for pop operations with boundary check for the temporary stack
bool update_temp_stack_pointer_pop(Risc256* aCPUPt, size_t decrement) {
    if (*aCPUPt->vTP >= *aCPUPt->vTSP + decrement) {
        *aCPUPt->vTP -= decrement;
        return true;
    } else {
        *aCPUPt->vRF |= E_SET; // Set error flag if stack underflow
    }
    return false;
}

// Helper function to push a register onto the temporary stack
void push_register_to_temp_stack(Risc256* aCPUPt, CPUType* reg, size_t size) {
    if (update_temp_stack_pointer_push(aCPUPt, size)) {
        unsigned char* tpAddr = aCPUPt->vMemByte + (*aCPUPt->vTP - size);
        memcpy(tpAddr, reg, size);
    }
}

// Helper function to pop a register from the temporary stack
void pop_register_from_temp_stack(Risc256* aCPUPt, CPUType* reg, size_t size) {
    if (update_temp_stack_pointer_pop(aCPUPt, size)) {
        unsigned char* tpAddr = aCPUPt->vMemByte + *aCPUPt->vTP;
        memcpy(reg, tpAddr, size);
    }
}



double logbn(double a, double b){
    return log(a)/log(b);
}

#if WORDSIZE==1
    CPUFloat cputype_to_float(CPUType aConv){

        CPUFloat lRet = mini_to_float(aConv);
        return lRet;
    }

    CPUType float_to_cputype(CPUFloat aConv){
        CPUType lRet = float_to_mini(aConv);
        return lRet;
    }
    
    bool cputype_is_nan(CPUType aConv){
        return isNan(aConv);
    }
    
    bool cputype_is_inf(CPUType aConv){
        return isInf(aConv);
    }
#elif WORDSIZE==2
    float cputype_to_float(CPUType aConv){

        float lRet = half_to_float(aConv);
        return lRet;
    }

    CPUType float_to_cputype(float aConv){
        CPUType lRet = half_from_float(*(uint32_t*)(&aConv) );
        return lRet;
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



void cpu_qstf(Risc256* aCPUPt){
    
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    CPUFloat lFVal = atof(lBuff);
    CPUType lVal = float_to_cputype(lFVal);
    *aCPUPt->vRA = lVal;
    
}

void cpu_qsti(Risc256* aCPUPt){
    
    char* lBuff = (char*)(aCPUPt->vRA+*aCPUPt->vRE);
    *aCPUPt->vRA  = atoi(lBuff);
    
}

void cpu_nop(Risc256* aCPUPt){
    return;
}


void cpu_qadd(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)+(*aCPUPt->vRB);
}

void cpu_qsub(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)-(*aCPUPt->vRB);
}

void cpu_qmul(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)*(*aCPUPt->vRB);
}

void cpu_qdiv(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)/(*aCPUPt->vRB);
}

void cpu_qmod(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)%(*aCPUPt->vRB);
}

void cpu_stb(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)|(1<<(*aCPUPt->vRB));
}

void cpu_clb(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)&(~(1<<(*aCPUPt->vRB)));
}

void cpu_qnot(Risc256* aCPUPt){
    *aCPUPt->vRA = ~(*aCPUPt->vRA);
}

void cpu_qand(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)&(*aCPUPt->vRB);
}

void cpu_qor(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)|(*aCPUPt->vRB);
}

void cpu_qxor(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)^(*aCPUPt->vRB);
}

void cpu_qshl(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)<<(*aCPUPt->vRB);
}

void cpu_qshr(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)>>(*aCPUPt->vRB);
}




//=========================================================//
// 0x1X


//=========================================================//
// 0x2X



//=========================================================//
// 0x01



//
//void cpu_qsin(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*sin(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qcos(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*cos(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qtan(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*tan(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qasin(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*asin(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qacos(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*acos(lVal1d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qatan2(Risc256* aCPUPt){
//
//    CPUType lVal1 = (*aCPUPt->vRA);
//    CPUType lVal2 = (*aCPUPt->vRB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = atan2(lVal1d,lVal2d);
//    *aCPUPt->vRA = float_to_cputype(lRet);
//    
//}

//=========================================================//
// 0x3 - INC

//
//void cpu_inc_ra(Risc256* aCPUPt){
//        
//    CPUType lVal1 = *aCPUPt->vRA;
//
//    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *aCPUPt->vRA = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *aCPUPt->vRS = lRFPt;
//            
//}
//
//void cpu_inc_rb(Risc256* aCPUPt){
//        
//    CPUType lVal1 = *aCPUPt->vRB;
//
//    bool lASign = (*aCPUPt->vRB & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *aCPUPt->vRB = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *aCPUPt->vRS = lRFPt;
//            
//}
//
//void cpu_inc_rc(Risc256* aCPUPt){
//        
//    CPUType lVal1 = *aCPUPt->vRC;
//
//    bool lASign = (*aCPUPt->vRC & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *aCPUPt->vRC = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *aCPUPt->vRS = lRFPt;
//            
//}
//
//
//void cpu_inc_ri(Risc256* aCPUPt){
//        
//    CPUType lVal1 = *aCPUPt->vRI;
//
//    bool lASign = (*aCPUPt->vRI & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *aCPUPt->vRI = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *aCPUPt->vRS = lRFPt;
//            
//}
//
//void cpu_inci(Risc256* aCPUPt){
//        
//    CPUType lVal1 = *aCPUPt->vRA;
//    CPUType lVal2 = *aCPUPt->vRI;
//
//    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
//    bool lBSign = (*aCPUPt->vRI & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+lVal2;
//    *aCPUPt->vRA = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lASign == lBSign && lSign != lASign)?(O_SET):(0)) |
//        ((lVal2 > lRet)?(C_SET):(0)));
//
//    *aCPUPt->vRS = lRFPt;
//            
//}
//
//void cpu_incdws(Risc256* aCPUPt){
//        
//    CPUType lVal1 = *aCPUPt->vRA;
//
//    bool lASign = (*aCPUPt->vRA & SIGNBIT)!=0;
//    CPUType lRet = lVal1+WORDSIZE;
//    *aCPUPt->vRA = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *aCPUPt->vRS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)) |
//        ((lVal1 > lRet)?(C_SET):(0)));
//
//    *aCPUPt->vRS = lRFPt;
//            
//}


void cpu_qinc(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)+1;
}

void cpu_qinci(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)+(*aCPUPt->vRI);
}

void cpu_qincaddr(Risc256* aCPUPt, CPUType* aRetH, CPUType* aRetL){
    *aRetL = (*aRetL)+1;
    *aRetH = (*aRetH)+(*aRetL==0)*1;
}

//0x30
void cpu_qira(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRA);
}

//0x31
void cpu_qirb(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRB);
}

//0x32
void cpu_qirc(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRC);
}

//0x33
void cpu_qird(Risc256* aCPUPt){
    cpu_qincaddr(aCPUPt,aCPUPt->vRDH,aCPUPt->vRDL);
}

//0x24
void cpu_qire(Risc256* aCPUPt){
    cpu_qincaddr(aCPUPt,aCPUPt->vREH,aCPUPt->vREL);
}

//0x25
void cpu_qirrh(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRRH);
}

//0x26
void cpu_qirrl(Risc256* aCPUPt){
    cpu_qinc(aCPUPt,aCPUPt->vRRL);
}

//0x27
void cpu_qirai(Risc256* aCPUPt){
    cpu_qinci(aCPUPt,aCPUPt->vRA);
}

//0x28
void cpu_qirbi(Risc256* aCPUPt){
    cpu_qinci(aCPUPt,aCPUPt->vRB);
}

//0x29
void cpu_qirci(Risc256* aCPUPt){
    cpu_qinci(aCPUPt,aCPUPt->vRC);
}

//=========================================================//
// 0x4 - COND



//=========================================================//
// 0x5 - INC



//0x2A
//0x2B
//0x2C
//0x2D
//0x2E
//0x2F

//=========================================================//
// 0x03 - DEC

void cpu_qdec(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)-1;
}

void cpu_qdeci(Risc256* aCPUPt, CPUType* aRet){
    *aRet = (*aRet)-(*aCPUPt->vRI);
}

void cpu_qdecaddr(Risc256* aCPUPt, CPUType* aRetH, CPUType* aRetL){
    *aRetL = (*aRetL)-1;
    *aRetH = (*aRetH)-(*aRetL==0)*1;
}

void cpu_qdra(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRA);
}

void cpu_qdrb(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRB);
}

void cpu_qdrc(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRC);
}

void cpu_qdrd(Risc256* aCPUPt){
    cpu_qdecaddr(aCPUPt,aCPUPt->vRDH,aCPUPt->vRDL);
}

void cpu_qdre(Risc256* aCPUPt){
    cpu_qdecaddr(aCPUPt,aCPUPt->vREH,aCPUPt->vREL);
}

void cpu_qdrrh(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRRH);
}

void cpu_qdrrl(Risc256* aCPUPt){
    cpu_qdec(aCPUPt,aCPUPt->vRRL);
}

void cpu_qdrai(Risc256* aCPUPt){
    cpu_qdeci(aCPUPt,aCPUPt->vRA);
}

void cpu_qdrbi(Risc256* aCPUPt){
    cpu_qdeci(aCPUPt,aCPUPt->vRB);
}

void cpu_qdrci(Risc256* aCPUPt){
    cpu_qdeci(aCPUPt,aCPUPt->vRC);
}

//=========================================================//
// 0x04 - CMP

//40
void cpu_qgt(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)>(*aCPUPt->vRB);
}

//41
void cpu_qlt(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)<(*aCPUPt->vRB);
}

//42
void cpu_qeq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)==(*aCPUPt->vRB);
}

//43
void cpu_qgeq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)>=(*aCPUPt->vRB);
}

//44
void cpu_qleq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)<=(*aCPUPt->vRB);
}

//45
void cpu_qneq(Risc256* aCPUPt){
    *aCPUPt->vRF = (*aCPUPt->vRA)!=(*aCPUPt->vRB);
}

//46
void cpu_qmaf(Risc256* aCPUPt){
    *aCPUPt->vRA = (*aCPUPt->vRA)*(*aCPUPt->vRF);
}

//47
void cpu_qmbf(Risc256* aCPUPt){
    *aCPUPt->vRB = (*aCPUPt->vRB)*(*aCPUPt->vRF);
}

//48
void cpu_qfgt(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d>lVal2d;
    
}

//49
void cpu_qflt(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d<lVal2d;
    
}

//4A
void cpu_qfeq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d==lVal2d;
    
}

//4B
void cpu_qfgeq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d>=lVal2d;
    
}

//4C
void cpu_qfleq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d<=lVal2d;
    
}

//4D
void cpu_qfneq(Risc256* aCPUPt){

    CPUType lVal1 = (*aCPUPt->vRA);
    CPUType lVal2 = (*aCPUPt->vRB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *aCPUPt->vRF = lVal1d!=lVal2d;
    
}

//4E


//4F

//=========================================================//
// 0x06 - BR/JMP

//=========================================================//
// 0xAX - Temp Push
void cpu_tps_all(Risc256* aCPUPt){
    *aCPUPt->vTP -= WORDSIZE*16;    //16 Registers
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);
    memcpy(aCPUPt->vSPAddr+1, aCPUPt->vRA, WORDSIZE*16);    
}

void cpu_tps(Risc256* aCPUPt, CPUType* aReg){
    *(aCPUPt->vSPAddr) = (*aReg);
    *aCPUPt->vSP -= WORDSIZE;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
}


void cpu_tpsa(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRA);
}

void cpu_tpsb(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRB);
}

void cpu_tpsc(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRC);
}

void cpu_tpsdh(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRDH);
}

void cpu_tpsdl(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRDL);
}

void cpu_tpseh(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vREH);
}

void cpu_tpsel(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vREL);
}

void cpu_tpstp(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vTP);
}

void cpu_tpssp(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vSP);
}

void cpu_tpsi(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRI);
}

void cpu_tpspch(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vPCH);
}

void cpu_tpspcl(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vPCL);
}

void cpu_tpsf(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRF);
}

void cpu_tpss(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRS);
}

void cpu_tpsrh(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRRH);
}

void cpu_tpsrl(Risc256* aCPUPt){
    cpu_tps(aCPUPt, aCPUPt->vRRL);
}

//=========================================================//
// 0xBX - Temp Pop

//Pop all registers from temp stack
void cpu_tpp_all(Risc256* aCPUPt){
    memcpy(aCPUPt->vRA, aCPUPt->vTPAddr+1, WORDSIZE*16);
    *aCPUPt->vTP += WORDSIZE*16;
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);
    
}

//Pop single register from temp stack
void cpu_tpp(Risc256* aCPUPt, CPUType *aReg){
    *aCPUPt->vTP += WORDSIZE;
    aCPUPt->vTPAddr = aCPUPt->vMemByte+(*aCPUPt->vTP);
    *(aReg) = *(aCPUPt->vTPAddr);
    
}

void cpu_tppa(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRA);
}

void cpu_tppb(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRB);
}

void cpu_tppc(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRC);
}

void cpu_tppdh(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRDH);
}

void cpu_tppdl(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRDL);
}

void cpu_tppeh(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vREH);
}

void cpu_tppel(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vREL);
}

void cpu_tpptp(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vTP);
}

void cpu_tppsp(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vSP);
}

void cpu_tppi(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRI);
}

void cpu_tpppch(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vPCH);
}

void cpu_tpppcl(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vPCL);
}

void cpu_tppf(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRF);
}

void cpu_tpps(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRS);
}

void cpu_tpprh(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRRH);
}

void cpu_tpprl(Risc256* aCPUPt){
    cpu_tpp(aCPUPt, aCPUPt->vRRL);
}


//=========================================================//
// 0xCX - Push
void cpu_psh_int(Risc256* aCPUPt){
    *aCPUPt->vSP += WORDSIZE*16;    //16 Registers
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    memcpy(aCPUPt->vSPAddr+1, aCPUPt->vRA, WORDSIZE*16);
    
}

void cpu_psh_call(Risc256* aCPUPt){
    *aCPUPt->vSP += WORDSIZE*14;    //16 Registers
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    memcpy(aCPUPt->vSPAddr+1, aCPUPt->vRA, WORDSIZE*14);
    
}

void cpu_psh(Risc256* aCPUPt, CPUType* aReg){
    *(aCPUPt->vSPAddr) = (*aReg);
    *aCPUPt->vSP += WORDSIZE;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
}

void cpu_psha(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRA);
}

void cpu_pshb(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRB);
}

void cpu_pshc(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRC);
}

void cpu_pshdh(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRDH);
}

void cpu_pshdl(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRDL);
}

void cpu_psheh(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vREH);
}

void cpu_pshel(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vREL);
}

void cpu_pshtp(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vTP);
}

void cpu_pshsp(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vSP);
}

void cpu_pshi(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRI);
}

void cpu_pshpch(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vPCH);
}

void cpu_pshpcl(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vPCL);
}

void cpu_pshf(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRF);
}

void cpu_pshs(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRS);
}

void cpu_pshrh(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRRH);
}

void cpu_pshrl(Risc256* aCPUPt){
    cpu_psh(aCPUPt, aCPUPt->vRRL);
}

//=========================================================//
// 0xDX - Pop

void cpu_pop_int(Risc256* aCPUPt){
    memcpy(aCPUPt->vRA, aCPUPt->vSPAddr+1, WORDSIZE*16);
    *aCPUPt->vSP += WORDSIZE*16;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    
}

void cpu_pop_call(Risc256* aCPUPt){
    memcpy(aCPUPt->vRA, aCPUPt->vSPAddr+1, WORDSIZE*14);
    *aCPUPt->vSP += WORDSIZE*14;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    
}

void cpu_pop(Risc256* aCPUPt, CPUType *aReg){
    *aCPUPt->vSP += WORDSIZE;
    aCPUPt->vSPAddr = aCPUPt->vMemByte+(*aCPUPt->vSP);
    *(aReg) = *(aCPUPt->vSPAddr);
    
}

void cpu_popa(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRA);
}

void cpu_popb(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRB);
}

void cpu_popc(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRC);
}

void cpu_popdh(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRDH);
}

void cpu_popdl(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRDL);
}

void cpu_popeh(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vREH);
}

void cpu_popel(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vREL);
}

void cpu_poptp(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vTP);
}

void cpu_popsp(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vSP);
}

void cpu_popi(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRI);
}

void cpu_poppch(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vPCH);
}

void cpu_poppcl(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vPCL);
}

void cpu_popf(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRF);
}

void cpu_pops(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRS);
}

void cpu_poprh(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRRH);
}

void cpu_poprl(Risc256* aCPUPt){
    cpu_pop(aCPUPt, aCPUPt->vRRL);
}



//=========================================================//
// 0xEX - Relative push


//=========================================================//
// 0xFX - Set/clear flags

void push_registers(Risc256* aCPUPt){
    
    
    
}

//
//void cpu_clrIF(Risc256* cpu){
//    
//    if((*cpu->vRS & IF_SET)!=0){
//
//        //printf("Before POP: %lu %lu\n",*aCPUPt->vRegisters->vRF, *aCPUPt->vRegisters->vPC);
//        *cpu->vSP += cpu->vMemSize;
//        *cpu->vRF = *((CPUType*)(cpu->vMemByte+*cpu->vSP));
//
//        *cpu->vSP += cpu->vMemSize;
//        *cpu->vPC = *((CPUType*)(cpu->vMemByte+*cpu->vSP));
//        (*cpu->vPC)--;
//
//        *cpu->vRS &= IF_CLR;
//
//        //printf("After POP: %lu %lu\n",*aCPUPt->vRegisters->vRF, *aCPUPt->vRegisters->vPC);
//    }
//}