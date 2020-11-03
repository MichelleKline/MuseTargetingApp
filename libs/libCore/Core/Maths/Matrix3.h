// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef Matrix3H
#define Matrix3H

#include "../../libCore.h"
#include "Vector3.h"

namespace core {


/// A 3x3 matrix.
class TGCORE_API Matrix3
{
public:
	// I/O
	friend TGCORE_API std::ostream & operator<<(std::ostream &, const Matrix3 &);
	friend TGCORE_API std::istream & operator>>(std::istream &, Matrix3 &);

	// Constructors

	Matrix3();

	Matrix3(double a, double b, double c,
	        double d, double e, double f,
	        double g, double h, double i);

	Matrix3(const Vector3 & row0, const Vector3 & row1, const Vector3 & row2);

	Matrix3(const Matrix3 & m);

	// Accessor functions
	inline Vector3 & operator[] (unsigned int i);

	inline const Vector3 & operator[] (unsigned int i) const;

	// Assignment operators
	Matrix3 & operator= (const Matrix3 & m);

	Matrix3 & operator+= (const Matrix3 & m);

	Matrix3 & operator-= (const Matrix3 & m);

	Matrix3 & operator*= (const Matrix3 & m);

	Matrix3 & operator*= (double d);

	Matrix3 & operator/= (double d);

protected:
	Vector3 row[3];
};


// --- Constants --------------------------------------------------------------

extern TGCORE_API const Matrix3 M3_NULL;
extern TGCORE_API const Matrix3 M3_IDENTITY;

// --- Matrix operations ------------------------------------------------------

inline Matrix3 transpose (const Matrix3 & m);

inline double determinant (const Matrix3 & m);

inline Matrix3 invert (const Matrix3 & m);


// --- Arithmetic operators ---------------------------------------------------

inline Matrix3 operator+ (const Matrix3 & m1, const Matrix3 & m2);

inline Matrix3 operator- (const Matrix3 & m1, const Matrix3 & m2);

inline Matrix3 operator- (const Matrix3 & m);

inline Matrix3 operator* (const Matrix3 & m1, const Matrix3 & m2);

inline Matrix3 operator* (const Matrix3 & m, double d);

inline Matrix3 operator* (double d, const Matrix3 & m);

inline Matrix3 operator/ (const Matrix3 & m, double d);

inline Vector3 & operator*= (Vector3 & v, const Matrix3 & m);

inline Vector3 operator* (const Matrix3 & m, const Vector3 & v);

inline Vector3 operator* (const Vector3 & v, const Matrix3 & m);

inline bool operator== (const Matrix3 &, const Matrix3 &);

// --- Inlines ----------------------------------------------------------------


inline Matrix3::Matrix3()
{
	row[0][0] = 0.0;
	row[0][1] = 0.0;
	row[0][2] = 0.0;
	row[1][0] = 0.0;
	row[1][1] = 0.0;
	row[1][2] = 0.0;
	row[2][0] = 0.0;
	row[2][1] = 0.0;
	row[2][2] = 0.0;
}


inline Matrix3::Matrix3(double a, double b, double c,
                        double d, double e, double f,
                        double g, double h, double i)
{
	row[0][0] = a;
	row[0][1] = b;
	row[0][2] = c;
	row[1][0] = d;
	row[1][1] = e;
	row[1][2] = f;
	row[2][0] = g;
	row[2][1] = h;
	row[2][2] = i;
}


inline Matrix3::Matrix3(const Vector3 & row0, const Vector3 & row1, const Vector3 & row2)
{
	row[0] = row0;
	row[1] = row1;
	row[2] = row2;
}


inline Matrix3::Matrix3(const Matrix3 & m)
{
	row[0] = m[0];
	row[1] = m[1];
	row[2] = m[2];
}


inline Matrix3 & Matrix3::operator= (const Matrix3 & m)
{
	if (this != &m) {
		row[0] = m[0];
		row[1] = m[1];
		row[2] = m[2];
	}
	return *this;
}


inline Matrix3 & Matrix3::operator+= (const Matrix3 & m)
{
	row[0] += m[0];
	row[1] += m[1];
	row[2] += m[2];

	return *this;
}


inline Matrix3 & Matrix3::operator-= (const Matrix3 & m)
{
	row[0] -= m[0];
	row[1] -= m[1];
	row[2] -= m[2];

	return *this;
}


inline Matrix3 & Matrix3::operator*= (const Matrix3 & m)
{
	*this = *this * m;
	return *this;
}


inline Matrix3 & Matrix3::operator*= (double d)
{
	row[0] *= d;
	row[1] *= d;
	row[2] *= d;

	return *this;
}


inline Matrix3 & Matrix3::operator/= (double d)
{
	if (std::abs(d) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix3");
	row[0] /= d;
	row[1] /= d;
	row[2] /= d;

	return *this;
}


inline Vector3 & Matrix3::operator[] (unsigned int i)
{
	return row[i];
}


inline const Vector3 & Matrix3::operator[] (unsigned int i) const
{
	return row[i];
}


inline Vector3 operator* (const Matrix3 & m, const Vector3 & v)
{
	return Vector3
		   (
		v * m[0],
		v * m[1],
		v * m[2]
	       );
}


inline Vector3 operator* (const Vector3 & v, const Matrix3 & m)
{
	return Vector3
		   (
		v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0],
		v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1],
		v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2]
	       );
}


