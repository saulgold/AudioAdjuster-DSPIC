/**************************************************************************************************
* @file		Projects\AudioAdjuster\src\complexmultiply.c
*
* Summary:
*         	functions to multiply two arrays of complex numbers; and an array of complex with an array of fractional numbers 
*
* ToDo:
*     		none
*
* Originator:
*     		Andy Watt
*
* History:
* 			Version 1.00	07/05/2013	Andy Watt	Initial Version with complex multiply function 
*      		Version 1.01    08/05/2013	Andy Watt	Added combination multiply function 
*
**************************************************************************************************/
#include "..\inc\complexmultiply.h"
#include <dsp.h>

#define FRAME_SIZE 128

//for real and imag parts of each number: (a + bj)(c + dj)
fractional a[FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractional b[FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractional c[FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractional d[FRAME_SIZE]__attribute__ ((space(xmemory),far));

//for multiply results: ac, bcj, adj, bd
fractional ac[FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractional bc[FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractional ad[FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractional bd[FRAME_SIZE]__attribute__ ((space(xmemory),far)); 

fractcomplex compTemp[FRAME_SIZE]__attribute__ ((space(xmemory),far));

/************************************************************************************************** 
* @fn void complexVectorMultiply() 
* @param int iVectorSize,fractcomplex *compResult,fractcomplex *compValue1,fractcomplex *compValue2
* @return None
* @brief Multiplies two same length arrays of complex fractional type and gets a resulting array of 
* complex fractional type 
**************************************************************************************************/

void complexVectorMultiply(int iVectorSize,fractcomplex *compResult,fractcomplex *compValue1,fractcomplex *compValue2)
{
	int i;

	for(i=0;i<iVectorSize;i++)//put the real and imaginary parts into their respective fractional arrays
	{
		a[i] = compValue1[i].real;
		b[i] = compValue1[i].imag;
		c[i] = compValue2[i].real;
		d[i] = compValue2[i].imag;
	}
	VectorMultiply(iVectorSize,ac,a,c);
	VectorMultiply(iVectorSize,bc,b,c);
	VectorMultiply(iVectorSize,ad,a,d);
	VectorMultiply(iVectorSize,bd,b,d);

	VectorAdd(iVectorSize,a,ac,bd);
	VectorAdd(iVectorSize,b,ad,bc);

	for(i=0;i<iVectorSize;i++)//put the real and imaginary fractional parts into a single complex fractional number
	{
		compResult[i].real=a[i];
		compResult[i].imag=b[i];
	}
}

/************************************************************************************************** 
* @fn void combinationVectorMultiply() 
* @param int iVectorSize,fractional *frctResult1,fractcomplex *compResult2,fractional *frctValue1,fractcomplex *compValue2
* @return None
* @brief Multiplies an array of complex type with one of fractional type and gets a two resulting 
* arrays one of complex and one of fractional type 
**************************************************************************************************/

void combinationVectorMultiply(int iVectorSize,fractional *frctResult1,fractcomplex *compResult2,fractional *frctValue1,fractcomplex *compValue2)
{
	int i=0;

	for(i=0;i<iVectorSize;i++)
	{
		compTemp[i].real = frctValue1[i];//put the fractional value 1 into the real part of a single complex fractional number
		compTemp[i].imag = 0;
	}

	complexVectorMultiply(iVectorSize,compResult2,compTemp,compValue2);
	
	for(i=0;i<iVectorSize;i++)//put the real part of the single complex fractional result into a fractional number
	{
		frctResult1[i] = compResult2[i].real;
	}
}
