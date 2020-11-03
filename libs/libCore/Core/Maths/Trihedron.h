// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef TrihedronH
#define TrihedronH

#include "../../libCore.h"
#include "Matrix4.h"
#include "Vector3.h"

namespace core {

/**
 * @brief Trihedron is a tool used to represent a three dimensional Cartesian coordinate system.
 *
 * Trihedron is based on three vectors representing the axis of the coordinante system and a point
 * representing the origin of the coordinante system.
 *
 * The trihedron class also provides methods to transform a point between one coordinate system
 * to another one (see xformTo and xformFrom).
 */
class TGCORE_API Trihedron
{

public:
	/// Exports the trihedron to a std::ostream.
	friend TGCORE_API std::ostream & operator<< (std::ostream &, const Trihedron &);

	/// Imports a trihedron from a std::istream.
	friend TGCORE_API std::istream & operator>> (std::istream &, Trihedron &);

	/// Returns whether two Trihedron are equals.
	friend TGCORE_API bool operator== (const Trihedron &, const Trihedron &);

	/// Returns whether two Trihedron are differents.
	friend TGCORE_API bool operator!= (const Trihedron &, const Trihedron &);

	/**
	 * Default constructor.<br>
	 * Set default values: xVector is (1, 0, 0), yVector is (0, 1, 0), zVector is (0, 0, 1)	and the origin is (0, 0, 0).
	 */
	Trihedron() :
		x(Vector3(1, 0, 0)), y(Vector3(0, 1, 0)), z(Vector3(0, 0, 1)), o(Point3(0, 0, 0))
	{ }

	/**
	 * Constructor.<br>
	 * Same as the default constructor but with a custom origin.
	 */
	explicit Trihedron(const Point3 & o_) :
		x(Vector3(1, 0, 0)), y(Vector3(0, 1, 0)), z(Vector3(0, 0, 1)), o(o_)
	{ }

	/**
	 * Constructor.
	 */
	Trihedron(const Point3 & o_, const Vector3 & x_, const Vector3 & y_, const Vector3 & z_);  // Throw IGTDivideByZero if matrix determinant is 0


	/**
	 * Build a trihedron from an homogeneous inversible matrix.
	   @param m an homogeneous inversible matrix.
	   @warning The last line of the matrix must be (0, 0, 0, 1),
	   @throws IGTInvalidParameterErr otherwise.
	 */
	explicit Trihedron(const Matrix4 & m);

	/**
	 * Copy constructor.<br>
	 * Nothing special.
	 */
	Trihedron(const Trihedron &);

	/**
	 * operator =.<br>
	 * Nothing special.
	 */
	Trihedron & operator= (const Trihedron &);

	/**
	 * Sets the norm of all vectors in the trihedron to 1.
	 * @warning Throw IGTDivideByZero if one vector is null.
	 */
	inline void normalise();

	/**
	 * Returns a point corresponding to @em p transformed in the coordinate system represented by the trihedron @em newT.
	 * WARNING : p is a point, not a vector. To express a vector3 in new trihedron, use xformTo(t, Vector4) with homogeneous
	 * coordinate if 0.
	 * @param newT
	 * @param pInMe the point in the current coordinate system.
	 */
	Point3 xformTo (const Trihedron & newT, const Point3 & pInMe) const;

	/**
	 * Returns a point corresponding to @em p transformed in the coordinate system represented by
	 * the trihedron @em newT.
	 * p is expressed in homogeneous coordinates.
	 * @param newT
	 * @param pInMe the point in the current coordinate system.
	 */
	Vector4 xformTo (const Trihedron & newT, const Vector4 & pInMe) const;

	/**
	 * Returns a point corresponding to @em p transformed in the coordinate system represented by
	 * the trihedron. pInAbsolute is expressed in homogeneous coordinates, in "absolute" space
	 * (ie the space in wich trihedron is expressed).
	 * @param pInAbsolute the point in the current coordinate system
	 */
	Vector4 xformTo (const Vector4 & pInAbsolute) const;

	/**
	 * Exprim a Trihedron in this trihedron space
	 * @param tInAbsolute the Trihedron in the current coordinate system.
	 */
	Trihedron xformTo (const Trihedron & tInAbsolute) const;

	/**
	 * Returns a point corresponding to @em p transformed in the current coordinate system.
	 * WARNING : p is a point, not a vector. To express a vector3 in new trihedron,
	 * use xformTo(t, Vector4) with homogeneous coordinate if 0.
	 * @param t
	 * @param pInT the point in the coordinate system represented by the trihedron @em t.
	 */
	Point3 xformFrom (const Trihedron & t, const Point3 & pInT) const;

