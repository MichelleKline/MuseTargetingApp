// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Polygon.h"
#include "Triangle.h"
#include "Segment.h"
#include "../Tools.h"
#include "Trihedron.h"
//#include <wx/xml/xml.h>
#include <fstream>
//#include "../Logger/LogManager.h"

namespace core {

Polygon::Polygon(int n)
{
	for (int i = 0; i < n; ++i) {
		vertices.push_back(Point3());
	}
}


Polygon::Polygon(const Vertices & pts)
{
	vertices.clear();
	for (Vertices::const_iterator it = pts.begin(); it != pts.end(); ++it) {
		vertices.push_back(*it);
	}
}


Polygon::Polygon(const EllipseBoundingBox & ellipse, int nSeg)
{

	Point3 center = Vector3(ellipse.upperLeft + ellipse.lowerRigth) / 2.0f;
	Vector3 v1    = ellipse.upperRigth - ellipse.upperLeft; // x increase left to rigth
	Vector3 v2    = ellipse.upperLeft - ellipse.lowerLeft;  // y increase bottom to up
	Vector3 v3    = v1 ^ v2;
	if (v3.length() == 0)
		return; // empty polygon

	// Compute all points in a plan, transform points in new trihedron
	core::Trihedron trihedron;
	trihedron = core::Trihedron(center, v1.normalise(), v2.normalise(), v3.normalise());


	Point3 newUL  = trihedron.xformFrom(core::Trihedron(), ellipse.upperLeft);
	Point3 newLR  = trihedron.xformFrom(core::Trihedron(), ellipse.lowerRigth);

	float radiusA = abs((newUL[0] - newLR[0]) / 2.0f);
	float radiusB = abs((newUL[1] - newLR[1]) / 2.0f);
	if (radiusA == 0 || radiusB == 0)
		return; // empty polygon


	// compute coord and transform the result on the ellipse trihedron
	for (int i = 0; i < nSeg; ++i) {
		float x = radiusA * sin((double(i) / double(nSeg)) * (IGT_PI * 2.0));
		float y = radiusB * cos((double(i) / double(nSeg)) * (IGT_PI * 2.0));
		vertices.push_back(trihedron.xformTo(core::Trihedron(), Point3(x, y, 0.0f)));
	}
}


Polygon::Polygon(const Polygon & other)
{
	vertices.clear();
	for (Vertices::const_iterator it = other.vertices.begin(); it != other.vertices.end(); ++it) {
		vertices.push_back(*it);
	}
}


Polygon & Polygon::operator= (const Polygon & other)
{
	if (this == &other)
		return *this;
	vertices.clear();
	for (Vertices::const_iterator it = other.vertices.begin(); it != other.vertices.end(); ++it) {
		vertices.push_back(*it);
	}
	return *this;
}


void Polygon::resize (int n)
{
	if (n < 0)
		vertices.clear();
	else
		vertices.resize(n);
}


float Polygon::getArea() const
{
	// Use vector here, easier for random acces
	std::vector<Point3> verticesOrdered;
	for (Vertices::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		verticesOrdered.push_back(*it);
	}
	////Stokes
	float surface           = 0.0;
	unsigned int nbVertices = (unsigned int)(verticesOrdered.size());
	float * DX = new float[nbVertices];
	float * DY = new float[nbVertices];
	for (unsigned int i = 0; i < nbVertices; ++i) {
		unsigned int a = (i + 1) % nbVertices;
		unsigned int b = (i + nbVertices - 1) % nbVertices;
		if (a > nbVertices || b > nbVertices) {  // Shoult not be here
			DX[i] = 0;
			DY[i] = 0;
			continue;
		}
		DX[i] = (verticesOrdered[a][0] - verticesOrdered[b][0]) / 2;
		DY[i] = (verticesOrdered[a][1] - verticesOrdered[b][1]) / 2;
	}

	for (unsigned int j = 0; j < nbVertices; ++j) {
		surface += (verticesOrdered[j][0] * DY[j] - verticesOrdered[j][1] * DX[j]);
	}
	delete[] DX;
	delete[] DY;
	return abs(surface / 2);
}


float Polygon::getPerimeter() const
{
	float perimeter = 0.0f;
	if (vertices.size() < 3) // not a polygon
		return 0.0f;
	for (Vertices::const_iterator it = vertices.begin(); it != vertices.end();) {
		Point3 p = *it;
		++it;
		if (it == vertices.end()) {
			Point3 firstVertex = *(vertices.begin());
			Vector3 v          = firstVertex - p;
			perimeter += v.length();
			break;
		} else {
			Point3 NextV = *it;
			Vector3 v    = NextV - p;
			perimeter += v.length();
		}
	}
	return perimeter;
}


float isLeft (std::pair<Point3, Point3> segment, Point3 p)
{
	return ((segment.second[0] - segment.first[0]) * (p[1] - segment.first[1]) - (p[0] - segment.first[0]) * (segment.second[1] - segment.first[1]));
}


bool Polygon::isIn (const Point3 & p) const
{
	if (vertices.size() < 3)
		return false;
	if (isInPolygonVertices(p))
		return true;
	int wn = 0;

	std::list<Point3>::const_iterator itPt = vertices.begin();
	Point3 origin = *itPt;
	++itPt;
	Point3 p1     = *itPt;
	++itPt;
	Point3 p2     = *itPt;
	Vector3 v1(p1 - origin);
	Vector3 v2(p2 - origin);
	core::Segment s1(p1, origin);
	core::Segment s2(p2, origin);

	while (s1.isParallel(s2)) {  // find the 2 vector wich are not parrallel to compute normal
		++itPt;

		if (itPt == vertices.end()) {
			// here all points are on the same line
			break;
		} else {
			Point3 thirdVertex = *itPt;
			s2 = core::Segment(thirdVertex, origin);
			v2 = Vector3(thirdVertex - origin);
		}

	}

	Vector3 normale = v1 ^ v2;
	if (normale == Point3()) {  // polygon line(v1 and v2 are parallel)
		// FIXME : take the segment the longer, not v1 and v2
		if (! Segment(origin, p1).includes(p) && ! Segment(origin, p2).includes(p))
			return false;
		else
			return true;
	}
	core::Plane polygonPlane(normale.normalise(), origin);
	if (! polygonPlane.includes(p))
		return false;                           // important, test before projection

	// projection of the plane and the point, on the 2D plane the nearest
	int coordToIgnore = (abs(normale[0]) <= abs(normale[1])) ? 1 : 0;
	if (abs(normale[coordToIgnore]) <= abs(normale[2]))
		coordToIgnore = 2;

	Point3 newP;  // projection of p on plan
	if (coordToIgnore == 0)
		newP = Point3(p[1], p[2], 0.0f);
	if (coordToIgnore == 1)
		newP = Point3(p[0], p[2], 0.0f);
	if (coordToIgnore == 2)
		newP = Point3(p[0], p[1], 0.0f);

	std::list<Point3> newVertices;  // vertices Projected
	for (std::list<Point3>::const_iterator it2 = vertices.begin(); it2 != vertices.end(); ++it2) {
		Point3 newVertex;
		if (coordToIgnore == 0)
			newVertex = Point3((*it2)[1], (*it2)[2], 0.0f);
		if (coordToIgnore == 1)
			newVertex = Point3((*it2)[0], (*it2)[2], 0.0f);
		if (coordToIgnore == 2)
			newVertex = Point3((*it2)[0], (*it2)[1], 0.0f);
		newVertices.push_back(newVertex);
	}

	/////////////////////////////////
	// Method of change frame (too expensive)

	// Vector3 v2Perp = normale^v1;//perpendicular to v1
	// core::Trihedron polygonTrihedron (origin, v1.normalise(), v2Perp.normalise(),normale.normalise());
	// core::Trihedron base;

	// Point3 newP = base.xformTo(polygonTrihedron, p);
	// if (newP[2] != 0) return false;

	// std::list<Point3> newVertices;//vertices in polygon plan
	// for (std::list<Point3>::const_iterator it2 = vertices.begin(); it2 != vertices.end(); ++it2)
	// {
	//	newVertices.push_back(base.xformTo(polygonTrihedron, *it2));
	// }
	///////////////////////////////////


	//// loop through all edges of the polygon
	for (Vertices::const_iterator it3 = newVertices.begin(); it3 != newVertices.end();) {
		Point3 current = *it3;
		++it3;
		Point3 next;
		if (it3 == newVertices.end())
			next = *(newVertices.begin());
		else {
			next = *it3;
		}
		Segment s(current, next);
		if (s.includes(newP) || (newP.isClose(current)) || (newP.isClose(next)))
			return true;
		if (current[1] <= newP[1]) {
			// start y <= P.y
			if (next[1] > newP[1]) {  // an upward crossing
				if (isLeft(std::make_pair(current, next), newP) > 0) // P left of edge
					++wn;                                            // have a valid up intersect
			}
		} else {
			// start y > P.y (no test needed)
			if (next[1] <= newP[1]) {  // an downward crossing
				if (isLeft(std::make_pair(current, next), newP) < 0) // P right of edge
					--wn;                                            // have a valid down intersect
			}
		}
	}
	return wn != 0;
}


bool Polygon::isIn (const Segment & s) const
{
	const int NBPOINTS = 50;
	for (float t = 0; t < 1; t += 1 / float(NBPOINTS)) {
		Point3 p = (1 - t) * s.from() + t * s.to();
		if (! isIn(p))
			return false;
	}
	return true;
}


bool Polygon::isIn (const Plane & p, float epsilon) const
{

	if (vertices.empty())
		return false;

	for (Vertices::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if (! p.includes(*it, epsilon))
			return false;
	}
	return true;
}


// we compare the order of points, and if it's the same points
bool Polygon::operator== (const Polygon & other) const
{
	std::list<Point3> newVertices, newOherVertices;

	/////delete points not neccessary(points i belonging to segment [i-1,i+1])
	Point3 prev, next;

	// check if points are belonging to segment
	for (std::list<Point3>::const_iterator currentIt = vertices.begin(); currentIt != vertices.end(); ++currentIt) {
		Point3 curr = *currentIt;
		std::list<Point3>::const_iterator prevIt = currentIt;
		std::list<Point3>::const_iterator nextIt = currentIt;
		++nextIt;

		if (currentIt == vertices.begin()) {
			prevIt = --vertices.end();
			prev   = *(prevIt);
		} else {
			--prevIt;
			prev = *(prevIt);
		}
		if (nextIt == vertices.end()) {
			next = *(vertices.begin());
		} else
			next = *nextIt;
		core::Segment s(prev, next);
		if (! s.includes(curr))
			newVertices.push_back(curr);
	}

	for (std::list<Point3>::const_iterator currentIt = other.vertices.begin(); currentIt != other.vertices.end(); ++currentIt) {
		Point3 curr = *currentIt;
		std::list<Point3>::const_iterator prevIt = currentIt;
		std::list<Point3>::const_iterator nextIt = currentIt;
		++nextIt;

		if (currentIt == other.vertices.begin()) {
			prevIt = --other.vertices.end();
			prev   = *(prevIt);
		} else {
			--prevIt;
			prev = *(prevIt);
		}
		if (nextIt == other.vertices.end()) {
			next = *(other.vertices.begin());
		} else
			next = *nextIt;
		core::Segment s(prev, next);
		if (! s.includes(curr))
			newOherVertices.push_back(curr);
	}

	if (newVertices.size() != newOherVertices.size())
		return false;
	if (newVertices.empty() && newOherVertices.empty())
		return true; // both are null polygon
	// first we find the first point have in common
	Vertices::const_iterator it      = newVertices.begin();
	Vertices::const_iterator itOther = newOherVertices.begin();
	for (; itOther != newOherVertices.end(); ++itOther) {
		if ((*it) == (*itOther))
			break;
	}
	if (itOther == newOherVertices.end())
		return false;                                   // no common point
	// the first point of this is equal to the itother point in  other
	int testOtherdirection = false;
	Vertices::const_iterator itOtherCopy = itOther;
	// In this loop we folow the order of the list of point of this
	for (it = newVertices.begin(); it != newVertices.end(); ++it) {
		if (itOtherCopy == newOherVertices.end())
			itOtherCopy = newOherVertices.begin();
		if ((*it) != (*itOtherCopy))
			testOtherdirection = true;
		++itOtherCopy;
	}
	if (testOtherdirection) {
		Vertices::const_iterator itOtherCopy2 = itOther;
		// In this loop we folow the inverse order of the list of point of this
		// exemple for the 2 equal polygon :abcd and adcb
		for (Vertices::iterator it2 = newVertices.begin(); it2 != newVertices.end(); ++it2) {
			if ((*it2) != (*itOtherCopy2))
				return false;
			if (itOtherCopy2 == newOherVertices.begin())
				itOtherCopy2 = --newOherVertices.end();
			else
				--itOtherCopy2;
		}
	}
	return true;
}


bool Polygon::isClose (const Polygon & other, float epsilon)
{
	std::list<Point3> newVertices, newOherVertices;

	/////delete points not neccessary(points i belonging to segment [i-1,i+1])
	Point3 prev, next;

	// check if points are belonging to segment
	for (std::list<Point3>::const_iterator currentIt = vertices.begin(); currentIt != vertices.end(); ++currentIt) {
		Point3 curr = *currentIt;
		std::list<Point3>::const_iterator prevIt = currentIt;
		std::list<Point3>::const_iterator nextIt = currentIt;
		++nextIt;

		if (currentIt == vertices.begin()) {
			prevIt = --vertices.end();
			prev   = *(prevIt);
		} else {
			--prevIt;
			prev = *(prevIt);
		}
		if (nextIt == vertices.end()) {
			next = *(vertices.begin());
		} else
			next = *nextIt;
		core::Segment s(prev, next);
		if (! s.includes(curr, epsilon))
			newVertices.push_back(curr);
	}

	for (std::list<Point3>::const_iterator currentIt = other.vertices.begin(); currentIt != other.vertices.end(); ++currentIt) {
		Point3 curr = *currentIt;
		std::list<Point3>::const_iterator prevIt = currentIt;
		std::list<Point3>::const_iterator nextIt = currentIt;
		++nextIt;

		if (currentIt == other.vertices.begin()) {
			prevIt = --other.vertices.end();
			prev   = *(prevIt);
		} else {
			--prevIt;
			prev = *(prevIt);
		}
		if (nextIt == other.vertices.end()) {
			next = *(other.vertices.begin());
		} else
			next = *nextIt;
		core::Segment s(prev, next);
		if (! s.includes(curr, epsilon))
			newOherVertices.push_back(curr);
	}

	if (newVertices.size() != newOherVertices.size())
		return false;
	if (newVertices.empty() && newOherVertices.empty())
		return true; // both are null polygon
	// first we find the first point have in common
	Vertices::const_iterator it      = newVertices.begin();
	Vertices::const_iterator itOther = newOherVertices.begin();
	for (; itOther != newOherVertices.end(); ++itOther) {
		if ((*it).isClose(*itOther, epsilon))
			break;
	}
	if (itOther == newOherVertices.end())
		return false;                                   // no common point
	// the first point of this is equal to the itother point in  other
	int testOtherdirection = false;
	Vertices::const_iterator itOtherCopy = itOther;
	// In this loop we folow the order of the list of point of this
	for (it = newVertices.begin(); it != newVertices.end(); ++it) {
		if (itOtherCopy == newOherVertices.end())
			itOtherCopy = newOherVertices.begin();
		if (! (*it).isClose(*itOtherCopy, epsilon))
			testOtherdirection = true;
		++itOtherCopy;
	}
	if (testOtherdirection) {
		Vertices::const_iterator itOtherCopy2 = itOther;
		// In this loop we folow the inverse order of the list of point of this
		// exemple for the 2 equal polygon :abcd and adcb
		for (Vertices::iterator it2 = newVertices.begin(); it2 != newVertices.end(); ++it2) {
			if (! (*it2).isClose(*itOtherCopy2, epsilon))
				return false;
			if (itOtherCopy2 == newOherVertices.begin())
				itOtherCopy2 = --newOherVertices.end();
			else
				--itOtherCopy2;
		}
	}
	return true;
}


bool Polygon::operator!= (const Polygon & other) const
{
	return ! (*this == other);
}


void Polygon::addVertex (const Point3 & p, int index)
{
	if (index <= 0) {
		vertices.push_front(p);
		return;
	}
	if (index >= int(vertices.size())) {
		vertices.push_back(p);
		return;
	}
	std::list<Point3>::iterator it = vertices.begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	if (it == vertices.end())
		vertices.push_back(p);
	else
		vertices.insert(it, p);
}


void Polygon::deleteVertex (int index)
{
	if (index < 0 || index >= int(vertices.size()))
		return;
	std::list<Point3>::iterator it = vertices.begin();
	for (int i = 0; i < index; ++i) {
		++it;
	}
	if (it != vertices.end())
		vertices.erase(it);
}


void Polygon::deleteVertex (const Point3 & p, float epsilon)
{
	for (std::list<Point3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if ((*it).isClose(p, epsilon)) {
			vertices.erase(it);
			return;
		}
	}
}


void Polygon::replaceVertex (const Point3 & oldP, const Point3 & newP, float epsilon)
{

	for (std::list<Point3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if ((*it).isClose(oldP, epsilon)) {
			*it = newP;
			// it = vertices.erase(it);
			// vertices.insert(it, newP);
			// std::replace(it, ++it, oldP, newP);
			return;
		}
	}
}


void Polygon::deleteAllVertices()
{
	vertices.clear();
}


std::ostream & operator<< (std::ostream & out, const core::Polygon & poly)
{
	out << "Points " << int(poly.vertices.size()) << std::endl;
	for (std::list<Point3>::const_iterator it = poly.vertices.begin(); it != poly.vertices.end(); ++it) {
		out << "P " << (*it) << std::endl;
	}
	return out;
}


std::istream & operator>> (std::istream & is, Polygon & poly)
{
	std::string stuff;
	int nbVertices = 0;
	while (stuff.find("Points") == std::string::npos && is.good())
		is >> stuff;
	is >> nbVertices;
	if (! is.good())
		throw IGTException("Polygon cannot be loaded.");
	// is.seekg (0);
	// while (stuff.find("Points") == std::string::npos && is.good()) is >> stuff;
	// is >> stuff;
	for (int i = 0; i < nbVertices; ++i) {
		std::string dump;
		while (dump.find("P") == std::string::npos && is.good())
			is >> dump;
		if (! is.good())
			throw IGTException("Polygon: cannot load points of file.");
		Point3 p;
		is >> p;
		poly.vertices.push_back(p);
	}
	return is;
}


Point3 & Polygon::operator[] (int index)
{
	int i = 0;
	for (Vertices::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if (i == index)
			return *it;
		++i;
	}
	throw IGTIndexOutOfBounds("Polygon", index, int(vertices.size()));
}


const Point3 & Polygon::operator[] (int index) const
{
	int i = 0;
	for (Vertices::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if (i == index)
			return *it;
		++i;
	}
	throw IGTIndexOutOfBounds("Polygon", index, int(vertices.size()));
}


int Polygon::getIndex (const Point3 & v, float epsilon) const
{
	int index = 0;
	for (Vertices::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if ((*it).isClose(v, epsilon))
			return index;
		++index;
	}
	return -1;
}


bool Polygon::isInPolygonVertices (const Point3 & v, float epsilon) const
{

	for (Vertices::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		if ((*it).isClose(v, epsilon))
			return true;
	}
	return false;
}


Point3 Polygon::getGravityCenter() const
{
	std::list<Point3> verticesCopy;
	for (std::list<Point3>::const_iterator it = vertices.begin(); it != vertices.end(); ++it) {
		verticesCopy.push_back(*it);
	}
	Point3 firstVertex = *(verticesCopy.begin());
	Point3 lastVertex  = *(--vertices.end());
	if (firstVertex == lastVertex)
		verticesCopy.pop_back(); // even if it's periodic, this equality will be a problem to triangulate

	std::vector<Triangle> triangles = triangulate(verticesCopy);
	Point3 center;
	float totalArea = getArea();
	if (totalArea == 0)
		return center; // throw exception
	for (std::vector<Triangle>::iterator it = triangles.begin(); it != triangles.end(); ++it) {
		center += (it->getArea() / totalArea) * it->getGravityCenter();
	}
	return center;
}


Point3 Polygon::getBoundingBoxCenter() const
{
	BoundingBox bb = getBoundingBox();
	Point3 lowerBound(bb.getLowerBound()[0], bb.getLowerBound()[1], bb.getLowerBound()[2]);
	Point3 upperBound(bb.getUpperBound()[0], bb.getUpperBound()[1], bb.getUpperBound()[2]);

	Point3 center = (upperBound + lowerBound) / 2.0;
	Vector3 normal;
	if (! getNormal(normal))
		return center;

	core::Plane polyPlane(normal, vertices.front());
	return polyPlane.projection(center);  // center belong to the polygon plane
}


BoundingBox Polygon::getBoundingBox() const
{
	if (vertices.empty())
		return BoundingBox();

	Point3 upperBound = *vertices.begin();
	Point3 lowerBound = *vertices.begin();

	for (std::list<Point3>::const_iterator it = ++vertices.begin(); it != vertices.end(); ++it) {
		if (lowerBound[0] > (*it)[0])
			lowerBound[0] = (*it)[0];
		if (lowerBound[1] > (*it)[1])
			lowerBound[1] = (*it)[1];
		if (lowerBound[2] > (*it)[2])
			lowerBound[2] = (*it)[2];

		if (upperBound[0] < (*it)[0])
			upperBound[0] = (*it)[0];
		if (upperBound[1] < (*it)[1])
			upperBound[1] = (*it)[1];
		if (upperBound[2] < (*it)[2])
			upperBound[2] = (*it)[2];
	}

	return BoundingBox(Point4(lowerBound[0], lowerBound[1], lowerBound[2], 0.0),
		Point4(upperBound[0], upperBound[1], upperBound[2], 0.0));
}


BoundingBox Polygon::getBoundingRectangle (core::Vector3 & u, core::Vector3 & v) const
{

	if (vertices.empty())
		return BoundingBox();                  // less than 2 points
	Point3 firstVertex = *(vertices.begin());
	std::list<Point3>::const_iterator secondIt = vertices.begin();
	++secondIt;
	if (secondIt == vertices.end())
		return BoundingBox();                             // less than 2 points
	Point3 secondVertex          = *secondIt;
	core::Vector3 uInPolygonPlan = Vector3(secondVertex - firstVertex);
	u = uInPolygonPlan.normalise();
	core::Vector3 normal;
	getNormal(normal);

	core::Vector3 vInPolygonPlan = (normal ^ uInPolygonPlan).normalise();
	v = vInPolygonPlan.normalise();


	// Projection on u and u to find the bb in the plan (u,v)
	float minU = 0;
	float minV = 0;
	float maxU = 0;
	float maxV = 0;

	for (std::list<Point3>::const_iterator it = ++vertices.begin(); it != vertices.end(); ++it) {  // todo avoid second too point
		Point3 currentVertex   = *it;
		Vector3 currentSegment = currentVertex - firstVertex;

		// compute composant on Uand compare with min and max
		float projectionValueOnU = currentSegment * u;
		if (projectionValueOnU < minU)
			minU = projectionValueOnU;
		else if (projectionValueOnU > maxU)
			maxU = projectionValueOnU;
		// compute composant on V and compare with min and max
		float projectionValueOnV = currentSegment * v;
		if (projectionValueOnV < minV)
			minV = projectionValueOnV;
		else if (projectionValueOnV > maxV)
			maxV = projectionValueOnV;
	}
	core::Point3 lowerBound = minU * u + minV * v + firstVertex;
	core::Point3 upperBound = maxU * u + maxV * v + firstVertex;

	return BoundingBox(Point4(lowerBound[0], lowerBound[1], lowerBound[2], 0.0),
		Point4(upperBound[0], upperBound[1], upperBound[2], 0.0));
}


//
// float Polygon::getOrientedAngle (const Point3& prev, const Point3& current, const Point3& next)const
// {
//	const double MIN_LENGTH = 0.001;
//	float angle = 0.0f;
//
//	Vector3 firstLine = prev - current;
//	float firstLineLength = firstLine.length();
//
//	if (firstLineLength > MIN_LENGTH)
//	{
//		firstLine /= firstLineLength;
//		Vector3 secondLine = next - current;
//		float secondLineLength = secondLine.length();
//		if (secondLineLength > MIN_LENGTH)
//		{
//			secondLine /= secondLineLength;
//			angle = static_cast<float>(core::radToDeg(std::acos(firstLine * secondLine)));
//		}
//	}
//	Vector3 currPrev = prev - current;
//	Vector3 currNext = next - current;
//	Vector3 v = currPrev^currNext;
//	if (v[2] != 0)
//		angle *= v[2]/abs(v[2]); //we want the sign of sinus
//
//	return angle;
// }


void Polygon::reversePoints()
{
	vertices.reverse();
}


bool Polygon::isEar (const std::vector<Point3> & points, const Point3 & currentPt) const
{
	Point3 prev, next;
	std::vector<Point3>::const_iterator currentPtIt = std::find(points.begin(), points.end(), currentPt);
	if (currentPtIt == points.end())
		return false;

	std::vector<Point3>::const_iterator prevPtIt = currentPtIt;
	std::vector<Point3>::const_iterator nextPtIt = currentPtIt;
	++nextPtIt;

	if (currentPtIt == points.begin())
		prev = points[points.size() - 1];
	else {
		--prevPtIt;
		prev = *(prevPtIt);
	}
	if (nextPtIt == points.end())
		next = points[0];
	else
		next = *(nextPtIt);

	if (isIn(Segment(prev, next))) {  // the segment belong completely inside polygon
		// if (getOrientedAngle(prev, currentPt, next) < 0)// if true =>convexPoint, can be an ear
		core::Triangle t(prev, currentPt, next);
		std::vector<Point3>::const_iterator it2;
		for (it2 = points.begin(); it2 != points.end(); ++it2) {
			if (! t.isInPolygonVertices(*it2) && t.isIn(*it2)) {  // t does not contains other point in the triangle
				t.isIn(*it2);
				return false;
			}
		}
		if (it2 == points.end())
			return true;
	}
	return false;
}


bool Polygon::getNormal (Vector3 & normal) const
{
	if (vertices.empty())
		return false;                  // less than 3 points
	Point3 firstVertex = *(vertices.begin());
	std::list<Point3>::const_iterator secondIt = vertices.begin();
	++secondIt;
	if (secondIt == vertices.end())
		return false;                             // less than 3 points
	Point3 secondVertex = *secondIt;
	++secondIt;
	if (secondIt == vertices.end())
		return false;                             // less than 3 points
	Point3 thirdVertex = *secondIt;

	Vector3 v1(secondVertex - firstVertex);
	Vector3 v2(thirdVertex - firstVertex);
	core::Segment s1(secondVertex, firstVertex);
	core::Segment s2(thirdVertex, firstVertex);
	while (s1.isParallel(s2)) {  // find the 2 vector which are not parallel to compute normal
		++secondIt;
		if (secondIt == vertices.end())
			return false; // here all points are on the same line
		Point3 thirdVertex2 = *secondIt;
		s2 = core::Segment(thirdVertex2, firstVertex);
		v2 = Vector3(thirdVertex2 - firstVertex);
	}
	core::Plane p(v1 ^ v2, firstVertex);

	if (! isIn(p))
		return false;          // polygon is not in a plane
	normal = p.getNormal();
	return true;
}


bool Polygon::getOrientedNormal (Vector3 & normal) const
{
	if (vertices.empty())
		return false;                  // less than 3 points
	Point3 firstVertex = *(vertices.begin());
	std::list<Point3>::const_iterator secondIt = vertices.begin();
	++secondIt;
	if (secondIt == vertices.end())
		return false;                             // less than 3 points
	Point3 secondVertex = *secondIt;
	++secondIt;
	if (secondIt == vertices.end())
		return false;                             // less than 3 points
	Point3 thirdVertex = *secondIt;

	Vector3 v1(secondVertex - firstVertex);
	Vector3 v2(thirdVertex - firstVertex);
	core::Segment s1(secondVertex, firstVertex);
	core::Segment s2(thirdVertex, firstVertex);
	while (s1.isParallel(s2)) {  // find the 2 vector wich are not parrallel to compute normal
		++secondIt;
		if (secondIt == vertices.end())
			return false; // here all points are on the same line

		Point3 thirdVertex2 = *secondIt;
		s2 = core::Segment(thirdVertex2, firstVertex);
		v2 = Vector3(thirdVertex2 - firstVertex);
	}
	core::Plane p(v1 ^ v2, firstVertex);

	if (! isIn(p))
		return false;          // polygon is not in a plane
	normal = v1 ^ v2;
	normal.normalise();
	return true;
}


std::vector<Triangle> Polygon::triangulate (const std::list<Point3> & points) const
{
	// TODO: not optimized for the moment
	// only ear are computed(not yet reflex and convex point)
	std::vector<Triangle> triangles;

	std::vector<Point3> remainingPoints;
	std::vector<Point3> earsPoints;
	int cpt = 0;
	/// if the polygon is convex, easy triangulation to do(connect one point to all others, except neighbourg)

	// prefere to work with vector to use random access
	for (std::list<Point3>::const_iterator it = points.begin(); it != points.end(); ++it, ++cpt) {
		remainingPoints.push_back(*it);
	}

	for (int i = 0; i < int(remainingPoints.size()); ++i) {
		if (isEar(remainingPoints, remainingPoints[i]))
			earsPoints.push_back(remainingPoints[i]);
	}

	while (int(remainingPoints.size()) > 3) {
		if (int(earsPoints.size()) == 0)
			return triangles; /// should not be here

		unsigned firstEarIndex = 0;
		for (unsigned i = 0; i < remainingPoints.size(); ++i) {
			if (earsPoints[0] == remainingPoints[i])
				firstEarIndex = i;
		}

		// Add the triangle with the ear to the output list of triangles.
		Point3 prevOfEar, nextOfEar;
		if (firstEarIndex == 0)
			prevOfEar = remainingPoints[remainingPoints.size() - 1];
		else
			prevOfEar = remainingPoints[firstEarIndex - 1];  // point juste before the ear

		Point3 earPt = earsPoints[0];                        // == remainingPoints[firstEarIndex];

		if (firstEarIndex == remainingPoints.size() - 1)
			nextOfEar = remainingPoints[0];
		else
			nextOfEar = remainingPoints[firstEarIndex + 1];
		triangles.push_back(core::Triangle(prevOfEar, earPt, nextOfEar));

		// Remove the vertex corresponding to the ear.
		std::vector<Point3>::iterator firstEarIterator = std::find(remainingPoints.begin(), remainingPoints.end(), earPt);
		remainingPoints.erase(firstEarIterator);


		if (int(remainingPoints.size()) == 3)
			break;

		// Removal of the ear can cause an adjacent vertex to become an ear or to stop being an ear.
		earsPoints.erase(earsPoints.begin());
		// Check the previous and the next vertex
		// if the previous point was an ear
		std::vector<Point3>::iterator earPrev = std::find(earsPoints.begin(), earsPoints.end(), prevOfEar);
		if (earPrev != earsPoints.end()) {  // if == earsPoints.end() the previous was not a ear
			// check that the previous point is still an ear
			if (! isEar(remainingPoints, prevOfEar))
				earsPoints.erase(earPrev); // prevOfEar is no longer an ear
		} else {
			// check if it can become an ear
			if (isEar(remainingPoints, prevOfEar))
				earsPoints.push_back(prevOfEar);
		}

		// if the next point was an ear
		std::vector<Point3>::iterator earNext = std::find(earsPoints.begin(), earsPoints.end(), nextOfEar);
		if (earNext != earsPoints.end()) {
			// check that the next point is still an ear
			if (! isEar(remainingPoints, nextOfEar))
				earsPoints.erase(earNext);
		} else {
			// check if it can become an ear
			if (isEar(remainingPoints, nextOfEar))
				earsPoints.push_back(nextOfEar); // nextOfEar is no longer an ear
		}
	}

	if (remainingPoints.size() == 3)
		triangles.push_back(core::Triangle(remainingPoints[0], remainingPoints[1], remainingPoints[2]));

	return triangles;
}


std::vector<Point3> Polygon::getIntersection (const Plane & plane) const
{
	std::vector<Point3> result;
	try {
		for (Vertices::const_iterator it = vertices.begin(); it != vertices.end();) {
			Point3 p = *it;
			++it;
			Point3 next;
			if (it == vertices.end())
				next = *(vertices.begin());
			else
				next = *it;

			Segment s(p, next);
			if (s.in(plane)) {
				// add the 2 points only if there are not in the vector
				std::vector<Point3>::const_iterator itFrom = std::find(result.begin(), result.end(), s.from());
				if (itFrom == result.end())
					result.push_back(s.from());

				std::vector<Point3>::const_iterator itTo = std::find(result.begin(), result.end(), s.to());
				if (itTo == result.end())
					result.push_back(s.to());
			} else {
				if (s.intersects(plane)) {
					// be carrefull double
					Point3 interP = s.at(s.intersectionIdx(plane));  // the intersection point
					std::vector<Point3>::const_iterator itInterP = std::find(result.begin(), result.end(), interP);
					if (itInterP == result.end())
						result.push_back(interP);
				}
			}
		}
	}
	catch(const IGTDivideByZeroErr &) {
		// should not be here, because s1 can't be parallel to p here, we it test before
		//logger::getLog()->logAPP("Error to compute intersection between a segment and a plane");
	}
	return result;
}


//void Polygon::loadFromXmlNode (wxXmlNode * polygonNode)
//{
//	if (polygonNode->GetName() != "polygon")
//		// return Polygon();// FIXME: should throw ?
//		return;
//	wxXmlNode * pointNode = polygonNode->GetChildren();
//	while (pointNode) {
//		Point3 p;
//		p.loadFromXmlNode(pointNode);
//		vertices.push_back(p);
//		pointNode = pointNode->GetNext();
//	}
//}


// wxXmlNode* Polygon::exportToXML() const
// {
//	wxXmlNode* polygonNode = new wxXmlNode(wxXML_ELEMENT_NODE, "polygon");
//	for (std::list<Point3>::const_iterator itP = vertices.begin(); itP != vertices.end(); ++itP)
//		polygonNode->AddChild(itP->exportToXML());
//	return polygonNode;
// }


//void Polygon::appendToStream (std::ofstream & file) const
//{
//	file << "<polygon>" << std::endl;
//	for (std::list<Point3>::const_iterator itP = vertices.begin(); itP != vertices.end(); ++itP) {
//		itP->appendToStream(file);
//	}
//	file << "</polygon>" << std::endl;
//}


};  // namespace core
