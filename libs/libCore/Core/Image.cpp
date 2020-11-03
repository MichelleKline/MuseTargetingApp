// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Image.h"

namespace core {

//// Image<bool> implementation

Image<bool>::Image(unsigned width, unsigned height, bool value) :
	m_width(width),
	m_height(height),
	m_own(true),
	m_pixels(new Pixel[m_width * m_height]),
	m_updateNeeded(false),
	m_box(),
	m_surface(0)
{
	std::fill(m_pixels, m_pixels + m_width * m_height, value);
	if (value) {
		m_box     = BoundingBox(Point4(0, 0, 0, 0), Point4(float(m_width - 1), float(m_height - 1), 0, 0));
		m_surface = m_width * m_height;
	}
}


Image<bool>::Image(const Image<bool> & im) :
	m_width(im.m_width),
	m_height(im.m_height),
	m_own(im.m_own),
	m_updateNeeded(im.m_updateNeeded),
	m_box(im.m_box),
	m_surface(im.m_surface)
{
	if (im.m_own && im.m_pixels) {
		m_pixels = new Pixel[m_width * m_height];
		::memcpy(m_pixels, im.m_pixels, m_width * m_height * sizeof(Pixel));
		/*std::copy(&im.m_pixels[0], &im.m_pixels[0] + m_width * m_height,
		          stdext::checked_array_iterator<bool*>(&m_pixels[0], m_width * m_height));*/
	} else
		m_pixels = im.m_pixels;
}


Image<bool>::Image(unsigned w, unsigned h, bool * mem) :
	m_width(w),
	m_height(h),
	m_own(false),
	m_pixels(mem),
	m_updateNeeded(true),
	m_surface(0u)
{ }


Image<bool> & Image<bool>::operator= (const Image<bool> & im)
{
	if (this == &im)
		return *this;
	if (m_own && m_pixels)
		delete[] m_pixels;

	m_width        = im.m_width;
	m_height       = im.m_height;
	m_own          = im.m_own;
	m_box          = im.m_box;
	m_surface      = im.m_surface;
	m_updateNeeded = im.m_updateNeeded;

	if (im.m_own && im.m_pixels) {
		m_pixels = new Pixel[m_width * m_height];
		::memcpy(m_pixels, im.m_pixels, m_width * m_height * sizeof(Pixel));
		/*std::copy(&im.m_pixels[0], &im.m_pixels[0] + m_width * m_height,
		          stdext::checked_array_iterator<bool*>(&m_pixels[0], m_width * m_height));*/
	} else
		m_pixels = im.m_pixels;

	return *this;
}


void Image<bool>::fillRow (unsigned row, const Pixel & pix)
{
	unsigned start = row * m_width;
	unsigned end   = start + m_width;
	for (unsigned p = start; p < end; ++p) {
		m_pixels[p] = pix;
	}
	m_updateNeeded = true;
}


void Image<bool>::fillColumn (unsigned col, const Pixel & pix)
{
	unsigned start = col;
	unsigned end   = start + (m_width * (m_height - 1));
	for (unsigned p = start; p < end; p += m_width) {
		m_pixels[p] = pix;
	}
	m_updateNeeded = true;
}


void Image<bool>::fill (const Pixel & pix)
{
	unsigned size = m_width * m_height;
	for (unsigned p = 0; p < size; ++p) {
		m_pixels[p] = pix;
	}

	if (pix) {
		m_box     = BoundingBox(Point4(0, 0, 0, 0), Point4(float(m_width - 1), float(m_height - 1), 0, 0));
		m_surface = size;
	} else {
		m_box     = BoundingBox();
		m_surface = 0;
	}
	m_updateNeeded = false;
}


void Image<bool>::fillFrom (const Pixel * array)
{
	if (array == nullptr)
		return;
	::memcpy(m_pixels, array, m_width * m_height * sizeof(Pixel));
	m_updateNeeded = true;
}


void Image<bool>::copyPixels (const Image<bool> & im)
{
	if (m_width != im.m_width || m_height != im.m_height)
		throw std::logic_error("Masks sizes mismatch");

	unsigned pixelCount = m_width * m_height;
	::memcpy(m_pixels, im.m_pixels, pixelCount * sizeof(Pixel));
	m_updateNeeded = true;
}


void Image<bool>::updateStoredValues() const
{
	int n = 0;

	// Find how many m_pixels are true
	for (unsigned k = 0; k < m_width * m_height; ++k) {
		if (m_pixels[k])
			++n;
	}

	m_surface = n;

	bool boundFound = false;
	unsigned minX = 0, maxX = 0, minY = 0, maxY = 0;

	// scan column by column starting from the first one to find min X
	for (unsigned i = 0; i < m_width; ++i) {
		for (unsigned j = 0; j < m_height; ++j) {
			if ((*this)(i, j)) {
				minX       = i;
				boundFound = true;
				break;
			}
		}
		if (boundFound)
			break;
	}

	// scan column by column starting from the last one to find max X
	boundFound = false;
	for (int i = m_width - 1; i >= 0; --i) {
		for (int j = m_height - 1; j >= 0; --j) {
			if ((*this)(i, j)) {
				maxX       = i;
				boundFound = true;
				break;
			}
		}
		if (boundFound)
			break;
	}

	// scan line by line starting from the first one to find min Y
	boundFound = false;
	for (unsigned j = 0; j < m_height; ++j) {
		for (unsigned i = 0; i < m_width; ++i) {

			if ((*this)(i, j)) {
				minY       = j;
				boundFound = true;
				break;
			}
		}
		if (boundFound)
			break;
	}

	// scan line by line starting from the last one to find max Y
	boundFound = false;
	for (int j = m_height - 1; j >= 0; --j) {
		for (int i = m_width - 1; i >= 0; --i) {
			if ((*this)(i, j)) {
				maxY       = j;
				boundFound = true;
				break;
			}
		}
		if (boundFound)
			break;
	}

	Point4 lowerBound(minX, minY, 0, 0);
	Point4 upperBound(maxX, maxY, 0, 0);
	m_box          = BoundingBox(lowerBound, upperBound);

	m_updateNeeded = false;
}


unsigned Image<bool>::surface() const
{
	if (m_updateNeeded)
		updateStoredValues();
	return m_surface;
}


bool Image<bool>::empty() const
{
	if (m_updateNeeded)
		updateStoredValues();
	return m_surface == 0;
}


bool Image<bool>::full() const
{
	if (m_updateNeeded)
		updateStoredValues();
	return m_surface == m_width * m_height;
}


const BoundingBox & Image<bool>::boundingBox() const
{
	if (m_updateNeeded)
		updateStoredValues();
	return m_box;
}


Image<bool> & Image<bool>::inverse()
{
	unsigned pixelCount = m_width * m_height;
	for (unsigned i = 0; i < pixelCount; ++i) {
		m_pixels[i] = ! m_pixels[i];
	}
	m_updateNeeded = true;
	return *this;
}


Image<bool> Image<bool>::operator~() const
{
	Image<bool> copy(*this);
	copy.inverse();
	return copy;
}


Image<bool> & Image<bool>::operator&= (const Image<bool> & other)
{
	if (m_width != other.m_width || m_height != other.m_height)
		throw std::logic_error("Masks sizes mismatch");

	unsigned pixelCount = m_width * m_height;
	for (unsigned i = 0; i < pixelCount; ++i) {
		m_pixels[i] = m_pixels[i] ? other.m_pixels[i] : false;
	}

	m_updateNeeded = true;

	return *this;
}


Image<bool> & Image<bool>::operator|= (const Image<bool> & other)
{
	if (m_width != other.m_width || m_height != other.m_height)
		throw std::logic_error("Masks sizes mismatch");

	unsigned pixelCount = m_width * m_height;
	for (unsigned i = 0; i < pixelCount; ++i) {
		m_pixels[i] = m_pixels[i] ? true : other.m_pixels[i];
	}

	m_updateNeeded = true;

	return *this;
}


Image<bool> & Image<bool>::operator^= (const Image<bool> & other)
{
	if (m_width != other.m_width || m_height != other.m_height)
		throw std::logic_error("ROIs sizes mismatch");

	unsigned pixelCount = m_width * m_height;
	for (unsigned i = 0; i < pixelCount; ++i) {
		m_pixels[i] = (m_pixels[i] != other.m_pixels[i]);
	}

	m_updateNeeded = true;

	return *this;
}


Image<bool> Image<bool>::halfCopy() const
{
	Image<bool> res(m_width / 2, m_height / 2);

	unsigned k = 0;
	for (unsigned j = 0; j < res.m_height; ++j) {
		for (unsigned i = 0; i < res.m_width; ++i, ++k) {
			res.m_pixels[k] = (m_pixels[j * 2 * m_width + i * 2] + m_pixels[j * 2 * m_width + i * 2 + 1]
			                   + m_pixels[(j * 2 + 1) * m_width + i * 2] + m_pixels[(j * 2 + 1) * m_width + i * 2 + 1]) >= 2;
		}
	}

	res.m_updateNeeded = true;

	return res;
}


Image<bool> Image<bool>::dup() const
{
	Image<bool> im(*this);

	im.m_own = true;

	if (! m_own && m_pixels) {
		im.m_pixels = new Pixel[m_width * m_height];
		::memcpy(im.m_pixels, m_pixels, m_width * m_height * sizeof(Pixel));
		/*std::copy(&m_pixels[0], &m_pixels[0] + m_width * m_height,
		          stdext::checked_array_iterator<bool*>(&im.m_pixels[0], m_width * m_height));*/
	}

	return im;
}


void Image<bool>::statMoments (int & m0, double & m1, double & m2, const Image<bool> * mask) const
{
	m0 = 0;
	m1 = 0.0f;
	m2 = 0.0f;

	int i_m1 = 0;

	unsigned pixelCount = m_width * m_height;
	for (unsigned k = 0; k < pixelCount; ++k) {
		if (! mask || (*mask)[k]) {
			++m0;
			if (m_pixels[k])
				++i_m1;
		}
	}

	m1 = m2 = double(i_m1);
}


double Image<bool>::mean (const Image<bool> * mask) const
{
	int m0;
	double m1, m2;

	statMoments(m0, m1, m2, mask);

	return m1 / m0;
}


double Image<bool>::moment (int i, int j, const Image<bool> * mask) const
{
	double M   = 0.0f;

	unsigned k = 0;
	for (unsigned y = 0; y < m_height; ++y) {
		for (unsigned x = 0; x < m_width; ++x, ++k) {
			if (! mask || ((*mask)[k] && m_pixels[k]))
				M += pow(double(x), i) * pow(double(y), j);
		}
	}

	return M;
}


Xform2DParams Image<bool>::mainAxis (int flags, const Image<bool> * mask) const
{
	Xform2DParams P(flags);
	if (flags < Xform2DParams::TRANS)
		return P;

	double M  = moment(0, 0, mask);
	double Mx = moment(1, 0, mask) / M;
	double My = moment(0, 1, mask) / M;

	P[0] = float(Mx);
	P[1] = float(My);

	if (flags < Xform2DParams::ROTATE)
		return P;

	double Mxx = moment(2, 0, mask) / M - Mx * Mx;
	double Myy = moment(0, 2, mask) / M - My * My;
	double Mxy = moment(1, 1, mask) / M - Mx * My;

	P[2] = float(std::atan2(2.0 * Mxy, Mxx - Myy)) / 2.0f;

	if (flags < Xform2DParams::SCALE)
		return P;

	// Covariance matrix eigenvalues
	P[3] = float((Mxx + Myy) + std::sqrt(4.0f * Mxy * Mxy + (Mxx - Myy) * (Mxx - Myy))) / 2.0f;
	P[4] = float((Mxx + Myy) + std::sqrt(4.0f * Mxy * Mxy - (Mxx - Myy) * (Mxx - Myy))) / 2.0f;

	if (flags < Xform2DParams::SHEAR)
		return P;

	P[5] = 0.0f;  // No shear factor computable, or so it seems.

	return P;
}


// Image<bool> Image<bool>::resize(unsigned w, unsigned h, bool value) const
// {
//	if (w == m_width && h == m_height)
//		return *this;
//
//	Image<T> im(w, h);
//
//	double xfact = double(w) / m_width;
//	double yfact = double(h) / m_height;
//
//	if (w > m_width)
//	{
//		unsigned k = 0;
//		for (unsigned j = 0; j < h; ++j)
//			for (unsigned i = 0; i < w; ++i, ++k)
//				im.m_pixels[k] = (*this)(i / xfact, j / yfact);
//	}
//	else
//	{
//		unsigned k = 0;
//		for (unsigned j = 0; j < h; ++j)
//			for (unsigned i = 0; i < w; ++i, ++k)
//			{
//				double xo = i / xfact;
//				double yo = j / yfact;
//				unsigned io = std::floor(xo);
//				unsigned wjo = std::floor(yo * m_width);
//
//				im.m_pixels[k] = m_pixels[wjo + io];
//			}
//	}
//
//	return im;
// }


void Image<bool>::resize (unsigned width, unsigned height, bool value)
{
	if (width == m_width && height == m_height)
		return;

	if (! m_own)
		throw std::logic_error("Can not delete image buffer (not owned)");

	delete[] m_pixels;

	m_width  = width;
	m_height = height;
	m_pixels = new Pixel[m_width * m_height];
	fill(value);
}


}  // namespace core
