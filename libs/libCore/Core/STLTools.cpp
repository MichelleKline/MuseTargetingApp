// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "STLTools.h"

namespace core {

std::string TGCORE_API removeFileExt (const std::string & fileName)
{
	std::string::size_type i = fileName.rfind('.');
	if (i == std::string::npos)
		return fileName;
	return fileName.substr(0, i);
}


std::string TGCORE_API getFileExt (const std::string & fileName)
{
	std::string::size_type i = fileName.rfind('.');
	if (i == std::string::npos)
		return std::string("");
	return fileName.substr(i + 1, fileName.size());
}


}  // namespace core
