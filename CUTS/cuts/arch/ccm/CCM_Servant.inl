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
