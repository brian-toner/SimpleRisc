/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   output.h
 * Author: brian
 *
 * Created on September 16, 2020, 6:21 PM
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
    
void print_bin_char(char val);
void print_bin(char* val, int size);
void print_mem(unsigned char* val, int size);

#ifdef __cplusplus
}
#endif

#endif /* OUTPUT_H */

