// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef Vector3H
#define Vector3H

#include "Vector4.h"

#include "../../libCore.h"
#include "../Constants.h"
#include "../CoreExceptions.h"
#include <cmath>
#include <iostream>

class wxXmlNode;

namespace core {

class Vector4;

/// A 3D vector.
class TGCORE_API Vector3
{
	// I/O
	/// Returns an std::ostream displaying vector components.
	friend TGCORE_API std::ostream & operator<<(std::ostream &, const Vector3 &);
	/// Fills vector components from the std::istream.
	friend TGCORE_API std::istream & operator>>(std::istream &, Vector3 &);

public:
	// Constructors
	/// Default constructor. x, y and z are set to 0.0.
	Vector3();
	/// Constructor.
	/// @param X the first component,
	/// @param Y the second component.
	/// @param Z the third component.
	Vector3(double X, double Y, double Z);
	/// Copy constructor.
	Vector3(const Vector3 & v);
	/// Copy constructor from a Vector4 (the fourth component will be ignored).
	explicit Vector3(const Vector4 & v);

	/// Component accessor: [0] to access the first component, [1] to access the second component
	/// and [2] to access the third component.
	inline double & operator[] (int i) { return elements[i]; }

	/// Accessor to the first component.
	inline double & x() { return elements[0]; }

	/// Accessor to the second component.
	inline double & y() { return elements[1]; }

	/// Accessor to the third component.
	inline double & z() { return elements[2]; }

	/// Const component accessor: [0] to access the first component, [1] to access the second component
	/// and [2] to access the third component.
	inline const double & operator[] (int i) const { return elements[i]; }

	/// Const accessor to the first component.
	inline const double & x()       const { return elements[0]; }

	/// Const accessor to the second component.
	inline const double & y()       const { return elements[1]; }

	/// Const accessor to the third component.
	inline const double & z()       const { return elements[2]; }

	// Assignment operators
	/// Assignment operator.
	inline Vector3 & operator= (const Vector3 & v);

	/// Operator to add a vector.
	inline Vector3 & operator+= (const Vector3 & v);

	/// Operator to substract a vector.
	inline Vector3 & operator-= (const Vector3 & v);

	/// Operator to multiply a vector with a scalar.
	inline Vector3 & operator*= (double s);

	/// Operator to divide a vector with a scalar.
	inline Vector3 & operator/= (double s);

	/// Normalise the vector.
	inline Vector3 & normalise();

	/// Returns the length of the vector.
	inline double length() const;

	/// Returns the square of the length of the vector.
	inline double sqrLength() const;

	/// Returns whether vector is null.
	inline bool isNull (double epsilon=IGT_LITTLE_EPSILON) const;

	/// Returns whether two vectors are equal (with the given epsilon).
	inline bool isClose (const Vector3 & other, double epsilon=IGT_EPSILON) const;

	/// Returns whether two vectors are collinear.
	bool isCollinear (const Vector3 & other, double epsilon=IGT_EPSILON) const;

	/** Returns a rotated vector. Rotation values are in radian. */
	Vector3 rotate (double xAngle=0.0f, double yAngle=0.0f, double zAngle=0.0f) const;

	/** Returns a rotated vector about an axis. Rotation value is in radian. */
	Vector3 rotate (const Vector3 & axis, double rotation) const;

	/** Return the angle (in Radian, [0, PI]) between 2 vectors. Throw IGTDivideByZeroErr if one of the vector is null */
	double getAngle (const Vector3 & vector) const;

	/** Return V3_X, V3_Y or V3_Z depending on which axis is this vector the most aligned.
	 * Return V3_X by default (axis is null of 45°). */
	const Vector3 & getMainAxis() const;

	/// Returns a const pointer to the components of the vector.
	inline operator const double *() const { return elements; }
	/// Returns a pointer to the components of the vector.
	inline operator double *() { return elements; }

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	//wxXmlNode * exportToXML() const;

	/// Appends the vector3 to file in XML format (faster than wxWidgets XML).
	//void appendToStream (std::ofstream & file) const;

	//void loadFromXmlNode (wxXmlNode *);

