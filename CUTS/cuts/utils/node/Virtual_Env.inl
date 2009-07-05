// -*- C++ -*-
// $Id$

//
// CUTS_Virtual_Env
//
CUTS_INLINE
CUTS_Virtual_Env::CUTS_Virtual_Env (const ACE_CString & name)
: name_ (name),
  inherit_ (true)
{

}

//
// ~CUTS_Virtual_Env
//
CUTS_INLINE
CUTS_Virtual_Env::~CUTS_Virtual_Env (void)
{
  this->close ();
}

//
// env_table
//
CUTS_INLINE
CUTS_Property_Map & CUTS_Virtual_Env::env_table (void)
{
  return this->env_;
}

//
// env_table
//
CUTS_INLINE
const CUTS_Property_Map & CUTS_Virtual_Env::env_table (void) const
{
  return this->env_;
}

//
// name
//
CUTS_INLINE
const ACE_CString & CUTS_Virtual_Env::name (void) const
{
  return this->name_;
}

//
// start
//
CUTS_INLINE
int CUTS_Virtual_Env::start (void)
{
  return this->spawn (this->startup_);
}
