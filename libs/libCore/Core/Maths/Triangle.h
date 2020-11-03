// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#pragma once

#include "../../libCore.h"
#include "Polygon.h"

namespace core {

// forward declare
class Polygon;

/**
 * @brief Class representing a triangle.
 */
class TGCORE_API Triangle : public Polygon
{
public:
	Triangle();

	/**
	 * Build a triangle from 3 points.
	 */
	Triangle(const Point3 & p1, const Point3 & p2, const Point3 & p3);

	/**
	 * Returns the center of the circonscript circle of the triangle.
	 * If triangle is flat, return false.
	 */
	bool getCircumscribedCircleCenter (Point3 & res) const;

	// getInscribedCircle();

	/**
	 * Returns true if the plan intersect the triangle IN TWO POINTS, and put those in Segment.
	 * @param p the plan to compute intersection
	 * @param intersections contains all intersection point(0,1 or 2 points)
	 * @param epsilon margin for comparison
	 */
	bool intersectIn2Points (const Plane & p, std::deque<Point3> & intersections, double epsilon=IGT_EPSILON);

	/** Compute intersection with a line.
	 * return true if intersection found. */
	bool getIntersection (const core::Line & line, core::Point3 & result, float epsilon=IGT_EPSILON) const;

	/**
	 * Return isobarycenter of the triangle
	 */
	Point3 getGravityCenter() const;

	/**
	 * Return the area of the triangle
	 */
	double getArea() const;

	/**
	 * Return the 1st point of the triangle
	 */
	Point3 A() const;

	/**
	 * Return the 2nd point of the triangle
	 */
	Point3 B() const;

	/**
	 * Return the 3rd point of the triangle
	 */
	Point3 C() const;

};


}  // namespace core
