// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef Vector4H
#define Vector4H

#include "Vector3.h"

#include "../../libCore.h"
#include "../Constants.h"
#include "../CoreExceptions.h"
#include <cmath>
#include <iostream>

namespace core {

class Vector3;

/// A 4D vector.
class TGCORE_API Vector4
{
	// I/O
	/// Returns an std::ostream displaying vector components.
	friend TGCORE_API std::ostream & operator<<(std::ostream &, const Vector4 &);
	/// Fills vector components from the std::istream.
	friend TGCORE_API std::istream & operator>>(std::istream &, Vector4 &);

public:
	// Constructors
	/// Default constructor. x, y, z and t are set to 0.0.
	Vector4();
	/// Constructor.
	/// @param x the first component,
	/// @param y the second component.
	/// @param z the third component.
	/// @param t the fourth component.
	Vector4(double x, double y, double z, double t);
	/// Copy constructor.
	Vector4(const Vector4 & v);
	/// Copy constructor from a Vector3.
	/// @param v the Vector3.
	/// @param t the fourth component.
	Vector4(const Vector3 & v, double t);

	/// Component accessor: [0] to access the first component, [1] to access the second component,
	/// [2] to access the third component and [3] to access the fourth component.
	inline double & operator[] (int i) { return elements[i]; }

	/// Accessor to the first component.
	inline double & x() { return elements[0]; }

	/// Accessor to the second component.
	inline double & y() { return elements[1]; }

	/// Accessor to the third component.
	inline double & z() { return elements[2]; }

	/// Accessor to the fourth component.
	inline double & t() { return elements[3]; }

	/// Const component accessor: [0] to access the first component, [1] to access the second component,
	/// [2] to access the third component and [3] to access the fourth component.
	inline const double & operator[] (int i) const { return elements[i]; }

	/// Const accessor to the first component.
	inline const double & x()       const { return elements[0]; }

	/// Const accessor to the second component.
	inline const double & y()       const { return elements[1]; }

	/// Const accessor to the third component.
	inline const double & z()       const { return elements[2]; }

	/// Const accessor to the fourth component.
	inline const double & t()       const { return elements[3]; }

	// Assignment operators
	/// Assignment operator.
	inline Vector4 & operator= (const Vector4 & v);

	/// Operator to add a vector.
	inline Vector4 & operator+= (const Vector4 & v);

	/// Operator to substract a vector.
	inline Vector4 & operator-= (const Vector4 & v);

	/// Operator to multiply a vector with a scalar.
	inline Vector4 & operator*= (double s);

	/// Operator to divide a vector with a scalar.
	inline Vector4 & operator/= (double s);

	/// Normalise the vector.
	inline Vector4 & normalise();

	/// Returns the length of the vector.
	inline double length() const;

	/// Returns the square of the length of the vector.
	inline double sqrLength() const;

	/// Returns whether two vectors are equals (with the given epsilon).
	inline bool isClose (const Vector4 & v2, double epsilon=IGT_EPSILON) const;

