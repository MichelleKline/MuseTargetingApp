// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef Vector2H
#define Vector2H

#include "../../libCore.h"
#include "../Constants.h"
#include "../CoreExceptions.h"
#include <cmath>
#include <iostream>
#include <vector>

namespace core {

/// A 2D vector.
class TGCORE_API Vector2
{
	// I/O
	/// Returns an std::ostream displaying vector components.
	friend TGCORE_API std::ostream & operator<<(std::ostream &, const Vector2 &);
	/// Fills vector components from the std::istream.
	friend TGCORE_API std::istream & operator>>(std::istream &, Vector2 &);

public:
	// Constructors
	/// Default constructor. x and y are set to 0.0.
	Vector2();
	/// Constructor.
	/// @param X the first component,
	/// @param Y the second component.
	Vector2(double X, double Y);
	/// Copy constructor.
	Vector2(const Vector2 & v);

	/// Component accessor: [0] to access the first component, [1] to access the second component.
	inline double & operator[] (unsigned int i) { return elements[i]; }

	/// Accessor to the first component.
	inline double & x() { return elements[0]; }

	/// Accessor to the second component.
	inline double & y() { return elements[1]; }

	/// Const component accessor: [0] to access the first component, [1] to access the second component.
	inline const double & operator[] (unsigned int i) const { return elements[i]; }

	/// Const accessor to the first component.
	inline const double & x()                const { return elements[0]; }

	/// Const accessor to the second component.
	inline const double & y()                const { return elements[1]; }

	// Assignment operators
	/// Assignment operator.
	inline Vector2 & operator= (const Vector2 & v);

	/// Operator to add a vector.
	inline Vector2 & operator+= (const Vector2 & v);

	/// Operator to substract a vector.
	inline Vector2 & operator-= (const Vector2 & v);

	/// Operator to multiply a vector with a scalar.
	inline Vector2 & operator*= (double s);

	/// Operator to divide a vector with a scalar.
	inline Vector2 & operator/= (double s);

	/// Sets the two components of the vector.
	inline void set (double X, double Y);

	/// Normalise the vector.
	inline Vector2 & normalise();

	/// Returns the length of the vector.
	inline double length() const;

	/// Returns the square of the length of the vector.
	inline double sqrLength() const;

