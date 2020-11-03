// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef Matrix4H
#define Matrix4H

#include "../../libCore.h"
#include "Vector4.h"
#include "Vector2.h"
#include "../CoreExceptions.h"
#include "../Constants.h"

namespace core {


/// A 4x4 matrix.
class TGCORE_API Matrix4
{

public:
	// I/O
	/// Returns an std::ostream displaying matrix components.
	friend TGCORE_API std::ostream & operator<<(std::ostream &, const Matrix4 &);
	/// Fills matrix components from the std::istream.
	friend TGCORE_API std::istream & operator>>(std::istream &, Matrix4 &);

	// Constructors
	/// Default constructor.
	Matrix4();

	/// Constructor.
	Matrix4(double a, double b, double c, double d,
	        double e, double f, double g, double h,
	        double i, double j, double k, double l,
	        double m, double n, double o, double p);

	/// Constructor.
	Matrix4(const Vector4 & row0, const Vector4 & row1, const Vector4 & row2, const Vector4 & row3);

	/// Copy constructor.
	Matrix4(const Matrix4 & m);

	/// Create a matrix with colum-major format :
	/// c[0] c[4] c[8]  c[12]
	/// c[1] c[5] c[9]  c[13]
	/// c[2] c[6] c[10] c[14]
	/// c[3] c[7] c[11] c[15]
	explicit Matrix4(const double c[16]);

	/// Create a matrix with colum-major format :
	/// c[0] c[4] c[8]  c[12]
	/// c[1] c[5] c[9]  c[13]
	/// c[2] c[6] c[10] c[14]
	/// c[3] c[7] c[11] c[15]
	explicit Matrix4(const float c[16]);

	// Accessor functions
	/// Returns the given row with read and write access.
	inline Vector4 & operator[] (unsigned int i);

	/// Returns the given row with read access.
	inline const Vector4 & operator[] (unsigned int i) const;

	// Operators
	/// Assignment operator.
	Matrix4 & operator= (const Matrix4 & m);

	/// Addition operator.
	Matrix4 & operator+= (const Matrix4 & m);

	/// Substraction operator.
	Matrix4 & operator-= (const Matrix4 & m);

	/// Product operator.
	Matrix4 & operator*= (const Matrix4 & m);

	/// Computes the product of the matrix with a scalar.
	Matrix4 & operator*= (double d);

	/// Computes the division of the matrix with a scalar.
	Matrix4 & operator/= (double d);

	// other functions
	/// Fill the buffer in colum-major format :
	/// c[0] c[4] c[8]  c[12]
	/// c[1] c[5] c[9]  c[13]
	/// c[2] c[6] c[10] c[14]
	/// c[3] c[7] c[11] c[15]
	void toColMajor (double c[16]) const;

	/// Create a rotation matrix with angle in radian along an axe.
	static Matrix4 rotation (double angle, const Vector3 & axe);

