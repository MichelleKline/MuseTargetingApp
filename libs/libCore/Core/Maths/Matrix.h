// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#pragma once

#include "../../libCore.h"
#if defined(_DEBUG)
#  include "../CoreExceptions.h"
#endif
#include <algorithm>
#include <deque>

namespace core {

//! @cond EXCLUDE_FROM_PLUGINS_SDK

/// Extended Euler parameters.
struct TGCORE_API Xform2DParams
{
	enum Params {
		TRANS  = 1,
		ROTATE = 2,
		SCALE  = 4,
		SHEAR  = 8,
		ALL    = 15
	};

	explicit Xform2DParams(int flags_=ALL);

	int nrParams() const
	{
		int n = 0;
		if (flags & TRANS)
			n += 2;
		if (flags & ROTATE)
			++n;
		if (flags & SCALE)
			n += 2;
		if (flags & SHEAR)
			++n;

		return n;
	}

	double operator[] (int i) const
	{ return P[i]; }

	double & operator[] (int i)
	{ return P[i]; }

	double P[6];
	int flags;
};

//! @endcond


/// @brief General purpose n x m matrix.
class TGCORE_API Matrix
{
public:
	/**
	 * Constructor. The matrix is initialized as identity (0 everywhere, 1 on the main diagonal).
	 * @param cols_ the number of columns of the matrix.
	 * @param rows_ the number of rows of the matrix.
	 */
	Matrix(int cols_, int rows_);

	/**
	 * Constructs an identity square matrix.
	 * @param dim the dimension of the matrix.
	 */
	explicit Matrix(int dim);

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	explicit Matrix(const Xform2DParams &);
	//! @endcond

	/// Copy constructor.
	Matrix(const Matrix &);

	/// Destructor. Nothing special.
	~Matrix();

	/// Assignment operator.
	Matrix & operator= (const Matrix & other);

	/// Set all components of the matrix to 0.
	Matrix & nullify();

	/// Returns the given component of the matrix.
	double operator[] (int k) const
	{ checkIndexOrThrow(k); return m_data[k]; }

	/// Returns the given component of the matrix with read/write access.
	double & operator[] (int k)
	{ checkIndexOrThrow(k); return m_data[k]; }

	/// Returns the element at given position (x = column/horizontal, y = row/vertical).
	double operator() (int x, int y) const
	{ checkCoordsOrThrow(x, y); return m_data[y * m_cols + x]; }

	/// Returns the element at given position (x = column/horizontal, y = row/vertical).
	double & operator() (int x, int y)
	{ checkCoordsOrThrow(x, y); return m_data[y * m_cols + x]; }

	/// Returns the column count of the matrix.
	int columns() const
	{ return m_cols; }

	/// Returns the row count of the matrix.
	int rows() const
	{ return m_rows; }

	/// Transpose the current matrix.
	Matrix transpose() const;

	/// Inverse the current matrix.
	Matrix inverse() const;

	/// Addition operator.
	Matrix & operator+= (const Matrix &);

	/// Product operator.
	Matrix & operator*= (const Matrix &);

	/// Product operator.
	friend TGCORE_API Matrix operator* (const Matrix & lhs, const Matrix & rhs);

	/// ! @cond EXCLUDE_FROM_PLUGINS_SDK
	friend TGCORE_API Matrix solve (const Matrix & lhs, const Matrix & rhs);

	/// ! @endcond

private:
	// Matrix(int dim, const double* elems);
	void init();

	bool     m_own;
	int      m_cols, m_rows;
	double * m_data;

#if defined(_DEBUG)
	inline void checkIndexOrThrow (int k) const
	{
		if (! m_data || k >= (m_cols * m_rows))
			throw IGTImageIndexOutOfBounds("Matrix<>", k, m_cols, m_rows);
	}

	inline void checkCoordsOrThrow (int x, int y) const
	{
		if (! m_data || x >= m_cols || y >= m_rows)
			throw IGTImageIndexOutOfBounds("Matrix<>", x + y * m_cols, m_cols, m_rows);
	}

#else // if defined(_DEBUG)
	inline void checkIndexOrThrow (int) const { }

