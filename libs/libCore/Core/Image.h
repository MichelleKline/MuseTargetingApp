// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef ImageH
#define ImageH

#include "../libCore.h"
// #include "Maths/VectorField.h"
#include "Maths/Matrix.h"
#include "Maths/BoundingBox.h"

#include <stdexcept>
#include <cstring>
#include <cmath>
#if USE_OPENMP
#  include <omp.h>
#endif
#undef min
#undef max

namespace core {


/**
 * @brief Image is the base class to access and manipulate pixels of images.
 */
template <typename T>
class Image
{
public:
	/// Template Pixel type.
	typedef T Pixel;

	/** Default constructor. Creates an empty image. */
	Image() :
		m_width(0),
		m_height(0),
		m_own(true),
		m_pixels(nullptr)
	{ }

	/** Creates an image of size @em width x @em height pixels. */
	Image(unsigned width, unsigned height);

	/** Copy constructor. */
	Image(const Image &);

	/** Creates an Image from existing data.
	    @param width the width of the image in pixels
	    @param height the height of the image in pixels
	    @param pixels existing data of the image
	    @warning @em pixels will not be freed. */
	Image(unsigned width, unsigned height, T * pixels);

	/** Destructor. Nothing special. */
	virtual ~Image()
	{
		if (m_own)
			delete[] m_pixels;
		m_pixels = nullptr;
		m_width  = m_height = 0;
		m_own    = false;
	}

	/** Assignment operator. */
	Image & operator= (const Image & im);

	/** Returns a copy of this image (duplicates its pixels too). */
	Image dup() const;

	/** Fills the specified row with the given pixel value.
	    @param row the row index (from 0)
	    @param p the pixel value
	    @throw IGTIndexOutOfBounds if @em row >= height(). */
	void fillRow (unsigned row, const Pixel & p);

	/** Fills the specified row with the given pixel value.
	    @param col the column index (from 0)
	    @param p the pixel value
	    @throw IGTIndexOutOfBounds if @em col >= width(). */
	void fillColumn (unsigned col, const Pixel & p);

	/** Fills the entire image with the given pixel value. */
	void fill (const Pixel & p);

	/** Fills the image from an array of pixels.
	    The array must contain at least width x size items. */
	void fillFrom (const Pixel * array);

	/** Sets all pixels to zero. */
	void zeroPixels() { fill(Pixel(0)); }

	/** Copies only the pixel values from another image.
	    @throw std::logic_error exception if sizes do not match. */
	void copyPixels (const Image & im);

	/** Returns whether the Image is properly built (i.e. pixels are allocated). Same as exists(). */
	operator bool() const
	{ return m_pixels != nullptr; }

	/** Returns whether the Image is properly built (i.e. pixels are allocated). */
	bool exists() const
	{ return m_pixels != nullptr; }

	/** Returns the width of the image, in pixels. */
	unsigned width() const
	{ return m_width; }

	/** Returns the height of the image, in pixels. */
	unsigned height() const
	{ return m_height; }

	/** Returns the minimum pxiel value in the image.
	    @throw IGTImageIndexOutOfBounds if the image is empty. */
	Pixel min() const;

	/** Returns the maximum value in the image.
	    @throw IGTImageIndexOutOfBounds if the image is empty. */
	Pixel max() const;

	/** Returns a scaled copy of the image (which is not modified).
	    Not very good for image reduction, see halfCopy() instead. */
	Image scaledCopy (unsigned width, unsigned height) const;

	/** Returns a copy of the image, scaled to half size in both width and height. */
	Image halfCopy() const;

	/** Returns the pixel at given position (between 0 and width x height). */
	inline Pixel & operator[] (unsigned k)
	{
		checkIndexOrThrow(k);
		return m_pixels[k];
	}

	/** Returns the pixel at given position (between 0 and width x height). */
	inline Pixel operator[] (unsigned k) const
	{
		checkIndexOrThrow(k);
		return m_pixels[k];
	}

	/** Returns the pixel at given position (x = column/horizontal, y = row/vertical)
	    using bilinear interpolation. Returns 0.0 if out of bounds. */
	inline double operator() (double x, double y) const;

	/** Returns the pixel at given position (x = column/horizontal, y = row/vertical). */
	inline Pixel operator() (unsigned x, unsigned y) const
	{
		checkCoordsOrThrow(x, y);
		return m_pixels[y * m_width + x];
	}

