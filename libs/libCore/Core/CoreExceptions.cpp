// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "CoreExceptions.h"

//#include "Logger/LogManager.h"
#include <sstream>

#include <windows.h>
//#include <wx/msw/winundef.h>  // See http://www.wxwidgets.org/docs/faqmsw.htm#asuffix

namespace core {

IGTException::IGTException(const std::string & msg) :
	std::exception()
	, message(msg)
{ }


const char * IGTException::what() const
{
	return message.c_str();
}


const char * IGTException::getAndLogMsg() const
{
	const char * msg = what();

	//logger::getLog()->logBlockHeader("Exception thrown! Message reads: ");
	//logger::getLog()->logAPP(msg, logger::LOG_ERROR);
	//logger::getLog()->logBlockEnd("Exception message end.");
	return msg;
}


// class IGTDivideByZeroErr

IGTDivideByZeroErr::IGTDivideByZeroErr(const std::string & caller) :
	IGTException(std::string("Divide by zero exception in class ") + caller)
{ }


// class IGTInvalidParameterErr

IGTInvalidParameterErr::IGTInvalidParameterErr(const std::string & caller, const std::string & message) :
	IGTException(std::string("Invalid parameter in class \"") + caller + "\": " + message)
{ }


// class IGTImageIndexOutOfBounds

IGTImageIndexOutOfBounds::IGTImageIndexOutOfBounds(const std::string & caller, int id, int width, int height) :
	IGTException()
{
	std::stringstream msg;
	msg << "Index " << id << "  out of bounds (width = " << width << ", height = " << height <<
	    ") when trying to access a pixel in class " << caller;
	message = msg.str();
}


// class IGTSliceIndexOutOfBounds

IGTSliceIndexOutOfBounds::IGTSliceIndexOutOfBounds(const std::string & caller, int id, int sliceCount) :
	IGTException()
{
	std::stringstream msg;
	msg << "Slice index " << id << "  out of bounds (size = " << sliceCount <<
	    ") when trying to access an element in function " << caller;
	message = msg.str();
}


// class IGTGraphIndexOutOfBounds

IGTGraphIndexOutOfBounds::IGTGraphIndexOutOfBounds(const std::string & caller, int id, int width, int height) :
	IGTException()
{
	std::stringstream msg;
	msg << "Index " << id << "  out of bounds (width = " << width << ", height = " << height <<
	    ") when trying to access an element in class " << caller;
	message = msg.str();
}


// class IGTIndexOutOfBounds

IGTIndexOutOfBounds::IGTIndexOutOfBounds(const std::string & caller, int id, int size) :
	IGTException()
{
	std::stringstream msg;
	msg << "Index " << id << "  out of bounds (size = " << size <<
	    ") when trying to access an element in class " << caller;
	message = msg.str();
}


// class IGTIndexOutOfRanges

IGTIndexOutOfRanges::IGTIndexOutOfRanges(const std::string & caller, float value, float min, float max) :
	IGTException()
{
	std::stringstream msg;
	msg << "Value " << value << "  out of ranges [ " << min << ", " << max <<
	    "] when trying to access an element in class " << caller;
	message = msg.str();
}


// class IGTCoordinateSystemErr

IGTCoordinateSystemErr::IGTCoordinateSystemErr(const std::string & caller, const std::string & sourceCoordSys, const std::string & destCoordSys)
{
	std::stringstream msg;
	msg << "Could not transform from " << sourceCoordSys << " coordinate system to " << destCoordSys << " coordinate system "
	    " in class " << caller;
	message = msg.str();
}


IGTWin32Exception::IGTWin32Exception(unsigned code_, const std::string & text) :
	IGTException()
	, code(code_)
{
	std::stringstream msg;
	msg << "Windows exception \"" << text << "\" thrown.";
	message = msg.str();
}


void IGTWin32Exception::translator (unsigned code_, struct _EXCEPTION_POINTERS *)
{
	std::string text;

	switch (code_) {
	case EXCEPTION_ACCESS_VIOLATION:
		text = "Access violation";
		break;
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		text = "Array bounds exceeded";
		break;
	case EXCEPTION_DATATYPE_MISALIGNMENT:
		text = "Datatype misalignment";
		break;
	case EXCEPTION_IN_PAGE_ERROR:
		text = "In page error";
		break;
	case EXCEPTION_STACK_OVERFLOW:
		text = "Stack overflow";
		break;

	case EXCEPTION_BREAKPOINT:
		text = "Breakpoint";
		break;
	case EXCEPTION_SINGLE_STEP:
		text = "Single step";
		break;

	case EXCEPTION_FLT_DENORMAL_OPERAND:
		text = "Float denormal operand";
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		text = "Float divide by zero";
		break;
	case EXCEPTION_FLT_INEXACT_RESULT:
		text = "Float inexact result";
		break;
	case EXCEPTION_FLT_INVALID_OPERATION:
		text = "Float invalid operation";
		break;
	case EXCEPTION_FLT_OVERFLOW:
		text = "Float overflow";
		break;
	case EXCEPTION_FLT_STACK_CHECK:
		text = "Float stack check";
		break;
	case EXCEPTION_FLT_UNDERFLOW:
		text = "Float underflow";
		break;

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		text = "Integer divide by zero";
		break;
	case EXCEPTION_INT_OVERFLOW:
		text = "Integer overflow";
		break;

	case EXCEPTION_ILLEGAL_INSTRUCTION:
		text = "Illegal instruction";
		break;
	case EXCEPTION_PRIV_INSTRUCTION:
		text = "Private instruction";
		break;

	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		text = "Non-continuable exception";
		break;
	case EXCEPTION_INVALID_DISPOSITION:
		text = "Invalid disposition";
		break;

	default:
		text = "<Unknown exception>";
	}

	throw IGTWin32Exception(code_, text);
}


}  // namespace core
