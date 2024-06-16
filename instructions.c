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

uint8_t get_iopl(Risc256* cpu){
    CPUType IOPL = *cpu->RF & (P0_SET | P1_SET);
    return IOPL;
}

uint8_t get_current_ring(Risc256* cpu) {
    CPUPtrType pc = *cpu->PC;
    if (pc < *cpu->RING1Start) {
        return 0; // Ring 0
    } else if (pc < *cpu->RING2Start) {
        return 1; // Ring 1
    } else if (pc < *cpu->RING3Start) {
        return 2; // Ring 2
    } else {
        return 3; // Ring 3
    }
}

void cpu_set_addr(Risc256* cpu){
    cpu->RDAddr = cpu-> MemByte+(*cpu->RD);
    cpu->REAddr = cpu-> MemByte+(*cpu->RE);
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
    cpu->TPAddr = cpu-> MemByte+(*cpu->TP);

}

// Helper function to check if we are in ring 0
bool is_in_ring_0(Risc256* cpu) {
    return !(*cpu->RF & (P0_SET | P1_SET));
}

bool is_iopl_authorized(Risc256* cpu, CPUPtrType addr) {
    uint8_t current_ring = get_current_ring(cpu);
    if (current_ring <= (*cpu->RF & (P0_SET | P1_SET))) {
        return true; // Authorized if current ring is within IOPL
    } else {
        *cpu->RF |= (E_SET | A_SET); // Set error and authorization error flags if not authorized
        return false;
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
    cpu_vinit, cpu_start, cpu_stop, cpu_step,  cpu_save, cpu_vload, cpu_RSave, cpu_vrload,
    cpu_vbegin, cpu_vend, cpu_RSsetre, cpu_vcopy, cpu_viserror, cpu_vishlt, cpu_SWInterrupt, cpu_HWInterrupt,
        
    //0xF0-0xFF: Control instructions
    cpu_func_call, cpu_swi, cpu_branch, cpu_branch_t, cpu_branch_f, cpu_ternary_ra_rb, cpu_ternary_rd_re, cpu_ternary_rd_re_mem, 
    cpu_rfi, cpu_ret, cpu_reset_sp, cpu_reset_tp, cpu_time, cpu_jmp, cpu_rjmp, cpu_hlt
    
};

void executeInstruction(Risc256* cpu) {
    uint8_t opcode = *(cpu-> MemByte + *(cpu->PC));
    instructionHandlers[opcode](cpu);
    (*(cpu->PC))++; // Increment the program counter after executing the instruction
}



// Helper function to update stack pointer for push operations with boundary and ring 0 check for the regular stack
bool update_stack_pointer_push(Risc256* cpu, size_t increment) {
    if (is_in_ring_0(cpu)) {
        if (*cpu->SP + increment <= *cpu->SEP) {
            *cpu->SP += increment;
            return true;
        } else {
            *cpu->RF |= E_SET; // Set error flag if stack overflow
        }
    } else {
        *cpu->RF |= (E_SET | A_SET); // Set error and authorization error flags if not in ring 0
    }
    return false;
}

// Helper function to update stack pointer for pop operations with boundary and ring 0 check for the regular stack
bool update_stack_pointer_pop(Risc256* cpu, size_t decrement) {
    if (is_in_ring_0(cpu)) {
        if (*cpu->SP >= *cpu->SSP + decrement) {
            *cpu->SP -= decrement;
            return true;
        } else {
            *cpu->RF |= E_SET; // Set error flag if stack underflow
        }
    } else {
        *cpu->RF |= (E_SET | A_SET); // Set error and authorization error flags if not in ring 0
    }
    return false;
}

// Helper function to push a register onto the regular stack
void push_register_to_stack(Risc256* cpu, CPUType* reg, size_t size) {
    if (update_stack_pointer_push(cpu, size)) {
        unsigned char* spAddr = cpu-> MemByte + (*cpu->SP - size);
        memcpy(spAddr, reg, size);
    }
}

// Helper function to pop a register from the regular stack
void pop_register_from_stack(Risc256* cpu, CPUType* reg, size_t size) {
    if (update_stack_pointer_pop(cpu, size)) {
        unsigned char* spAddr = cpu-> MemByte + *cpu->SP;
        memcpy(reg, spAddr, size);
    }
}


// Helper function to update stack pointer for push operations with boundary check for the temporary stack
bool update_temp_stack_pointer_push(Risc256* cpu, size_t increment) {
    if (*cpu->TP + increment <= *cpu->TEP) {
        *cpu->TP += increment;
        return true;
    } else {
        *cpu->RF |= E_SET; // Set error flag if stack overflow
    }
    return false;
}

// Helper function to update stack pointer for pop operations with boundary check for the temporary stack
bool update_temp_stack_pointer_pop(Risc256* cpu, size_t decrement) {
    if (*cpu->TP >= *cpu->TSP + decrement) {
        *cpu->TP -= decrement;
        return true;
    } else {
        *cpu->RF |= E_SET; // Set error flag if stack underflow
    }
    return false;
}

// Helper function to push a register onto the temporary stack
void push_register_to_temp_stack(Risc256* cpu, CPUType* reg, size_t size) {
    if (update_temp_stack_pointer_push(cpu, size)) {
        unsigned char* tpAddr = cpu-> MemByte + (*cpu->TP - size);
        memcpy(tpAddr, reg, size);
    }
}

// Helper function to pop a register from the temporary stack
void pop_register_from_temp_stack(Risc256* cpu, CPUType* reg, size_t size) {
    if (update_temp_stack_pointer_pop(cpu, size)) {
        unsigned char* tpAddr = cpu-> MemByte + *cpu->TP;
        memcpy(reg, tpAddr, size);
    }
}



double logbn(double a, double b){
    return log(a)/log(b);
}




void cpu_qstf(Risc256* cpu){
    
    char* lBuff = (char*)(cpu->RA+*cpu->RE);
    CPUFloat lFVal = atof(lBuff);
    CPUType lVal = float_to_cputype(lFVal);
    *cpu->RA = lVal;
    
}

void cpu_qsti(Risc256* cpu){
    
    char* lBuff = (char*)(cpu->RA+*cpu->RE);
    *cpu->RA  = atoi(lBuff);
    
}

void cpu_nop(Risc256* cpu){
    return;
}


void cpu_qadd(Risc256* cpu){
    *cpu->RA = (*cpu->RA)+(*cpu->RB);
}

void cpu_qsub(Risc256* cpu){
    *cpu->RA = (*cpu->RA)-(*cpu->RB);
}

void cpu_qmul(Risc256* cpu){
    *cpu->RA = (*cpu->RA)*(*cpu->RB);
}

void cpu_qdiv(Risc256* cpu){
    *cpu->RA = (*cpu->RA)/(*cpu->RB);
}

void cpu_qmod(Risc256* cpu){
    *cpu->RA = (*cpu->RA)%(*cpu->RB);
}

void cpu_stb(Risc256* cpu){
    *cpu->RA = (*cpu->RA)|(1<<(*cpu->RB));
}

void cpu_clb(Risc256* cpu){
    *cpu->RA = (*cpu->RA)&(~(1<<(*cpu->RB)));
}

void cpu_qnot(Risc256* cpu){
    *cpu->RA = ~(*cpu->RA);
}

void cpu_qand(Risc256* cpu){
    *cpu->RA = (*cpu->RA)&(*cpu->RB);
}

void cpu_qor(Risc256* cpu){
    *cpu->RA = (*cpu->RA)|(*cpu->RB);
}

void cpu_qxor(Risc256* cpu){
    *cpu->RA = (*cpu->RA)^(*cpu->RB);
}

void cpu_qshl(Risc256* cpu){
    *cpu->RA = (*cpu->RA)<<(*cpu->RB);
}

void cpu_qshr(Risc256* cpu){
    *cpu->RA = (*cpu->RA)>>(*cpu->RB);
}




//=========================================================//
// 0x1X


//=========================================================//
// 0x2X



//=========================================================//
// 0x01



//
//void cpu_qsin(Risc256* cpu){
//
//    CPUType lVal1 = (*cpu->RA);
//    CPUType lVal2 = (*cpu->RB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*sin(lVal1d);
//    *cpu->RA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qcos(Risc256* cpu){
//
//    CPUType lVal1 = (*cpu->RA);
//    CPUType lVal2 = (*cpu->RB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*cos(lVal1d);
//    *cpu->RA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qtan(Risc256* cpu){
//
//    CPUType lVal1 = (*cpu->RA);
//    CPUType lVal2 = (*cpu->RB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*tan(lVal1d);
//    *cpu->RA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qasin(Risc256* cpu){
//
//    CPUType lVal1 = (*cpu->RA);
//    CPUType lVal2 = (*cpu->RB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*asin(lVal1d);
//    *cpu->RA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qacos(Risc256* cpu){
//
//    CPUType lVal1 = (*cpu->RA);
//    CPUType lVal2 = (*cpu->RB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = lVal2d*acos(lVal1d);
//    *cpu->RA = float_to_cputype(lRet);
//    
//}
//
//void cpu_qatan2(Risc256* cpu){
//
//    CPUType lVal1 = (*cpu->RA);
//    CPUType lVal2 = (*cpu->RB);
//
//    double lVal1d = cputype_to_float(lVal1);
//    double lVal2d = cputype_to_float(lVal2);
//
//    double lRet = atan2(lVal1d,lVal2d);
//    *cpu->RA = float_to_cputype(lRet);
//    
//}

//=========================================================//
// 0x3 - INC

//
//void cpu_inc_ra(Risc256* cpu){
//        
//    CPUType lVal1 = *cpu->RA;
//
//    bool lASign = (*cpu->RA & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *cpu->RA = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *cpu->RS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *cpu->RS = lRFPt;
//            
//}
//
//void cpu_inc_rb(Risc256* cpu){
//        
//    CPUType lVal1 = *cpu->RB;
//
//    bool lASign = (*cpu->RB & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *cpu->RB = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *cpu->RS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *cpu->RS = lRFPt;
//            
//}
//
//void cpu_inc_rc(Risc256* cpu){
//        
//    CPUType lVal1 = *cpu->RC;
//
//    bool lASign = (*cpu->RC & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *cpu->RC = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *cpu->RS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *cpu->RS = lRFPt;
//            
//}
//
//
//void cpu_inc_ri(Risc256* cpu){
//        
//    CPUType lVal1 = *cpu->RI;
//
//    bool lASign = (*cpu->RI & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+1;
//    *cpu->RI = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *cpu->RS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET|C_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)));
//
//    *cpu->RS = lRFPt;
//            
//}
//
//void cpu_inci(Risc256* cpu){
//        
//    CPUType lVal1 = *cpu->RA;
//    CPUType lVal2 = *cpu->RI;
//
//    bool lASign = (*cpu->RA & SIGNBIT)!=0;
//    bool lBSign = (*cpu->RI & SIGNBIT)!=0;
//
//    CPUType lRet = lVal1+lVal2;
//    *cpu->RA = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *cpu->RS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lASign == lBSign && lSign != lASign)?(O_SET):(0)) |
//        ((lVal2 > lRet)?(C_SET):(0)));
//
//    *cpu->RS = lRFPt;
//            
//}
//
//void cpu_incdws(Risc256* cpu){
//        
//    CPUType lVal1 = *cpu->RA;
//
//    bool lASign = (*cpu->RA & SIGNBIT)!=0;
//    CPUType lRet = lVal1+WORDSIZE;
//    *cpu->RA = lRet;
//    
//    bool lSign = (lRet & SIGNBIT)!=0;
//
//    /*Set flags*/
//    CPUType lRFPt = *cpu->RS&CZOS_MASK;
//
//    lRFPt |= 
//        (((lRet==0)?(Z_SET):(0)) | 
//        ((lSign)?(S_SET):(0)) |
//        ((lSign != lASign)?(O_SET):(0)) |
//        ((lVal1 > lRet)?(C_SET):(0)));
//
//    *cpu->RS = lRFPt;
//            
//}


void cpu_qinc(Risc256* cpu, CPUType* aRet){
    *aRet = (*aRet)+1;
}

void cpu_qinci(Risc256* cpu, CPUType* aRet){
    *aRet = (*aRet)+(*cpu->RI);
}

void cpu_qincaddr(Risc256* cpu, CPUType* aRetH, CPUType* aRetL){
    *aRetL = (*aRetL)+1;
    *aRetH = (*aRetH)+(*aRetL==0)*1;
}

//0x30
void cpu_qira(Risc256* cpu){
    cpu_qinc(cpu,cpu->RA);
}

//0x31
void cpu_qirb(Risc256* cpu){
    cpu_qinc(cpu,cpu->RB);
}

//0x32
void cpu_qirc(Risc256* cpu){
    cpu_qinc(cpu,cpu->RC);
}

//0x33
void cpu_qird(Risc256* cpu){
    cpu_qincaddr(cpu,cpu->RDH,cpu->RDL);
}

//0x24
void cpu_qire(Risc256* cpu){
    cpu_qincaddr(cpu,cpu->REH,cpu->REL);
}

//0x25
void cpu_qirrh(Risc256* cpu){
    cpu_qinc(cpu,cpu->RRH);
}

//0x26
void cpu_qirrl(Risc256* cpu){
    cpu_qinc(cpu,cpu->RRL);
}

//0x27
void cpu_qirai(Risc256* cpu){
    cpu_qinci(cpu,cpu->RA);
}

//0x28
void cpu_qirbi(Risc256* cpu){
    cpu_qinci(cpu,cpu->RB);
}

//0x29
void cpu_qirci(Risc256* cpu){
    cpu_qinci(cpu,cpu->RC);
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

void cpu_qdec(Risc256* cpu, CPUType* aRet){
    *aRet = (*aRet)-1;
}

void cpu_qdeci(Risc256* cpu, CPUType* aRet){
    *aRet = (*aRet)-(*cpu->RI);
}

void cpu_qdecaddr(Risc256* cpu, CPUType* aRetH, CPUType* aRetL){
    *aRetL = (*aRetL)-1;
    *aRetH = (*aRetH)-(*aRetL==0)*1;
}

void cpu_qdra(Risc256* cpu){
    cpu_qdec(cpu,cpu->RA);
}

void cpu_qdrb(Risc256* cpu){
    cpu_qdec(cpu,cpu->RB);
}

void cpu_qdrc(Risc256* cpu){
    cpu_qdec(cpu,cpu->RC);
}

void cpu_qdrd(Risc256* cpu){
    cpu_qdecaddr(cpu,cpu->RDH,cpu->RDL);
}

void cpu_qdre(Risc256* cpu){
    cpu_qdecaddr(cpu,cpu->REH,cpu->REL);
}

void cpu_qdrrh(Risc256* cpu){
    cpu_qdec(cpu,cpu->RRH);
}

void cpu_qdrrl(Risc256* cpu){
    cpu_qdec(cpu,cpu->RRL);
}

void cpu_qdrai(Risc256* cpu){
    cpu_qdeci(cpu,cpu->RA);
}

void cpu_qdrbi(Risc256* cpu){
    cpu_qdeci(cpu,cpu->RB);
}

void cpu_qdrci(Risc256* cpu){
    cpu_qdeci(cpu,cpu->RC);
}

//=========================================================//
// 0x04 - CMP

//40
void cpu_qgt(Risc256* cpu){
    *cpu->RF = (*cpu->RA)>(*cpu->RB);
}

//41
void cpu_qlt(Risc256* cpu){
    *cpu->RF = (*cpu->RA)<(*cpu->RB);
}

//42
void cpu_qeq(Risc256* cpu){
    *cpu->RF = (*cpu->RA)==(*cpu->RB);
}

//43
void cpu_qgeq(Risc256* cpu){
    *cpu->RF = (*cpu->RA)>=(*cpu->RB);
}

//44
void cpu_qleq(Risc256* cpu){
    *cpu->RF = (*cpu->RA)<=(*cpu->RB);
}

//45
void cpu_qneq(Risc256* cpu){
    *cpu->RF = (*cpu->RA)!=(*cpu->RB);
}

//46
void cpu_qmaf(Risc256* cpu){
    *cpu->RA = (*cpu->RA)*(*cpu->RF);
}

//47
void cpu_qmbf(Risc256* cpu){
    *cpu->RB = (*cpu->RB)*(*cpu->RF);
}

//48
void cpu_qfgt(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *cpu->RF = lVal1d>lVal2d;
    
}

//49
void cpu_qflt(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *cpu->RF = lVal1d<lVal2d;
    
}

//4A
void cpu_qfeq(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *cpu->RF = lVal1d==lVal2d;
    
}

//4B
void cpu_qfgeq(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *cpu->RF = lVal1d>=lVal2d;
    
}

//4C
void cpu_qfleq(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *cpu->RF = lVal1d<=lVal2d;
    
}

//4D
void cpu_qfneq(Risc256* cpu){

    CPUType lVal1 = (*cpu->RA);
    CPUType lVal2 = (*cpu->RB);
    double lVal1d = cputype_to_float(lVal1);
    double lVal2d = cputype_to_float(lVal2);
    
    *cpu->RF = lVal1d!=lVal2d;
    
}

//4E


//4F

//=========================================================//
// 0x06 - BR/JMP

//=========================================================//
// 0xAX - Temp Push
void cpu_tps_all(Risc256* cpu){
    *cpu->TP -= WORDSIZE*16;    //16 Registers
    cpu->TPAddr = cpu-> MemByte+(*cpu->TP);
    memcpy(cpu->SPAddr+1, cpu->RA, WORDSIZE*16);    
}

void cpu_tps(Risc256* cpu, CPUType* aReg){
    *(cpu->SPAddr) = (*aReg);
    *cpu->SP -= WORDSIZE;
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
}


void cpu_tpsa(Risc256* cpu){
    cpu_tps(cpu, cpu->RA);
}

void cpu_tpsb(Risc256* cpu){
    cpu_tps(cpu, cpu->RB);
}

void cpu_tpsc(Risc256* cpu){
    cpu_tps(cpu, cpu->RC);
}

void cpu_tpsdh(Risc256* cpu){
    cpu_tps(cpu, cpu->RDH);
}

void cpu_tpsdl(Risc256* cpu){
    cpu_tps(cpu, cpu->RDL);
}

void cpu_tpseh(Risc256* cpu){
    cpu_tps(cpu, cpu->REH);
}

void cpu_tpsel(Risc256* cpu){
    cpu_tps(cpu, cpu->REL);
}

void cpu_tpstp(Risc256* cpu){
    cpu_tps(cpu, cpu->TP);
}

void cpu_tpssp(Risc256* cpu){
    cpu_tps(cpu, cpu->SP);
}

void cpu_tpsi(Risc256* cpu){
    cpu_tps(cpu, cpu->RI);
}

void cpu_tpspch(Risc256* cpu){
    cpu_tps(cpu, cpu->PCH);
}

void cpu_tpspcl(Risc256* cpu){
    cpu_tps(cpu, cpu->PCL);
}

void cpu_tpsf(Risc256* cpu){
    cpu_tps(cpu, cpu->RF);
}

void cpu_tpss(Risc256* cpu){
    cpu_tps(cpu, cpu->RS);
}

void cpu_tpsrh(Risc256* cpu){
    cpu_tps(cpu, cpu->RRH);
}

void cpu_tpsrl(Risc256* cpu){
    cpu_tps(cpu, cpu->RRL);
}

//=========================================================//
// 0xBX - Temp Pop

//Pop all registers from temp stack
void cpu_tpp_all(Risc256* cpu){
    memcpy(cpu->RA, cpu->TPAddr+1, WORDSIZE*16);
    *cpu->TP += WORDSIZE*16;
    cpu->TPAddr = cpu-> MemByte+(*cpu->TP);
    
}

//Pop single register from temp stack
void cpu_tpp(Risc256* cpu, CPUType *aReg){
    *cpu->TP += WORDSIZE;
    cpu->TPAddr = cpu-> MemByte+(*cpu->TP);
    *(aReg) = *(cpu->TPAddr);
    
}

void cpu_tppa(Risc256* cpu){
    cpu_tpp(cpu, cpu->RA);
}

void cpu_tppb(Risc256* cpu){
    cpu_tpp(cpu, cpu->RB);
}

void cpu_tppc(Risc256* cpu){
    cpu_tpp(cpu, cpu->RC);
}

void cpu_tppdh(Risc256* cpu){
    cpu_tpp(cpu, cpu->RDH);
}

void cpu_tppdl(Risc256* cpu){
    cpu_tpp(cpu, cpu->RDL);
}

void cpu_tppeh(Risc256* cpu){
    cpu_tpp(cpu, cpu->REH);
}

void cpu_tppel(Risc256* cpu){
    cpu_tpp(cpu, cpu->REL);
}

void cpu_tpptp(Risc256* cpu){
    cpu_tpp(cpu, cpu->TP);
}

void cpu_tppsp(Risc256* cpu){
    cpu_tpp(cpu, cpu->SP);
}

void cpu_tppi(Risc256* cpu){
    cpu_tpp(cpu, cpu->RI);
}

void cpu_tpppch(Risc256* cpu){
    cpu_tpp(cpu, cpu->PCH);
}

void cpu_tpppcl(Risc256* cpu){
    cpu_tpp(cpu, cpu->PCL);
}

void cpu_tppf(Risc256* cpu){
    cpu_tpp(cpu, cpu->RF);
}

void cpu_tpps(Risc256* cpu){
    cpu_tpp(cpu, cpu->RS);
}

void cpu_tpprh(Risc256* cpu){
    cpu_tpp(cpu, cpu->RRH);
}

void cpu_tpprl(Risc256* cpu){
    cpu_tpp(cpu, cpu->RRL);
}


//=========================================================//
// 0xCX - Push
void cpu_psh_int(Risc256* cpu){
    *cpu->SP += WORDSIZE*16;    //16 Registers
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
    memcpy(cpu->SPAddr+1, cpu->RA, WORDSIZE*16);
    
}

void cpu_psh_call(Risc256* cpu){
    *cpu->SP += WORDSIZE*14;    //16 Registers
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
    memcpy(cpu->SPAddr+1, cpu->RA, WORDSIZE*14);
    
}

void cpu_psh(Risc256* cpu, CPUType* aReg){
    *(cpu->SPAddr) = (*aReg);
    *cpu->SP += WORDSIZE;
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
}

void cpu_psha(Risc256* cpu){
    cpu_psh(cpu, cpu->RA);
}

void cpu_pshb(Risc256* cpu){
    cpu_psh(cpu, cpu->RB);
}

void cpu_pshc(Risc256* cpu){
    cpu_psh(cpu, cpu->RC);
}

void cpu_pshdh(Risc256* cpu){
    cpu_psh(cpu, cpu->RDH);
}

void cpu_pshdl(Risc256* cpu){
    cpu_psh(cpu, cpu->RDL);
}

void cpu_psheh(Risc256* cpu){
    cpu_psh(cpu, cpu->REH);
}

void cpu_pshel(Risc256* cpu){
    cpu_psh(cpu, cpu->REL);
}

void cpu_pshtp(Risc256* cpu){
    cpu_psh(cpu, cpu->TP);
}

void cpu_pshsp(Risc256* cpu){
    cpu_psh(cpu, cpu->SP);
}

void cpu_pshi(Risc256* cpu){
    cpu_psh(cpu, cpu->RI);
}

void cpu_pshpch(Risc256* cpu){
    cpu_psh(cpu, cpu->PCH);
}

void cpu_pshpcl(Risc256* cpu){
    cpu_psh(cpu, cpu->PCL);
}

void cpu_pshf(Risc256* cpu){
    cpu_psh(cpu, cpu->RF);
}

void cpu_pshs(Risc256* cpu){
    cpu_psh(cpu, cpu->RS);
}

void cpu_pshrh(Risc256* cpu){
    cpu_psh(cpu, cpu->RRH);
}

void cpu_pshrl(Risc256* cpu){
    cpu_psh(cpu, cpu->RRL);
}

//=========================================================//
// 0xDX - Pop

void cpu_pop_int(Risc256* cpu){
    memcpy(cpu->RA, cpu->SPAddr+1, WORDSIZE*16);
    *cpu->SP += WORDSIZE*16;
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
    
}

void cpu_pop_call(Risc256* cpu){
    memcpy(cpu->RA, cpu->SPAddr+1, WORDSIZE*14);
    *cpu->SP += WORDSIZE*14;
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
    
}

void cpu_pop(Risc256* cpu, CPUType *aReg){
    *cpu->SP += WORDSIZE;
    cpu->SPAddr = cpu-> MemByte+(*cpu->SP);
    *(aReg) = *(cpu->SPAddr);
    
}

void cpu_popa(Risc256* cpu){
    cpu_pop(cpu, cpu->RA);
}

void cpu_popb(Risc256* cpu){
    cpu_pop(cpu, cpu->RB);
}

void cpu_popc(Risc256* cpu){
    cpu_pop(cpu, cpu->RC);
}

void cpu_popdh(Risc256* cpu){
    cpu_pop(cpu, cpu->RDH);
}

void cpu_popdl(Risc256* cpu){
    cpu_pop(cpu, cpu->RDL);
}

void cpu_popeh(Risc256* cpu){
    cpu_pop(cpu, cpu->REH);
}

void cpu_popel(Risc256* cpu){
    cpu_pop(cpu, cpu->REL);
}

void cpu_poptp(Risc256* cpu){
    cpu_pop(cpu, cpu->TP);
}

void cpu_popsp(Risc256* cpu){
    cpu_pop(cpu, cpu->SP);
}

void cpu_popi(Risc256* cpu){
    cpu_pop(cpu, cpu->RI);
}

void cpu_poppch(Risc256* cpu){
    cpu_pop(cpu, cpu->PCH);
}

void cpu_poppcl(Risc256* cpu){
    cpu_pop(cpu, cpu->PCL);
}

void cpu_popf(Risc256* cpu){
    cpu_pop(cpu, cpu->RF);
}

void cpu_pops(Risc256* cpu){
    cpu_pop(cpu, cpu->RS);
}

void cpu_poprh(Risc256* cpu){
    cpu_pop(cpu, cpu->RRH);
}

void cpu_poprl(Risc256* cpu){
    cpu_pop(cpu, cpu->RRL);
}



//=========================================================//
// 0xEX - Relative push


//=========================================================//
// 0xFX - Set/clear flags

void push_registers(Risc256* cpu){
    
    
    
}

//
//void cpu_clrIF(Risc256* cpu){
//    
//    if((*cpu->RS & IF_SET)!=0){
//
//        //printf("Before POP: %lu %lu\n",*cpu->REgisters->RF, *cpu->REgisters->PC);
//        *cpu->SP += cpu->MemSize;
//        *cpu->RF = *((CPUType*)(cpu-> MemByte+*cpu->SP));
//
//        *cpu->SP += cpu->MemSize;
//        *cpu->PC = *((CPUType*)(cpu-> MemByte+*cpu->SP));
//        (*cpu->PC)--;
//
//        *cpu->RS &= IF_CLR;
//
//        //printf("After POP: %lu %lu\n",*cpu->REgisters->RF, *cpu->REgisters->PC);
//    }
//}