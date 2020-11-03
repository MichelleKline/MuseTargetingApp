// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "BoundingBox.h"

namespace core {


BoundingBox::BoundingBox(const Point4 & lowerBound_, const Point4 & upperBound_) :
	lowerBound(lowerBound_)
	, upperBound(upperBound_)
{ }


BoundingBox::BoundingBox() :
	lowerBound(Point4())   // to have an empty width => empty box
	, upperBound(Point4(-1.0, 0.0, 0.0, 0.0))
{ }


BoundingBox::BoundingBox(const BoundingBox & source) :
	lowerBound(source.lowerBound)
	, upperBound(source.upperBound)
{ }


BoundingBox & BoundingBox::operator= (const BoundingBox & source)
{
	if (this != &source) {
		lowerBound = source.lowerBound;
		upperBound = source.upperBound;
	}
	return *this;
}


BoundingBox::~BoundingBox()
{ }


bool BoundingBox::isEmpty() const
{
	// The fourth coordinate is not used to compare
	if (! (upperBound[0] >= lowerBound[0] && upperBound[1] >= lowerBound[1] && upperBound[2] >= lowerBound[2]))
		return true;

	return false;
}


std::ostream & operator<< (std::ostream & os, const BoundingBox & bb)
{
	os << bb.lowerBound << " " << bb.upperBound;
	return os;
}


std::istream & operator>> (std::istream & is, BoundingBox & bb)
{
	is >> bb.lowerBound >> bb.upperBound;
	return is;
}


// ---------------------------------------------------------------------------
// Functions implement

TGCORE_API BoundingBox computeIntersection (const BoundingBox & b1, const BoundingBox & b2)
{
	return BoundingBox (
		Point4 (
			std::max(b1.getLowerBound()[0], b2.getLowerBound()[0]),
			std::max(b1.getLowerBound()[1], b2.getLowerBound()[1]),
			std::max(b1.getLowerBound()[2], b2.getLowerBound()[2]),
			std::max(b1.getLowerBound()[3], b2.getLowerBound()[3])
		),
		Point4 (
			std::min(b1.getUpperBound()[0], b2.getUpperBound()[0]),
			std::min(b1.getUpperBound()[1], b2.getUpperBound()[1]),
			std::min(b1.getUpperBound()[2], b2.getUpperBound()[2]),
			std::min(b1.getUpperBound()[3], b2.getUpperBound()[3])
		)
	);
}


TGCORE_API BoundingBox computeUnion (const BoundingBox & b1, const BoundingBox & b2)
{
	return BoundingBox (
		Point4 (
			std::min(b1.getLowerBound()[0], b2.getLowerBound()[0]),
			std::min(b1.getLowerBound()[1], b2.getLowerBound()[1]),
			std::min(b1.getLowerBound()[2], b2.getLowerBound()[2]),
			std::min(b1.getLowerBound()[3], b2.getLowerBound()[3])
		),
		Point4 (
			std::max(b1.getUpperBound()[0], b2.getUpperBound()[0]),
			std::max(b1.getUpperBound()[1], b2.getUpperBound()[1]),
			std::max(b1.getUpperBound()[2], b2.getUpperBound()[2]),
			std::max(b1.getUpperBound()[3], b2.getUpperBound()[3])
		)
	);
}


};  // namespace core