	inline void checkCoordsOrThrow (int, int) const { }
#endif // if defined(_DEBUG)
};


/// Product operator.
TGCORE_API Matrix operator* (const Matrix & lhs, const Matrix & rhs);

/// ! @cond EXCLUDE_FROM_PLUGINS_SDK
TGCORE_API Matrix solve (const Matrix & A, const Matrix & b);

/// ! @endcond

/** @cond EXCLUDE_FROM_PLUGINS_SDK */

/**
 * @brief Tridiagonal matrix used for CubicSpline.
 *
 * The Tridiagonal matrix have been added to resolve equation like AX = L, where X is unknown.
 * This Matrix can be stored in a vector of n lines of 3 columns.
 * Its methods allow to solve equations for period or non-period curves.
 */

class TGCORE_API TridiagonalMatrix
{
public:
	/**Default constructor.*/
	TridiagonalMatrix();

	/**Copy constructor.*/
	TridiagonalMatrix(const TridiagonalMatrix &);

	/**
	 * Constructor.<br>
	 * Matrix size is n => size of buffer is n * 3
	 */
	explicit TridiagonalMatrix(int n);

	/**Constructor.*/
	explicit TridiagonalMatrix(const std::deque<double> &);

	/// Destructor. Nothing special.
	~TridiagonalMatrix();

	int size() const;

	/**
	 * operator [] const.<br>
	 * Nothing special.
	 */
	double operator[] (int k) const
	{ return a[k]; }

	/**
	 * operator [].<br>
	 * Nothing special.
	 */
	double & operator[] (int k)
	{ return a[k]; }


	/**Solve equation a*X = l by the "Pivot de gauss" method, commented.
	 */
	std::deque<double> syst_solve (const std::deque<double> & l);

	/** Solve equation a*X = l for a tridiagonal matrix with non null value in the top right corner and in the bottom left corner. */
	std::deque<double> syst_solve_period (const std::deque<double> & l);

	/**
	 * Important: L.size() == nb * matrixSize.
	 * The L vector of this method correspond to nb vectors.
	 * Important if l1, l2... lnb are nb vectors,
	 * then  L = l1(1), l2(1),...,lnb(1), l1(2), l2(2), ..... , lnb(size-1), lnb(size).
	 * The returned vector is the same form.
	 */
	std::deque<float> multi_syst_solve (const std::deque<float> & l, int nb);

	/**
	 * Important: L.size() == nb * matrixSize.
	 * The L vector of this method correspond to nb vectors.
	 * Important if l1, l2... lnb are nb vectors,
	 * then  L = l1(1), l2(1),...,lnb(1), l1(2), l2(2), ..... , lnb(size-1), lnb(size).
	 * The returned vector is the same form.
	 */
	std::deque<float> multi_syst_solve_period (const std::deque<float> & l, int nb);

private:
	///< A contains the non null values of a tridiagonal matrix of  matrixSize lines
	///< Be carrefull : the first element of A is the top right corner and the last is the bottom left corner of matrix, == 0 if the matrix is really tridiagonal

	///< a contains n lines of 3 columns, i.e. only the non nuls values, except for the first and the last line.
	///< For the first line, top rigth corner is taken as first value of the 3 columns
	///< For the last line, bottom left corner is taken as the last value of the 3 columns
	///< Example: a={f,b1,c1,a2,b2,c2,a3,b3,c3,a4,b4,g} where f and g are zero for real tridiagonal, and not nul for periodic tridiagonal.
	///<							b1	c1	0	f
	///<							a2	b2	c2	0
	///<							0	a3	b3	c3
	///<							g	0	a4	b4

	double * a;

	///< Number of lines of the initial tridiagonal matrix ( = A.size()/3 )
	int matrixSize;

	TridiagonalMatrix & operator= (const TridiagonalMatrix &);  // forbid

};


/** @endcond */

}  // namespace core
