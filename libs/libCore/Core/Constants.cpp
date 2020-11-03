// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Constants.h"
#include <cmath>
#include <limits>


namespace core {

const double IGT_PI             = std::atan(1.0) * 4.0;

const double IGT_1_PI           = 1.0 / IGT_PI;

const float IGT_MRI_EPSILON     = 0.001f;

const float IGT_EPSILON         = std::numeric_limits<float>::epsilon() * 1.0e3f;

const double IGT_LITTLE_EPSILON = std::numeric_limits<double>::epsilon() * 1.0e3f;

const float IGT_INFINITY        = std::numeric_limits<float>::infinity();


}  // namespace core
