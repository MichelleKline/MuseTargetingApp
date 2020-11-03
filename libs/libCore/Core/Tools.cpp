// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include <cstdlib>
#include "Tools.h"

namespace core {

float rand (float min, float max)
{
	// uniform random value in [0, 1]
	float rnd = std::rand() / (float)RAND_MAX;
	// uniform random value in [a, b]
	rnd = rnd * (max - min) + min;

	return rnd;
}


float randN (float avgN, float varN)
{
	// use the central limit theorme :
	// sum 12 uniform variable (m, s) and obtain
	// a normal variable (12*m, 12*sigma²)

	const float sig = sqrt(12.0f) / 2.0f;

	// average and ecartyp of uniform variable
	float avgU = avgN / 12.0f;
	float ectU = sqrt(varN / 12.0f);

	// for a uniform variable in [a, b], average = (a+b)/2 and ecartype = (b-a)/sqrt(12)
	float a   = avgU - sig * ectU;
	float b   = sig * ectU + avgU;

	float res = 0;
	for (int i = 0; i < 12; i++) {
		// uniform random value in [0, 1]
		float rnd = std::rand() / (float)RAND_MAX;
		// uniform random value in [a, b]
		rnd  = rnd * (b - a) + a;
		res += rnd;
	}
	return res;
}


};  // namespace core
