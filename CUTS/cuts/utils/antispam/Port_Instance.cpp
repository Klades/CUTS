// $Id$

#include "Port_Instance.h"

#if !defined (__CUTS_INLINE__)
#include "Port_Instance.inl"
#endif

#include "Antispam_Visitor.h"
#include "ace/CORBA_macros.h"

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Input_Event_Port_Instance

//
// ~CUTS_Input_Event_Port_Instance
//
CUTS_Input_Event_Port_Instance::~CUTS_Input_Event_Port_Instance (void)
{
  outputs_type::ITERATOR iter (this->outputs_);

  for ( ; !iter.done (); ++ iter)
    delete *iter;
}

//
// new_output
//
CUTS_Output_Event_Port_Instance *
CUTS_Input_Event_Port_Instance::
new_output (const CUTS_Output_Event_Port * type)
{
  CUTS_Output_Event_Port_Instance * instance = 0;

  ACE_NEW_THROW_EX (instance,
                    CUTS_Output_Event_Port_Instance (this->parent_, *type),
                    ACE_bad_alloc ());

  this->outputs_.insert (instance);
  return instance;
}

//
// accept
//
void CUTS_Input_Event_Port_Instance::
accept (CUTS_Antispam_Visitor & visitor)
{
  visitor.visit_CUTS_Input_Event_Port_Instance (*this);
}

//
// reset
//
void CUTS_Input_Event_Port_Instance::reset (void)
{
  // Reset each of the output ports.
  outputs_type::ITERATOR iter (this->outputs_);

  for ( ; !iter.done (); ++ iter)
    (*iter)->reset ();

  // Pass control to the base class.
  CUTS_Port_Instance::reset ();
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Ouput_Event_Port_Instance

//
// accept
//
void CUTS_Output_Event_Port_Instance::
accept (CUTS_Antispam_Visitor & visitor)
{
  visitor.visit_CUTS_Output_Event_Port_Instance (*this);
}