	/// Create a translation matrix
	static Matrix4 translation (const Vector3 & vec);

protected:
	/// Matrix components.
	Vector4 row[4];
};


// --- Constants --------------------------------------------------------------
/// A null matrix: all components equal 0.
extern TGCORE_API const Matrix4 M4_NULL;
/// An identity matrix.
extern TGCORE_API const Matrix4 M4_IDENTITY;

// --- Matrix operations ------------------------------------------------------

/// Transposes the given matrix.
inline Matrix4 transpose (const Matrix4 & m);

/// Computes the determinant of the given matrix.
inline double determinant (const Matrix4 & m);

/// Inverts the given matrix.
inline Matrix4 invert (const Matrix4 & m);


// --- Arithmetic operators ---------------------------------------------------
/// Addition operator.
inline Matrix4 operator+ (const Matrix4 & m1, const Matrix4 & m2);

/// Substraction operator.
inline Matrix4 operator- (const Matrix4 & m1, const Matrix4 & m2);

/// Substraction operator.
inline Matrix4 operator- (const Matrix4 & m);

/// Computes the product of two matrices.
inline Matrix4 operator* (const Matrix4 & m1, const Matrix4 & m2);

/// Computes the product of a matrix and a scalar.
inline Matrix4 operator* (const Matrix4 & m, double d);

/// Computes the product of a scalar and a matrix.
inline Matrix4 operator* (double d, const Matrix4 & m);

/// Computes the division of a matrix by a scalar.
inline Matrix4 operator/ (const Matrix4 & m, double d);

/// Computes the product of a vector and a matrix.
inline Vector4 & operator*= (Vector4 & v, const Matrix4 & m);

/// Computes the product of a matrix and a vector.
inline Vector4 operator* (const Matrix4 & m, const Vector4 & v);

/// Computes the product of a vector and a matrix.
inline Vector4 operator* (const Vector4 & v, const Matrix4 & m);

/// Computes the product of a scalar and a matrix.
inline Matrix4 operator* (const double d, const Matrix4 & m);

/// Returns wheter two matrices are equals.
inline bool operator== (const Matrix4 &, const Matrix4 &);


// --- Inlines ----------------------------------------------------------------

inline Matrix4::Matrix4()
{
	row[0][0] = 0.0;
	row[0][1] = 0.0;
	row[0][2] = 0.0;
	row[0][3] = 0.0;
	row[1][0] = 0.0;
	row[1][1] = 0.0;
	row[1][2] = 0.0;
	row[1][3] = 0.0;
	row[2][0] = 0.0;
	row[2][1] = 0.0;
	row[2][2] = 0.0;
	row[2][3] = 0.0;
	row[3][0] = 0.0;
	row[3][1] = 0.0;
	row[3][2] = 0.0;
	row[3][3] = 0.0;
}


inline Matrix4::Matrix4(double a, double b, double c, double d,
                        double e, double f, double g, double h,
                        double i, double j, double k, double l,
                        double m, double n, double o, double p)
{
	row[0][0] = a;
	row[0][1] = b;
	row[0][2] = c;
	row[0][3] = d;
	row[1][0] = e;
	row[1][1] = f;
	row[1][2] = g;
	row[1][3] = h;
	row[2][0] = i;
	row[2][1] = j;
	row[2][2] = k;
	row[2][3] = l;
	row[3][0] = m;
	row[3][1] = n;
	row[3][2] = o;
	row[3][3] = p;
}


inline Matrix4::Matrix4(const Vector4 & row0, const Vector4 & row1, const Vector4 & row2, const Vector4 & row3)
{
	row[0] = row0;
	row[1] = row1;
	row[2] = row2;
	row[3] = row3;
}


inline Matrix4::Matrix4(const Matrix4 & m)
{
	row[0] = m[0];
	row[1] = m[1];
	row[2] = m[2];
	row[3] = m[3];
}


inline Matrix4::Matrix4(const double c[16])
{
	row[0][0] = c[0];
	row[0][1] = c[4];
	row[0][2] = c[8];
	row[0][3] = c[12];
	row[1][0] = c[1];
	row[1][1] = c[5];
	row[1][2] = c[9];
	row[1][3] = c[13];
	row[2][0] = c[2];
	row[2][1] = c[6];
	row[2][2] = c[10];
	row[2][3] = c[14];
	row[3][0] = c[3];
	row[3][1] = c[7];
	row[3][2] = c[11];
	row[3][3] = c[15];
}


inline Matrix4::Matrix4(const float c[16])
{
	row[0][0] = c[0];
	row[0][1] = c[4];
	row[0][2] = c[8];
	row[0][3] = c[12];
	row[1][0] = c[1];
	row[1][1] = c[5];
	row[1][2] = c[9];
	row[1][3] = c[13];
	row[2][0] = c[2];
	row[2][1] = c[6];
	row[2][2] = c[10];
	row[2][3] = c[14];
	row[3][0] = c[3];
	row[3][1] = c[7];
	row[3][2] = c[11];
	row[3][3] = c[15];
}


inline Matrix4 & Matrix4::operator= (const Matrix4 & m)
{
	if (this != &m) {
		row[0] = m[0];
		row[1] = m[1];
		row[2] = m[2];
		row[3] = m[3];
	}
	return *this;
}


inline Matrix4 & Matrix4::operator+= (const Matrix4 & m)
{
	row[0] += m[0];
	row[1] += m[1];
	row[2] += m[2];
	row[3] += m[3];

	return *this;
}


inline Matrix4 & Matrix4::operator-= (const Matrix4 & m)
{
	row[0] -= m[0];
	row[1] -= m[1];
	row[2] -= m[2];
	row[3] -= m[3];

	return *this;
}


inline Matrix4 & Matrix4::operator*= (const Matrix4 & m)
{
	*this = *this * m;
	return *this;
}


inline Matrix4 & Matrix4::operator*= (double d)
{
	row[0] *= d;
	row[1] *= d;
	row[2] *= d;
	row[3] *= d;

	return *this;
}


inline Matrix4 & Matrix4::operator/= (double d)
{
	if (std::abs(d) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix4");
	double inv = 1.0 / d;
	row[0] *= inv;
	row[1] *= inv;
	row[2] *= inv;
	row[3] *= inv;

	return *this;
}


inline Vector4 & Matrix4::operator[] (unsigned int i)
{
	return row[i];
}


inline const Vector4 & Matrix4::operator[] (unsigned int i) const
{
	return row[i];
}


inline double determinant (const Matrix4 & m)
{
	return (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * (m[2][2] * m[3][3] - m[3][2] * m[2][3])
	       - (m[0][0] * m[1][2] - m[1][0] * m[0][2]) * (m[2][1] * m[3][3] - m[3][1] * m[2][3])
	       + (m[0][0] * m[1][3] - m[1][0] * m[0][3]) * (m[2][1] * m[3][2] - m[3][1] * m[2][2])
	       + (m[0][1] * m[1][2] - m[1][1] * m[0][2]) * (m[2][0] * m[3][3] - m[3][0] * m[2][3])
	       - (m[0][1] * m[1][3] - m[1][1] * m[0][3]) * (m[2][0] * m[3][2] - m[3][0] * m[2][2])
	       + (m[0][2] * m[1][3] - m[1][2] * m[0][3]) * (m[2][0] * m[3][1] - m[3][0] * m[2][1]);

}


inline Matrix4 invert (const Matrix4 & m)
{
	/*
	   double det = determinant(m);
	   // det of a matrix can be very small. To check if a matrix is non invertible, check if its determinant
	   // is very small.
	   if (std::abs(det) < IGT_LITTLE_EPSILON) throw IGTDivideByZeroErr("Matrix4 invert, determinant zero");

	   return Matrix4
	   (
	    m[1][2] * m[2][3] * m[3][1] - m[1][3] * m[2][2] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] + m[1][1] * m[2][2] * m[3][3],
	    m[0][3] * m[2][2] * m[3][1] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2] + m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] - m[0][1] * m[2][2] * m[3][3],
	    m[0][2] * m[1][3] * m[3][1] - m[0][3] * m[1][2] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] - m[0][2] * m[1][1] * m[3][3] + m[0][1] * m[1][2] * m[3][3],
	    m[0][3] * m[1][2] * m[2][1] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2] + m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] - m[0][1] * m[1][2] * m[2][3],
	    m[1][3] * m[2][2] * m[3][0] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2] + m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] - m[1][0] * m[2][2] * m[3][3],
	    m[0][2] * m[2][3] * m[3][0] - m[0][3] * m[2][2] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] + m[0][0] * m[2][2] * m[3][3],
	    m[0][3] * m[1][2] * m[3][0] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2] + m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] - m[0][0] * m[1][2] * m[3][3],
	    m[0][2] * m[1][3] * m[2][0] - m[0][3] * m[1][2] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] + m[0][0] * m[1][2] * m[2][3],
	    m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][1] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] + m[1][0] * m[2][1] * m[3][3],
	    m[0][3] * m[2][1] * m[3][0] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1] + m[0][0] * m[2][3] * m[3][1] + m[0][1] * m[2][0] * m[3][3] - m[0][0] * m[2][1] * m[3][3],
	    m[0][1] * m[1][3] * m[3][0] - m[0][3] * m[1][1] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] + m[0][0] * m[1][1] * m[3][3],
	    m[0][3] * m[1][1] * m[2][0] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1] + m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] - m[0][0] * m[1][1] * m[2][3],
	    m[1][2] * m[2][1] * m[3][0] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1] + m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] - m[1][0] * m[2][1] * m[3][2],
	    m[0][1] * m[2][2] * m[3][0] - m[0][2] * m[2][1] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] + m[0][0] * m[2][1] * m[3][2],
	    m[0][2] * m[1][1] * m[3][0] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1] + m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] - m[0][0] * m[1][1] * m[3][2],
	    m[0][1] * m[1][2] * m[2][0] - m[0][2] * m[1][1] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] + m[0][0] * m[1][1] * m[2][2]
	   ) / det;
	 */

	// faster method
	double a0  = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	double a1  = m[0][0] * m[1][2] - m[0][2] * m[1][0];
	double a2  = m[0][0] * m[1][3] - m[0][3] * m[1][0];
	double a3  = m[0][1] * m[1][2] - m[0][2] * m[1][1];
	double a4  = m[0][1] * m[1][3] - m[0][3] * m[1][1];
	double a5  = m[0][2] * m[1][3] - m[0][3] * m[1][2];
	double b0  = m[2][0] * m[3][1] - m[2][1] * m[3][0];
	double b1  = m[2][0] * m[3][2] - m[2][2] * m[3][0];
	double b2  = m[2][0] * m[3][3] - m[2][3] * m[3][0];
	double b3  = m[2][1] * m[3][2] - m[2][2] * m[3][1];
	double b4  = m[2][1] * m[3][3] - m[2][3] * m[3][1];
	double b5  = m[2][2] * m[3][3] - m[2][3] * m[3][2];

	double det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

	if (std::abs(det) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix4 invert, determinant zero");

	return Matrix4
		   (
		m[1][1] * b5 - m[1][2] * b4 + m[1][3] * b3,
		-m[0][1] * b5 + m[0][2] * b4 - m[0][3] * b3,
		m[3][1] * a5 - m[3][2] * a4 + m[3][3] * a3,
		-m[2][1] * a5 + m[2][2] * a4 - m[2][3] * a3,
		-m[1][0] * b5 + m[1][2] * b2 - m[1][3] * b1,
		m[0][0] * b5 - m[0][2] * b2 + m[0][3] * b1,
		-m[3][0] * a5 + m[3][2] * a2 - m[3][3] * a1,
		m[2][0] * a5 - m[2][2] * a2 + m[2][3] * a1,
		m[1][0] * b4 - m[1][1] * b2 + m[1][3] * b0,
		-m[0][0] * b4 + m[0][1] * b2 - m[0][3] * b0,
		m[3][0] * a4 - m[3][1] * a2 + m[3][3] * a0,
		-m[2][0] * a4 + m[2][1] * a2 - m[2][3] * a0,
		-m[1][0] * b3 + m[1][1] * b1 - m[1][2] * b0,
		m[0][0] * b3 - m[0][1] * b1 + m[0][2] * b0,
		-m[3][0] * a3 + m[3][1] * a1 - m[3][2] * a0,
		m[2][0] * a3 - m[2][1] * a1 + m[2][2] * a0
	       ) / det;
}


inline Matrix4 transpose (const Matrix4 & m)
{
	return Matrix4
		   (
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]
	       );
}


inline Matrix4 operator+ (const Matrix4 & m1, const Matrix4 & m2)
{
	return Matrix4
		   (
		m1[0] + m2[0],
		m1[1] + m2[1],
		m1[2] + m2[2],
		m1[3] + m2[3]
	       );
}


inline Matrix4 operator- (const Matrix4 & m1, const Matrix4 & m2)
{
	return Matrix4
		   (
		m1[0] - m2[0],
		m1[1] - m2[1],
		m1[2] - m2[2],
		m1[3] - m2[3]
	       );
}


inline Matrix4 operator- (const Matrix4 & m)
{
	return Matrix4
		   (
		-m[0],
		-m[1],
		-m[2],
		-m[3]
	       );
}


inline Matrix4 operator* (const Matrix4 & m1, const Matrix4 & m2)
{
	return Matrix4(
		m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0],
		m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1],
		m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2],
		m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3],

