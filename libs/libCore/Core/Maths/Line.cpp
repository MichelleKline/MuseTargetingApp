// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Line.h"
#include "Segment.h"

#include "Matrix2.h"


namespace core {

Line::Line() :
	origin(P3_NULL),
	direction(V3_X)
{ }


Line::Line(const Point3 & origin_, const Vector3 & direction_) :
	origin(origin_),
	direction(direction_)
{
	if (direction.isNull()) {
		throw IGTInvalidParameterErr("Line", "Director vector of a line can't be null");
	}
}


bool Line::getIntersection (const core::Line & line, Point3 & res, double epsilon) const
{
	// see "3D Math Primer for Graphics and Game Development" p.283

	const Vector3 & d1 = getDirection();
	const Vector3 & d2 = line.getDirection();
	const Point3 & p1  = getOrigin();
	const Point3 & p2  = line.getOrigin();

	double d           = (d1 ^ d2).sqrLength();

	// lines are parallels
	if (d < epsilon) {
		res = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}

	double t1   = (((p2 - p1) ^ d2) * (d1 ^ d2)) / d;
	double t2   = (((p2 - p1) ^ d1) * (d1 ^ d2)) / d;

	Point3 res1 = p1 + t1 * d1;
	Point3 res2 = p2 + t2 * d2;

	// lines are coplanar
	if (res1.isClose(res2)) {
		// return point over this line as approximation.
		res = res1;
		return true;
	} else {
		res = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}
}


bool Line::include (const Point3 & point, double epsilon) const
{
	return (point - origin).isCollinear(direction, epsilon);
}


Point3 Line::getProjection (const Point3 & point) const
{
	Vector3 u(this->getDirection());
	u.normalise();

	double lambda = (point - this->getOrigin()) * u;

	Point3 res    = this->getOrigin() + lambda * u;

	return res;
}


bool Line::isEquivalent (const Line & line, double epsilon) const
{
	return (direction.isCollinear(line.getDirection(), epsilon) && include(line.getOrigin(), epsilon) );
}


Segment Line::getPerpendicularSegment (const core::Line & line) const
{
	// if lines are coplanar
	Point3 pt;
	if (getIntersection(line, pt)) {
		return Segment(pt, pt);
	}


	// we are looking for segment [H1, H2].
	// Line1 = A + alpha * u
	// Line2 = B + beta * v;
	//
	// H1 = A + alpha*u
	// H2 = B + beta*v
	// we will solve the system:
	//
	// alpha * (u*u) + beta * (u*v) = -u*AB
	// alpha * (u*v) + beta * (v*v) = -v*AB


	const Vector3 & u = direction;
	const Vector3 & v = line.direction;
	const Point3 & A  = origin;
	const Point3 & B  = line.origin;
	Vector3 AB        = B - A;

	double uv         = u * v;

	double delta      = u.sqrLength() * v.sqrLength() - uv * uv;

	// delta = 0 => lines are parallele
	if (delta < IGT_LITTLE_EPSILON) {
		// if line //, project origin in 2nd line.
		return Segment(A, line.getProjection(A));
	}

	double delta1 = -(uv * (v * AB)) + v.sqrLength() * (u * AB);
	double delta2 = -u.sqrLength() * (v * (AB)) + uv * (u * AB);

	double alpha  = delta1 / delta;
	double beta   = delta2 / delta;

	Point3 H1     = A + alpha * u;
	Point3 H2     = B + beta * v;

	return Segment(H1, H2);
}


double Line::distance (const Point3 & point) const
{
	return (point - getProjection(point)).length();
}


double Line::distance (const Line & line) const
{
	Segment perpendicularSegment = getPerpendicularSegment(line);
	return (perpendicularSegment.to() - perpendicularSegment.from()).length();
}


double Line::distance (const Segment & segment) const
{
	// special case if segment is reduce to a point
	if (segment.from().isClose(segment.to()))
		return distance(segment.from());

	// line in which the segment is
	Line segmentLine(segment.from(), segment.to() - segment.from());
	// compute orthogonal segment: perpendicularSegment.from() is over this line,
	// perpendicularSegment.to() is over segmentLine.
	Segment perpendicularSegment = getPerpendicularSegment(segmentLine);

	// now, test is perpendicularSegment.to() is in segment. if it's the case, distance is
	// (perpendicularSegment.to() - perpendicularSegment.from()).length().
	// else, distance is the min of segment extremities projected over line.
	if (segment.includes(perpendicularSegment.to()))
		return (perpendicularSegment.to() - perpendicularSegment.from()).length();
	else {
		// distance from segment.from to line
		double lengthFrom = (segment.from() - getProjection(segment.from())).length();

		// distance from segment.to to line
		double lengthTo = (segment.to() - getProjection(segment.to())).length();

		return std::min(lengthFrom, lengthTo);
	}
}


Line::~Line(void)
{ }


}  // namespace core
