// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Plane.h"
#include "Segment.h"
#include "Matrix2.h"
#include "Vector2.h"

namespace core {

void Plane::init (const Vector3 & normal, const Point3 & p0)
{
	Vector3 n = normal;
	n.normalise();

	a = n[0];
	b = n[1];
	c = n[2];

	if (std::abs(a) < IGT_EPSILON) {
		if (std::abs(b) < IGT_EPSILON) {
			if (c < 0.0)
				c = -c;
		} else if (b < 0.0) {
			b = -b;
			c = -c;
		}
	} else if (a < 0.0) {
		a = -a;
		b = -b;
		c = -c;
	}

	d = -(a * p0[0] + b * p0[1] + c * p0[2]);
}


double Plane::getAngle (const Plane & plane) const
{
	const Vector3 normalThis  = this->getNormal();
	const Vector3 normalPlane = plane.getNormal();

	double cosAngle           = normalThis * normalPlane;
	return acos(std::abs(cosAngle));
}


std::pair<core::Point3, core::Vector3> Plane::getIntersection (const Plane & p) const
{

	// this :	ax	+ by	+ cz	+ d =0;
	// p	:	a'x + b'y	+ c'z	+ d' = 0;
	core::Vector3 n1 = getNormal();    // n1(a,b,c)
	core::Vector3 n2 = p.getNormal();  // n2(a',b',c')

	// Find the director vector
	core::Vector3 u = n1 ^ n2; // u is the director vector of the line
	if (u == V3_NULL)          // Planes are parallells
		return std::make_pair(P3_NULL, V3_NULL);

	// Find a point on this line
	double x = 0.0f;
	double y = 0.0f;
	double z = 0.0f;

	Matrix2 mx(n1[1], n1[2], n2[1], n2[2]);
	Vector2 ddprime(-d, -p.getAffineComponent());
	// let px = 0.0f
	if (std::abs(determinant(mx)) > IGT_EPSILON) {  // if det	|b  c | == 0 Stop and let py or pz = 0
		//	|b' c'|
		// , else	(py)=(b  c )-1(-d)
		//			(pz) (b' c')  (-d')
		Vector2 yz = invert(mx) * ddprime;
		x = 0.0f;
		y = yz[0];
		z = yz[1];
	} else {
		// let y = 0.0f;
		Matrix2 my(n1[0], n1[2], n2[0], n2[2]);
		if (std::abs(determinant(my)) > IGT_EPSILON) {
			Vector2 xz = invert(my) * ddprime;
			x = xz[0];
			y = 0.0f;
			z = xz[1];
		} else {
			// let z = 0.0f;
			Matrix2 mz(n1[0], n1[1], n2[0], n2[1]);
			if (std::abs(determinant(mz)) > IGT_EPSILON) {
				Vector2 xy = invert(mz) * ddprime;
				x = xy[0];
				y = xy[1];
				z = 0.0f;
			} else {
				// Should never be here
				return std::make_pair(P3_NULL, V3_NULL);
			}
		}
	}
	return std::make_pair(Point3(x, y, z), u);
}


bool Plane::separate (const std::vector<Point3> & points) const
{
	// compute side of first point
	bool isPositive = (distanceSigned(points[0]) > 0);
	for (std::vector<Point3>::const_iterator itPoint = points.begin(); itPoint != points.end(); ++itPoint) {
		// if a point is not in the same side that the first point, return true
		if ( (distanceSigned(*itPoint) > 0) != isPositive) {
			return true;
		}
	}
	return false;
}


bool Plane::intersect (const BoundingBox & bbox) const
{
	double minX = bbox.getLowerBound().x();
	double minY = bbox.getLowerBound().y();
	double minZ = bbox.getLowerBound().z();
	double maxX = bbox.getUpperBound().x();
	double maxY = bbox.getUpperBound().y();
	double maxZ = bbox.getUpperBound().z();

	std::vector<Point3> points;
	points.push_back(Point3(minX, minY, minZ));
	points.push_back(Point3(minX, minY, maxZ));
	points.push_back(Point3(minX, maxY, minZ));
	points.push_back(Point3(minX, maxY, maxZ));
	points.push_back(Point3(maxX, minY, minZ));
	points.push_back(Point3(maxX, minY, maxZ));
	points.push_back(Point3(maxX, maxY, minZ));
	points.push_back(Point3(maxX, maxY, maxZ));

	return separate(points);
}


Point3 Plane::getAPoint()
{
	double x = 0;
	double y = 0;
	double z = 0;

	if (std::abs(a) > IGT_EPSILON) {
		y = 0;
		z = 0;
		x = -d / a;
	} else if (std::abs(b) > IGT_EPSILON) {
		x = 0;
		z = 0;
		y = -d / b;
	} else if (std::abs(c) > IGT_EPSILON) {
		x = 0;
		y = 0;
		z = -d / c;
	}

	return Point3(x, y, z);
}


bool Plane::getIntersection (const Line & line, Point3 & point) const
{

	double denominator = (a * line.getDirection().x() + b * line.getDirection().y() + c * line.getDirection().z());
	if (std::abs(denominator) < IGT_EPSILON) {
		point = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}

	double lambda = -apply(line.getOrigin()) / denominator;
	point = line.getOrigin() + lambda * line.getDirection();
	return true;
}


Point3 Plane::projection (const Point3 & p, const Vector3 & v) const
{
	Segment s(p, p + v);
	return s.at(s.intersectionIdx(*this));
}


TGCORE_API std::ostream & operator<< (std::ostream & out, const core::Plane & p)
{
	return out << '[' << p.a << ", " << p.b << ", " << p.c << ", " << p.d << ']';
}


};  // namespace core

namespace std { }  // namespace std
