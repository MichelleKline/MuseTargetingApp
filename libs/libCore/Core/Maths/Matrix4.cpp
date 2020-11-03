// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Matrix4.h"
#include "Matrix3.h"

namespace core {

extern TGCORE_API const Matrix4 M4_NULL     = Matrix4(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
extern TGCORE_API const Matrix4 M4_IDENTITY = Matrix4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);


void Matrix4::toColMajor (double c[16]) const
{
	c[0]  = row[0][0];
	c[1]  = row[1][0];
	c[2]  = row[2][0];
	c[3]  = row[3][0];

	c[4]  = row[0][1];
	c[5]  = row[1][1];
	c[6]  = row[2][1];
	c[7]  = row[3][1];

	c[8]  = row[0][2];
	c[9]  = row[1][2];
	c[10] = row[2][2];
	c[11] = row[3][2];

	c[12] = row[0][3];
	c[13] = row[1][3];
	c[14] = row[2][3];
	c[15] = row[3][3];
}


// Static method
Matrix4 Matrix4::rotation (double angle, const Vector3 & axe)
{
	double x           = axe.x();
	double y           = axe.y();
	double z           = axe.z();

	double cosTheta    = cos(angle);
	double sinTheta    = sin(angle);
	double oneMinusCos = 1 - cosTheta;

	return Matrix4(cosTheta + x * x * oneMinusCos, x * y * oneMinusCos - z * sinTheta, x * z * oneMinusCos + y * sinTheta, 0,
		y * x * oneMinusCos + z * sinTheta, cosTheta + y * y * oneMinusCos, y * z * oneMinusCos - x * sinTheta, 0,
		z * x * oneMinusCos - y * sinTheta, z * y * oneMinusCos + x * sinTheta, cosTheta + z * z * oneMinusCos, 0,
		0, 0, 0, 1);
}


// Static method
Matrix4 Matrix4::translation (const Vector3 & vec)
{
	return Matrix4(1, 0, 0, vec.x(),
		0, 1, 0, vec.y(),
		0, 0, 1, vec.z(),
		0, 0, 0, 1);
}


// I/O
std::ostream & operator<< (std::ostream & os, const Matrix4 & m)
{
	os << m.row[0] << " " << m.row[1] << " " << m.row[2] << " " << m.row[3];
	return os;
}


std::istream & operator>> (std::istream & is, Matrix4 & m)
{
	is >> m.row[0] >> m.row[1] >> m.row[2] >> m.row[3];
	return is;
}


};  // namespace core
