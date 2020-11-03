// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Matrix2.h"


namespace core {


extern TGCORE_API const Matrix2 M2_NULL     = Matrix2(0.0, 0.0, 0.0, 0.0);
extern TGCORE_API const Matrix2 M2_IDENTITY = Matrix2(1.0, 0.0, 0.0, 1.0);


// I/O
std::ostream & operator<< (std::ostream & os, const Matrix2 & m)
{
	os << m.row[0] << " " << m.row[1];
	return os;
}


std::istream & operator>> (std::istream & is, Matrix2 & m)
{
	is >> m.row[0] >> m.row[1];
	return is;
}


};  // namespace core