	//! @endcond

private:
	/// The array storing the vector components
	double elements[3];
};


// Defines
/// A 3D point.
typedef Vector3 Point3;

// Constants
/// A  null 3D vector.
extern TGCORE_API const Vector3 V3_NULL;
/// A 3D vector with the given components: (1.0, 0.0, 0.0).
extern TGCORE_API const Vector3 V3_X;
/// A 3D vector with the given components: (0.0, 1.0, 0.0).
extern TGCORE_API const Vector3 V3_Y;
/// A 3D vector with the given components: (0.0, 0.0, 1.0).
extern TGCORE_API const Vector3 V3_Z;
/// A 3D point at (0.0, 0.0, 0.0).
extern TGCORE_API const Point3 P3_NULL;

// Multiply / divide by a scalar
/// Operator to multiply a vector and a scalar.
inline Vector3 operator* (const Vector3 & v, double s);

/// Operator to multiply a scalar and a vector.
inline Vector3 operator* (double s, const Vector3 & v);

/// Operator to divide a vector and a scalar.
inline Vector3 operator/ (const Vector3 & v, double s);

// Add, subtract two vectors, unary negate
/// Operator to add two vectors.
inline Vector3 operator+ (const Vector3 & v1, const Vector3 & v2);

/// Operator to substract two vectors.
inline Vector3 operator- (const Vector3 & v1, const Vector3 & v2);

/// Operator of unary negate of a vector.
inline Vector3 operator- (const Vector3 & v);

// Dot and cross products
/// Computes the dot product of two vectors.
inline double operator* (const Vector3 & v1, const Vector3 & v2);

/// Computes the cross product of two vectors.
inline Vector3 operator^ (const Vector3 & v1, const Vector3 & v2);

// Comparison functions
/// Returns whether two vectors are equals.
inline bool operator== (const Vector3 & v1, const Vector3 & v2);

/// Returns whether two vectors are differents.
inline bool operator!= (const Vector3 & v1, const Vector3 & v2);

/// Returns whether the first vector is lesser than the second.
inline bool operator< (const Vector3 & v1, const Vector3 & v2);

/// Returns whether the first vector is greater than the second.
inline bool operator> (const Vector3 & v1, const Vector3 & v2);

// Utilities
/// Normalises the given vector.
inline Vector3 normalise (const Vector3 & v);

// ---------------------------------------------------------------------------
// Member Implmentation


inline Vector3::Vector3()
{
	elements[0] = elements[1] = elements[2] = 0.0;
}


inline Vector3::Vector3(double X, double Y, double Z)
{
	elements[0] = X;
	elements[1] = Y;
	elements[2] = Z;
}


inline Vector3::Vector3(const Vector3 & v)
{
	elements[0] = v[0];
	elements[1] = v[1];
	elements[2] = v[2];
}


inline Vector3 & Vector3::operator= (const Vector3 & v)
{
	if (this != &v) {
		elements[0] = v[0];
		elements[1] = v[1];
		elements[2] = v[2];
	}
	return *this;
}


inline Vector3 & Vector3::operator+= (const Vector3 & v)
{
	elements[0] += v[0];
	elements[1] += v[1];
	elements[2] += v[2];

	return *this;
}


inline Vector3 & Vector3::operator-= (const Vector3 & v)
{
	elements[0] -= v[0];
	elements[1] -= v[1];
	elements[2] -= v[2];

	return *this;
}


inline Vector3 & Vector3::operator*= (double s)
{
	elements[0] *= s;
	elements[1] *= s;
	elements[2] *= s;

	return *this;
}


inline Vector3 & Vector3::operator/= (double s)
{
	if (std::abs(s) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector3");

	elements[0] /= s;
	elements[1] /= s;
	elements[2] /= s;

	return *this;
}


inline Vector3 & Vector3::normalise()
{
	double len = length();
	if (std::abs(len) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector3::normalise");
	return operator/=(len);
}


inline double Vector3::length() const
{
	return std::sqrt(sqrLength());
}


inline double Vector3::sqrLength() const
{
	return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
}


// ---------------------------------------------------------------------------
// Non-member Implmentation

inline Vector3 operator* (const Vector3 & v, double s)
{
	return Vector3(s * v[0], s * v[1], s * v[2]);
}


inline Vector3 operator* (double s, const Vector3 & v)
{
	return v * s;
}


inline Vector3 operator/ (const Vector3 & v, double s)
{
	if (std::abs(s) < IGT_LITTLE_EPSILON)
		throw IGTDivideByZeroErr("Vector3");
	return Vector3(v[0] / s, v[1] / s, v[2] / s);
}


inline Vector3 operator+ (const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}


inline Vector3 operator- (const Vector3 & v1, const Vector3 & v2)
{
	return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}


inline Vector3 operator- (const Vector3 & v)
{
	return Vector3(-v[0], -v[1], -v[2]);
}


inline double operator* (const Vector3 & v1, const Vector3 & v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


inline Vector3 operator^ (const Vector3 & v1, const Vector3 & v2)
{
	return Vector3
		   (
		v1[1] * v2[2] - v1[2] * v2[1],
		v1[2] * v2[0] - v1[0] * v2[2],
		v1[0] * v2[1] - v1[1] * v2[0]
	       );
}


// Comparison functions
inline bool operator== (const Vector3 & v1, const Vector3 & v2)
{
	return (
		std::abs(v1[0] - v2[0]) < IGT_LITTLE_EPSILON &&
		std::abs(v1[1] - v2[1]) < IGT_LITTLE_EPSILON &&
		std::abs(v1[2] - v2[2]) < IGT_LITTLE_EPSILON
	);
}


inline bool Vector3::isNull (double epsilon) const
{
	return std::abs(elements[0]) < epsilon &&
	       std::abs(elements[1]) < epsilon &&
	       std::abs(elements[2]) < epsilon;
}


inline bool Vector3::isClose (const Vector3 & other, double epsilon) const
{
	return std::abs(elements[0] - other[0]) < epsilon &&
	       std::abs(elements[1] - other[1]) < epsilon &&
	       std::abs(elements[2] - other[2]) < epsilon;
}


inline bool operator!= (const Vector3 & v1, const Vector3 & v2)
{
	return ! (v1 == v2);
}


inline bool operator< (const Vector3 & v1, const Vector3 & v2)
{
	return v1[0] < v2[0] && v1[1] < v2[1] && v1[2] < v2[2];
}


inline bool operator> (const Vector3 & v1, const Vector3 & v2)
{
	return v1[0] > v2[0] && v1[1] > v2[1] && v1[2] > v2[2];
}


inline Vector3 normalise (const Vector3 & v)
{
	Vector3 v3(v);
	return v3.normalise();
}


};  // namespace core
#endif // ifndef Vector3H
