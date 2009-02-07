// $Id$

#include "Port.h"

#if !defined (__CUTS_INLINE__)
#include "Port.inl"
#endif

#include "ace/CORBA_macros.h"

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Input_Event_Port

//
// CUTS_Input_Event_Port
//
CUTS_Input_Event_Port::~CUTS_Input_Event_Port (void)
{
  outputs_type::ITERATOR iter (this->outputs_);

  for ( ; !iter.done (); ++ iter)
    delete *iter;
}

//
// new_output_port
//
CUTS_Output_Event_Port * CUTS_Input_Event_Port::new_output_port (void)
{
  CUTS_Output_Event_Port * port = 0;

  ACE_NEW_THROW_EX (port,
                    CUTS_Output_Event_Port (this->parent_),
                    ACE_bad_alloc ());

  this->outputs_.insert (port);

  return port;
}
