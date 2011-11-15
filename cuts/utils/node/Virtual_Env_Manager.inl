// -*- C++ -*-
// $Id$

//
// CUTS_Virtual_Env_Manager
//
CUTS_INLINE
CUTS_Virtual_Env_Manager::CUTS_Virtual_Env_Manager (void)
: active_ (0)
{

}

//
// ~CUTS_Virtual_Env_Manager
//
CUTS_INLINE
CUTS_Virtual_Env_Manager::~CUTS_Virtual_Env_Manager (void)
{
  this->close ();
}

//
// create
//
CUTS_INLINE
int CUTS_Virtual_Env_Manager::create (const ACE_CString & name)
{
  CUTS_Virtual_Env * env = 0;
  return this->create (name, env);
}

//
// find
//
CUTS_INLINE
int CUTS_Virtual_Env_Manager::
find (const ACE_CString & name, CUTS_Virtual_Env * & env)
{
  return this->env_table_.find (name, env);
}

//
// get_active_environment
//
CUTS_INLINE
CUTS_Virtual_Env * CUTS_Virtual_Env_Manager::get_active_environment (void)
{
  return this->active_;
}
