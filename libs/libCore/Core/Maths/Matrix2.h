// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef Matrix2H
#define Matrix2H

#include "../../libCore.h"
#include "Vector3.h"
#include "Vector2.h"


namespace core {


/// A 2x2 matrix.
class TGCORE_API Matrix2
{

public:
	// I/O
	friend TGCORE_API std::ostream & operator<<(std::ostream &, const Matrix2 &);
	friend TGCORE_API std::istream & operator>>(std::istream &, Matrix2 &);

	// Constructors
	Matrix2();

	Matrix2(double a, double b,
	        double c, double d);

	Matrix2(const Vector2 & row0, const Vector2 & row1);

	Matrix2(const Matrix2 & m);

	// Accessor functions
	inline Vector2 & operator[] (unsigned int i);

	inline const Vector2 & operator[] (unsigned int i) const;

	// Assignment operators
	Matrix2 & operator= (const Matrix2 & m);

	Matrix2 & operator+= (const Matrix2 & m);

	Matrix2 & operator-= (const Matrix2 & m);

	Matrix2 & operator*= (const Matrix2 & m);

	Matrix2 & operator*= (double d);

	Matrix2 & operator/= (double d);

	// Arithmetic operators

protected:
	Vector2 row[2];
};


// --- Constants --------------------------------------------------------------

extern TGCORE_API const Matrix2 M2_NULL;
extern TGCORE_API const Matrix2 M2_IDENTITY;


// --- Matrix operations ------------------------------------------------------

inline Matrix2 transpose (const Matrix2 & m);

inline double determinant (const Matrix2 & m);

inline Matrix2 invert (const Matrix2 & m);


// --- Arithmetic operators ---------------------------------------------------

inline Matrix2 operator+ (const Matrix2 & m1, const Matrix2 & m2);

inline Matrix2 operator- (const Matrix2 & m1, const Matrix2 & m2);

inline Matrix2 operator- (const Matrix2 & m);

inline Matrix2 operator* (const Matrix2 & m1, const Matrix2 & m2);

inline Matrix2 operator* (const Matrix2 & m, double d);

inline Matrix2 operator* (double d, const Matrix2 & m);

inline Matrix2 operator/ (const Matrix2 & m, double d);

inline Vector2 & operator*= (Vector2 & V, const Matrix2 & m);

inline Vector2 operator* (const Matrix2 & m, const Vector2 & V);

inline Vector2 operator* (const Vector2 & V, const Matrix2 & m);

inline Matrix2 operator* (const double d, const Matrix2 & m);


// --- Inlines ----------------------------------------------------------------

inline Matrix2::Matrix2()
{
	row[0][0] = 0.0;
	row[0][1] = 0.0;
	row[1][0] = 0.0;
	row[1][1] = 0.0;
}


inline Matrix2::Matrix2(double a, double b,
                        double c, double d)
{
	row[0][0] = a;
	row[0][1] = b;
	row[1][0] = c;
	row[1][1] = d;
}


inline Matrix2::Matrix2(const Vector2 & row0, const Vector2 & row1)
{
	row[0] = row0;
	row[1] = row1;
}


inline Matrix2::Matrix2(const Matrix2 & m)
{
	row[0] = m[0];
	row[1] = m[1];
}


inline Vector2 & Matrix2::operator[] (unsigned int i)
{
	return row[i];
}


inline const Vector2 & Matrix2::operator[] (unsigned int i) const
{
	return row[i];
}


inline Matrix2 & Matrix2::operator= (const Matrix2 & m)
{
	if (this != &m) {
		row[0] = m[0];
		row[1] = m[1];
	}
	return *this;
}


inline Matrix2 & Matrix2::operator+= (const Matrix2 & m)
{
	row[0] += m[0];
	row[1] += m[1];
	return *this;
}


inline Matrix2 & Matrix2::operator-= (const Matrix2 & m)
{
	row[0] -= m[0];
	row[1] -= m[1];
	return *this;
}


inline Matrix2 & Matrix2::operator*= (const Matrix2 & m)
{
	*this = *this * m;
	return *this;
}


inline Matrix2 & Matrix2::operator*= (double d)
{
	row[0] *= d;
	row[1] *= d;
	return *this;
}


inline Matrix2 & Matrix2::operator/= (double d)
{
	if (std::abs(d) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix2");
	row[0] /= d;
	row[1] /= d;
	return *this;
}


// --- Inlines ----------------------------------------------------------------

inline Matrix2 transpose (const Matrix2 & m)
{
	return Matrix2
		   (
		m[0][0], m[1][0],
		m[0][1], m[1][1]
	       );
}


inline double determinant (const Matrix2 & m)
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}


inline Matrix2 invert (const Matrix2 & m)
{
	double det = determinant(m);
// det of a matrix can be very small. To check if a matrix is non invertible, check if its determinant
	// is very small.
	if (std::abs(det) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix2 invert, determinant zero");

	return Matrix2
		   (
		m[1][1],
		-m[0][1],
		-m[1][0],
		m[0][0]
	       ) / det;
}


inline Matrix2 operator+ (const Matrix2 & m1, const Matrix2 & m2)
{
	return Matrix2
		   (
		m1[0] + m2[0],
		m1[1] + m2[1]
	       );
}


inline Matrix2 operator- (const Matrix2 & m1, const Matrix2 & m2)
{
	return Matrix2
		   (
		m1[0] - m2[0],
		m1[1] - m2[1]
	       );
}


inline Matrix2 operator- (const Matrix2 & m)
{
	return Matrix2
		   (
		-m[0],
		-m[1]
	       );
}


inline Matrix2 operator* (const Matrix2 & m1, const Matrix2 & m2)
{
	return Matrix2(
		m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0],
		m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1],
		m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0],
		m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1]
	);
}


inline Matrix2 operator* (const Matrix2 & m, double d)
{
	return Matrix2
		   (
		m[0] * d,
		m[1] * d
	       );
}


inline Matrix2 operator/ (const Matrix2 & m, double d)
{
	if (std::abs(d) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix2");
	return Matrix2
		   (
		m[0] / d,
		m[1] / d
	       );
}


inline Vector2 operator* (const Matrix2 & m, const Vector2 & V)
{
	return Vector2
		   (
		V[0] * m[0][0] + V[1] * m[0][1],
		V[0] * m[1][0] + V[1] * m[1][1]
	       );
}


inline Vector2 operator* (const Vector2 & V, const Matrix2 & m)
{
	return Vector2
		   (
		V[0] * m[0][0] + V[1] * m[1][0],
		V[0] * m[0][1] + V[1] * m[1][1]
	       );
}


inline Vector2 & operator*= (Vector2 & V, const Matrix2 & m)
{
	double T0 = V[0] * m[0][0] + V[1] * m[1][0];
	V[1] = V[0] * m[0][1] + V[1] * m[1][1];
	V[0] = T0;

	return (V);
}


inline Matrix2 operator* (const double d, const Matrix2 & m)
{
	return m * d;
}


};  // namespace core
#endif // ifndef Matrix2H