inline Vector3 & operator*= (Vector3 & v, const Matrix3 & m)
{
	double T0, T1;
	T0   = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0];
	T1   = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1];
	v[2] = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2];
	v[0] = T0;
	v[1] = T1;

	return (v);
}


inline Matrix3 operator+ (const Matrix3 & m1, const Matrix3 & m2)
{
	return Matrix3
		   (
		m1[0] + m2[0],
		m1[1] + m2[1],
		m1[2] + m2[2]
	       );
}


inline Matrix3 operator- (const Matrix3 & m1, const Matrix3 & m2)
{
	return Matrix3
		   (
		m1[0] - m2[0],
		m1[1] - m2[1],
		m1[2] - m2[2]
	       );
}


inline Matrix3 operator- (const Matrix3 & m)
{
	return Matrix3
		   (
		-m[0],
		-m[1],
		-m[2]
	       );
}


inline Matrix3 operator* (const Matrix3 & m1, const Matrix3 & m2)
{
	return Matrix3
		   (
		m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0],
		m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1],
		m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2],

		m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0],
		m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1],
		m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2],

		m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0],
		m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1],
		m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2]
	       );
}


inline Matrix3 operator* (const Matrix3 & m, double d)
{
	return Matrix3
		   (
		m[0] * d,
		m[1] * d,
		m[2] * d
	       );
}


inline Matrix3 operator* (double d, const Matrix3 & m)
{
	return m * d;
}


inline Matrix3 operator/ (const Matrix3 & m, double d)
{
	if (std::abs(d) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix3");
	return Matrix3
		   (
		m[0] / d,
		m[1] / d,
		m[2] / d
	       );
}


inline Matrix3 transpose (const Matrix3 & m)
{
	return Matrix3
		   (
		m[0][0], m[1][0], m[2][0],
		m[0][1], m[1][1], m[2][1],
		m[0][2], m[1][2], m[2][2]
	       );
}


inline double determinant (const Matrix3 & m)
{

	return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) +
	       m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) +
	       m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}


inline Matrix3 invert (const Matrix3 & m)
{
	double det = determinant(m);
	// det of a matrix can be very small. To check if a matrix is non invertible, check if its determinant
	// is very small.
	if (std::abs(det) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix3 invert, determinant zero");

	return Matrix3
		   (
		m[1][1] * m[2][2] - m[1][2] * m[2][1],
		m[2][1] * m[0][2] - m[2][2] * m[0][1],
		m[0][1] * m[1][2] - m[0][2] * m[1][1],
		m[1][2] * m[2][0] - m[1][0] * m[2][2],
		m[2][2] * m[0][0] - m[2][0] * m[0][2],
		m[0][2] * m[1][0] - m[0][0] * m[1][2],
		m[1][0] * m[2][1] - m[1][1] * m[2][0],
		m[2][0] * m[0][1] - m[2][1] * m[0][0],
		m[0][0] * m[1][1] - m[0][1] * m[1][0]
	       ) / det;
}


inline bool operator== (const Matrix3 & m1, const Matrix3 & m2)
{
	return (
		m1[0] == m2[0] &&
		m1[1] == m2[1] &&
		m1[2] == m2[2]
	);
}


};  // namespace core
#endif // ifndef Matrix3H
