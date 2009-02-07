// $Id$

#include "Component.h"

#if !defined (__CUTS_INLINE__)
#include "Component.inl"
#endif

#include "ace/CORBA_macros.h"

//
// ~CUTS_Component
//
CUTS_Component::~CUTS_Component (void)
{
  input_event_map_type::ITERATOR iter (this->input_events_);

  for (; !iter.done (); ++ iter)
    delete iter->int_id_;
}

//
// new_input_event
//
CUTS_Input_Event_Port * CUTS_Component::
new_input_event (const ACE_CString & name, bool start)
{
  CUTS_Input_Event_Port * port = 0;

  ACE_NEW_THROW_EX (port,
                    CUTS_Input_Event_Port (this),
                    ACE_bad_alloc ());

  port->name (name);
  this->input_events_.bind (name, port);

  if (start)
    this->start_.insert (port);

  return port;
}
