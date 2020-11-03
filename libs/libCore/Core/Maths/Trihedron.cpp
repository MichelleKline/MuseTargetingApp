// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Trihedron.h"

#include "Matrix3.h"

namespace core {

const Trihedron Trihedron::IDENTITY = Trihedron(Point3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));

Trihedron::Trihedron(const Point3 & o_, const Vector3 & x_, const Vector3 & y_, const Vector3 & z_) :
	x(x_)
	, y(y_)
	, z(z_)
	, o(o_)
{
	Matrix3 mat(x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2]);
	if (determinant(mat) == 0)
		throw IGTDivideByZeroErr("Trihedron : determinant zero");
}


Trihedron::Trihedron(const Matrix4 & m)
{
	if (! (std::abs(m[3][0]) < IGT_EPSILON
	       && std::abs(m[3][1]) < IGT_EPSILON
	       && std::abs(m[3][2]) < IGT_EPSILON
	       && std::abs(m[3][3] - 1) < IGT_EPSILON))
		throw IGTInvalidParameterErr("Trihedron", "Matrix is not an homogeneous matrix");

	if (std::abs(determinant(m)) < IGT_LITTLE_EPSILON) // determinant can be very small. Use little_epsilon here.
		throw IGTDivideByZeroErr("Trihedron : determinant zero");

	x = Vector3(m[0][0], m[1][0], m[2][0]);
	y = Vector3(m[0][1], m[1][1], m[2][1]);
	z = Vector3(m[0][2], m[1][2], m[2][2]);
	o = Point3(m[0][3], m[1][3], m[2][3]);
}


Trihedron::Trihedron(const Trihedron & other) :
	x(other.x)
	, y(other.y)
	, z(other.z)
	, o(other.o)
{ }


Trihedron & Trihedron::operator= (const Trihedron & other)
{
	o = other.o;
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}


Point3 Trihedron::xformTo (const Trihedron & newT, const Point3 & pInMe) const
{
	return Point3(xformTo(newT, Vector4(pInMe, 1.0)));
}


Vector4 Trihedron::xformTo (const Trihedron & newT, const Vector4 & pInMe) const
{
	Matrix4 meToAbs    = getMatrix();
	Point4 pInAbsolute = meToAbs * pInMe;

	Matrix4 newTToAbs  = newT.getMatrix();

	Matrix4 absToNewT  = invert(newTToAbs);

	return absToNewT * pInAbsolute;
}


Vector4 Trihedron::xformTo (const Vector4 & pInAbsolute) const
{
	Matrix4 meToAbs = getMatrix();

	Matrix4 absToMe = invert(meToAbs);

	return absToMe * pInAbsolute;
}


Trihedron Trihedron::xformTo (const Trihedron & tInAbsolute) const
{
	Matrix4 absToMe = invert(getMatrix());
	Matrix4 tInMe   = absToMe * tInAbsolute.getMatrix();

	return Trihedron(tInMe);
}


Point3 Trihedron::xformFrom (const Trihedron & t, const Point3 & pInT) const
{
	return Point3(xformFrom(t, Vector4(pInT, 1.0)));
}


Vector4 Trihedron::xformFrom (const Trihedron & t, const Vector4 & pInT) const
{
	Matrix4 tToAbs     = t.getMatrix();

	Point4 pInAbsolute = tToAbs * pInT;

	Matrix4 meToAbs    = getMatrix();
	Matrix4 absToMe    = invert(meToAbs);
	return absToMe * pInAbsolute;
}


Vector4 Trihedron::xformFrom (const Vector4 & pInMe) const
{
	Matrix4 meToAbs = getMatrix();
	Point4 pInAbs   = meToAbs * pInMe;
	return pInAbs;
}


Trihedron Trihedron::xformFrom (const Trihedron & tInMe) const
{
	Matrix4 meToAbs = getMatrix();
	Matrix4 tInAbs  = meToAbs * tInMe.getMatrix();

	return Trihedron(tInAbs);
}


