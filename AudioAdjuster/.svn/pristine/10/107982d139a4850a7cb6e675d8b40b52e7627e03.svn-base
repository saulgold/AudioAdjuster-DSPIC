/**************************************************************************************************
* @file		Projects\AudioAdjuster\src\filter.c
*
* Summary:
*         	initialise and filter functions for the audio adjuster project
*
* ToDo:
*     		none
*
* Originator:
*     		Andy Watt
*
* History:
*      		Version 1.00	28/04/2013	Andy Watt	Initial Version with initFilter and bandPassFilter function 
*			Version 1.01	01/05/2013	Andy Watt	Removed Filter Coefficient Generation and added Coefficients from MATLAB
*			Version 1.02	06/05/2013	Andy Watt	Added shifted low pass filter 
*
**************************************************************************************************/
#include "..\inc\filter.h"
#include "..\inc\modulate.h"
#include "..\inc\complexmultiply.h"
#include <dsp.h>

#define FILTER_LENGTH 	47

//coefficients for a BandPassFilter with LowFStop = 0Hz, LowFPass = 200Hz, HighFPass = 3000Hz,HighFStop = 3200Hz, 
//APass = 1dB,  AStop = 30dB
float fBandPassFilterCoef[FILTER_LENGTH] = 
{
	-0.0294,
   -0.0179,
    0.0015,
   -0.0254,
   -0.0012,
   -0.0188,
   -0.0204,
   -0.0037,
   -0.0331,
   -0.0106,
   -0.0163,
   -0.0402,
    0.0033,
   -0.0459,
   -0.0207,
   -0.0056,
   -0.0684,
    0.0185,
   -0.0533,
   -0.0517,
    0.0598,
   -0.1865,
    0.1781,
    0.7435,
    0.1781,
   -0.1865,
    0.0598,
   -0.0517,
   -0.0533,
    0.0185,
   -0.0684,
   -0.0056,
   -0.0207,
   -0.0459,
    0.0033,
   -0.0402,
   -0.0163,
   -0.0106,
   -0.0331,
   -0.0037,
   -0.0204,
   -0.0188,
   -0.0012,
   -0.0254,
    0.0015,
   -0.0179,
   -0.0294,
};
//coefficients for a LowPassFilter with FPass = 1400Hz, APass = 1dB, FStop = 1600Hz, AStop = 30dB
float fLowPassFilterCoef[FILTER_LENGTH] = 
{
    0.0196,
    0.0016,
   -0.0108,
   -0.0174,
   -0.0093,
    0.0053,
    0.0091,
   -0.0039,
   -0.0184,
   -0.0142,
    0.0076,
    0.0217,
    0.0075,
   -0.0222,
   -0.0303,
    0.0009,
    0.0401,
    0.0348,
   -0.0255,
   -0.0786,
   -0.0391,
    0.1130,
    0.2930,
    0.3733,
    0.2930,
    0.1130,
   -0.0391,
   -0.0786,
   -0.0255,
    0.0348,
    0.0401,
    0.0009,
   -0.0303,
   -0.0222,
    0.0075,
    0.0217,
    0.0076,
   -0.0142,
   -0.0184,
   -0.0039,
    0.0091,
    0.0053,
   -0.0093,
   -0.0174,
   -0.0108,
    0.0016,
    0.0196,
};

//variables for Band Pass Filter
FIRStruct structBandPassFilter;
fractional frctBandPassFilterCoef[FILTER_LENGTH]__attribute__ ((space(xmemory),far));
fractional frctBandPassDelayBuffer[FILTER_LENGTH]__attribute__ ((space(ymemory),far));

//variables for shifted Low Pass Filter
FIRStruct structShiftedLowPassFilter;
fractional frctLowPassFilterCoef[FILTER_LENGTH]__attribute__ ((space(xmemory),far));
fractional frctShiftedLowPassFilterCoef[FILTER_LENGTH]__attribute__ ((space(xmemory),far));
fractcomplex compShiftedLowPassFilterCoef[FILTER_LENGTH]__attribute__ ((space(xmemory),far));
fractional frctShiftedLowPassDelayBuffer[FILTER_LENGTH]__attribute__ ((space(ymemory),far));

/************************************************************************************************** 
* @fn initFilter 
* @param None
* @return None
* @brief Converts coefficients to fractional type and initialises the filter structures 
**************************************************************************************************/

void initFilter()
{
	int i;
	fractcomplex	compLowPassFilterModSignal[FILTER_LENGTH];

	//Filter METHOD 1: 0Hz-4KHz BandPass Filter
 
	//convert band pass filter coefficients from float to fractional data type
	for (i=0;i<FILTER_LENGTH;i++)
	{
		frctBandPassFilterCoef[i] = Float2Fract(fBandPassFilterCoef[i]);
	}
	//initialise band pass filter structure with coefficients and delay buffer
	FIRStructInit(&structBandPassFilter,FILTER_LENGTH,frctBandPassFilterCoef,0xFF00,frctBandPassDelayBuffer);
	FIRDelayInit(&structBandPassFilter);

	//Filter METHOD 2: 2KHz Low Pass Filter shifted out of negative frequency zone by a 2KHz carrier signal  

	//convert low pass filter coefficients from float to fractional data type
	for (i=0;i<FILTER_LENGTH;i++)
	{
		frctLowPassFilterCoef[i] = Float2Fract(fLowPassFilterCoef[i]);
	}
	//create a complex exponential signal at 1.6KHz to shift the low pass filter out of the negative frequency zone	
	createComplexSignal(1600,FILTER_LENGTH,compLowPassFilterModSignal);

	//frequency shift the low pass filter by multiplying it by the complex exponential modulating signal 
	combinationVectorMultiply(FILTER_LENGTH,frctShiftedLowPassFilterCoef,compShiftedLowPassFilterCoef,frctLowPassFilterCoef,compLowPassFilterModSignal);

	//initialise the shifted low pass filter structure with coefficients and delay buffer
	FIRStructInit(&structShiftedLowPassFilter,FILTER_LENGTH,frctShiftedLowPassFilterCoef,0xFF00,frctShiftedLowPassDelayBuffer);
	FIRDelayInit(&structShiftedLowPassFilter);
}
/************************************************************************************************** 
* @fn bandPassFilter 
* @param int iFrameSize,fractional *frctAudioWorkSpace,fractional *frctAudioIn
* @return None
* @brief implements the filter function in the DSP library with the supplied parameters and previously 
* initialised filter structure 
**************************************************************************************************/

void bandPassFilter(int iFrameSize,fractional *frctAudioWorkSpace,fractional *frctAudioIn)
{
	FIR(iFrameSize,frctAudioWorkSpace,frctAudioIn,&structBandPassFilter);	
}

/************************************************************************************************** 
* @fn shiftedLowPassFilter 
* @param int iFrameSize,fractional *frctAudioWorkSpace,fractional *frctAudioIn
* @return None
* @brief implements the filter function in the DSP library with the supplied parameters and previously 
* initialised filter structure 
**************************************************************************************************/

void shiftedLowPassFilter(int iFrameSize,fractional *frctAudioWorkSpace,fractional *frctAudioIn)
{
	FIR(iFrameSize,frctAudioWorkSpace,frctAudioIn,&structShiftedLowPassFilter);	
}
