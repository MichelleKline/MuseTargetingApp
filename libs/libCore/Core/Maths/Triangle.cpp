// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Triangle.h"
#include "Segment.h"
//#include "../Logger/LogManager.h"

namespace core {


Triangle::Triangle()
{
	addVertex(Point3(), 0);
	addVertex(Point3(), 1);
	addVertex(Point3(), 2);
}


Triangle::Triangle(const Point3 & p1, const Point3 & p2, const Point3 & p3)
{
	addVertex(p1, 0);
	addVertex(p2, 1);
	addVertex(p3, 2);
}


bool Triangle::getCircumscribedCircleCenter (Point3 & res) const
{
	Vector3 normal = (B() - A()) ^ (C() - A());
	// if triangle is flat
	if (normal.isNull()) {
		res = Point3(IGT_INFINITY, IGT_INFINITY, IGT_INFINITY);
		return false;
	}

	// retrieve 2 segment of the triangle
	Segment s1 (A(), B());
	Segment s2 (A(), C());
	normal.normalise();
	// compute PerpendicularBisector ("Mediatrices") of the triangle
	Line l1 = s1.getPerpendicularBisector(normal);
	Line l2 = s2.getPerpendicularBisector(normal);

	// center of Circumscribed Circle is the PerpendicularBisector intersection point.
	return l1.getIntersection(l2, res);
}


/* WILLIAM's function
   - Si le triangle ne coupe pas le plan (aucun point d'intersection), on ne fait rien et on passe au
   triangle suivant
   - S'il coupe le plan en deux points (cas d'intersection le plus courant), on ajoute le segment
   ainsi forme' a la liste des segments d'intersection.
   - Si une des aretes du triangle est confondue avec le plan, elle est le segment d'intersection
   (les deux points ajoutes sont les extremites de l'arete).
   - FIXME : Si le triangle est confondu avec le plan, on ne fait rien (les aretes seront comptees lors des
   tests des triangles voisins).
   FIXME: Si le triangle coupe le plan en 1 point : le sommet ???
*/
bool Triangle::intersectIn2Points (const Plane & p, std::deque<Point3> & intersections, double epsilon)
{
	if (vertices.size() != 3)
		return false; // should not be here
	try {
		bool intersect = false;
		int nbIntersectionVertices           = 0;

		Point3 firstVertex                   = *(vertices.begin());
		std::list<Point3>::iterator secondIt = vertices.begin();
		++secondIt;
		Point3 secondVertex                  = *secondIt;
		Point3 thirdVertex                   = vertices.back();

		if (isIn(p)) {
			intersections.push_back(firstVertex);
			intersections.push_back(secondVertex);
			intersections.push_back(thirdVertex);
			return false;  // not intersect in 2 points
		}

		Segment s1(firstVertex, secondVertex);
		if (s1.intersects(p) && ! s1.in(p)) {  // s1 intersect p
			try {

				Point3 interP = s1.at(s1.intersectionIdx(p));  // the intersection point
				intersections.push_back(interP);
				++nbIntersectionVertices;

			}
			catch(const IGTDivideByZeroErr &) {
				// should not be here, because s1 can't be parallel to p here, we it test before
				//logger::getLog()->logAPP("Error to compute intersection between a segment and a plane");
			}
		}
		Segment s2(secondVertex, thirdVertex);
		if (s2.intersects(p) && ! s2.in(p)) {
			try {

				Point3 interP = s2.at(s2.intersectionIdx(p));  // the intersection point
				intersections.push_back(interP);
				++nbIntersectionVertices;
			}
			catch(const IGTDivideByZeroErr &) {
				// should not be here, because s2 can't be parallel to p here, we test before
				//logger::getLog()->logAPP("Error to compute intersection between a segment and a plane");
			}

		}
		Segment s3(thirdVertex, firstVertex);
		if (s3.intersects(p) && ! s3.in(p)) {
			try {

				Point3 interP = s3.at(s3.intersectionIdx(p));  // the intersection point
				intersections.push_back(interP);
				++nbIntersectionVertices;
			}
			catch(const IGTDivideByZeroErr &) {
				// should not be here, because s3 can't be parallel to p here, we test before
				//logger::getLog()->logAPP("Error to compute intersection between a segment and a plane");
			}
		}

		if (nbIntersectionVertices == 2) {
			// if plane intersect the triangle on one vertex, there is 2 solutions(twice the same point), but not useful
			if (! intersections[0].isClose(intersections[1], epsilon)) {
				intersect = true;
			}
			// added by Stephanie
			else {
				intersections.pop_back();  // no need to stock a point twice
			}
		} else {
			if (nbIntersectionVertices == 3) {
				// Here the plane intersect the triangle on a segment and one vertex(point twice)
				if (intersections[0].isClose(intersections[1], epsilon)) {
					intersections.pop_front();
					intersect = true;
				} else {
					if (intersections[0].isClose(intersections[2], epsilon)) {
						intersections.pop_front();
						intersect = true;
					} else {
						if (intersections[1].isClose(intersections[2], epsilon)) {
							intersections.pop_back();
							intersect = true;
						}
					}
				}
			}
		}
		return intersect;
	}
	catch(...) {
		return false;
	}
}


bool Triangle::getIntersection (const core::Line & line, core::Point3 & result, float epsilon) const
{
	// see http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm#intersect_RayTriangle%28%29

	Vector3 u, v, n; // triangle vectors
	Vector3 w0, w;   // ray vectors
	double r, a, b;  // params to calc ray-plane intersect

	// get triangle edge vectors and plane normal
	u = B() - A();
	v = C() - A();
	n = u ^ v;
	if (n.isClose(V3_NULL)) {  // triangle is degenerate
		// try to get intersection with segments
		Segment s1(A(), B());
		Segment s2(A(), B());
		if (s1.getIntersection(line, result, epsilon))
			return true;
		else if (s2.getIntersection(line, result, epsilon))
			return true;
		else
			return false;
	}

	Vector3 dir = line.getDirection();  // ray direction vector
	w0 = line.getOrigin() - A();
	a  = -(n * w0);
	b  = n * dir;
	if (std::abs(b) < epsilon) {  // ray is parallel to triangle plane
		return false;
	}

	// get intersect point of ray with triangle plane
	r      = a / b;

	result = line.getOrigin() + r * dir;  // intersect point of ray and plane

	// is I inside T?
	double uu, uv, vv, wu, wv, D;
	uu = u * u;
	uv = u * v;
	vv = v * v;
	w  = result - A();
	wu = w * u;
	wv = w * v;
	D  = uv * uv - uu * vv;

	// get and test parametric coords
	double s, t;
	s = (uv * wv - vv * wu) / D;
	if (s < -epsilon || s > 1.0 + epsilon) // I is outside T
		return false;
	t = (uv * wu - uu * wv) / D;
	if (t < -epsilon || (s + t) > 1.0 + epsilon) // I is outside T
		return false;

	return true;  // I is in T
}


double Triangle::getArea() const
{
	Point3 firstVertex = *(vertices.begin());
	std::list<Point3>::const_iterator secondIt = vertices.begin();
	++secondIt;
	Point3 secondVertex  = *secondIt;
	Point3 thirdVertex   = vertices.back();

	double abLength      = Segment(firstVertex, secondVertex).length();
	double bcLength      = Segment(thirdVertex, secondVertex).length();
	double acLength      = Segment(thirdVertex, firstVertex).length();

	double halfPerimeter = (abLength + bcLength + acLength) / 2;
	double area          = sqrt(halfPerimeter * (halfPerimeter - abLength) * (halfPerimeter - bcLength) * (halfPerimeter - acLength));
	return area;
}


Point3 Triangle::getGravityCenter() const
{
	Point3 firstVertex = *(vertices.begin());
	std::list<Point3>::const_iterator secondIt = vertices.begin();
	++secondIt;
	Point3 secondVertex = *secondIt;
	Point3 thirdVertex  = vertices.back();

	double xCenter      = (firstVertex[0] + secondVertex[0] + thirdVertex[0]) / 3.0f;
	double yCenter      = (firstVertex[1] + secondVertex[1] + thirdVertex[1]) / 3.0f;
	double zCenter      = (firstVertex[2] + secondVertex[2] + thirdVertex[2]) / 3.0f;
	return Point3(xCenter, yCenter, zCenter);
}


Point3 Triangle::A() const
{
	return (*this)[0];
}


Point3 Triangle::B() const
{
	return (*this)[1];
}


Point3 Triangle::C() const
{
	return (*this)[2];
}


}  // namespace core
