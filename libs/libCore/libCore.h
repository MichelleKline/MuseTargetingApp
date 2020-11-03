// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#ifndef LIBCORE_H
#define LIBCORE_H

#if LIBCORE_STATIC
	#  define TGCORE_API
#else
	#  ifdef LIBCORE_EXPORTS
	#    define TGCORE_API __declspec(dllexport)
	#  else
	#    define TGCORE_API __declspec(dllimport)
	#  endif
#endif

/** Contains generic classes, mostly mathematical (geometric) tools. */
namespace core { }

/// @cond EXCLUDE_FROM_PLUGINS_SDK
/// The logging system.
//namespace logger { }
/// @endcond

/** Examination namespace. */
namespace exam { }

/** ROI namespace. */
namespace roi { }


/// @cond EXCLUDE_FROM_PLUGINS_SDK
/// Computes statistics on a sequence.
namespace stats { }
/// @endcond

/// @cond EXCLUDE_FROM_PLUGINS_SDK
/// Sequence reconstructors.
namespace reconst { }
/// @endcond

#ifdef _MSC_VER
#  pragma warning(disable: 4290)
#endif


#ifdef _MSC_VER
#  define IGT_DEPRECATED(msg) __declspec(deprecated(msg))
#else
#  define IGT_DEPRECATED(msg)
#endif


#endif  // LIBCORE_H