	/** Returns the pixel at given position (x = column/horizontal, y = row/vertical). */
	inline Pixel & operator() (unsigned x, unsigned y)
	{
		checkCoordsOrThrow(x, y);
		return m_pixels[y * m_width + x];
	}

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	void statMoments (int & m0, double & m1, double & m2, const Image<bool> * =nullptr) const;

	//! @endcond

	/// Returns the mean of the image.
	double mean (const Image<bool> * =nullptr) const;

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	double moment (int i, int j, const Image<bool> * =nullptr) const;

	//! @endcond

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	Xform2DParams mainAxis (int flags, const Image<bool> * =nullptr) const;

	//! @endcond

	/** ??
	    The Mask is not used for the time being.
	   VectorField gradient(const Image<bool>* = nullptr) const; */

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	Image<double> laplacian() const;

	//! @endcond

	// Image<bool> snrMask(double echoTime, double deltaT = 2.0f) const;

	/** ?? */
	// template <typename U> friend double* apply(const VectorField&, const Image<U>&);

	/** Moves the content of the image, by shifting all rows down or up.
	    @param shift size of the shift in pixels, a positive value will move down, and negative
	    will move up. The value is used modulo height() (so it can be greater). */
	void shiftRows (int shift); // cppcheck-suppress functionConst

	/** Moves the content of the image, by shifting all columns right or left.
	    @param shift size of the shift in pixels, a positive value will move right, and negative
	    will move left. The value is used modulo width() (so it can be greater). */
	void shiftColumns (int shift); // cppcheck-suppress functionConst

	/** Exchange rows and/or columns using the center as pivot.
	    @param leftRight if true, the first column is swapped with the last one, and so on until the center is reached
	    @param upDown if true, the first row is swapped with the last one, and so on until the center is reached */
	void mirror (bool leftRight, bool upDown); // cppcheck-suppress functionConst

	/** Swaps the four quarters of the image. Their content is not modified, only shifted.
	    The width and height must be even.
	    Example: A B  becomes  D C
	             C D           B A
	    @return true on success, false if nothing is modified.
	 */
	bool swapQuarters(); // cppcheck-suppress functionConst

//! @cond EXCLUDE_FROM_PLUGINS_SDK

protected:
	unsigned m_width;
	unsigned m_height;
	bool     m_own;
	Pixel *  m_pixels;

#if defined(_DEBUG)
	inline void checkIndexOrThrow (unsigned k) const
	{
		if (! m_pixels || k >= (m_width * m_height))
			throw IGTImageIndexOutOfBounds("Image<>", k, m_width, m_height);
	}

	inline void checkCoordsOrThrow (unsigned x, unsigned y) const
	{
		if (! m_pixels || x >= m_width || y >= m_height)
			throw IGTImageIndexOutOfBounds("Image<>", x + y * m_width, m_width, m_height);
	}

#else // if defined(_DEBUG)
	inline void checkIndexOrThrow (unsigned) const { }

