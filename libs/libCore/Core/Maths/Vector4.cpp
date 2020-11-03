// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Vector4.h"

namespace core {

// Constants
extern TGCORE_API const Vector4 V4_NULL = Vector4(0.0, 0.0, 0.0, 0.0);
extern TGCORE_API const Vector4 P4_NULL = V4_NULL;

Vector4::Vector4(const Vector3 & v, double t)
{
	elements[0] = v[0];
	elements[1] = v[1];
	elements[2] = v[2];
	elements[3] = t;
}


std::ostream & operator<< (std::ostream & os, const Vector4 & vec)
{
	os << vec.elements[0] << " " << vec.elements[1] << " " << vec.elements[2] << " " << vec.elements[3];
	return os;
}


std::istream & operator>> (std::istream & is, Vector4 & vec)
{
	is >> vec.elements[0] >> vec.elements[1] >> vec.elements[2] >> vec.elements[3];
	return is;
}


};  // namespace core
