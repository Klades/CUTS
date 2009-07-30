// $Id$

#include "Virtual_Env_Manager.h"

#if !defined (__CUTS_INLINE__)
#include "Virtual_Env_Manager.inl"
#endif

#include "Virtual_Env.h"
#include "ace/CORBA_macros.h"

//
// close
//
void CUTS_Virtual_Env_Manager::close (void)
{
  for (VIRTUAL_ENV_TABLE::ITERATOR iter (this->env_table_);
       !iter.done ();
       ++ iter)
  {
    delete iter->item ();
  }

  // Remove all the entries in the virtual table.
  this->env_table_.unbind_all ();
}

//
// create
//
int CUTS_Virtual_Env_Manager::
create (const ACE_CString & name, CUTS_Virtual_Env * & env)
{
  // Allocate a new virtual environment.
  CUTS_Virtual_Env * temp = 0;

  ACE_NEW_THROW_EX (temp,
                    CUTS_Virtual_Env (name),
                    ACE_bad_alloc ());

  ACE_Auto_Ptr <CUTS_Virtual_Env> auto_clean (temp);

  // Store the virtual environment.
  int retval = this->env_table_.bind (name, temp);

  if (0 == retval)
    env = auto_clean.release ();

  return retval;
}

//
// destroy
//
int CUTS_Virtual_Env_Manager::destroy (const ACE_CString & name)
{
  // Locate the environment to destroy.
  CUTS_Virtual_Env * env = 0;

  if (0 != this->env_table_.unbind (name, env))
    return -1;

  // Delete the environment. This will automatically close it.
  if (0 != env)
    delete env;

  return 0;
}

//
// set_active_environment
//
int CUTS_Virtual_Env_Manager::
set_active_environment (const ACE_CString & name)
{
  CUTS_Virtual_Env * env = 0;
  if (0 != this->env_table_.find (name, env))
    return -1;

  // Shutdown the active environment if it exists.
  if (0 != this->active_)
  {
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("%T (%t) - %M - shutting down %s environment\n"),
                this->active_->name ().c_str ()));

    this->active_->shutdown ();
    this->active_ = 0;
  }

  // Activate the new environment, and cache it.
  if (0 == env->start ())
    this->active_ = env;

  return 0 != this->active_ ? 0 : -1;
}