	inline void checkCoordsOrThrow (unsigned, unsigned) const { }
#endif // if defined(_DEBUG)
//! @endcond
};


// some global functions about Image<>

/** Returns the result of the image transformed by the given matrix, as an array of double.
    Does not modify the original image.
    The result must be delete[]'d. */
template <typename T> double * transformedImage (const Matrix &, const Image<T> &);

/* disabled since never used
   /// Applies the matrix transform to the image.
   template <typename T> Image<T> operator*(const Matrix&, const Image<T>&);

   /// Applies the vector field to the image.
   template <typename T> Image<T> operator*(const VectorField&, const Image<T>&);

   /// Applies the vector field to the image. The result must be delete[]'d.
   template <typename T> double* apply(const VectorField&, const Image<T>&);
 */

// ----------------------------------------------------------------------
/** A specialization of Image<> class for booleans.
    This class is mainly knowned as Mask.
 */
template<> class TGCORE_API Image<bool>
{
public:
	/// Template Pixel type specialized for boolean.
	typedef bool Pixel;

	/// Default constructor. Creates an empty mask.
	Image() :
		m_width(0)
		, m_height(0)
		, m_own(true)
		, m_pixels(nullptr)
		, m_updateNeeded(false)
		, m_box()
		, m_surface(0)
	{ }

	/// Creates a mask of size @em width x @em height pixels.
	Image(unsigned width, unsigned height, bool value=false);
	
	/// Copy constructor.
	Image(const Image<bool> &);

	/** Creates a Mask from existing data.
	    @param w the width of the mask in pixels
	    @param h the height of the mask in pixels
	    @param mem existing data of the mask
	    @warning @em mem will not be freed. */
	Image(unsigned w, unsigned h, bool * mem);

	/** Destructor. Nothing special. */
	virtual ~Image()
	{
		if (m_own)
			delete[] m_pixels;
		m_pixels = nullptr;
		m_width  = m_height = 0;
		m_own    = false;
	}

	/** Assignment operator. */
	Image<bool> & operator= (const Image<bool> & im);

	/** Returns a copy of this mask (duplicates its pixels too). */
	Image<bool> dup() const;

	/// Resize the image to (@em width, @em height) and setting all pixels to @em value.
	/// @param width the new width of the mask,
	/// @param height the new height of the mask,
	/// @param value the new value for ALL pixels.
	void resize (unsigned width, unsigned height, bool value);

	/** Fills the specified row with the given pixel value.
	    @param row the row index (from 0)
	    @param p the pixel value
	    @throw IGTIndexOutOfBounds if @em row >= height(). */
	void fillRow (unsigned row, const Pixel & p);

	/** Fills the specified row with the given pixel value.
	    @param col the column index (from 0)
	    @param p the pixel value
	    @throw IGTIndexOutOfBounds if @em col >= width(). */
	void fillColumn (unsigned col, const Pixel & p);

	/** Fills the entire mask with the given pixel value. */
	void fill (const Pixel & p);

	/** Fills the mask from an array of pixels.
	    The array must contain at least width x size items. */
	void fillFrom (const Pixel * array);

	/** Sets all pixels to false. */
	void zeroPixels() { fill(Pixel(0)); }

	/** Copies only the pixel values from another mask.
	    @throw std::logic_error exception if sizes do not match. */
	void copyPixels (const Image & im);

	/** Returns whether the mask is properly built (i.e. pixels are allocated). Same as exists(). */
	operator bool() const { return m_pixels != nullptr; }
	/** Returns whether the mask is properly built (i.e. pixels are allocated). */
	bool exists() const { return m_pixels != nullptr; }

	/** Returns the width of the mask, in pixels. */
	inline unsigned width() const { return m_width; }

	/** Returns the height of the mask, in pixels. */
	inline unsigned height() const { return m_height; }

	/** Returns a copy of the mask, scaled to half size in both width and height. */
	Image<bool> halfCopy() const;

	/** Returns the pixel at given position (between 0 and width x height). */
	inline Pixel & operator[] (unsigned k)
	{
		checkIndexOrThrow(k);
		if (! m_updateNeeded)
			m_updateNeeded = true;
		return m_pixels[k];
	}

	/** Returns the pixel at given position (between 0 and width x height). */
	inline Pixel operator[] (unsigned k) const
	{
		checkIndexOrThrow(k);
		return m_pixels[k];
	}

	/** Returns the pixel at given position (x = column/horizontal, y = row/vertical). */
	inline Pixel & operator() (unsigned x, unsigned y)
	{
		checkCoordsOrThrow(x, y);
		if (! m_updateNeeded)
			m_updateNeeded = true;
		return m_pixels[y * m_width + x];
	}

	/** Returns the pixel at given position (x = column/horizontal, y = row/vertical). */
	inline Pixel operator() (unsigned x, unsigned y) const
	{
		checkCoordsOrThrow(x, y);
		return m_pixels[y * m_width + x];
	}

	/// Returns the mean of the image.
	double mean (const Image<bool> * mask=nullptr) const;

	//! @cond EXCLUDE_FROM_PLUGINS_SDK
	void statMoments (int & m0, double & m1, double & m2, const Image<bool> * mask=nullptr) const;

	double moment (int i, int j, const Image<bool> * mask=nullptr) const;

	Xform2DParams mainAxis (int flags, const Image<bool> * mask=nullptr) const;
	//! @endcond

	/** Returns the number of pixels that are true.
	    Specific to Image<bool>. */
	unsigned surface() const;

	/** Returns whether all pixels of the mask are false. */
	bool empty() const;

	/** Returns whether all pixels of the mask are true. */
	bool full() const;

	/** Returns the bounding box of the mask.
	    @return a BoundingBox object (only the two first components are useful: 2D bounding box).
	    @warning If the mask is empty, m_box.lowerbound == m_box.upperbound == Point4(0, 0, 0, 0). */
	const BoundingBox & boundingBox() const;

	/// Computes and returns the inverse of the current mask.
	Image<bool> operator~() const;

	/// Inverses of the current mask.
	Image<bool> & inverse();

	/// Computes the intersection with the given mask.
	Image<bool> & operator&= (const Image<bool> & other);

	/// Computes the union with the given mask.
	Image<bool> & operator|= (const Image<bool> & other);

	/// Computes the complement with the given mask.
	Image<bool> & operator^= (const Image<bool> & other);

private:
	/** Recomputes all stored values: m_box and m_surface.
	    This method should only be called when the mask has changed
	    and not each time we get one of the stored values: use the @em m_updateNeeded member
	    to know if m_box and m_surface are up to date.
	    @warning this method is const to allow public methods such as surface(),
	    empty() and full() to be const. */
	void updateStoredValues() const;

//! @cond EXCLUDE_FROM_PLUGINS_SDK

protected:
	unsigned m_width;
	unsigned m_height;
	bool     m_own;
	Pixel *  m_pixels;

#if defined(_DEBUG)
	inline void checkIndexOrThrow (unsigned k) const
	{
		if (! m_pixels || k >= (m_width * m_height))
			throw IGTImageIndexOutOfBounds("Image<bool>", k, m_width, m_height);
	}

	inline void checkCoordsOrThrow (unsigned x, unsigned y) const
	{
		if (! m_pixels || x >= m_width || y >= m_height)
			throw IGTImageIndexOutOfBounds("Image<bool>", x + y * m_width, m_width, m_height);
	}

#else // if defined(_DEBUG)
	inline void checkIndexOrThrow (unsigned) const { }

	inline void checkCoordsOrThrow (unsigned, unsigned) const { }
#endif // if defined(_DEBUG)

	/** Flag to know whether the mask has changed.
	    If m_updateNeeded is true, stored values (m_box and m_surface) are no longer up to date. */
	mutable bool m_updateNeeded;

	/** The bounding box of the mask.
	    @warning If the mask is empty, m_box.lowerbound == m_box.upperbound == Point4(0, 0, 0, 0). */
	mutable BoundingBox m_box;

	/** The number of pixels in the mask whose value is true. */
	mutable unsigned m_surface;
//! @endcond
};


// Some template instanciations
/// A specialization of Image<> class for booleans.
typedef Image<bool> Mask;


//= =====================================================================
// Image<T> implementation


template <typename T>
Image<T>::Image(unsigned width, unsigned height) :
	m_width(width),
	m_height(height),
	m_own(false),
	m_pixels(nullptr)
{
	if (m_width * m_height > 0) {
		m_own    = true;
		m_pixels = new Pixel[m_width * m_height];
		zeroPixels();
	}
}


template <typename T> Image<T>::Image(const Image<T> & im) :
	m_width(im.m_width),
	m_height(im.m_height),
	m_own(im.m_own),
	m_pixels(nullptr)
{
	if (im.m_own && im.m_pixels) {
		m_pixels = new Pixel[m_width * m_height];
		copyPixels(im);
	} else
		m_pixels = im.m_pixels;
}


template <typename T> Image<T>::Image(unsigned width, unsigned height, T * pixels) :
	m_width(width),
	m_height(height),
	m_own(false),
	m_pixels(pixels)
{ }


template <typename T> Image<T> & Image<T>::operator= (const Image<T> & im)
{
	if (this == &im)
		return *this;
	if (m_own && m_pixels)
		delete[] m_pixels;

	m_width  = im.m_width;
	m_height = im.m_height;
	m_own    = im.m_own;

	if (im.m_own && im.m_pixels) {
		m_pixels = new Pixel[m_width * m_height];
		copyPixels(im);
	} else
		m_pixels = im.m_pixels;

	return *this;
}


template <typename T> Image<T> Image<T>::dup() const
{
	Image<T> im(*this);

	if (! m_own && m_pixels) {  // Make a copy anyway
		im.m_own    = true;
		im.m_pixels = new Pixel[m_width * m_height];
		im.copyPixels(*this);
	}

	return im;
}


template <typename T> inline double Image<T>::operator() (double x, double y) const
{
	int xi = int(std::floor(x));
	int yi = int(std::floor(y));

	if (! m_pixels)
		return 0.0f;
	if (xi < 0 || xi > (int)m_width - 1
	    || yi < 0 || yi > (int)m_height - 1)
		return 0.0f;

	double xf = x - xi;
	double yf = y - yi;

	return (1.0f - yf) * ((1.0f - xf) * m_pixels[yi * m_width + xi] + xf * m_pixels[yi * m_width + xi + 1])
	       + yf * ((1.0f - xf) * m_pixels[(yi + 1) * m_width + xi] + xf * m_pixels[(yi + 1) * m_width + xi + 1]);
}


template <typename T> void Image<T>::fillRow (unsigned row, const Pixel & pix)
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::fillRow", "null data");
	if (row >= m_height)
		throw IGTIndexOutOfBounds("Image::fillRow", row, m_height);
	unsigned start = row * m_width;
	unsigned end   = start + m_width;
	for (unsigned p = start; p < end; ++p) {
		m_pixels[p] = pix;
	}
}


