// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef BoundingBoxH
#define BoundingBoxH
#include<algorithm>
#include "../../libCore.h"
#include "../CoreExceptions.h"
#include "Vector4.h"


namespace core {
/**
 * @brief A geometrical aligned bounding box with two Points: lowerBound and upperBound.
 * The fourth coordinate is not used yet and always set to zero.
 */
class TGCORE_API BoundingBox
{
	// I/O
	friend TGCORE_API std::ostream & operator<< (std::ostream &, const BoundingBox &);

	friend TGCORE_API std::istream & operator>> (std::istream &, BoundingBox &);

public:
	/// Constructor.
	/// @param lowerBound_ the lower bound of the bounding box,
	/// @param upperBound_ the upper bound of the bounding box.
	BoundingBox(const Point4 & lowerBound_, const Point4 & upperBound_);
	/// Default constructor. Creates an empty bounding box.
	BoundingBox();
	/// Copy constructor.
	BoundingBox(const BoundingBox &);
	/// Assignment operator.
	BoundingBox & operator= (const BoundingBox &);

	/// Destructor. Nothing special.
	~BoundingBox();

	/// Returns true if the box is empty (upperB !> lowerB)
	bool isEmpty() const;

	/// Returns the lower bound of the bounding box.
	const Point4 & getLowerBound() const { return lowerBound; }

	/// Returns the upper bound of the bounding box.
	const Point4 & getUpperBound() const { return upperBound; }

	/// Returns whether the given point inside the bounding box.
	inline bool isInBox (const Point4 & p) const;

	/// Returns whether the two BoundingBox are equals.
	inline bool operator== (const BoundingBox & bb2) const;

private:
	Point4 lowerBound;
	Point4 upperBound;
};


// ---------------------------------------------------------------------------
// Functions

/// Computes the intersection of two bounding boxes (The fourth coordinate is not used and always set to zero.).
TGCORE_API BoundingBox computeIntersection (const BoundingBox & b1, const BoundingBox & b2);

/// Computes the union of the bounding boxes (The fourth coordinate is not used and always set to zero.).
TGCORE_API BoundingBox computeUnion (const BoundingBox & b1, const BoundingBox & b2);


// ---------------------------------------------------------------------------
// Inline implmentation

inline bool BoundingBox::isInBox (const Point4 & p) const
{
	return (
		p[0] >= lowerBound[0] && p[0] <= upperBound[0] &&
		p[1] >= lowerBound[1] && p[1] <= upperBound[1] &&
		p[2] >= lowerBound[2] && p[2] <= upperBound[2] &&
		p[3] >= lowerBound[3] && p[3] <= upperBound[3]
	);
}


inline bool BoundingBox::operator== (const BoundingBox & bb2) const
{
	return (lowerBound.isClose(bb2.getLowerBound()) &&
	        upperBound.isClose(bb2.getUpperBound()));
}


};  // namespace core
#endif // ifndef BoundingBoxH
