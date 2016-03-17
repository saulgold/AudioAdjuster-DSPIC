#ifndef __FILTER_H__
#define __FILTER_H__

#include <dsp\h\dsp.h>

void initFilter();
void bandPassFilter(int iFrameSize,fractional *frctAudioWorkSpace,fractional *frctAudioIn);
void shiftedLowPassFilter(int iFrameSize,fractional *frctAudioWorkSpace,fractional *frctAudioIn);

#endif