template <typename T> void Image<T>::fillColumn (unsigned col, const Pixel & pix)
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::fillColumn", "null data");
	if (col >= m_width)
		throw IGTIndexOutOfBounds("Image::fillColumn", col, m_width);
	unsigned start = col;
	unsigned end   = start + (m_width * m_height);
	for (unsigned p = start; p < end; p += m_width) {
		m_pixels[p] = pix;
	}
}


template <typename T> void Image<T>::fill (const Pixel & pix)
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::fill", "null data");
	unsigned size = m_width * m_height;
	for (unsigned p = 0; p < size; ++p) {
		m_pixels[p] = pix;
	}
}


template <typename T> void Image<T>::fillFrom (const Pixel * array)
{
	if (array == nullptr)
		return;
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::fillFrom", "null data");
	::memcpy(m_pixels, array, m_width * m_height * sizeof(Pixel));
}


template <typename T> void Image<T>::copyPixels (const Image<T> & im)
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::fillFrom", "null data");
	if (m_width != im.m_width || m_height != im.m_height)
		throw std::logic_error("Image sizes mismatch");
	::memcpy(m_pixels, im.m_pixels, m_width * m_height * sizeof(Pixel));
}


template <typename T> T Image<T>::min() const
{
	// Note: k and pixelCount must be SIGNED integers for OpenMP
	int pixelCount = m_height * m_width;
	if (pixelCount > 0 && m_pixels) {
		Pixel minValue = m_pixels[0];
		int k          = 0;
		Pixel * ptr    = m_pixels; // OpenMP does not like members, use a local instead
#if USE_OPENMP
#  pragma omp parallel for shared(minValue, ptr, pixelCount) private(k) default(none)
#endif
		for (k = 0; k < pixelCount; ++k) {
			if (ptr[k] < minValue)
				minValue = ptr[k];
		}
		return minValue;
	}
	throw IGTImageIndexOutOfBounds("Image<T>::min()", 0, m_width, m_height);
}


