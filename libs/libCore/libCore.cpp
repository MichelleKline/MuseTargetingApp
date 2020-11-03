// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers
#include <windows.h>
//#include <wx/msw/winundef.h> // See http://www.wxwidgets.org/docs/faqmsw.htm#asuffix

#if _DEBUG && USE_LEAK_DETECTOR
	#  include <vld.h>
#endif

#include "libCore.h"

//#include "Core/sigslot.h"  // To force the compilation of non-template classes of sigslot.h.

BOOL APIENTRY DllMain (HANDLE  /*hModule*/,
	DWORD ul_reason_for_call,
	LPVOID  /*lpReserved*/)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