	/**
	 * Returns a point corresponding to @em p transformed in the current coordinate system.
	 * p is expressed in homogeneous coordinates.
	 * @param t
	 * @param pInT the point in the coordinate system represented by the trihedron @em t.
	 */
	Vector4 xformFrom (const Trihedron & t, const Vector4 & pInT) const;

	/**
	 * Returns a point corresponding to @em p transformed in the current coordinate system.
	 * pInMe is expressed in homogeneous coordinates.
	 * @param pInMe the point in the coordinate system represented by the trihedron.
	 */
	Vector4 xformFrom (const Vector4 & pInMe) const;

	/**
	 * Express a Trihedron from this trihedron space to absolute space.
	 * @param tInMe the Trihedron in this coordinate system.
	 */
	Trihedron xformFrom (const Trihedron & tInMe) const;

	/**
	 * Checks the closeness of @em t with the current trihedron.
	 */
	bool isClose (const Trihedron & t, double e=IGT_EPSILON) const
	{ return x.isClose(t.getX(), e) && y.isClose(t.getY(), e) && z.isClose(t.getZ(), e) && o.isClose(t.getO(), e); }

	/**
	 * Returns the vector representing the x axis of the coordinate system.
	 */
	const Vector3 & getX() const { return x; }

	/**
	 * Returns the vector representing the y axis of the coordinate system.
	 */
	const Vector3 & getY() const { return y; }

	/**
	 * Returns the vector representing the z axis of the coordinate system.
	 */
	const Vector3 & getZ() const { return z; }

	/**
	 * Returns the origin of the coordinate system.
	 */
	const Point3 & getO() const { return o; }

	/**
	 * Sets the origin of the coordinate system.
	 */
	void setO (const Point3 & newO) { o = newO; }

	/**
	 * Sets the vector representing the x axis of the coordinate system.
	 * @warning Throw IGTDivideByZero if matrix determinant is 0.
	 */
	void setX (const Vector3 & newX);

	/**
	 * Sets the vector representing the y axis of the coordinate system.
	 * @warning Throw IGTDivideByZero if matrix determinant is 0.
	 */
	void setY (const Vector3 & newY);

	/**
	 * Sets the vector representing the z axis of the coordinate system.
	 * @warning Throw IGTDivideByZero if matrix determinant is 0.
	 */
	void setZ (const Vector3 & newZ);

	/// Get the homogeneous matrix associated to this trihedron.
	inline Matrix4 getMatrix() const;

	/// Returns an identity trihedron: origin (0,0,0), x (1,0,0), y (0,1,0) and z (0,0,1).
	static const Trihedron IDENTITY;

private:
	/** The x axis of the coordinate system. */
	Vector3 x;

	/** The y axis of the coordinate system. */
	Vector3 y;

	/** The z axis of the coordinate system. */
	Vector3 z;

	/** The origin of the coordinate system. */
	Point3 o;
};


// Utilities
/// Normalise all three vectors of the trihedron.
inline Trihedron normalise (const Trihedron & t);

/**
 * Create a transition trihedron from three points that are in two different
 * orthonormal trihedron (Tri1 and Tri2).
 * o1, a1 and b1 are in Tri1.
 * o2, a2 and b2 are in Tri2.
 * We assume that the origin of Tri1 is o1.
 * We assume that the origin of Tri2 is o2.
 * @return a transition trihedron that can be used to change a point in
 * Tri1 to Tri2.
 */
TGCORE_API Trihedron transitionTrihedron (const Point3 & o1, const Point3 & a1,
                                          const Point3 & b1, const Point3 & o2, const Point3 & a2,
                                          const Point3 & b2);

inline void Trihedron::normalise()  // Throw IGTDivideByZero if cannot normalise (null vector, etc.)
{
	x.normalise();
	y.normalise();
	z.normalise();
}


inline Trihedron normalise (const Trihedron & t)  // Throw IGTDivideByZero if cannot normalise (null vector, etc.)
{
	Trihedron tNorm(t);
	tNorm.normalise();
	return tNorm;
}


inline Matrix4 Trihedron::getMatrix() const
{
	return Matrix4(x.x(), y.x(), z.x(), o.x(),
		x.y(), y.y(), z.y(), o.y(),
		x.z(), y.z(), z.z(), o.z(),
		0.0, 0.0, 0.0, 1.0);
}


};  // namespace core
#endif  // TrihedronH
