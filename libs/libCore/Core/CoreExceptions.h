// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef CoreExceptionsH
#  define CoreExceptionsH

#  include <exception>
#  include "../libCore.h"
#  include <string>

namespace core {

#pragma warning(push)
#pragma warning(disable: 4275)

/**
 * @brief IGTException is the base class for all IGT exceptions.
 */
class TGCORE_API IGTException : public std::exception
{
public:
	/**
	 * Constructor.
	 * @param msg The exception message.
	 */
	explicit IGTException(const std::string & msg="");

	/** Destructor. */
	virtual ~IGTException() throw () { }

	/** Returns the exception message. */
	virtual const char * what() const /*throw ()*/;

	/** Returns the exception message and writes it to the log file. */
	virtual const char * getAndLogMsg() const;

protected:
	/** The exception message. */
	std::string message;
};

#pragma warning(push)


/// An exception to throw division by zero errors.
class TGCORE_API IGTDivideByZeroErr : public IGTException
{
public:
	/// Constructor.
	explicit IGTDivideByZeroErr(const std::string & caller);
};


/// An exception to throw invalid parameters errors.
class TGCORE_API IGTInvalidParameterErr : public IGTException
{
public:
	/// Constructor.
	explicit IGTInvalidParameterErr(const std::string & caller, const std::string & message);
};


/// An exception to throw out of bounds index of an image.
class TGCORE_API IGTImageIndexOutOfBounds : public IGTException
{
public:
	/// Constructor.
	IGTImageIndexOutOfBounds(const std::string & caller, int id, int width, int height);
};


/// An exception to throw out of bounds index of a slice.
class TGCORE_API IGTSliceIndexOutOfBounds : public IGTException
{
public:
	/// Constructor.
	IGTSliceIndexOutOfBounds(const std::string & caller, int id, int sliceCount);
};


/// An exception to throw out of bounds index in a graph.
class TGCORE_API IGTGraphIndexOutOfBounds : public IGTException
{
public:
	/// Constructor.
	IGTGraphIndexOutOfBounds(const std::string & caller, int id, int width, int height);
};


/// An exception to throw generic out of bounds index.
class TGCORE_API IGTIndexOutOfBounds : public IGTException
{
public:
	/// Constructor.
	IGTIndexOutOfBounds(const std::string & caller, int id, int size);
};


/// An exception to throw generic out of ranges index.
class TGCORE_API IGTIndexOutOfRanges : public IGTException
{
public:
	/// Constructor.
	IGTIndexOutOfRanges(const std::string & caller, float value, float min, float max);
};


/// An exception to throw coordinate system errors.
class TGCORE_API IGTCoordinateSystemErr : public IGTException
{
public:
	/// Constructor.
	IGTCoordinateSystemErr(const std::string & caller,
	                       const std::string & sourceCoordSys,
	                       const std::string & destCoordSys);
};


/// An exception to rethrow win32 exceptions.
class TGCORE_API IGTWin32Exception : public IGTException
{
public:
	/// Translator.
	static void translator (unsigned code_, struct _EXCEPTION_POINTERS * ep);

private:
	explicit IGTWin32Exception(unsigned code_, const std::string & text="Unknown");

	unsigned code;
};


}  // namespace core

#endif // ifndef CoreExceptionsH
