#include "instructions.h"



void cpu_dec_ra(Risc256* cpu) { cpu_add_word(cpu, cpu->RA, -1, SUB);}
void cpu_dec_rb(Risc256* cpu) { cpu_add_word(cpu, cpu->RB, -1, SUB);}
void cpu_dec_rc(Risc256* cpu) { cpu_add_word(cpu, cpu->RC, -1, SUB);}
void cpu_dec_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RI, -1, SUB);}

void cpu_dec_rd_ws(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, -WORDSIZE, SUB);}
void cpu_dec_rd_as(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, -ADDRSIZE, SUB);}
void cpu_dec_re_ws(Risc256* cpu) { cpu_add_addr(cpu, cpu->RE, -WORDSIZE, SUB);}
void cpu_dec_re_as(Risc256* cpu) { cpu_add_addr(cpu, cpu->RE, -ADDRSIZE, SUB);}

void cpu_dec_ra_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RA, -*cpu->RI, SUB);}
void cpu_dec_rb_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RB, -*cpu->RI, SUB);}
void cpu_dec_rc_ri(Risc256* cpu) { cpu_add_word(cpu, cpu->RC, -*cpu->RI, SUB);}
void cpu_dec_rd_ri(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, -*cpu->RI, SUB);}
void cpu_dec_re_ri(Risc256* cpu) { cpu_add_addr(cpu, cpu->RE, -*cpu->RI, SUB);}

void cpu_dec_sp_ws(Risc256* cpu) { 
    if(isRing0(cpu)){
        cpu_add_addr(cpu, cpu->SP, -WORDSIZE, SUB);
    } else {
        *cpu->RF |= (E_SET | A_SET);
    }

}
void cpu_dec_tp_ws(Risc256* cpu) { cpu_add_addr(cpu, cpu->TP, -WORDSIZE, SUB);}
void cpu_dec_mem(Risc256* cpu) { cpu_add_addr(cpu, cpu->RD, -WORDSIZE, SUB); cpu_add_addr(cpu, cpu->RE, -WORDSIZE, SUB);}