template <typename T> T Image<T>::max() const
{
	// Note: k and pixelCount must be SIGNED integers for OpenMP
	int pixelCount = m_height * m_width;
	if (pixelCount > 0 && m_pixels) {
		Pixel maxValue = m_pixels[0];
		int k          = 0;
		Pixel * ptr    = m_pixels; // OpenMP does not like members, use a local instead
#if USE_OPENMP
#  pragma omp parallel for shared(maxValue, ptr, pixelCount) private(k) default(none)
#endif
		for (k = 0; k < pixelCount; ++k) {
			if (ptr[k] > maxValue)
				maxValue = ptr[k];
		}
		return maxValue;
	}
	throw IGTImageIndexOutOfBounds("Image<T>::max()", 0, m_width, m_height);
}


template <typename T> Image<T> Image<T>::scaledCopy (unsigned width, unsigned height) const
{
	if (width == m_width && height == m_height)
		return *this;
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::scaledCopy", "null data");
	Image<T> im(width, height);

	double xfact = static_cast<double>(width) / m_width;
	double yfact = static_cast<double>(height) / m_height;

	if (width > m_width) {
		unsigned k = 0;
		for (unsigned j = 0; j < height; ++j) {
			for (unsigned i = 0; i < width; ++i, ++k) {
				im.m_pixels[k] = static_cast<T>((*this)(i / xfact, j / yfact));
			}
		}
	} else {
		unsigned k = 0;
		for (unsigned j = 0; j < height; ++j) {
			for (unsigned i = 0; i < width; ++i, ++k) {
				double xo    = i / xfact;
				double yo    = j / yfact;
				unsigned io  = int(std::floor(xo));
				unsigned wjo = int(std::floor(yo * m_width));

				im.m_pixels[k] = m_pixels[wjo + io];
			}
		}
	}

	return im;
}


template <typename T> Image<T> Image<T>::halfCopy() const
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::halfCopy", "null data");
	Image<T> res(m_width / 2, m_height / 2);

	unsigned k = 0;
	for (unsigned j = 0; j < res.m_height; ++j) {
		for (unsigned i = 0; i < res.m_width; ++i, ++k) {
			res.m_pixels[k] = (m_pixels[j * 2 * m_width + i * 2] + m_pixels[j * 2 * m_width + i * 2 + 1]
			                   + m_pixels[(j * 2 + 1) * m_width + i * 2] + m_pixels[(j * 2 + 1) * m_width + i * 2 + 1])
			    / 4;
		}
	}

	return res;
}


