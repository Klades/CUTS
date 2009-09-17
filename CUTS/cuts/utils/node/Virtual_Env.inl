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
// startup_list
//
CUTS_INLINE
CUTS_Process_Options_List & CUTS_Virtual_Env::startup_list (void)
{
  return this->startup_;
}

//
// startup_list
//
CUTS_INLINE
const CUTS_Process_Options_List & CUTS_Virtual_Env::startup_list (void) const
{
  return this->startup_;
}

//
// shutdown_list
//
CUTS_INLINE
CUTS_Process_Options_List & CUTS_Virtual_Env::shutdown_list (void)
{
  return this->shutdown_;
}

//
// shutdown_list
//
CUTS_INLINE
const CUTS_Process_Options_List & CUTS_Virtual_Env::shutdown_list (void) const
{
  return this->shutdown_;
}
