// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#pragma once

#include "Line.h"

#include "../../libCore.h"
#include "../Constants.h"
#include "Vector3.h"
#include "Plane.h"

#include <ostream>

namespace core {

/**
 * @brief A straight segment given 2 points.
 */
class TGCORE_API Segment
{
public:
	Segment(const Point3 & from, const Point3 & to);

	bool operator== (const Segment & s) const
	{ return a == s.a && b == s.b; }

	bool operator!= (const Segment & s) const
	{ return ! (*this == s); }

	bool isEquivalent (const Segment & s, double epsilon=IGT_EPSILON) const
	{
		return (a.isClose(s.a, epsilon) && b.isClose(s.b, epsilon))
		       || (a.isClose(s.b, epsilon) && b.isClose(s.a, epsilon));
	}

	inline double length() const
	{ return (b - a).length(); }

	inline Vector3 getVector() const
	{ return b - a; }

	inline Segment operator-() const
	{ return Segment(b, a); }

	inline Point3 & from() { return a; }

	inline const Point3 & from() const
	{ return a; }

	inline Point3 & to() { return b; }

	inline const Point3 & to() const
	{ return b; }

	inline Point3 at (double t) const  // In-segment values range from 0 to 1
	{ return (b - a) * t + a; }

	inline double index (const Point3 & p) const  // Projects p on the segment
	{ return ((p - a) * (b - a)) / ((b - a) * (b - a)); }

	inline bool includes (const Point3 & p, double epsilon=IGT_EPSILON) const
	{
		double t = index(p);
		return t >= 0.0 && t <= 1.0 && (at(t)).isClose(p, epsilon);
	}

	inline double distance (const Point3 & p) const
	{
		double t = index(p);

		if (t < 0.0)
			return (p - a).length();
		else if (t > 1.0)
			return (p - b).length();
		else
			return (p - at(t)).length();
	}

	inline double distanceExt (const Point3 & p) const  // Extended to the segment as a line
	{
		double t = index(p);
		return (p - at(t)).length();
	}

	inline double distance (const Segment & s) const
	{
		std::pair<double, double> t = closestPointsIdx(s);

		if (t.first < 0.0)
			t.first = 0.0;
		else if (t.first > 1.0)
			t.first = 1.0;

		if (t.second < 0.0)
			t.second = 0.0;
		else if (t.second > 1.0)
			t.second = 1.0;

		return (at(t.first) - s.at(t.second)).length();
	}

	inline double distanceExt (const Segment & s) const  // Extended to the segment as a line
	{
		const std::pair<double, double> & t = closestPointsIdx(s);
		return (at(t.first) - s.at(t.second)).length();
	}

	inline std::pair<double, double> closestPointsIdx (const Segment & s) const
	{
		return closestPointsIdx(*this, s);
	}

	static inline std::pair<double, double> closestPointsIdx (const Segment & s1, const Segment & s2);

	inline bool isAligned (const Point3 & p) const
	{
		return at(index(p)) == p;
	}

	inline bool isAligned (const Segment & s) const
	{
		return isAligned(s.a) && isAligned(s.b);
	}

	inline bool isParallel (const Segment & s) const
	{
		const Vector3 & v1 = b - a;  // Could use cross product, but costs an extra Vector3::length call
		const Vector3 & v2 = s.b - s.a;
		return std::abs(v1[0] * v2[1] - v2[0] * v1[1]) < IGT_EPSILON
		       && std::abs(v1[1] * v2[2] - v2[1] * v1[2]) < IGT_EPSILON
		       && std::abs(v1[2] * v2[0] - v2[2] * v1[0]) < IGT_EPSILON;
	}

	inline bool isParallel (const Plane & p) const
	{ return std::abs(p.getNormal() * (b - a)) < IGT_EPSILON; }

	inline bool isCoplanar (const Segment & s) const
	{
		return a == s.a || a == s.b || b == s.a || b == s.b
		       || isParallel(s)
		       || Plane(b - a, s.a - a, a).includes(s.b);
	}

	inline bool in (const Plane & p, double epsilon=IGT_EPSILON) const
	{ return p.includes(a, epsilon) && p.includes(b, epsilon); }