	/// Returns a const pointer to the components of the vector.
	inline operator const double *() const { return elements; }
	/// Returns a pointer to the components of the vector.
	inline operator double *() { return elements; }

private:
	/// The array storing the vector components
	double elements[4];

};


// Defines
/// A 4D point.
typedef Vector4 Point4;

// Constants
/// A  null 4D vector.
extern TGCORE_API const Vector4 V4_NULL;
/// A  null 4D point.
extern TGCORE_API const Point4 P4_NULL;


// Multiply / divide by a scalar
/// Operator to multiply a vector and a scalar.
inline Vector4 operator* (const Vector4 & v, double s);

/// Operator to multiply a scalar and a vector.
inline Vector4 operator* (double s, const Vector4 & v);

/// Operator to divide a vector and a scalar.
inline Vector4 operator/ (const Vector4 & v, double s);

// Add, subtract two vectors, unary negate
/// Operator to add two vectors.
inline Vector4 operator+ (const Vector4 & v1, const Vector4 & v2);

/// Operator to substract two vectors.
inline Vector4 operator- (const Vector4 & v1, const Vector4 & v2);

/// Operator of unary negate of a vector.
inline Vector4 operator- (const Vector4 & v);

// Dot
/// Computes the dot product of two vectors.
inline double operator* (const Vector4 & v1, const Vector4 & v2);

// Comparison functions
/// Returns whether two vectors are equals.
inline bool operator== (const Vector4 & v1, const Vector4 & v2);

/// Returns whether two vectors are differents.
inline bool operator!= (const Vector4 & v1, const Vector4 & v2);

/// Returns whether the first vector is lesser than the second.
inline bool operator< (const Vector4 & v1, const Vector4 & v2);

/// Returns whether the first vector is greater than the second.
inline bool operator> (const Vector4 & v1, const Vector4 & v2);

// Utilities
/// Normalises the given vector.
inline Vector4 normalise (const Vector4 & v);

// ---------------------------------------------------------------------------
// Member Implmentation


inline Vector4::Vector4()
{
	elements[0] = elements[1] = elements[2] = elements[3] = 0.0;
}


inline Vector4::Vector4(double x, double y, double z, double t)
{
	elements[0] = x;
	elements[1] = y;
	elements[2] = z;
	elements[3] = t;
}


inline Vector4::Vector4(const Vector4 & v)
{
	elements[0] = v[0];
	elements[1] = v[1];
	elements[2] = v[2];
	elements[3] = v[3];
}


inline Vector4 & Vector4::operator= (const Vector4 & v)
{
	if (this != &v) {
		elements[0] = v[0];
		elements[1] = v[1];
		elements[2] = v[2];
		elements[3] = v[3];
	}
	return *this;
}


inline Vector4 & Vector4::operator+= (const Vector4 & v)
{
	elements[0] += v[0];
	elements[1] += v[1];
	elements[2] += v[2];
	elements[3] += v[3];

	return *this;
}


inline Vector4 & Vector4::operator-= (const Vector4 & v)
{
	elements[0] -= v[0];
	elements[1] -= v[1];
	elements[2] -= v[2];
	elements[3] -= v[3];

	return *this;
}


inline Vector4 & Vector4::operator*= (double s)
{
	elements[0] *= s;
	elements[1] *= s;
	elements[2] *= s;
	elements[3] *= s;

	return *this;
}


inline Vector4 & Vector4::operator/= (double s)
{
	if (std::abs(s) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector4");
	elements[0] /= s;
	elements[1] /= s;
	elements[2] /= s;
	elements[3] /= s;

	return *this;
}


inline Vector4 & Vector4::normalise()
{
	double len = length();
	if (std::abs(len) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector4::normalise");
	return operator/=(len);
}


inline double Vector4::length() const
{
	return std::sqrt(sqrLength());
}


inline double Vector4::sqrLength() const
{
	return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2] + elements[3] * elements[3];
}


// ---------------------------------------------------------------------------
// Non-member Implmentation

inline Vector4 operator* (const Vector4 & v, double s)
{
	return Vector4(s * v[0], s * v[1], s * v[2], s * v[3]);
}


inline Vector4 operator* (double s, const Vector4 & v)
{
	return v * s;
}


inline Vector4 operator/ (const Vector4 & v, double s)
{
	if (std::abs(s) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector4");
	return Vector4(v[0] / s, v[1] / s, v[2] / s, v[3] / s);
}


inline Vector4 operator+ (const Vector4 & v1, const Vector4 & v2)
{
	return Vector4(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2], v1[3] + v2[3]);
}


inline Vector4 operator- (const Vector4 & v1, const Vector4 & v2)
{
	return Vector4(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2], v1[3] - v2[3]);
}


inline Vector4 operator- (const Vector4 & v)
{
	return Vector4(-v[0], -v[1], -v[2], -v[3]);
}


inline double operator* (const Vector4 & v1, const Vector4 & v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}


// Comparison functions
inline bool operator== (const Vector4 & v1, const Vector4 & v2)
{
	return (
		std::abs(v1[0] - v2[0]) < IGT_LITTLE_EPSILON &&
		std::abs(v1[1] - v2[1]) < IGT_LITTLE_EPSILON &&
		std::abs(v1[2] - v2[2]) < IGT_LITTLE_EPSILON &&
		std::abs(v1[3] - v2[3]) < IGT_LITTLE_EPSILON
	);
}


inline bool Vector4::isClose (const Vector4 & v2, double epsilon) const
{
	return (
		std::abs(elements[0] - v2[0]) < epsilon &&
		std::abs(elements[1] - v2[1]) < epsilon &&
		std::abs(elements[2] - v2[2]) < epsilon &&
		std::abs(elements[3] - v2[3]) < epsilon
	);
}


inline bool operator!= (const Vector4 & v1, const Vector4 & v2)
{
	return ! (v1 == v2);
}


inline bool operator< (const Vector4 & v1, const Vector4 & v2)
{
	return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2] && v1[3] < v2[3];
}


inline bool operator> (const Vector4 & v1, const Vector4 & v2)
{
	return v1[0] > v2[0] && v1[1] > v2[1] && v1[2] > v2[2] && v1[3] > v2[3];
}


inline Vector4 normalise (const Vector4 & v)
{
	Vector4 v4(v);
	return v4.normalise();
}


};  // namespace core
#endif // ifndef Vector4H
