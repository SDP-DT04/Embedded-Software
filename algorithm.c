/*
 * File:   algorithm.c
 * Author: DT04
 *
 * Created on April 9, 2017, 8:06 PM
 */

#include "xc.h"
#include "algorithm.h"

const static int L1 = 10L; 
const static int L2 = 2L;
const static int L3 = 2L;

static int R, Rm1, xf, vi, si, xfm1, vim1, sim1, am1 = 0; 

void ALG_Init_R()
{
    /* reset all variables to zero*/
    R = 0;
    Rm1 = 0;
    xf = 0; 
    vi = 0;
    si = 0; 
    xfm1 = 4096; 
    vim1 = 0;
    sim1 = 0; 
    am1 = 4096; 
    
//    ALG_Calculate_R(4096);
//    ALG_Calculate_R(4096);
//    ALG_Calculate_R(4096);
//    ALG_Calculate_R(4096);
}

int ALG_Calculate_R(short a)
{
    /* calculate the R value */
	xf = L1*a + (100L-L1)*xfm1; //running average
	vi = L2 * (a - xfm1) * (a-xfm1)  + (100L-L2)*vim1; // running variance (1)
	si = L3 * (a - am1) * (a-am1) + (100L-L3)*sim1; // running variance (2)
	R = ((200L-L1)*vi) / si;
    
    /* update previous values */
    xfm1 = xf; 
    sim1 = si; 
    vim1 = vi;
    am1 = a; 
    Rm1 = R;
    
    return R; 
}