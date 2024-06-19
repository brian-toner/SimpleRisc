#include "instructions.h"

void cpu_inc_ra(Risc256* cpu) { cpu_add_word(cpu, cpu->RA, 1, 0);}
void cpu_inc_rb(Risc256* cpu) { cpu_add_word(cpu, cpu->RB, 1, 0);}
void cpu_inc_rc(Risc256* cpu) { cpu_add_word(cpu, cpu->RC, 1, 0);}
void cpu_inc_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RI, 1, 0);}

void cpu_inc_rd_ws(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, WORDSIZE, ADD);}
void cpu_inc_rd_as(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, ADDRSIZE, ADD);}
void cpu_inc_re_ws(Risc256* cpu) { cpu_add_addr(cpu, cpu->RE, WORDSIZE, ADD);}
void cpu_inc_re_as(Risc256* cpu) { cpu_add_addr(cpu, cpu->RE, ADDRSIZE, ADD);}

void cpu_inc_ra_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RA, *cpu->RI, 0);}
void cpu_inc_rb_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RB, *cpu->RI, 0);}
void cpu_inc_rc_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RC, *cpu->RI, 0);}
void cpu_inc_rd_ri(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, *cpu->RI, ADD);}
void cpu_inc_re_ri(Risc256* cpu) { cpu_add_addr(cpu, cpu->RE, *cpu->RI, ADD);}

void cpu_inc_sp_ws(Risc256* cpu) { 
    if(isRing0(cpu)){
        cpu_add_addr(cpu, cpu->SP, WORDSIZE, ADD);
    } else {
        *cpu->RF |= (E_SET | A_SET);
    }

}
void cpu_inc_tp_ws(Risc256* cpu) { cpu_add_addr(cpu, cpu->TP, WORDSIZE, ADD);}
void cpu_inc_mem(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, WORDSIZE, ADD); cpu_add_addr(cpu, cpu->RE, WORDSIZE, ADD);}