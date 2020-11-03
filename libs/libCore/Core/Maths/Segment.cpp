// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Segment.h"

namespace core {

Segment::Segment(const Point3 & from, const Point3 & to) :
	a(from)
	, b(to)
{ }


bool Segment::getIntersection (const Plane & p, Point3 & point) const
{
	// 1st point of segment is included in plane
	double pa = p.apply(a);
	if (std::abs(pa) < IGT_EPSILON) {
		point = a;
		return true;
	}

	// second point of segment is included in plane
	double pb = p.apply(b);
	if (std::abs(pb) < IGT_EPSILON) {
		point = b;
		return true;
	}

	// segment is // to plane and not included in
	if (std::abs(pa - pb) < IGT_EPSILON)
		return false;

	// intersection point between plane and segment line.
	point = a + pa / (pa - pb) * (b - a);

	return (pa < 0.0 && pb > 0.0) || (pa > 0.0 && pb < 0.0);
}


bool Segment::getIntersection (const Line & line, Point3 & point, float epsilon) const
{
	// see "3D Math Primer for Graphics and Game Development" p.283

	const Vector3 & d1 = to() - from();
	const Vector3 & d2 = line.getDirection();
	const Point3 & p1  = from();
	const Point3 & p2  = line.getOrigin();

	double d           = (d1 ^ d2).sqrLength();

	// lines are parallels
	if (d < epsilon) {
		point = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}

	double t1 = (((p2 - p1) ^ d2) * (d1 ^ d2)) / d;

	// point is not on segment
	if (t1 < -epsilon || t1 > 1 + epsilon) {
		point = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}

	double t2   = (((p2 - p1) ^ d1) * (d1 ^ d2)) / d;

	Point3 res1 = p1 + t1 * d1;
	Point3 res2 = p2 + t2 * d2;

	// lines are coplanar
	if (res1.isClose(res2, epsilon)) {
		// return point over this line as approximation.
		point = res1;
		return true;
	} else {
		point = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}
}


Line Segment::getPerpendicularBisector (const Vector3 & normal) const
{
	Vector3 segmentDirection = b - a;
	segmentDirection.normalise();
	// if normal is not perpendicular to segment
	if (std::abs(normal * segmentDirection) > IGT_EPSILON) {
		throw IGTInvalidParameterErr("Segment", "normal vector must be perpendicular to the segment.");
	}

	Vector3 segmentMiddle = 0.5 * (b + a);
	Vector3 lineDirection = normal ^ segmentDirection;
	lineDirection.normalise();
	return Line(segmentMiddle, lineDirection);
}


}  // namespace core


namespace std {

TGCORE_API std::ostream & operator<< (std::ostream & out, const core::Segment & s)
{
	return out << '[' << s.from() << ", " << s.to() << ']';
}


}  // namespace std