		m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0],
		m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1],
		m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2],
		m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3],

		m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0],
		m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1],
		m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2],
		m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3],

		m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0],
		m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1],
		m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2],
		m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3]

	);
}


inline Matrix4 operator* (const Matrix4 & m, double d)
{
	return Matrix4
		   (
		m[0] * d,
		m[1] * d,
		m[2] * d,
		m[3] * d
	       );
}


inline Matrix4 operator/ (const Matrix4 & m, double d)
{
	if (std::abs(d) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Matrix4");
	double inv = 1.0 / d;
	return Matrix4
		   (
		m[0] * inv,
		m[1] * inv,
		m[2] * inv,
		m[3] * inv
	       );
}


inline Vector4 operator* (const Matrix4 & m, const Vector4 & v)
{
	return Vector4
		   (
		v * m[0],
		v * m[1],
		v * m[2],
		v * m[3]
	       );
}


inline Vector4 operator* (const Vector4 & v, const Matrix4 & m)
{
	return Vector4
		   (
		v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0],
		v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1],
		v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2],
		v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3]
	       );
}


inline Vector4 & operator*= (Vector4 & v, const Matrix4 & m)
{
	double T0, T1, T2;
	T0   = v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0];
	T1   = v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1];
	T2   = v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2];
	v[3] = v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3];
	v[0] = T0;
	v[1] = T1;
	v[2] = T2;

	return (v);
}


inline Matrix4 operator* (const double d, const Matrix4 & m)
{
	return m * d;
}


inline bool operator== (const Matrix4 & m1, const Matrix4 & m2)
{
	return (
		m1[0] == m2[0] &&
		m1[1] == m2[1] &&
		m1[2] == m2[2] &&
		m1[3] == m2[3]
	);
}


};  // namespace core
#endif // ifndef Matrix4H
