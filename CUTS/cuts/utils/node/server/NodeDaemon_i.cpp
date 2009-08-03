// $Id$

#include "NodeDaemon_i.h"

#if !defined (__CUTS_INLINE__)
#include "NodeDaemon_i.inl"
#endif

#include "../Virtual_Env_Manager.h"
#include "../Virtual_Env.h"

//
// active_environment
//
char * CUTS_NodeDaemon_i::active_environment (void)
{
  CUTS_Virtual_Env * env = this->virtual_envs_.get_active_environment ();

  if (0 == env)
    throw ::CUTS::NodeDaemon::NoActiveEnvironment ();

  ::CORBA::String_var str = ::CORBA::string_dup (env->name ().c_str ());
  return str._retn ();
}

//
// set_active_environment
//
void CUTS_NodeDaemon_i::
set_active_environment (const char * name)
{
  this->virtual_envs_.set_active_environment (name);
}

//
// reset
//
void CUTS_NodeDaemon_i::reset (void)
{
  CUTS_Virtual_Env * env = this->virtual_envs_.get_active_environment ();

  if (0 == env)
    throw ::CUTS::NodeDaemon::NoActiveEnvironment ();

  env->restart ();
}
