// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef IgtConstantsH
#define IgtConstantsH

#include "../libCore.h"

namespace core {

/// The pi constant.
extern TGCORE_API const double IGT_PI;

/// A constant defining 1 / pi.
extern TGCORE_API const double IGT_1_PI;

/** Represents the precision of the MR scanner in mm.
    It should be used only when slice position is not precise enough to use IGT_EPSILON.
    TODO: put it in conf ?... */
extern TGCORE_API const float IGT_MRI_EPSILON;

/// A constant representing a very small value (epsilon) used in comparisons.
extern TGCORE_API const float IGT_EPSILON;

/// An epsilon for "double" type.
extern TGCORE_API const double IGT_LITTLE_EPSILON;

/// A constant representing the max value of floats.
extern TGCORE_API const float IGT_INFINITY;

}  // namespace core
#endif // ifndef IgtConstantsH
