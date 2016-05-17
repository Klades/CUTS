// -*- C++ -*-
// $Id$

namespace iCCM
{

//
// Servant
//
CUTS_INLINE
Servant::Servant (const char * name)
: name_ (name)
{

}

//
// ~Servant
//
CUTS_INLINE
Servant::~Servant (void)
{

}

//
// name
//
CUTS_INLINE
const ACE_CString & Servant::name (void) const
{
  return this->name_;
}

//
// activate_component
//
CUTS_INLINE
void Servant::activate_component (void)
{

}

//
// ~Servant
//
CUTS_INLINE
void Servant::passivate_component (void)
{

}

//
// remove
//
CUTS_INLINE
void Servant::remove (void)
{

}

//
// set_attributes
//
CUTS_INLINE
void Servant::
set_attributes (const ::Components::ConfigValues &)
{

}

//
// handle_config
//
void Servant::handle_config (const ::Components::ConfigValues & values)
{

}

}