	/** Return true is segment intersect specified plane */
	inline bool intersects (const Plane & p) const
	{
		// 1st point of segment is included in plane
		double pa = p.apply(a);
		if (std::abs(pa) < IGT_EPSILON)
			return true;

		// second point of segment is included in plane
		double pb = p.apply(b);
		if (std::abs(pb) < IGT_EPSILON)
			return true;

		// segment is // to plane and not included in
		if (std::abs(pa - pb) < IGT_EPSILON)
			return false;

		return (pa < 0.0 && pb > 0.0) || (pa > 0.0 && pb < 0.0);
	}

	/** Return true is segment intersect specified plane.
	 * If true, result is stored in point.
	 * If segment is included in plane, segment.from is returned. */
	bool getIntersection (const Plane & p, Point3 & point) const;

	bool getIntersection (const Line & line, Point3 & point, float epsilon=IGT_EPSILON) const;

	inline std::pair<double, double> intersectionIdx (const Segment & s)
	{
		return intersectionIdx(*this, s);
	}

	inline double intersectionIdx (const Plane & p) const
	{
		double pa = p.apply(a);
		double pb = p.apply(b);

		if (std::abs(pa - pb) < IGT_EPSILON)
			throw IGTDivideByZeroErr("Segment");

		return pa / (pa - pb);
	}

	// @throw IGTDivideByZeroErr
	static inline std::pair<double, double> intersectionIdx (const Segment & s1, const Segment & s2);

	/**
	 * Return the perpendicalar bisector ("Mediatrice" in french) of the segment, which is normal to the specifed vector.
	 *
	 * @param normal a normal vector of the segment. The returned line will be normal to this vector. If this vector is nor normal to the segment, an IGTInvalidParameterErr is thrown.
	 * @return A line which is normal to the segment and the specifed vector and which pass by the segment's middle point.
	 */
	Line getPerpendicularBisector (const Vector3 & normal) const;

private:
	Point3 a, b;
};


// Assumes s1 and s2 are coplanar. If segments are parallel (or colinear) throws IGTDivideByZeroErr.
// Check t1 and t2 values for intersection included in both segments.
// Use s1.at(t1) or s2.at(t2) to get the point coordinates.
inline std::pair<double, double> Segment::intersectionIdx (const Segment & s1, const Segment & s2)
{
	double det = (s2.b[0] - s2.a[0]) * (s1.b[1] - s1.a[1])
	    - (s1.b[0] - s1.a[0]) * (s2.b[1] - s2.a[1]);
	if (std::abs(det) < IGT_EPSILON)
		throw IGTDivideByZeroErr("Segment");

	double t1 = ((s2.a[0] - s1.a[0]) * (s2.a[1] - s2.b[1])
	             - (s2.a[1] - s1.a[1]) * (s2.a[0] - s2.b[0]));
	double t2 = ((s1.b[0] - s1.a[0]) * (s2.a[1] - s1.a[1])
	             - (s1.b[1] - s1.a[1]) * (s2.a[0] - s1.a[0]));

	return std::make_pair(t1 / det, t2 / det);
}


inline std::pair<double, double> Segment::closestPointsIdx (const Segment & s1, const Segment & s2)
{
	const Vector3 & u  = s1.getVector();
	const Vector3 & v  = s2.getVector();
	const Vector3 & w  = s1.a - s2.a;

	double a_          = u * u;
	double b_          = u * v;
	double c_          = v * v;
	double d_          = u * w;
	double e_          = v * w;

	double denominator = a_ * c_ - b_ * b_;

	if (denominator < IGT_EPSILON) // Segments are parallel (or colinear): any point will do
		return std::make_pair(0.0f, e_ / c_);
	else {
		double t1 = (b_ * e_ - c_ * d_) / denominator;
		double t2 = (a_ * e_ - b_ * d_) / denominator;

		return std::make_pair(t1, t2);
	}
}


};  // namespace core


namespace std {

TGCORE_API std::ostream & operator<< (std::ostream & out, const core::Segment & s);

}  // namespace std
