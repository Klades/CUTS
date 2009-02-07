// -*- C++ -*-
// $Id$

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Port_Instance

//
// CUTS_Port_Instance
//
CUTS_INLINE
CUTS_Port_Instance::
CUTS_Port_Instance (const CUTS_Component_Instance & parent,
                    const CUTS_Port & type)
: parent_ (parent),
  type_ (type),
  service_time_ (type.service_time ())
{

}

//
// CUTS_Port_Instance
//
CUTS_INLINE
CUTS_Port_Instance::~CUTS_Port_Instance (void)
{

}

//
// type
//
CUTS_INLINE
const CUTS_Port & CUTS_Port_Instance::type (void) const
{
  return this->type_;
}

//
// parent
//
CUTS_INLINE
const CUTS_Component_Instance & CUTS_Port_Instance::parent (void) const
{
  return this->parent_;
}

//
// reset
//
CUTS_INLINE
void CUTS_Port_Instance::reset (void)
{
  this->service_time_ = this->type_.service_time ();
}

//
// service_time
//
CUTS_INLINE
double CUTS_Port_Instance::service_time (void) const
{
  return this->service_time_;
}

//
// service_time
//
CUTS_INLINE
void CUTS_Port_Instance::service_time (double t)
{
  this->service_time_ = t;
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Input_Event_Port_Instance


//
// CUTS_Input_Event_Port_Instance
//
CUTS_INLINE
CUTS_Input_Event_Port_Instance::
CUTS_Input_Event_Port_Instance (const CUTS_Component_Instance & parent,
                                const CUTS_Input_Event_Port & type)
: CUTS_Port_Instance (parent, type),
  lambda_ (0.0)
{

}

//
// lambda
//
CUTS_INLINE
double CUTS_Input_Event_Port_Instance::lambda (void) const
{
  return this->lambda_;
}

//
// lambda
//
CUTS_INLINE
void CUTS_Input_Event_Port_Instance::lambda (double l)
{
  this->lambda_ = l;
}

//
// outputs
//
CUTS_INLINE
const CUTS_Input_Event_Port_Instance::outputs_type &
CUTS_Input_Event_Port_Instance::outputs (void) const
{
  return this->outputs_;
}

//
// utilization
//
CUTS_INLINE
double CUTS_Input_Event_Port_Instance::utilization (void) const
{
  return this->lambda_ * this->service_time_;
}

//
// utilization
//
CUTS_INLINE
double CUTS_Input_Event_Port_Instance::response_time (void) const
{
  // RT = 1 / (mu - lambda)
  return 1.0 / ((1.0 / this->service_time_) - this->lambda_);
}

///////////////////////////////////////////////////////////////////////////////
// class CUTS_Output_Event_Port_Instance

//
// CUTS_Output_Event_Port_Instance
//
CUTS_INLINE
CUTS_Output_Event_Port_Instance::
CUTS_Output_Event_Port_Instance (const CUTS_Component_Instance & parent,
                                 const CUTS_Output_Event_Port & type)
: CUTS_Port_Instance (parent, type)
{

}

//
// ~CUTS_Output_Event_Port_Instance
//
CUTS_INLINE
CUTS_Output_Event_Port_Instance::~CUTS_Output_Event_Port_Instance (void)
{

}

//
// new_connection
//
CUTS_INLINE
int CUTS_Output_Event_Port_Instance::
new_connection (CUTS_Input_Event_Port_Instance * input)
{
  return this->conns_.insert (input);
}

//
// service_time
//
CUTS_INLINE
double CUTS_Output_Event_Port_Instance::service_time (void) const
{
  return this->service_time_;
}

//
// new_connection
//
CUTS_INLINE
void CUTS_Output_Event_Port_Instance::service_time (double t)
{
  this->service_time_ = t;
}

//
// connections
//
CUTS_INLINE
const CUTS_Output_Event_Port_Instance::connections_type &
CUTS_Output_Event_Port_Instance::connections (void) const
{
  return this->conns_;
}