//! @cond EXCLUDE_FROM_PLUGINS_SDK
template <typename T> void Image<T>::statMoments (int & m0, double & m1, double & m2, const Mask * mask) const
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::statMoments", "null data");
	if (mask) {
		if (mask->width() != m_width || mask->height() != m_height)
			throw IGTInvalidParameterErr("Image::statMoments", "Image sizes mismatch");
		if (! mask->exists())
			throw IGTInvalidParameterErr("Image::statMoments", "null mask's data");
	}
	m0 = 0;
	m1 = 0.0f;
	m2 = 0.0f;

	unsigned pixelCount = m_width * m_height;
	for (unsigned k = 0; k < pixelCount; ++k) {
		if (! mask || (*mask)[k]) {
			++m0;
			double p = double(m_pixels[k]);
			m1 += p;
			m2 += p * p;
		}
	}
}


//! @endcond

template <typename T> double Image<T>::mean (const Mask * roi) const
{
	int m0;
	double m1, m2;

	statMoments(m0, m1, m2, roi);
	if (m0 > 0)
		return m1 / m0;
	return 0.;
}


//! @cond EXCLUDE_FROM_PLUGINS_SDK
template <typename T> double Image<T>::moment (int i, int j, const Mask * mask) const
{
	double M = 0.0f;
	if (mask) {
		if (mask->width() != m_width || mask->height() != m_height)
			throw IGTInvalidParameterErr("Image::moment", "Image sizes mismatch");
		if (! mask->exists())
			throw IGTInvalidParameterErr("Image::moment", "null mask's data");
	}
	unsigned k = 0;
	for (unsigned y = 0; y < m_height; ++y) {
		for (unsigned x = 0; x < m_width; ++x, ++k) {
			if (! mask || (*mask)[k])
				M += pow(double(x), i) * pow(double(y), j) * double(m_pixels[k]);
		}
	}

	return M;
}


//! @endcond

//! @cond EXCLUDE_FROM_PLUGINS_SDK
template <typename T> Xform2DParams Image<T>::mainAxis (int flags, const Mask * mask) const
{
	Xform2DParams P(flags);
	if (flags < Xform2DParams::TRANS)
		return P;

	double M  = moment(0, 0, mask); // returns P if M==0?
	double Mx = moment(1, 0, mask) / M;
	double My = moment(0, 1, mask) / M;

	P[0] = float(Mx);
	P[1] = float(My);

	if (flags < Xform2DParams::ROTATE)
		return P;

	double Mxx = moment(2, 0, mask) / M - Mx * Mx;
	double Myy = moment(0, 2, mask) / M - My * My;
	double Mxy = moment(1, 1, mask) / M - Mx * My;

	P[2] = float(std::atan2(2.0 * Mxy, Mxx - Myy) / 2.0);

	if (flags < Xform2DParams::SCALE)
		return P;

	// Covariance matrix eigenvalues
	P[3] = float(((Mxx + Myy) + std::sqrt(4.0 * Mxy * Mxy + (Mxx - Myy) * (Mxx - Myy))) / 2.0);
	P[4] = float(((Mxx + Myy) + std::sqrt(4.0 * Mxy * Mxy - (Mxx - Myy) * (Mxx - Myy))) / 2.0);

	if (flags < Xform2DParams::SHEAR)
		return P;

	P[5] = 0.0f;  // No shear factor computable, or so it seems.

	return P;
}


//! @endcond

/*
   template <typename T> VectorField Image<T>::gradient(const Mask* mask) const
   {
    VectorField g(m_width, m_height);

    unsigned k = m_width + 1;
    for (unsigned j = 1; j < m_height - 1; ++j, k += 2)
        for (unsigned i = 1; i < m_width - 1; ++i, ++k)
            g[k].set((m_pixels[k + 1] - m_pixels[k - 1]) / 2.0f, (m_pixels[k + m_width] - m_pixels[k - m_width]) / 2.0f);

    return g;
   }
 */
