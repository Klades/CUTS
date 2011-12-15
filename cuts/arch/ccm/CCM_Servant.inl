// -*- C++ -*-
// $Id$

//
// CUTS_CCM_Servant
//
CUTS_INLINE
CUTS_CCM_Servant::CUTS_CCM_Servant (const char * name)
: name_ (name)
{

}

//
// ~CUTS_CCM_Servant
//
CUTS_INLINE
CUTS_CCM_Servant::~CUTS_CCM_Servant (void)
{

}

//
// ~CUTS_CCM_Servant
//
CUTS_INLINE
const ACE_CString & CUTS_CCM_Servant::name (void) const
{
  return this->name_;
}

//
// ~CUTS_CCM_Servant
//
CUTS_INLINE
void CUTS_CCM_Servant::activate_component (void)
{

}

//
// ~CUTS_CCM_Servant
//
CUTS_INLINE
void CUTS_CCM_Servant::passivate_component (void)
{

}

//
// ~CUTS_CCM_Servant
//
CUTS_INLINE
void CUTS_CCM_Servant::remove (void)
{

}

//
// set_attributes
//
CUTS_INLINE
void CUTS_CCM_Servant::
set_attributes (const ::Components::ConfigValues &)
{

}
