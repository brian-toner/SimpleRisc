#include "instructions.h"


void cpu_getstatus(Risc256* cpu) {
    *cpu->RA = *cpu->RS;
}

void cpu_getflags(Risc256* cpu) {
    *cpu->RA = *cpu->RF;
}

void cpu_isset(Risc256* cpu) {
    bool condition = (*cpu->RA & (1 << *cpu->RB)) != 0;
    set_t_flag(cpu, condition);
}

void cpu_isclear(Risc256* cpu) {
    bool condition = (*cpu->RA & (1 << *cpu->RB)) == 0;
    set_t_flag(cpu, condition);
}

void cpu_istrue(Risc256* cpu) {
    bool condition = *cpu->RA != 0;
    set_t_flag(cpu, condition);
}

void cpu_isfalse(Risc256* cpu) {
    bool condition = *cpu->RA == 0;
    set_t_flag(cpu, condition);
}

void cpu_iscset(Risc256* cpu) {
    bool condition = (*cpu->RS & C_SET) != 0;
    set_t_flag(cpu, condition);
}

void cpu_iscclear(Risc256* cpu) {
    bool condition = (*cpu->RS & C_SET) == 0;
    set_t_flag(cpu, condition);
}

void cpu_isoset(Risc256* cpu) {
    bool condition = (*cpu->RS & O_SET) != 0;
    set_t_flag(cpu, condition);
}

void cpu_isoclear(Risc256* cpu) {
    bool condition = (*cpu->RS & O_SET) == 0;
    set_t_flag(cpu, condition);
}

void cpu_istime(Risc256* cpu) {
    //bool condition = *cpu->vRT >= *(cpu->Mem + *cpu->RE);
    //set_t_flag(cpu, condition);
}

void cpu_tpsh_t(Risc256* cpu) {
    *(cpu->Mem + *cpu->TP) = (*cpu->RS & T_SET) ? 1 : 0;
    *cpu->TP += WORDSIZE;
}

void cpu_and_tpop_t(Risc256* cpu) {
    *cpu->TP -= WORDSIZE;
    bool stack_val = (*(cpu->Mem + *cpu->TP)) != 0;
    bool t_val = (*cpu->RS & T_SET) != 0;
    set_t_flag(cpu, t_val && stack_val);
}

void cpu_or_tpop_t(Risc256* cpu) {
    *cpu->TP -= WORDSIZE;
    bool stack_val = (*(cpu->Mem + *cpu->TP)) != 0;
    bool t_val = (*cpu->RS & T_SET) != 0;
    set_t_flag(cpu, t_val || stack_val);
}

void cpu_nand_tpop_t(Risc256* cpu) {
    *cpu->TP -= WORDSIZE;
    bool stack_val = (*(cpu->Mem + *cpu->TP)) != 0;
    bool t_val = (*cpu->RS & T_SET) != 0;
    set_t_flag(cpu, t_val && !stack_val);
}

void cpu_nor_tpop_t(Risc256* cpu) {
    *cpu->TP -= WORDSIZE;
    bool stack_val = (*(cpu->Mem + *cpu->TP)) != 0;
    bool t_val = (*cpu->RS & T_SET) != 0;
    set_t_flag(cpu, t_val || !stack_val);
}