//! @cond EXCLUDE_FROM_PLUGINS_SDK
template <typename T> Image<double> Image<T>::laplacian() const
{
	if (! m_pixels)
		throw IGTInvalidParameterErr("Image::laplacian", "null data");
	Image<double> res(m_width, m_height);
	unsigned k = m_width + 1;
	for (unsigned j = 1; j < m_height - 1; ++j, k += 2) {
		for (unsigned i = 1; i < m_width - 1; ++i, ++k) {
			unsigned index1 = k - m_width - 1;
			unsigned index2 = k - m_width;
			unsigned index3 = k - m_width + 1;
			unsigned index4 = k - 1;
			unsigned index5 = k + 1;
			unsigned index6 = k + m_width - 1;
			unsigned index7 = k + m_width;
			unsigned index8 = k + m_width + 1;
			res[k] = (8.0f * m_pixels[k] - double(m_pixels[index1] + m_pixels[index2] + m_pixels[index3]
			                                      + m_pixels[index4] + m_pixels[index5]
			                                      + m_pixels[index6] + m_pixels[index7] + m_pixels[index8]))
			    / 9.0f;
		}
	}

	return res;
}


//! @endcond

// template <typename T> Mask Image<T>::snrMask(double echoTime, double deltaT) const
// {
//	static const double B0		= 1.5f;		// MRI's magnetic field magnitude (T)
//	static const double gammaH	= 42.56E6;  // Hydrogen's gyromagnetic ratio (Hz/T)
//	static const double PRF		= gammaH * 9.0E-9 * B0 * 2*M_PI; // Protonic Resonance Frequency (K^-1)
//
//	Mask snr(m_width, m_height);
//
//	Image<double>& l = laplacian();
//
//	int		M0;
//	double	M1;
//	double	M2;
//	l.statMoments(M0, M1, M2);
//
//	double var = M2 / M0 - (M1 * M1) / (M0 * M0);
//	double stdev = std::sqrt(var);
//
//	double threshold = stdev / (deltaT * PRF * echoTime);
//
//	unsigned k = m_width + 1;
//    for (unsigned j = 1; j < m_height - 1; ++j, k += 2)
//		for (unsigned i = 1; i < m_width - 1; ++i, ++k)
//			if (double(m_pixels[k]) >= threshold)
//				snr.set(k, true);
//
//	return snr;
// }


template <typename T> void Image<T>::shiftRows (int shift)
{
	if (! m_pixels)
		return;
	unsigned offset = 0;
	if (shift >= 0)
		offset = shift % m_height;
	else
		offset = m_height - ( (-shift) % m_height);
	if (offset == 0)
		return;

	Pixel * const buffer = new Pixel[offset * m_width];
	// save overlapped content into temp. buffer (bottom of image)
	std::memcpy(buffer, m_pixels + (m_height - offset) * m_width, offset * m_width * sizeof(Pixel));
	// move remaining content
	std::memmove(m_pixels + offset * m_width, m_pixels, (m_height - offset) * m_width * sizeof(Pixel));
	// restore saved content on the other side (at the top)
	std::memcpy(m_pixels, buffer, offset * m_width * sizeof(Pixel));
	delete[] buffer;
}


template <typename T> void Image<T>::shiftColumns (int shift)
{
	if (! m_pixels)
		return;
	unsigned offset = 0;
	if (shift >= 0)
		offset = shift % m_width;
	else
		offset = m_width - ( (-shift) % m_width);
	if (offset == 0)
		return;

	Pixel * const buffer = new Pixel[offset];
	Pixel * beginOfRow   = m_pixels;
	Pixel * endOfRow     = m_pixels + m_width - offset;
	for (unsigned y = 0; y < m_height; ++y) {
		// save overlapped content (end of row) into a buffer
		std::memcpy(buffer, endOfRow, offset * sizeof(Pixel));
		// shift the remaining content right
		std::memmove(beginOfRow + offset, beginOfRow, (m_width - offset) * sizeof(Pixel));
		// restore saved content at the beginning
		std::memcpy(beginOfRow, buffer, offset * sizeof(Pixel));
		beginOfRow += m_width;
		endOfRow   += m_width;
	}
	delete[] buffer;
}


template <typename T> void Image<T>::mirror (bool leftRight, bool upDown)
{
	if (! m_pixels)
		return;
	if (leftRight == false && upDown == false)
		return;
	if (m_pixels == nullptr)
		return;

	Pixel * paa, * pa, * pbb, * pb, t;

	if (leftRight && m_width > 1) {
		// Mirror horizontally
		paa = m_pixels;
		pbb = m_pixels + m_width * m_height;
		do {
			pa   = paa;
			paa += m_width;
			pb   = paa;
			do {
				t     = *--pb;
				*pb   = *pa;
				*pa++ = t;
			}
			while (pa < pb);
		}
		while (paa < pbb);
	}

	if (upDown && m_height > 1) {
		// Mirror vertically
		paa = m_pixels;
		pbb = m_pixels + m_width * (m_height - 1);
		do {
			pa   = paa;
			paa += m_width;
			pb   = pbb;
			pbb -= m_width;
			do {
				t     = *pa;
				*pa++ = *pb;
				*pb++ = t;
			}
			while (pa < paa);
		}
		while (paa < pbb);
	}
}


