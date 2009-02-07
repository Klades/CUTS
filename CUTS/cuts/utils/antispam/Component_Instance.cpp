// $Id$

#include "Component_Instance.h"

#if !defined (__CUTS_INLINE__)
#include "Component_Instance.inl"
#endif

#include "Antispam_Visitor.h"
#include "Component.h"
#include "Port_Instance.h"
#include "ace/CORBA_macros.h"
#include "boost/bind.hpp"
#include <algorithm>
#include <numeric>

//
// CUTS_Component_Instance
//
CUTS_INLINE
CUTS_Component_Instance::
CUTS_Component_Instance (const ACE_CString & name,
                         const CUTS_Component & type)
: name_ (name),
  type_ (type)
{
  this->init ();
}


//
// ~CUTS_Component_Instance
//
CUTS_Component_Instance::~CUTS_Component_Instance (void)
{
  input_event_port_type::ITERATOR iter (this->input_events_);

  for ( ; !iter.done (); ++ iter)
    delete iter->int_id_;
}

//
// init
//
void CUTS_Component_Instance::init (void)
{
  std::for_each (this->type_.input_events ().begin (),
                 this->type_.input_events ().end (),
                 boost::bind (&CUTS_Component_Instance::new_input_event,
                              this,
                              _1));

  std::for_each (this->type_.start ().begin (),
                 this->type_.start ().end (),
                 boost::bind (&CUTS_Component_Instance::make_start,
                              this,
                              _1));
}

//
// new_input_event
//
void CUTS_Component_Instance::
new_input_event (const CUTS_Component::input_event_map_type::ENTRY & entry)
{
  // Allocate a new input event port instance.
  CUTS_Input_Event_Port_Instance * instance = 0;

  ACE_NEW_THROW_EX (instance,
                    CUTS_Input_Event_Port_Instance (*this, *entry.int_id_),
                    ACE_bad_alloc ());

  // Save the instance.
  this->input_events_.bind (entry.ext_id_, instance);

  // Visit each of the output ports.
  std::for_each (entry.int_id_->outputs ().begin (),
                 entry.int_id_->outputs ().end (),
                 boost::bind (&CUTS_Input_Event_Port_Instance::new_output,
                              instance,
                              _1));
}

//
// make_start
//
void CUTS_Component_Instance::
make_start (const CUTS_Input_Event_Port * port)
{
  CUTS_Input_Event_Port_Instance * instance = 0;

  if (this->input_events_.find (port->name (), instance) == 0)
    this->start_.insert (instance);
}

//
// accept
//
void CUTS_Component_Instance::
accept (CUTS_Antispam_Visitor & visitor)
{
  visitor.visit_CUTS_Component_Instance (*this);
}

//
// utilization
//
double CUTS_Component_Instance::utilization (void) const
{
  double util = 0.0;

  // The component's utilization is the sum of the utilization
  // of each of its input ports.
  input_event_port_type::CONST_ITERATOR iter (this->input_events_);

  for ( ; !iter.done (); ++ iter)
    util += iter->int_id_->utilization ();

  return util;
}