	/// Returns whether two vectors are equals (with the given epsilon).
	inline bool isClose (const Vector2 & v2, double epsilon=IGT_EPSILON) const;

private:
	/// The array storing the vector components
	double elements[2];
};


/// A 2D point.
typedef Vector2 Point2;


// Constants
/// A null 2D vector.
extern TGCORE_API const Vector2 V2_NULL;
/// A 2D point at (0.0, 0.0).
extern TGCORE_API const Point2 P2_NULL;

// Multiply / divide by a scalar
/// Operator to multiply a vector and a scalar.
inline Vector2 operator* (const Vector2 & v, double s);

/// Operator to multiply a scalar and a vector.
inline Vector2 operator* (double s, const Vector2 & v);

/// Operator to divide a vector and a scalar.
inline Vector2 operator/ (const Vector2 & v, double s);

// Add, subtract two vectors, unary negate
/// Operator to add two vectors.
inline Vector2 operator+ (const Vector2 & v1, const Vector2 & v2);

/// Operator to substract two vectors.
inline Vector2 operator- (const Vector2 & v1, const Vector2 & v2);

/// Operator of unary negate of a vector.
inline Vector2 operator- (const Vector2 & v);

// Dot and cross products
/// Computes the dot product of two vectors.
inline double operator* (const Vector2 & v1, const Vector2 & v2);

/// Computes the cross product of two vectors.
inline Vector2 cross (const Vector2 & v);

// Comparison operators
/// Returns whether two vectors are equals.
inline bool operator== (const Vector2 & v1, const Vector2 & v2);

/// Returns whether two vectors are differents.
inline bool operator!= (const Vector2 & v1, const Vector2 & v2);

/// Returns whether the first vector is lesser than the second.
inline bool operator< (const Vector2 & v1, const Vector2 & v2);

/// Returns whether the first vector is greater than the second.
inline bool operator> (const Vector2 & v1, const Vector2 & v2);

// Utilities
/// Normalises the given vector.
inline Vector2 normalise (const Vector2 & v);


// ---------------------------------------------------------------------------
// Member Implmentation

inline Vector2::Vector2()
{
	elements[0] = 0.0;
	elements[1] = 0.0;
}


inline Vector2::Vector2(double X, double Y)
{
	elements[0] = X;
	elements[1] = Y;
}


inline Vector2::Vector2(const Vector2 & v)
{
	elements[0] = v[0];
	elements[1] = v[1];
}


inline void Vector2::set (double X, double Y)
{
	elements[0] = X;
	elements[1] = Y;
}


inline Vector2 & Vector2::operator= (const Vector2 & v)
{
	if (this != &v) {
		elements[0] = v[0];
		elements[1] = v[1];
	}
	return *this;
}


inline Vector2 & Vector2::operator+= (const Vector2 & v)
{
	elements[0] += v[0];
	elements[1] += v[1];
	return *this;
}


inline Vector2 & Vector2::operator-= (const Vector2 & v)
{
	elements[0] -= v[0];
	elements[1] -= v[1];
	return *this;
}


inline Vector2 & Vector2::operator*= (double s)
{
	elements[0] *= s;
	elements[1] *= s;
	return *this;
}


inline Vector2 & Vector2::operator/= (double s)
{
	if (std::abs(s) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector2");
	elements[0] /= s;
	elements[1] /= s;
	return *this;
}


inline Vector2 cross (const Vector2 & v)
{
	return Vector2(v[1], -v[0]);
}


inline Vector2 & Vector2::normalise()
{
	double len = length();
	if (std::abs(len) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector2::normalise");
	return operator/=(len);
}


inline double Vector2::length() const
{
	return std::sqrt(sqrLength());
}


inline double Vector2::sqrLength() const
{
	return elements[0] * elements[0] + elements[1] * elements[1];
}


// ---------------------------------------------------------------------------
// Non-member Implmentation

inline Vector2 operator* (const Vector2 & v, double s)
{
	return Vector2(s * v[0], s * v[1]);
}


inline Vector2 operator* (double s, const Vector2 & v)
{
	return v * s;
}


inline Vector2 operator/ (const Vector2 & v, double s)
{
	if (std::abs(s) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector2");
	return Vector2(v[0] / s, v[1] / s);
}


inline Vector2 operator+ (const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1[0] + v2[0], v1[1] + v2[1]);
}


inline Vector2 operator- (const Vector2 & v1, const Vector2 & v2)
{
	return Vector2(v1[0] - v2[0], v1[1] - v2[1]);
}


inline Vector2 operator- (const Vector2 & v)
{
	return Vector2(-v[0], -v[1]);
}


inline double operator* (const Vector2 & v1, const Vector2 & v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}


// Comparison functions
inline bool operator== (const Vector2 & v1, const Vector2 & v2)
{
	return (
		std::abs(v1[0] - v2[0]) < IGT_LITTLE_EPSILON &&
		std::abs(v1[1] - v2[1]) < IGT_LITTLE_EPSILON
	);
}


inline bool Vector2::isClose (const Vector2 & v2, double epsilon) const
{
	return (
		std::abs(elements[0] - v2[0]) < epsilon &&
		std::abs(elements[1] - v2[1]) < epsilon
	);
}


inline bool operator!= (const Vector2 & v1, const Vector2 & v2)
{
	return ! (v1 == v2);
}


inline bool operator< (const Vector2 & v1, const Vector2 & v2)
{
	return v1[0] < v2[0] && v1[1] < v2[1];
}


inline bool operator> (const Vector2 & v1, const Vector2 & v2)
{
	return v1[0] > v2[0] && v1[1] > v2[1];
}


inline Vector2 normalise (const Vector2 & v)
{
	Vector2 v2(v);
	return v2.normalise();
}


};  // namespace core
#endif // ifndef Vector2H
