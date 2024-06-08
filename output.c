/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "output.h"

void print_bin_char(char val){
    int outputVal[8];
    
    for(int i = 0; i < 8; i++)
        outputVal[7-i] = (val&(1<<i))>0;

    for(int i = 0; i < 8; i++)
      printf("%d", outputVal[i]);    
}

void print_bin(char* val, int size){
    for(int i = 0; i < size; i++){
        print_bin_char(val[size-i-1]);
    }
    printf("\n");
}

void print_mem(unsigned char* val, int size){
    for(int i = 0; i < size; i++){
        
        printf("%02X ",(unsigned int)val[i]);
        if((i+1)%8 == 0){
            printf(" ");
        }
        if((i+1)%32 == 0){
            printf("\n");
        }
        
    }
    printf("\n");
}