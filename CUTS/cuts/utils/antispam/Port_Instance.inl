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
  type_ (type)
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
const CUTS_Input_Event_Port_Instance::output_set_type &
CUTS_Input_Event_Port_Instance::outputs (void) const
{
  return this->outputs_;
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
new_connection (const CUTS_Input_Event_Port_Instance * input)
{
  return this->conns_.insert (input);
}
