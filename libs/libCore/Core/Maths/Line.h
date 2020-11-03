// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef __LINE_H_
#define __LINE_H_

#include "../../libCore.h"
#include "Vector3.h"

namespace core {

class Segment;

/**
 * @brief Modelize an infinite line defined by a point (origin) and a vector (direction).
 */
class TGCORE_API Line
{
public:
	/**
	 * Default constructor. Build line with (0, 0, 0) as origin and (1, 0, 0) as direction.
	 */
	Line();

	/**
	 * Constructor
	 *
	 * @param origin_ origin of the line
	 * @param direction_ director vector of the line. If this vector is null, throw an IGTInvalidParameterErr.
	 */
	Line(const Point3 & origin_, const Vector3 & direction_);

	/**
	 * Return the origin of the line
	 */
	inline Point3 getOrigin() const { return origin; }

	/**
	 * Set the origin of the line
	 */
	inline void setOrigin (const Point3 & origin_) { origin = origin_; }

	/**
	 * Return the direction of the line
	 */
	inline Vector3 getDirection() const { return direction; }

	/**
	 * Set the direction of the line.
	 * @warning Direction vector can't be null.
	 * @throw throwIGTInvalidParameterErr if the direction is null
	 */
	inline void setDirection (const Vector3 & direction_) { if (direction.isNull()) { throw IGTInvalidParameterErr("Line", "Director vector of a line can't be null"); } else { direction = direction_; } }

	/**
	 * Assuming lines are coplanar, return the intersection between this line and specified line.
	 * If no intersections, return false and set the result point to Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY).
	 * @param line The line to intersect with.
	 * @param point The result intersection.
	 * @param epsilon A tolerance over "coplanarity" of lines. This is an arbitrary tolerance that does not
	 * represent any geometric value, and is here to avoid rounding issues. if 2 lines does not intersect
	 * whereas they should, try to increase it.
	 */
	bool getIntersection (const Line & line, Point3 & point, double epsilon=IGT_EPSILON) const;

	/**
	 * Return true if the point is include by the line
	 */
	bool include (const Point3 & point, double epsilon=IGT_EPSILON) const;

	/**
	 * Project the point on the line
	 */
	Point3 getProjection (const Point3 & point) const;

	/**
	 * Return true if the 2 lines are mathematically equals
	 */
	bool isEquivalent (const Line & line, double epsilon=IGT_EPSILON) const;

	/** return the (or "a" if lines are parallels) common perpendicular segment of 2 lines.
	 * 1st segment.from is in this line. segment.to is in specified line. */
	Segment getPerpendicularSegment (const Line & line) const;

	/// return distance between line and a point
	double distance (const core::Point3 & point) const;

	/// return distance between 2 lines (this correspond to the length of perpendicular segment)
	double distance (const Line & line) const;

	/** return distance between line and segment:
	 * perpendicularSegment between line and segment's line is computed.
	 * If perpendicularSegment.to doesn't belong to segment, the return distance is the min
	 * of distance from segment.from to line and segment.to to line. */
	double distance (const Segment & segment) const;

	/// Destructor. Nothing special.
	~Line();

protected:
	/// The origin of the line
	Point3 origin;

	/// The director vector of the line. Can't be null.
	Vector3 direction;
};


}  // namespace core
#endif  // __LINE_H_
