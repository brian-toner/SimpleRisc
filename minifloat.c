/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "minifloat.h"



const unsigned int FLOAT8MAP[256] ={0x00000000,0x3883126f,0x3903126f,0x39449ba6,0x3983126f,0x39a3d70a,0x39c49ba6,0x39e56042,
                                0x3a03126f,0x3a1374bc,0x3a23d70a,0x3a343958,0x3a449ba6,0x3a54fdf4,0x3a656042,0x3a75c28f,
                                0x3aa3d70a,0x3af5c28f,0x3b23d70a,0x3b4ccccd,0x3b75c28f,0x3b8f5c29,0x3ba3d70a,0x3bb851ec,
                                0x3bcccccd,0x3be147ae,0x3bf5c28f,0x3c051eb8,0x3c0f5c29,0x3c19999a,0x3c23d70a,0x3c2e147b,
                                0x3c4ccccd,0x3c99999a,0x3ccccccd,0x3d000000,0x3d19999a,0x3d333333,0x3d4ccccd,0x3d666666,
                                0x3d800000,0x3d8ccccd,0x3d99999a,0x3da66666,0x3db33333,0x3dc00000,0x3dcccccd,0x3dd9999a,
                                0x3e000000,0x3e400000,0x3e800000,0x3ea00000,0x3ec00000,0x3ee00000,0x3f000000,0x3f100000,
                                0x3f200000,0x3f300000,0x3f400000,0x3f500000,0x3f600000,0x3f700000,0x3f800000,0x3f880000,
                                0x3fa00000,0x3ff00000,0x40200000,0x40480000,0x40700000,0x408c0000,0x40a00000,0x40b40000,
                                0x40c80000,0x40dc0000,0x40f00000,0x41020000,0x410c0000,0x41160000,0x41200000,0x412a0000,
                                0x41480000,0x41960000,0x41c80000,0x41fa0000,0x42160000,0x422f0000,0x42480000,0x42610000,
                                0x427a0000,0x42898000,0x42960000,0x42a28000,0x42af0000,0x42bb8000,0x42c80000,0x42d48000,
                                0x42fa0000,0x433b8000,0x437a0000,0x439c4000,0x43bb8000,0x43dac000,0x43fa0000,0x440ca000,
                                0x441c4000,0x442be000,0x443b8000,0x444b2000,0x445ac000,0x446a6000,0x447a0000,0x4484d000,
                                0x449c4000,0x44ea6000,0x451c4000,0x45435000,0x456a6000,0x4588b800,0x459c4000,0x45afc800,
                                0x45c35000,0x45d6d800,0x45ea6000,0x45fde800,0x4608b800,0x46127c00,0x461c4000,0x7f800000,

                                0x7fffffff,0xb883126f,0xb903126f,0xb9449ba6,0xb983126f,0xb9a3d70a,0xb9c49ba6,0xb9e56042,
                                0xba03126f,0xba1374bc,0xba23d70a,0xba343958,0xba449ba6,0xba54fdf4,0xba656042,0xba75c28f,
                                0xbaa3d70a,0xbaf5c28f,0xbb23d70a,0xbb4ccccd,0xbb75c28f,0xbb8f5c29,0xbba3d70a,0xbbb851ec,
                                0xbbcccccd,0xbbe147ae,0xbbf5c28f,0xbc051eb8,0xbc0f5c29,0xbc19999a,0xbc23d70a,0xbc2e147b,
                                0xbc4ccccd,0xbc99999a,0xbccccccd,0xbd000000,0xbd19999a,0xbd333333,0xbd4ccccd,0xbd666666,
                                0xbd800000,0xbd8ccccd,0xbd99999a,0xbda66666,0xbdb33333,0xbdc00000,0xbdcccccd,0xbdd9999a,
                                0xbe000000,0xbe400000,0xbe800000,0xbea00000,0xbec00000,0xbee00000,0xbf000000,0xbf100000,
                                0xbf200000,0xbf300000,0xbf400000,0xbf500000,0xbf600000,0xbf700000,0xbf800000,0xbf880000,
                                0xbfa00000,0xbff00000,0xc0200000,0xc0480000,0xc0700000,0xc08c0000,0xc0a00000,0xc0b40000,
                                0xc0c80000,0xc0dc0000,0xc0f00000,0xc1020000,0xc10c0000,0xc1160000,0xc1200000,0xc12a0000,
                                0xc1480000,0xc1960000,0xc1c80000,0xc1fa0000,0xc2160000,0xc22f0000,0xc2480000,0xc2610000,
                                0xc27a0000,0xc2898000,0xc2960000,0xc2a28000,0xc2af0000,0xc2bb8000,0xc2c80000,0xc2d48000,
                                0xc2fa0000,0xc33b8000,0xc37a0000,0xc39c4000,0xc3bb8000,0xc3dac000,0xc3fa0000,0xc40ca000,
                                0xc41c4000,0xc42be000,0xc43b8000,0xc44b2000,0xc45ac000,0xc46a6000,0xc47a0000,0xc484d000,
                                0xc49c4000,0xc4ea6000,0xc51c4000,0xc5435000,0xc56a6000,0xc588b800,0xc59c4000,0xc5afc800,
                                0xc5c35000,0xc5d6d800,0xc5ea6000,0xc5fde800,0xc608b800,0xc6127c00,0xc61c4000,0xff800000};

