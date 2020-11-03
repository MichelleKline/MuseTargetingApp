// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Matrix.h"
#include <stdexcept>
#include <cmath>

namespace core {

Xform2DParams::Xform2DParams(int flags_) :
	flags(flags_)
{
	std::fill_n(P, 6, 0.0f);
}


Matrix::Matrix(int dim) :
	m_own(true)
	, m_cols(dim)
	, m_rows(dim)
	, m_data(new double[m_cols * m_rows])
{
	init();
}


Matrix::Matrix(int cols_, int rows_) :
	m_own(true)
	, m_cols(cols_)
	, m_rows(rows_)
	, m_data(new double[m_cols * m_rows])
{
	init();
}


void Matrix::init()
{
	for (int k = 0; k < m_cols * m_rows; ++k) {
		m_data[k] = 0.0f;
	}

	for (int k = 0; k < m_cols * m_rows; k += m_cols + 1) {
		m_data[k] = 1.0f;
	}
}


Matrix & Matrix::nullify()
{
	for (int k = 0; k < m_cols * m_rows; k += m_cols + 1) {
		m_data[k] = 0.0f;
	}

	return *this;
}


Matrix::Matrix(const Matrix & m_) :
	m_own(true)
	, m_cols(m_.m_cols)
	, m_rows(m_.m_rows)
	, m_data(new double[m_cols * m_rows])
{
	for (int k = 0; k < m_cols * m_rows; ++k) {
		m_data[k] = m_.m_data[k];
	}
}


Matrix & Matrix::operator= (const Matrix & other)
{
	if (this == &other)
		return *this;

	m_cols = other.m_cols;
	m_rows = other.m_rows;

	if (m_own)
		delete[] m_data;
	m_own  = true;
	m_data = new double[m_cols * m_rows];

	for (int k = 0; k < m_cols * m_rows; ++k) {
		m_data[k] = other.m_data[k];
	}

	return *this;
}


Matrix::Matrix(const Xform2DParams & P) :
	m_own(true)
	, m_cols(3)
	, m_rows(3)
	, m_data(new double[m_cols * m_rows])
{
	init();

	Matrix mat(3);

	if (P.flags & Xform2DParams::TRANS) {
		mat[0] = 1.0f;
		mat[1] = 0.0f;
		mat[2] = P[0];
		mat[3] = 0.0f;
		mat[4] = 1.0f;
		mat[5] = P[1];
		mat[6] = 0.0f;
		mat[7] = 0.0f;
		mat[8] = 1.0f;
		*this *= mat;
	}
	if (P.flags & Xform2DParams::ROTATE) {
		mat[0] = std::cos(P[2]);
		mat[1] = std::sin(P[2]);
		mat[2] = 0.0f;
		mat[3] = -std::sin(P[2]);
		mat[4] = std::cos(P[2]);
		mat[5] = 0.0f;
		mat[6] = 0.0f;
		mat[7] = 0.0f;
		mat[8] = 1.0f;
		*this *= mat;
	}
	if (P.flags & Xform2DParams::SCALE) {
		mat[0] = 1.0f + P[3];
		mat[1] = 0.0f;
		mat[2] = 0.0f;
		mat[3] = 0.0f;
		mat[4] = 1.0f + P[4];
		mat[5] = 0.0f;
		mat[6] = 0.0f;
		mat[7] = 0.0f;
		mat[8] = 1.0f;
		*this *= mat;
	}
	if (P.flags & Xform2DParams::SHEAR) {
		mat[0] = 1.0f;
		mat[1] = P[5];
		mat[2] = 0.0f;
		mat[3] = 0.0f;
		mat[4] = 1.0f;
		mat[5] = 0.0f;
		mat[6] = 0.0f;
		mat[7] = 0.0f;
		mat[8] = 1.0f;
		*this *= mat;
	}
}


Matrix::~Matrix(void)
{
	if (m_own)
		delete[] m_data;
}


Matrix Matrix::transpose() const
{
	Matrix res(m_rows, m_cols);

	for (int j = 0; j < m_rows; ++j) {
		for (int i = 0; i < m_cols; ++i) {
			res[i * m_rows + j] = m_data[j * m_cols + i];
		}
	}

	return res;
}


Matrix Matrix::inverse() const  // Gauss-Jordan elimination
{
	if (m_cols != m_rows)
		throw std::domain_error("Matrix inversion: matrix not square");

	Matrix mat(*this);
	Matrix res(m_cols, m_rows);

	for (int j0 = 0; j0 < m_rows; ++j0) {
		double pivot = mat[j0 * (m_cols + 1)];
		int pindex   = j0;
		for (int j = j0 + 1; j < m_rows; ++j) {
			double c = mat[j * m_cols + j0];
			if (std::abs(c) > std::abs(pivot)) {
				pivot  = c;
				pindex = j;
			}
		}

		if (pivot == 0.0f)
			throw std::domain_error("Matrix not invertible");

		if (pindex != j0) {
			for (int i = j0; i < m_cols; ++i) {
				std::swap(mat[j0 * m_cols + i], mat[pindex * m_cols + i]);
			}
			for (int i = 0; i < m_cols; ++i) {
				std::swap(res[j0 * m_cols + i], res[pindex * m_cols + i]);
			}
		}

		for (int i = j0; i < m_cols; ++i) {
			mat[j0 * m_cols + i] /= pivot;
		}
		for (int i = 0; i < m_cols; ++i) {
			res[j0 * m_cols + i] /= pivot;
		}

		for (int j = 0; j < m_rows; ++j) {
			if (j == j0)
				continue;

			double k = mat[j * m_cols + j0];
			if (k == 0.0f)
				continue;
			else
				mat[j * m_cols + j0] = 0.0f;

			for (int i = j0 + 1; i < m_cols; ++i) {
				mat[j * m_cols + i] -= k * mat[j0 * m_cols + i];
			}
			for (int i = 0; i < m_cols; ++i) {
				res[j * m_cols + i] -= k * res[j0 * m_cols + i];
			}
		}
	}

	return res;
}


Matrix operator* (const Matrix & lhs, const Matrix & rhs)
{
	if (lhs.m_cols != rhs.m_rows)
		throw std::domain_error("Matrix product: sizes mismatch");

	Matrix res(rhs.m_cols, lhs.m_rows);

	for (int j = 0; j < res.m_rows; ++j) {
		for (int i = 0; i < res.m_cols; ++i) {
			double & c = res[j * res.m_cols + i];
			c = 0.0f;
			for (int k = 0; k < lhs.m_cols; ++k) {
				c += lhs[k * lhs.m_rows + i] * rhs[j * rhs.m_cols + k];
			}
		}
	}

	return res;
}


Matrix & Matrix::operator+= (const Matrix & rhs)
{
	if (m_cols != rhs.m_cols || m_rows != rhs.m_rows)
		throw std::domain_error("Matrix sum: sizes mismatch");

	for (int k = 0; k < m_cols * m_rows; ++k) {
		m_data[k] += rhs[k];
	}

	return *this;
}


Matrix & Matrix::operator*= (const Matrix & rhs)
{
	Matrix mat(*this * rhs);

	// TRICKY Constant time copy and destroy
	// cppcheck-suppress unreadVariable
	mat.m_own = false;
	delete[] m_data;
	m_data    = mat.m_data;

	m_cols    = mat.m_cols;
	m_rows    = mat.m_rows;

	return *this;
}


// Solve mX = l
/*	//std::deque<double> tempRecipBeta (matrixSize-1);

    //if (m_data[matrixSize - 1] == 0)
    //	return std::deque<double>();//should not be here

    //double b0				= m_data[matrixSize - 1];
    //double recipBeta			= 1.0f/b0;
    //tmp[0]					= l[0] * recipBeta;

    //for (int i = 1; i < matrixSize; ++i)
    //{
    //	double ai			= m_data[i*(matrixSize-1)+matrixSize];	//on the diagonal
    //	double bi			= m_data[(i+1)*(matrixSize-1)];			//on the upper diagonal
    //	double ci			= m_data[i*(matrixSize-1) - 1];			//on the lower diagonal
    //
    //	tempRecipBeta[i-1]	= ci * recipBeta;

    //	if ((bi - ai  * tempRecipBeta[i-1]) == 0)
    //		return std::deque<double>();//should not be here

    //	recipBeta			= 1.0f/(bi - ai * tempRecipBeta[i-1]);
    //	tmp[i]				= (l[i] - ai * tmp[i-1]) * recipBeta;
    //}
    //for (int i = matrixSize - 2; i >= 0; --i)
    //	tmp[i] -= tempRecipBeta[i] * tmp[i+1];

    //return tmp;*/


Matrix solve (const Matrix & A, const Matrix & b)  // Gaussian elimination
{
	if (A.m_cols != A.m_rows)
		throw std::domain_error("System solving: matrix not square");

	if (b.m_cols != 1)
		throw std::domain_error("System solving: constant vector is not a one column matrix");

	if (A.m_rows != b.m_rows)
		throw std::domain_error("System solving: sizes mismatch");

	Matrix mat(A);
	Matrix vec(b);

	for (int j0 = 0; j0 < A.m_rows; ++j0) {
		double pivot = mat[j0 * (A.m_cols + 1)];
		int pindex   = j0;
		for (int j = j0 + 1; j < A.m_rows; ++j) {
			double c = mat[j * A.m_cols + j0];
			if (std::abs(c) > std::abs(pivot)) {
				pivot  = c;
				pindex = j;
			}
		}

		if (pivot == 0.0f)
			throw std::domain_error("System not solvable");

		if (pindex != j0) {
			for (int i = j0; i < A.m_cols; ++i) {
				std::swap(mat[j0 * A.m_cols + i], mat[pindex * A.m_cols + i]);
			}
			std::swap(vec[j0], vec[pindex]);
		}

		for (int j = j0 + 1; j < A.m_rows; ++j) {
			if (j != j0) {
				double k = mat[j * A.m_cols + j0] / pivot;

				for (int i = 0; i < A.m_cols; ++i) {
					mat[j * A.m_cols + i] -= k * mat[j0 * A.m_cols + i];
				}
				vec[j] -= k * vec[j0];
			}
		}
	}

	Matrix res(b.m_rows, 1);

	res[b.m_rows - 1] = vec[b.m_rows - 1] / mat[A.m_cols * A.m_rows - 1];

	for (int k = b.m_rows - 2; k >= 0; --k) {
		res[k] = vec[k];

		for (int i = k + 1; i < b.m_rows; ++i) {
			res[k] -= mat[k * A.m_cols + i] * res[i];
		}

		res[k] /= mat[k * (A.m_cols + 1)];
	}

	return res;
}


/////////Implementation of the tridiagonal matrix

TridiagonalMatrix::TridiagonalMatrix()  // default
{
	matrixSize = 0;
	a          = nullptr;
}


TridiagonalMatrix::TridiagonalMatrix(int n)
{
	matrixSize = n;
	a          = new double[3 * matrixSize];
	for (int i = 0; i < 3 * matrixSize; ++i) {
		a[i] = 0.0;
	}
}


TridiagonalMatrix::TridiagonalMatrix(const TridiagonalMatrix & copy)  // copy
{
	matrixSize = copy.matrixSize;
	a          = new double[3 * matrixSize];
	for (int i = 0; i < 3 * matrixSize; ++i) {
		a[i] = copy[i];
	}
}


TridiagonalMatrix::TridiagonalMatrix(const std::deque<double> & l)
{
	// Be careful: the first element of A is the top right corner, and the last element is the bottom left corner of the matrix
	matrixSize = (int)l.size() / 3;
	a          = new double[l.size()];
	for (int i = 0; i < 3 * matrixSize; ++i) {
		a[i] = l[i];
	}
}


TridiagonalMatrix::~TridiagonalMatrix()
{
	delete[] a;
}


int TridiagonalMatrix::size() const { return matrixSize; }


std::deque<double> TridiagonalMatrix::syst_solve (const std::deque<double> & l)
{
	std::deque<double> tmp(l.size()); // return value
	tmp = l;                          // initialized to  l
	TridiagonalMatrix B(*this);       // creation of a second TridiagonalMatrix same as this

	for (int i = 1; i < matrixSize; i++) {  // déscente de les matrices en réalisant la même opération sur les deux membres
		tmp[i]       = tmp[i] - tmp[i - 1] * B[3 * i] / B[3 * (i - 1) + 1];
		B[3 * i + 1] = B[3 * i + 1] - B[3 * i] * B[3 * (i - 1) + 2] / B[3 * (i - 1) + 1];
	}
	// on détermine la valeur exacte de X en (size-1) qui sera stockée dans tmp
	tmp[matrixSize - 1] = tmp[matrixSize - 1] / B[3 * matrixSize - 2];
	// int tmplast = tmp[matrixSize-1];
	// et on remonte les matrices en déterminant les valeurs des X[i] grâce aux valeurs des rangs précédents qu'on stockera également dans tmp
	for (int i = matrixSize - 2; i > -1; i--) {
		tmp[i] = (tmp[i] - tmp[i + 1] * B[3 * i + 2]) / B[3 * i + 1];
	}
	return tmp;
}


std::deque<double> TridiagonalMatrix::syst_solve_period (const std::deque<double> & l)
{
	std::deque<double> tmp        = l;
	std::deque<double> tmp_period = l;

	for (int i = 1; i < matrixSize - 2; ++i) {
		tmp_period[i] = 0.0;
	}

	tmp_period[0] = a[0];
	tmp_period[matrixSize - 2] = a[3 * (matrixSize - 2) + 2];
	tmp_period[matrixSize - 1] = a[3 * (matrixSize - 1) + 1];

	double val = a[3 * matrixSize - 1];
	TridiagonalMatrix b(*this);
	// solve_period
	for (int i = 1; i < matrixSize; i++) {
		// idem non periodic
		double coeff = b[3 * i] / b[3 * (i - 1) + 1];
		b[3 * i + 1] = b[3 * i + 1] - b[3 * (i - 1) + 2] * coeff;
		tmp[i]       = tmp[i] - tmp[i - 1] * coeff;
		// en plus si i < matrixSize-1
		if (i < matrixSize - 1) {
			double coeff2 = val / b[3 * (i - 1) + 1];
			// en plus - colonne de droite de la matrice
			tmp_period[i] = tmp_period[i] - tmp_period[i - 1] * coeff;
			tmp_period[matrixSize - 1] = tmp_period[matrixSize - 1] - tmp_period[i - 1] * coeff2;
			// en plus - ligne du bas de la matrice
			val = -b[3 * (i - 1) + 2] * coeff2;
			// en plus - membre de droite
			tmp[matrixSize - 1] = tmp[matrixSize - 1] - tmp[i - 1] * coeff2;
			// cas special i==size-2
			if (i == matrixSize - 2) {
				b[3 * (matrixSize - 1)]     = b[3 * (matrixSize - 1)] + val;
				b[3 * (matrixSize - 2) + 2] = tmp_period[matrixSize - 2];
				b[3 * (matrixSize - 1) + 1] = tmp_period[matrixSize - 1];
			}
		}
	}

	// détermination de la valeur de X en (matrixSize-1) et (matrixSize-2) et stockage dans tmp
	tmp[matrixSize - 1] = tmp[matrixSize - 1] / b[3 * matrixSize - 2];
	tmp[matrixSize - 2] = (tmp[matrixSize - 2] - tmp[matrixSize - 1] * b[3 * (matrixSize - 2) + 2]) / b[3 * (matrixSize - 2) + 1];
	// remontée de la matrice tmp et déterminationdes X(i) eux aussi stockés dans tmp
	for (int i = matrixSize - 3; i > -1; i--) {
		tmp[i] = (tmp[i] - tmp[i + 1] * b[3 * i + 2] - tmp[matrixSize - 1] * tmp_period[i]) / b[3 * i + 1];
	}
	return tmp;
}


std::deque<float> TridiagonalMatrix::multi_syst_solve (const std::deque<float> & l, int nb)
{
	// Check size!!!!
	if (l.size() != (unsigned)(nb * matrixSize))
		return std::deque<float>(); // FIXME : should throw ?
	std::deque<float> tmp;
	tmp = l;
	TridiagonalMatrix b(*this);
	for (int i = 1; i < matrixSize; i++) {
		for (int j = 0; j < nb; j++) {
			tmp[nb * i + j] = tmp[nb * i + j] - tmp[nb * (i - 1) + j] * (float)(b[3 * i] / b[3 * (i - 1) + 1]);
		}
		b[3 * i + 1] = b[3 * i + 1] - b[3 * i] * b[3 * (i - 1) + 2] / b[3 * (i - 1) + 1];
	}
	for (int j = 0; j < nb; j++) {
		tmp[nb * (matrixSize - 1) + j] = tmp[nb * (matrixSize - 1) + j] / (float)b[3 * matrixSize - 2];
	}

	for (int i = matrixSize - 2; i > -1; i--) {
		for (int j = 0; j < nb; j++) {
			tmp[nb * i + j] = (tmp[nb * i + j] - tmp[nb * (i + 1) + j] * (float)b[3 * i + 2]) / (float)b[3 * i + 1];
		}
	}
	return tmp;
}


std::deque<float> TridiagonalMatrix::multi_syst_solve_period (const std::deque<float> & l, int nb)
{
	std::deque<float> tmp, tmp_period;
	// Check size!!!!
	if (l.size() != (unsigned)(nb * matrixSize))
		return tmp; // FIXME : should throw ?

	// initialization of tmp
	tmp = l;
	// initilization of tmp_period
	tmp_period.push_back((float)a[0]);
	for (int i = 1; i < matrixSize - 2; ++i) {
		tmp_period.push_back(0.0);
	}
	tmp_period.push_back((float)a[3 * (matrixSize - 2) + 2]);
	tmp_period.push_back((float)a[3 * (matrixSize - 1) + 1]);

	float val = (float)a[3 * matrixSize - 1];
	TridiagonalMatrix b(*this);
	// solve_period
	for (int i = 1; i < matrixSize; i++) {
		// idem non periodique
		float coeff = (float)(b[3 * i] / b[3 * (i - 1) + 1]);
		b[3 * i + 1] = b[3 * i + 1] - b[3 * (i - 1) + 2] * coeff;
		for (int j = 0; j < nb; j++) {
			tmp[i * nb + j] = tmp[i * nb + j] - tmp[nb * (i - 1) + j] * coeff;
		}

		// en plus si i < matrixSize-1
		if (i < matrixSize - 1) {
			float coeff2 = val / (float)b[3 * (i - 1) + 1];
			// en plus - colonne de droite de la matrice
			tmp_period[i] = tmp_period[i] - tmp_period[i - 1] * coeff;
			tmp_period[matrixSize - 1] = tmp_period[matrixSize - 1] - tmp_period[i - 1] * coeff2;
			// en plus - ligne du bas de la matrice
			val = -(float)b[3 * (i - 1) + 2] * coeff2;
			// en plus - membre de droite
			for (int j = 0; j < nb; j++) {
				tmp[nb * (matrixSize - 1) + j] = tmp[nb * (matrixSize - 1) + j] - tmp[nb * (i - 1) + j] * coeff2;
			}
			// special case i==matrixSize-2
			if (i == matrixSize - 2) {
				b[3 * (matrixSize - 1)]     = b[3 * (matrixSize - 1)] + val;
				b[3 * (matrixSize - 2) + 2] = tmp_period[matrixSize - 2];
				b[3 * (matrixSize - 1) + 1] = tmp_period[matrixSize - 1];
			}
		}
	}

	for (int j = 0; j < nb; j++) {
		tmp[nb * (matrixSize - 1) + j] = tmp[nb * (matrixSize - 1) + j] / (float)b[3 * matrixSize - 2];
		tmp[nb * (matrixSize - 2) + j] = (tmp[nb * (matrixSize - 2) + j] - tmp[nb * (matrixSize - 1) + j] * (float)b[3 * (matrixSize - 2) + 2]) / (float)b[3 * (matrixSize - 2) + 1];
	}

	for (int i = matrixSize - 3; i > -1; i--) {
		for (int j = 0; j < nb; j++) {
			tmp[nb * i + j] = (tmp[nb * i + j] - tmp[nb * (i + 1) + j] * (float)b[3 * i + 2] - tmp[nb * (matrixSize - 1) + j] * tmp_period[i]) / (float)b[3 * i + 1];
		}
	}
	return tmp;
}


}  // namespace core