template <typename T> bool Image<T>::swapQuarters()
{
	if (! m_pixels)
		return false;
	if ((m_width % 2) || (m_height % 2) || m_width == 0 || m_height == 0)
		return false;

	unsigned w2    = m_width / 2;
	Pixel * buffer = new Pixel[w2];
	unsigned h2    = m_height / 2;
	// Q1 Q2 --> Q4 Q3
	// Q3 Q4     Q2 Q1
	Pixel * q1      = m_pixels;
	Pixel * q2      = q1 + w2;
	Pixel * q3      = m_pixels + h2 * m_width;
	Pixel * q4      = q3 + w2;
	unsigned w2size = w2 * sizeof(Pixel);
	for (unsigned y = 0; y < h2; ++y) {
		// Q1 <--> Q4
		memcpy(buffer, q1, w2size);
		memcpy(q1, q4, w2size);
		memcpy(q4, buffer, w2size);
		q1 += m_width;
		q4 += m_width;

		// Q2 <--> Q3
		memcpy(buffer, q2, w2size);
		memcpy(q2, q3, w2size);
		memcpy(q3, buffer, w2size);
		q2 += m_width;
		q3 += m_width;
	}
	delete[] buffer;
	return true;
}


// ----------------------------------------------------------------------
// global functions using Image<>s


template <typename T> double * transformedImage (const Matrix & mat, const Image<T> & im)
{
	if (mat.columns() != 3 && mat.rows() != 3)
		throw std::domain_error("Matrix * Image: Not a 2D transform");
	if (! im.exists())
		throw IGTInvalidParameterErr("transformedImage", "null data");
	double * res(new double[im.width() * im.height()]);

	unsigned k = 0;
	for (unsigned y = 0; y < im.height(); ++y) {
		for (unsigned x = 0; x < im.width(); ++x, ++k) {
			res[k] = im(mat[0] * (x - im.width() / 2.0f) +
				mat[1] * (y - im.height() / 2.0f) +
				mat[2] + im.width() / 2.0f,
				mat[3] * (x - im.width() / 2.0f) +
				mat[4] * (y - im.height() / 2.0f) +
				mat[5] + im.height() / 2.0f);
		}
	}

	return res;
}


/*
   template <typename T> Image<T> operator*(const Matrix& mat, const Image<T>& im)
   {
    if (mat.columns() != 3 && mat.rows() != 3)
        throw std::domain_error("Matrix * Image: Not a 2D transform");

    Image<T> res(im.width(), im.height());

    unsigned k = 0;
    for (unsigned y = 0; y < res.height(); ++y)
        for (unsigned x = 0; x < res.width(); ++x, ++k)
            res[k] = im(mat[0] * (x - res.width() / 2.0f) +
                        mat[1] * (y - res.height() / 2.0f) +
                        mat[2] + res.width() / 2.0f,
                        mat[3] * (x - res.width() / 2.0f) +
                        mat[4] * (y - res.height() / 2.0f) +
                        mat[5] + res.height() / 2.0f);

    return res;
   }


   template <typename T> Image<T> operator*(const VectorField& vf, const Image<T>& im)
   {
    if (vf.width() != im.width() || vf.height() != im.height())
        throw std::domain_error("VectorField * Image: Sizes mismatch");

    Image<T> res(im.width(), im.height());

    unsigned k = 0;
    for (unsigned y = 0; y < res.height(); ++y)
        for (unsigned x = 0; x < res.width(); ++x, ++k)
            res[k] = im(x + vf[k].x(), y + vf[k].y());

    return res;
   }


   template <typename T> double* apply(const VectorField& vf, const Image<T>& im)
   {
    if (vf.width() != im.width() || vf.height() != im.height())
        throw std::domain_error("Vector field * Image: Sizes mismatch");

    double* res(new double[im.width() * im.height()]);

    unsigned k = 0;
    for (unsigned y = 0; y < im.height(); ++y)
        for (unsigned x = 0; x < im.width(); ++x, ++k)
            res[k] = im(x + vf[k].x(), y + vf[k].y());

    return res;
   }
 */

}  // namespace core
#endif  // ImageH
