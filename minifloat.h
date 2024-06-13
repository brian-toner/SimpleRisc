/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   minifloat.h
 * Author: brian
 *
 * Created on September 19, 2020, 6:13 PM
 */

#ifndef MINIFLOAT_H
#define MINIFLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
    
#ifndef bool
typedef unsigned char boolean;
typedef unsigned char bool;
#endif

#define F2M_NAN 128
#define F2M_INF 127
#define F2M_NINF 255

#define MAXFLOAT 10000
#define MINFLOAT -10000

float mini_to_float(unsigned char mini);
unsigned char float_to_mini(float floatVal);
void print_float_map();
bool isNan(unsigned char mini);
bool isInf(unsigned char mini);
        
#ifdef __cplusplus
}
#endif

#endif /* MINIFLOAT_H */

