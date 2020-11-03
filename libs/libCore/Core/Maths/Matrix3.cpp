// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Matrix3.h"
#include <limits>


namespace core {


extern TGCORE_API const Matrix3 M3_NULL     = Matrix3(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
extern TGCORE_API const Matrix3 M3_IDENTITY = Matrix3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);


// I/O
std::ostream & operator<< (std::ostream & os, const Matrix3 & m)
{
	os << m.row[0] << " " << m.row[1] << " " << m.row[2];
	return os;
}


std::istream & operator>> (std::istream & is, Matrix3 & m)
{
	is >> m.row[0] >> m.row[1] >> m.row[2];
	return is;
}


};  // namespace core
