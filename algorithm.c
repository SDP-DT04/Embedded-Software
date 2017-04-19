/*
 * File:   algorithm.c
 * Author: DT04
 *
 * Created on April 9, 2017, 8:06 PM
 */

#include "xc.h"
#include "algorithm.h"

const static double L1 = .101; 
const static double L2 = .02;
const static double L3 = .02;

static double R, Rm1, xf, vi, si, xfm1, vim1, sim1, am1 = 0; 

void ALG_Init_R()
{
    /* reset all variables to zero*/
    R = 0;
    Rm1 = 0;
    xf = 0; 
    vi = 0;
    si = 0; 
    xfm1 = 4000; 
    vim1 = 0;
    sim1 = 0; 
    am1 = 4000; 
}

float ALG_Calculate_R(short a)
{
    /* calculate the R value */
	xf = L1*a + (1-L1)*xfm1; //running average
	vi = L2 * (a - xfm1) * (a-xfm1)  + (1-L2)*vim1; // running variance (1)
	si = L3 * (a - am1) * (a-am1) + (1-L3)*sim1; // running variance (2)
	R = ((2-L1)*vi) / si;
    
    /* update previous values */
    xfm1 = xf; 
    sim1 = si; 
    vim1 = vi;
    am1 = a; 
    Rm1 = R;
    
    return R; 
}