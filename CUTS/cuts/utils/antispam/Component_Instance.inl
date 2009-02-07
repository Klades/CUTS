// $Id$

//
// type
//
CUTS_INLINE
const CUTS_Component & CUTS_Component_Instance::type (void) const
{
  return this->type_;
}

//
// input_events
//
CUTS_INLINE
const CUTS_Component_Instance::input_event_port_type &
CUTS_Component_Instance::input_events (void) const
{
  return this->input_events_;
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Component_Instance::name (void) const
{
  return this->name_;
}

//
// start
//
CUTS_INLINE
const CUTS_Component_Instance::start_type &
CUTS_Component_Instance::start (void) const
{
  return this->start_;
}