const float PFLOAT8MAP[256]= {  0.00000000,0.00006250,0.00012500,0.00018750,0.00025000,0.00031250,0.00037500,0.00043750,
                                0.00050000,0.00056250,0.00062500,0.00068750,0.00075000,0.00081250,0.00087500,0.00093750,
                                0.00125000,0.00187500,0.00250000,0.00312500,0.00375000,0.00437500,0.00500000,0.00562500,
                                0.00625000,0.00687500,0.00750000,0.00812500,0.00875000,0.00937500,0.01000000,0.01062500,
                                0.01250000,0.01875000,0.02500000,0.03125000,0.03750000,0.04375000,0.05000000,0.05625000,
                                0.06250000,0.06875000,0.07500000,0.08125000,0.08750000,0.09375000,0.10000000,0.10625000,
                                0.12500000,0.18750000,0.25000000,0.31250000,0.37500000,0.43750000,0.50000000,0.56250000,
                                0.62500000,0.68750000,0.75000000,0.81250000,0.87500000,0.93750000,1.00000000,1.06250000,
                                1.25000000,1.87500000,2.50000000,3.12500000,3.75000000,4.37500000,5.00000000,5.62500000,
                                6.25000000,6.87500000,7.50000000,8.12500000,8.75000000,9.37500000,10.00000000,10.62500000,
                                12.50000000,18.75000000,25.00000000,31.25000000,37.50000000,43.75000000,50.00000000,56.25000000,
                                62.50000000,68.75000000,75.00000000,81.25000000,87.50000000,93.75000000,100.00000000,106.25000000,
                                125.00000000,187.50000000,250.00000000,312.50000000,375.00000000,437.50000000,500.00000000,562.50000000,
                                625.00000000,687.50000000,750.00000000,812.50000000,875.00000000,937.50000000,1000.00000000,1062.50000000,
                                1250.00000000,1875.00000000,2500.00000000,3125.00000000,3750.00000000,4375.00000000,5000.00000000,5625.00000000,
                                6250.00000000,6875.00000000,7500.00000000,8125.00000000,8750.00000000,9375.00000000,10000.00000000,10625.00000000};


float mini_to_float(unsigned char mini){
    //printf("mini_to_float: %u %u\n", mini, FLOAT8MAP+mini);
    return *(float*)(FLOAT8MAP+mini);
}

/*
void print_float_map(){
    float lVal;
    float lCVal;
    int lConv;
    for(int i = 0; i < 256; i++){
        //lVal = FLOAT8MAP[i];
        lVal = FLOAT8MAPNEW[i];
        lConv = *(int*)(&lVal);
        lCVal = *(float*)(&lConv);
        //printf("%u %f %f | %x\n",i,lVal,lCVal,lConv);
        printf("%u 0x%x\n",i,lConv);
    }
}
*/

unsigned char bin_search(float floatVal) {
    unsigned char left = 0;
    unsigned char right = 126;
    unsigned char mid;
    
    // Binary search for the closest value
    while (left < right) {
        mid = (left + right) / 2;
        if (floatVal < PFLOAT8MAP[mid]) {
            right = mid;
        } else if (floatVal > PFLOAT8MAP[mid + 1]) {
            left = mid + 1;
        } else {
            break;
        }
    }
    
    // Determine the closest value
    float dl = floatVal - PFLOAT8MAP[mid];
    float dr = PFLOAT8MAP[mid + 1] - floatVal;
    if (dr < dl) {
        mid++;
    }
    
    return mid;
}

unsigned char float_to_mini(float floatVal){

    if(isnan(floatVal)){
        return F2M_NAN;
    } else if(floatVal > MAXFLOAT){
        return F2M_INF;
    } else if(floatVal < MINFLOAT){
        return F2M_NINF;
    } else if(floatVal<0){
        return bin_search(-floatVal)+128;
    } else {
        return bin_search(floatVal);
    }
    
    return F2M_NAN;
}

bool isNan(unsigned char mini){
    return mini == F2M_NAN;
}

bool isInf(unsigned char mini){
    return (mini == F2M_INF || mini == F2M_NINF);
}