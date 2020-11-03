// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef IgtToolsH
#define IgtToolsH

#include <cmath>
#include "../libCore.h"
#include "Constants.h"

namespace core {

/// Convert radians to degrees
inline double radToDeg (double rad) { return rad * 180.0 * IGT_1_PI; }

/// Convert radians to degrees
inline float radToDeg (float rad) { return rad * 180.0f * (float)IGT_1_PI; }

/// Convert degrees to radians
inline double degToRad (double deg) { return deg * IGT_PI / 180.0; }

/// Convert degrees to radians
inline float degToRad (float deg) { return deg * (float)IGT_PI / 180.0f; }

/// Convert from millisecond to second
inline float msToS (float timeInMs) { return 0.001f * timeInMs; }

/// Convert from second to millisecond
inline float sToMs (float timeInS) { return 1000.0f * timeInS; }

/// Convert from micro second to millisecond
inline float usToMs (float timeInUs) { return 0.001f * timeInUs; }

/// Convert from micro second to second
inline float usToS (float timeInUs) { return 1e-6f * timeInUs; }

/// Convert from millisecond to micro second
inline float msToUs (float timeInMs) { return 1000.0f * timeInMs; }

/// Convert from meter to millimeters
inline float mToMm (float lengthInM) { return 1000.0f * lengthInM; }

/// Convert from millimeters to meter
inline float mmToM (float lengthInMm) { return 0.001f * lengthInMm; }

/// Return a uniform random value in [min and max].
TGCORE_API float rand (float min, float max);

/// Return a gaussian random value of average avgN and variance varN. Not very accurate but quite fast.
TGCORE_API float randN (float avgN, float varN);

/// Round value to the nearest integer.
inline int round (double value) { return (int)floor(value + 0.5); }

/// Return -1 if value <0, 1 otherwise.
inline int sign (double value) { return (value < 0) ? -1 : 1; }

/// Return the nearest value's upper power of 2.
inline unsigned int nearestUpperPowerOf2 (double value)
{
	unsigned int po2 = 1;
	while (po2 < value)
		po2 <<= 1;
	return po2;
}


/// If the value is in the range, return, otherwise fix to correct extremity.
template<class T> T getValueInRange (T value, T lowerBound, T upperBound)
{
	return (value < lowerBound) ? lowerBound : ((value > upperBound) ? upperBound : value);
}


/// Linear interpolation of generic value
template <typename T> inline T interpLinear (T value1, T value2, double factor)
{
	return static_cast<T>((1.0 - factor) * value1 + factor * value2);
}


/// Linear interpolation, specialized for booleans
template<> inline bool interpLinear (bool value1, bool value2, double factor)
{
	return (factor < 0.5) ? value1 : value2;
}


/// Bilinear interpolation of generic values
template <typename T> T interpBiLinear (T X1Y1, T X1Y2, T X2Y1, T X2Y2, double xFactor, double yFactor)
{
	T yInterp1 = interpLinear<T>(X1Y1, X1Y2, yFactor);
	T yInterp2 = interpLinear<T>(X2Y1, X2Y2, yFactor);
	return interpLinear(yInterp1, yInterp2, xFactor);
}


/// Trilinear interpolation of generic values
template <typename T>
T interpTriLinear (T X1Y1Z1, T X1Y1Z2, T X1Y2Z1, T X1Y2Z2,
	T X2Y1Z1, T X2Y1Z2, T X2Y2Z1, T X2Y2Z2,
	double xFactor, double yFactor, double zFactor)
{
	T zInterp1 = interpBiLinear<T>(X1Y1Z1, X1Y2Z1, X2Y1Z1, X2Y2Z1, xFactor, yFactor);
	T zInterp2 = interpBiLinear<T>(X1Y1Z2, X1Y2Z2, X2Y1Z2, X2Y2Z2, xFactor, yFactor);
	return interpLinear<T>(zInterp1, zInterp2, zFactor);
}


};  // namespace core
#endif // ifndef IgtToolsH
