// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

//	Some macros to ease the definition of new events from wxWidgets.
//	Include this file after wx/event.h.

#pragma once

#ifndef DECLARE_EVENT_TABLE_ENTRY
#  pragma message ("WARNING: You should include wx/event.h first.")
#endif

namespace core {

#define EVENT_HANDLER_TYPE(evtClass__) void (wxEvtHandler::*)(evtClass__ &)
#define EVENT_HANDLER(evtClass__, fn) \
	(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(EVENT_HANDLER_TYPE(evtClass__), fn)


// For dynamic connections using wxEvtHandler::Connect and wxEvtHandler::Disconnect
template <class Event__, class EvtHandler__>
inline wxObjectEventFunction EventHandler (void (EvtHandler__::* fn)(Event__ &))
{
	return EVENT_HANDLER(Event__, fn);
}


// Id range declaration
#define IGT_DECLARE_EVENT_ID2_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, idFirst, idLast, fn, obj) \
	DECLARE_EVENT_TABLE_ENTRY(EVENT_TYPE__, idFirst, idLast, \
		EVENT_HANDLER(evtClass__, &fn), static_cast<wxObject *>(obj)),

#define IGT_DECLARE_EVENT_ID2_TABLE_ENTRY(evtClass__, EVENT_TYPE__, idFirst, idLast, fn) \
	IGT_DECLARE_EVENT_ID2_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, idFirst, idLast, fn, 0)

// Single id declaration
#define IGT_DECLARE_EVENT_ID_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, id, fn, obj) \
	IGT_DECLARE_EVENT_ID2_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, id, wxID_ANY, fn, obj)

#define IGT_DECLARE_EVENT_ID_TABLE_ENTRY(evtClass__, EVENT_TYPE__, id, fn) \
	IGT_DECLARE_EVENT_ID_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, id, wxID_ANY, fn, 0)

// No id declaration
#define IGT_DECLARE_EVENT_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, fn, obj) \
	IGT_DECLARE_EVENT_ID_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, wxID_ANY, fn, obj)

#define IGT_DECLARE_EVENT_TABLE_ENTRY(evtClass__, EVENT_TYPE__, fn) \
	IGT_DECLARE_EVENT_OBJ_TABLE_ENTRY(evtClass__, EVENT_TYPE__, fn, 0)


// Call DEFINE_EVENT_HANDLER_TYPE below before using the name macro.
#define EVENT_FUNCTION_NAME(evtClass__) evtClass__ ## Function
#define DEFINE_EVENT_FUNCTION_TYPE(evtClass__) \
	typedef void (wxEvtHandler::* EVENT_FUNCTION_NAME(evtClass__))(evtClass__ &)


// Use only in a wxEvent derived class.
#define DEFINE_CLONE(evtClass__) \
	virtual wxEvent * Clone() const { return new evtClass__(*this); }

}  // namespace core
