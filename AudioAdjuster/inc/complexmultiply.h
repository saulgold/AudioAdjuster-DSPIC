#ifndef __COMPLEX_MULTIPLY_H__
#define __COMPLEX_MULTIPLY_H__

#include <dsp\h\dsp.h>

void complexVectorMultiply(int iVectorSize,fractcomplex *compResult,fractcomplex *compValue1,fractcomplex *compValue2);
void combinationVectorMultiply(int iVectorSize,fractional *frctResult1,fractcomplex *compResult2,fractional *frctValue1,fractcomplex *compValue2);

#endif
