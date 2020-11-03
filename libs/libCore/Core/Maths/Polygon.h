// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef PolygonH
#define PolygonH

#include "../../libCore.h"
#include "Vector3.h"
// #include "Segment.h"
#include "Plane.h"
#include "BoundingBox.h"


#include <list>
#include <vector>
#include <deque>
#include <algorithm>

//class wxXmlNode;

namespace core {

struct  TGCORE_API EllipseBoundingBox
{
	Point3 upperLeft;

	Point3 upperRigth;
	Point3 lowerLeft;
	Point3 lowerRigth;
};

// forward declare
class Triangle;

/**
 * @brief Polygon is a tool to represent a closed piece of plan.
 *
 * Polygon is a list of points in a plane.
 */
class TGCORE_API Polygon
{

public:
	typedef std::list<Point3> Vertices;  // Points container ordered

	friend TGCORE_API std::ostream & operator<< (std::ostream &, const Polygon &);

	friend TGCORE_API std::istream & operator>> (std::istream &, Polygon &);

	/**
	 * Default constructor.<br>
	 * Set default values
	 */
	Polygon() { }

	/**
	 * Default constructor.<br>
	 * Set n default values
	 */
	explicit Polygon(int n);

	/**
	 * Constructor
	 */
	explicit Polygon(const Vertices & pts);  // points are sorted, cannot modify this list later

	/**
	 * Constructor from 4 points(upperLeft, lowerleft, upperRigth and lowerRigth) to get an ellipse sampled in nSeg segment
	 */
	Polygon(const EllipseBoundingBox &, int nSeg);

	/**
	 * Copy constructor.<br>
	 * Nothing special.
	 */
	Polygon(const Polygon &);

	/**
	 * operator =.<br>
	 * Nothing special.
	 */
	Polygon & operator= (const Polygon &);

	/**
	 * operator [].<br>
	 * Nothing special.
	 */
	Point3 & operator[] (int index);

	/**
	 * operator [] const.<br>
	 * Nothing special.
	 */
	const Point3 & operator[] (int index) const;  // avoid because there is a loop on the list of points

	size_t size() const { return vertices.size(); }

	void resize (int n);  // {if (n <= 0) points.clear(); else  points.resize(n);}

	/**
	 * Compute and returns the Surface of the Polygon
	 */
	float getArea() const;

	/**
	 * Compute and returns the Perimeter of the Polygon
	 */
	float getPerimeter() const;

	/**
	 * Winding Number test for a point in a polygon.
	 * Returns wn = the winding number (=0 only if P is outside polygon).
	 */
	bool isIn (const Point3 &) const;

	/**
	 * Return true if the segment is in the polygon
	 */
	bool isIn (const Segment &) const;


	/**
	 * Returns true if the Polygon is in the Plane.
	 */
	bool isIn (const Plane &, float epsilon=IGT_EPSILON) const;

	/**
	 * Returns the list of intersection Points.
	 * @param plane the plan to compute intersection
	 */

	std::vector<Point3> getIntersection (const Plane & plane) const;

	/**
	 * Returns points ordered of Polygon.
	 */
	const Vertices & getVertices() const { return vertices; }

	/**
	 * operator ==.<br>
	 * Nothing special.
	 */
	bool operator== (const Polygon &) const;

	/**
	 * operator !=.<br>
	 * Nothing special.
	 */
	bool operator!= (const Polygon &) const;

	/**
	 * Checks if two Polygons are close.
	 */
	bool isClose (const Polygon &, float epsilon=IGT_EPSILON);

	/**
	 * Add new vertex at position index
	 */
	void addVertex (const Point3 & p, int index);

	/**
	 * Delete vertex at position index
	 */
	void deleteVertex (int index);

	/**
	 * Delete the vertex p.
	 */
	void deleteVertex (const Point3 & p, float epsilon=IGT_EPSILON);

	/**
	 * Replace the vertex oldP by newP.
	 */
	void replaceVertex (const Point3 & oldP, const Point3 & newP, float epsilon=IGT_EPSILON);

	/**
	 * Replaceall the vertices of polygon.List is cleared.
	 */
	void deleteAllVertices();

	/**
	 * Returns the index in the list of vertices of the vertex @em v.
	 */
	int getIndex (const Point3 & v, float epsilon=IGT_EPSILON) const;

	/**
	 * Returns true if the Pointv belong to the Polygon vertices.
	 */
	bool isInPolygonVertices (const Point3 & v, float epsilon=IGT_EPSILON) const;

	/** Return a vector of triangle, result of the triangulation of the polygon created by points
	 * Be carrefull : parameters "points" must not be "periodic"(first element and last one have to be different)
	 * (Not optimized function)
	 */
	std::vector<Triangle> triangulate (const std::list<Point3> & points) const;

	// float							getOrientedAngle (const Point3& prev, const Point3& current, const Point3& next)const;

	/** Reverse the order of vertices.*/
	void reversePoints();

	bool isConvexPoint (const std::vector<Point3> & points, const Point3 & prev, const Point3 & next) const;

	bool isEar (const std::vector<Point3> & points, const Point3 & currentPt) const;

	/** Get the gravity center of the polygon.
	 * Function is very slow.
	 */
	virtual Point3 getGravityCenter() const;

	/**
	 * Returns the Center of the polygon bounding box.
	 * Be carrefull, the center of bounding box is not always in the same plane of polygon
	 * we return the projection of the center in the plane of polygon.
	 */
	virtual Point3 getBoundingBoxCenter() const;

	/**
	 * Returns the bounding box of the polygon.
	 * @return the bounding box of the polygon (only the 3 first dimensions are relevant).
	 */
	virtual BoundingBox getBoundingBox() const;

	/**
	 * Returns the bounding rectangle in the same plan as the plan of the polygon in the coordinate system (Point3(0,0,0),u,v).
	 * @param u computes the vector u, used to loop in the bounding box
	 * @param v computes the vector v, used to loop in the bounding box
	 * @return the bounding/3D oriented rectangle in 2D of the plan of the polygon .
	 */
	BoundingBox getBoundingRectangle (core::Vector3 & u, core::Vector3 & v) const;

	/**Returns the normal of the polygon plane(not oriented)
	 */
	bool getNormal (Vector3 & normal) const;

	/**Returns the normal with an orientation depending on the polygon points order
	 */
	bool getOrientedNormal (Vector3 & normal) const;


	// virtual wxXmlNode*				exportToXML			() const;

	/**
	 * Appends the polygon to file in XML format (fastest than wxWidgets XML).
	 */
	//void appendToStream (std::ofstream & file) const;

	//virtual void loadFromXmlNode (wxXmlNode *);

protected:
	/** List ordered of all points  */
	Vertices vertices;
};


}  // namespace core
#endif  // PolygonH
