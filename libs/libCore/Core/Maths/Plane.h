// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#pragma once

#include "../../libCore.h"
#include "../Constants.h"
#include "Vector3.h"
#include <vector>
#include "BoundingBox.h"
#include "Line.h"

#include <ostream>


namespace core {

/// The euclidean plane.
class TGCORE_API Plane
{
public:
	/// Constructor.
	/// @param normal the normal vector of the plane,
	/// @param p a point in the plane.
	Plane(const Vector3 & normal, const Point3 & p) : a(0), b(0), c(0), d(0)
	{ init(normal, p); }

	/// Constructor.
	/// @param v1 a vector in the plane,
	/// @param v2 another vector in the plane,
	/// @param p a point in the plane.
	Plane(const Vector3 & v1, const Vector3 & v2, const Point3 & p) : a(0), b(0), c(0), d(0)
	{ init(v1 ^ v2, p); }

	// Plane(const Point3 &p, const Point3 &q, const Point3 &r)
	//	: Plane(q-p, r-p, p)
	// { }

	/// Returns the normal of the plane.
	inline Vector3 getNormal() const
	{ return Vector3(a, b, c); }

	/**Return d from the cartesian equation : ax + by + cz +d = 0
	 */
	inline double getAffineComponent() const
	{ return d; }

	/// Returns the distance between the plane and the point.
	inline double distance (const Point3 & p) const
	{ return std::abs(apply(p)); }

	/** Return the distance of the point from the plan.
	 * If distance > 0, it mean the the point is in the plan's normal side.
	 * Otherwise, distance is < 0.
	 */
	inline double distanceSigned (const Point3 & p) const
	{ return apply(p); }

	/**
	 * return true if the plan separate the point set. In other word, return false if
	 * all the points are in the same side of the plan.
	 */
	bool separate (const std::vector<Point3> & points) const;

	/** return true if the plan intersect the boundingBox */
	bool intersect (const BoundingBox & bbox) const;

	/** return an ordinary point that belongs to plane (can be useful for space change) */
	Point3 getAPoint();

	/**
	 * Compute the instersection between line and plane.
	 * If no intersections, return false and set the result point to Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY).
	 * If line is included in plane, return false ans set the result point to Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY).
	 */
	bool getIntersection (const Line & line, Point3 & point) const;

	/**
	 * Return the angle (in radian) between the 2 plane. The angle will be in [0, PI].
	 */
	double getAngle (const Plane & plane) const;

	/// Comparaison operator.
	inline bool operator== (const Plane & other) const
	{
		return isParallel(other)
		       && std::abs(d - other.d) < IGT_EPSILON;
	}

	/// Comparaison operator.
	inline bool operator!= (const Plane & other) const
	{ return ! (*this == other); }

	/// Returns whether the point @em a is included in the plane.
	inline bool includes (const Point3 & p, double epsilon=IGT_EPSILON) const
	{ return distance(p) < epsilon; }

	/// Returns whether the two planes are parallels.
	inline bool isParallel (const Plane & other) const
	{
		return std::abs(a - other.a) < IGT_EPSILON
		       && std::abs(b - other.b) < IGT_EPSILON
		       && std::abs(c - other.c) < IGT_EPSILON;
	}

	/// Returns whether the vector is parallel to the vector.
	inline bool isParallel (const Vector3 & v) const
	{ return std::abs(v * getNormal()) < IGT_EPSILON; }

	/// Apply the point coordinates to the plane equation.
	inline double apply (const Point3 & p) const
	{ return a * p[0] + b * p[1] + c * p[2] + d; }

	/// Computes the projection of the point on the plane.
	inline Point3 projection (const Point3 & p) const
	{ return p - apply(p) * getNormal(); }

	/// Computes the projection.
	/// @throw Throws IGTDivideByZeroErr if v is parallel to p.
	Point3 projection (const Point3 & p, const Vector3 & v) const;

	/**
	 * Return the intersection between 2 planes is a line(if they are not parallell)
	 * which have as parametric equation D: P + ku, with u the director vector and P,
	 * a point belong to it.
	 * Be Carrefull, return a Vector null if they are parallell
	 */
	std::pair<core::Point3, core::Vector3> getIntersection (const Plane & p) const;

private:
	/// @throw  core::IGTDivideByZeroErr if the length of the input vector is null
	void init (const Vector3 & normal, const Point3 & p0);

// public://for test
	double a, b, c, d;  // ax + by + cz + d = 0  with  a^2 + b^2 + c^2 = 1  and first non-null among (a, b, c) >= 0

private:
	friend TGCORE_API std::ostream & operator<< (std::ostream & out, const Plane & p);

};


/// Exports the plane as to a std::ostream.
TGCORE_API std::ostream & operator<< (std::ostream & out, const core::Plane & p);

};  // namespace core