void Trihedron::setX (const Vector3 & newX)
{
	x = newX;
	Matrix3 mat(x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2]);
	if (determinant(mat) == 0)
		throw IGTDivideByZeroErr("Trihedron : determinant zero");
}


void Trihedron::setY (const Vector3 & newY)
{
	y = newY;
	Matrix3 mat(x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2]);
	if (determinant(mat) == 0)
		throw IGTDivideByZeroErr("Trihedron : determinant zero");
}


void Trihedron::setZ (const Vector3 & newZ)
{
	z = newZ;
	Matrix3 mat(x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2]);
	if (determinant(mat) == 0)
		throw IGTDivideByZeroErr("Trihedron : determinant zero");
}


std::ostream & operator<< (std::ostream & os, const Trihedron & t)
{
	os << "Origin: " << t.o << " ,X " << t.x << " ,Y " << t.y << " ,Z " << t.z;
	return os;
}


std::istream & operator>> (std::istream & is, Trihedron & t)
{
	std::string dump;
	is >> dump >> t.o >> dump >> t.x >> dump >> t.y >> dump >> t.z;
	return is;
}


bool operator== (const Trihedron & t1, const Trihedron & t2)
{
	return (   (t1.x == t2.x)
	           && (t1.y == t2.y)
	           && (t1.z == t2.z)
	           && (t1.o == t2.o));
}


bool operator!= (const Trihedron & t1, const Trihedron & t2)
{
	return ! (t1 == t2);
}


Trihedron transitionTrihedron (const Point3 & o1, const Point3 & a1,
	const Point3 & b1, const Point3 & o2, const Point3 & a2,
	const Point3 & b2)
{
	// The transition trihedron is composed of a rotation matrix and a translation
	// vector.

	// TRANSLATION

	// We know that o1 and o2 are the origin of there basis (Basis1 and Basis2).
	// So, we can calculate the translation between the two bases.
	Vector3 translation = o2 - o1;


	// ROTATION

	// To calculate the rotation matrix, we need to resolve 3 equations
	// with 3 unknowns (each row of the rotation matrix).

	// First, we need to calculate the normals for the two bases.
	Vector3 OA1          = a1 - o1;
	Vector3 OB1          = b1 - o1;
	Vector3 normalBasis1 = (OA1 ^ OB1).normalise();
	Point3 c1 = a1 + normalBasis1;
	Vector3 OA2          = a2 - o2;
	Vector3 OB2          = b2 - o2;
	Vector3 normalBasis2 = (OA2 ^ OB2).normalise();
	Point3 c2 = a2 + normalBasis2;

	// We create the matrix with the points in Basis1
	Matrix3 m(a1[0], b1[0], c1[0],
	          a1[1], b1[1], c1[1],
	          a1[2], b1[2], c1[2]);

	// We create three vectors from 3 points in Basis2 aligned on Basis1
	// (to have the rotation from the origin o1)
	Point3 a2Aligned = a2 - translation;
	Point3 b2Aligned = b2 - translation;
	Point3 c2Aligned = c2 - translation;
	Vector3 x(a2Aligned[0], b2Aligned[0], c2Aligned[0]);
	Vector3 y(a2Aligned[1], b2Aligned[1], c2Aligned[1]);
	Vector3 z(a2Aligned[2], b2Aligned[2], c2Aligned[2]);

	// We calculate each row of the matrix by solving:
	// m.row1 = x  => row1 = x * m^-1
	// m.row2 = y
	// m.row3 = z
	Matrix3 mInv = invert(m);

	Vector3 row1 = x * mInv;
	Vector3 row2 = y * mInv;
	Vector3 row3 = z * mInv;

	Matrix3 rotation(row1, row2, row3);

	return Trihedron(Matrix4(Vector4(rotation[0], translation[0]),
		Vector4(rotation[1], translation[1]),
		Vector4(rotation[2], translation[2]),
		Vector4(0, 0, 0, 1)));
}


};  // namespace core
