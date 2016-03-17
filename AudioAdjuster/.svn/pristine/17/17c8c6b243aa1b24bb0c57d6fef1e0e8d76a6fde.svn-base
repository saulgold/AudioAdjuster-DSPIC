/**************************************************************************************************
* @file		Projects\AudioAdjuster\src\transform.c
*
* Summary:
*         	the functions to initialise parameters for, and perform FFT and inverse FFT operations
*
* ToDo:
*     		none
*
* Originator:
*     		Andy Watt
*
* History:
*      		Version 1.00	06/05/2013	Andy Watt	Initial Version with single function
*			Version 1.01	10/05/2013	Andy Watt	Split single function up into seperate Initialise, FFT and Inverse FFT 
*
**************************************************************************************************/
#include "..\inc\transform.h"
#include <dsp.h>

#define FFT_FRAME_SIZE		128

//variables to store the FFT twiddle factors
fractcomplex compTwidFactors[FFT_FRAME_SIZE]__attribute__ ((space(xmemory),far));
fractcomplex compWorkSpace[FFT_FRAME_SIZE]__attribute__ ((space(ymemory),far));

/************************************************************************************************** 
* @fn fourierTransform 
* @param int iFrameSize,fractcomplex *compX,fractional *frctAudioIn
* @return None
* @brief generates the fourier transform of the inputted signal 
**************************************************************************************************/

void fourierTransform(int iFrameSize,fractcomplex *compX,fractional *frctAudioIn)
{
	int i;
	
	//copy fractional audio signal into real part of complex fractional data type
	for(i=0;i<iFrameSize;i++)
	{
		compWorkSpace[i].real = frctAudioIn[i];
		compWorkSpace[i].imag = 0;
	}	
	
	//generate the first half of the set of twiddle factors required by the DFT
	TwidFactorInit (7,compTwidFactors,0);

	//generate the DFT of the audio signal
	FFTComplex(7,compX,compWorkSpace,compTwidFactors,0xFF00);
}

/************************************************************************************************** 
* @fn inverseFourierTransform 
* @param int iFrameSize,fractional *frctAudioWorkSpace,fractcomplex *compX
* @return None
* @brief generates the inverse fourier transform of the inputted signal 
**************************************************************************************************/

void inverseFourierTransform(int iFrameSize,fractional *frctAudioWorkSpace,fractcomplex *compX)
{
	int i;
	
	//generate the first half of the set of twiddle factors required by the DFT
	TwidFactorInit (7,compTwidFactors,1);//1 for inverse fourier transform

	//generate the inverse DFT of the audio signals frequency spectrum
	IFFTComplex(7,compWorkSpace,compX,compTwidFactors,0xFF00);

	for(i=0;i<iFrameSize;i++)
	{
		frctAudioWorkSpace[i] = compWorkSpace[i].real;
	}		
}

/************************************************************************************************** 
* @fn filterNegativeFreq 
* @param int iFrameSize,fractcomplex *compXfiltered,fractcomplex *compX
* @return None
* @brief filters out the negative frequencies by suppressing the upper half of the inputted frequency band 
**************************************************************************************************/

void filterNegativeFreq(int iFrameSize,fractcomplex *compXfiltered,fractcomplex *compX)
{
	int i;
	int iNegativeFreqStart = iFrameSize/2;//negative frequencies start from half way through the array
	
	//filter out negative frequencies
	for(i=0;i<iNegativeFreqStart;i++)
	{
		compXfiltered[i].real = compX[i].real;
		compXfiltered[i].imag = compX[i].imag;
	}	

	//filter out negative frequencies
	for(i=iNegativeFreqStart;i<iFrameSize;i++)
	{
		compXfiltered[i].real = 0;
		compXfiltered[i].imag = 0;
	}
}

/************************************************************************************************** 
* @fn shiftFreqSpectrum 
* @param int iFrameSize,int iShiftAmount,fractcomplex *compXshifted,fractcomplex *compX
* @return None
* @brief shifts the inputted frequency band by a set amount and filters any negative frequencies generated 
**************************************************************************************************/

void shiftFreqSpectrum(int iFrameSize,int iShiftAmount,fractcomplex *compXshifted,fractcomplex *compX)
{
	int i;
	int iNegativeFreqStart = iFrameSize/2;//negative frequencies start from half way through the array
	
	//frequency shift by 62.5Hz which is 1 bin to the right
	for(i=0;i<iShiftAmount;i++)//pad left side with zeros 
	{
		compXshifted[i].real = 0;
		compXshifted[i].imag = 0;		
	}
	//shift the bins to the right by shiftAmount
	for(i=0;i<iFrameSize-iShiftAmount;i++)
	{
		compXshifted[i+iShiftAmount].real = compX[i].real;
		compXshifted[i+iShiftAmount].imag = compX[i].imag;		
	}
	//filter out any frequencies that have been shifted into the ngative domain
	for(i=iNegativeFreqStart;i<iFrameSize;i++)
	{
		compXshifted[i].real = 0;
		compXshifted[i].imag = 0;		
	}
}

