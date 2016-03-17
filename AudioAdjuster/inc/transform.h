#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include <dsp\h\dsp.h>

void fourierTransform(int iFrameSize,fractcomplex *compX,fractional *frctAudioIn);
void inverseFourierTransform(int iFrameSize,fractional *frctAudioWorkSpace,fractcomplex *compX);
void filterNegativeFreq(int iFrameSize,fractcomplex *compXfiltered,fractcomplex *compX);
void shiftFreqSpectrum(int iFrameSize,int iShiftAmount,fractcomplex *compXshifted,fractcomplex *compX);

#endif
