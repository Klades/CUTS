// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Port

//
// CUTS_Port
//
CUTS_INLINE
CUTS_Port::CUTS_Port (CUTS_Component * parent)
: parent_ (parent),
  service_time_ (0.0)
{

}

//
// ~CUTS_Port
//
CUTS_INLINE
CUTS_Port::~CUTS_Port (void)
{

}

//
// name
//
CUTS_INLINE
void CUTS_Port::name (const ACE_CString & name)
{
  this->name_ = name;
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Port::name (void) const
{
  return this->name_;
}

//
// service_time
//
CUTS_INLINE
double CUTS_Port::service_time (void) const
{
  return this->service_time_;
}

//
// service_time
//
CUTS_INLINE
void CUTS_Port::service_time (double t)
{
  this->service_time_ = t;
}

//
// parent
//
CUTS_INLINE
CUTS_Component & CUTS_Port::parent (void)
{
  return *this->parent_;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Input_Event_Port

//
// CUTS_Input_Event_Port
//
CUTS_INLINE
CUTS_Input_Event_Port::
CUTS_Input_Event_Port (CUTS_Component * parent)
: CUTS_Port (parent)
{

}

//
// outputs
//
CUTS_INLINE
CUTS_Input_Event_Port::outputs_type &
CUTS_Input_Event_Port::outputs (void)
{
  return this->outputs_;
}


//
// outputs
//
CUTS_INLINE
const CUTS_Input_Event_Port::outputs_type &
CUTS_Input_Event_Port::outputs (void) const
{
  return this->outputs_;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Output_Event_Port

//
// CUTS_Output_Event_Port
//
CUTS_INLINE
CUTS_Output_Event_Port::
CUTS_Output_Event_Port (CUTS_Component * parent)
: CUTS_Port (parent)
{

}

//
// CUTS_Output_Event_Port
//
CUTS_INLINE
CUTS_Output_Event_Port::~CUTS_Output_Event_Port (void)
{

}
