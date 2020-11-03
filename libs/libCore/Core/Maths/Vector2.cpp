// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Vector2.h"

namespace core {


extern TGCORE_API const Vector2 V2_NULL = Vector2(0.0, 0.0);
extern TGCORE_API const Vector2 P2_NULL = V2_NULL;


std::ostream & operator<< (std::ostream & os, const Vector2 & vec)
{
	os << vec.elements[0] << " " << vec.elements[1];
	return os;
}


std::istream & operator>> (std::istream & is, Vector2 & vec)
{
	is >> vec.elements[0] >> vec.elements[1];
	return is;
}


};  // namespace core
