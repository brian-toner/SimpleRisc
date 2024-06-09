#include "instructions.h"


void cpu_getstatus(Risc256* aCPUPt) {
    *aCPUPt->vRA = *aCPUPt->vRS;
}

void cpu_getflags(Risc256* aCPUPt) {
    *aCPUPt->vRA = *aCPUPt->vRF;
}

void cpu_isset(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRA & (1 << *aCPUPt->vRB)) != 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_isclear(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRA & (1 << *aCPUPt->vRB)) == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_istrue(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA != 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_isfalse(Risc256* aCPUPt) {
    bool condition = *aCPUPt->vRA == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_iscset(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRS & C_SET) != 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_iscclear(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRS & C_SET) == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_isoset(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRS & O_SET) != 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_isoclear(Risc256* aCPUPt) {
    bool condition = (*aCPUPt->vRS & O_SET) == 0;
    set_t_flag(aCPUPt, condition);
}

void cpu_istime(Risc256* aCPUPt) {
    //bool condition = *aCPUPt->vRT >= *(aCPUPt->vMem + *aCPUPt->vRE);
    //set_t_flag(aCPUPt, condition);
}

void cpu_tpsh_t(Risc256* aCPUPt) {
    *(aCPUPt->vMem + *aCPUPt->vTP) = (*aCPUPt->vRS & T_SET) ? 1 : 0;
    *aCPUPt->vTP += WORDSIZE;
}

void cpu_and_tpop_t(Risc256* aCPUPt) {
    *aCPUPt->vTP -= WORDSIZE;
    bool stack_val = (*(aCPUPt->vMem + *aCPUPt->vTP)) != 0;
    bool t_val = (*aCPUPt->vRS & T_SET) != 0;
    set_t_flag(aCPUPt, t_val && stack_val);
}

void cpu_or_tpop_t(Risc256* aCPUPt) {
    *aCPUPt->vTP -= WORDSIZE;
    bool stack_val = (*(aCPUPt->vMem + *aCPUPt->vTP)) != 0;
    bool t_val = (*aCPUPt->vRS & T_SET) != 0;
    set_t_flag(aCPUPt, t_val || stack_val);
}

void cpu_nand_tpop_t(Risc256* aCPUPt) {
    *aCPUPt->vTP -= WORDSIZE;
    bool stack_val = (*(aCPUPt->vMem + *aCPUPt->vTP)) != 0;
    bool t_val = (*aCPUPt->vRS & T_SET) != 0;
    set_t_flag(aCPUPt, t_val && !stack_val);
}

void cpu_nor_tpop_t(Risc256* aCPUPt) {
    *aCPUPt->vTP -= WORDSIZE;
    bool stack_val = (*(aCPUPt->vMem + *aCPUPt->vTP)) != 0;
    bool t_val = (*aCPUPt->vRS & T_SET) != 0;
    set_t_flag(aCPUPt, t_val || !stack_val);
}
