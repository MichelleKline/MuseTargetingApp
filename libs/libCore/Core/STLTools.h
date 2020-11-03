// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef CHRONOMETER_H
#define CHRONOMETER_H

#include <string>
#include <vector>

#include "../libCore.h"

namespace core {

template<class T>
/// Remove duplicate values from specified vector.
void removeDuplicate (std::vector<T> & v)
{
	struct equal
	{
		bool operator() (const T & a, const T & b) const { return a == b; }

	} equal;

	removeDuplicate(v, equal);
}


/** Removes double values of specified vector. Predicate must contain a functor
 * which takes 2 T in parameters and returns true if they are considered as "equal":
 *
 * @code
 * struct predicate {
 *     bool operator() (const Point3 &a, const Point3 &b) { return a.isClose(b);}
 * } predicate;
 * std::vector<Point3> v(5);
 * removeDuplicate(v, predicate);
 * @endcode
 */
template<class T, class Pred>
void removeDuplicate (std::vector<T> & v, Pred & predicate)
{
	if (v.empty())
		return;

	// At any time, elements in [v.begin, itWrite[ are unique.
	// for each elements of v (itRead), find if it is in [v.begin, itWrite[.
	// if not foud, copy it in itWrite and increment itWrite.

	typename std::vector<T>::iterator writeIt = v.begin();
	++writeIt;
	typename std::vector<T>::iterator readIt  = writeIt;
	while (readIt != v.end()) {
		bool found = false;
		for (typename std::vector<T>::iterator it = v.begin(); it != writeIt; ++it) {
			if (predicate(*it, *readIt)) {
				found = true;
				break;
			}
		}

		if (! found) {
			*writeIt = *readIt;
			++writeIt;
		}
		++readIt;
	}

	v.resize(writeIt - v.begin());
}


/// Delete an element passed to operator ()
struct TGCORE_API deleteEach
{
	template <typename T> void operator() (T * & Elem) const
	{
		delete Elem;
		Elem = nullptr;
	}

	template <typename T, typename U> void operator() (std::pair<T, U *> & Elem) const
	{
		delete Elem.second;
		Elem.second = 0;
	}

};


/// Remove the extension from a file name (we suppose the extension to be the characters situated after the last "." in the string
std::string TGCORE_API removeFileExt (const std::string & fileName);

std::string TGCORE_API getFileExt (const std::string & fileName);

/**
 * Convert an object or a fundamental type to a std::string.
 */
template<typename T>
std::string toString (const T & val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}


}  // namespace core
#endif  // CHRONOMETER_H
