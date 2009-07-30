// -*- C++ -*-

//=============================================================================
/**
 * @file      Virtual_Env_Manager.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_VIRTUAL_ENV_MANAGER_H_
#define _CUTS_VIRTUAL_ENV_MANAGER_H_

#include "ace/SString.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/RW_Thread_Mutex.h"
#include "Node_Daemon_Common_export.h"

// Forward decl.
class CUTS_Virtual_Env;

/**
 * @class CUTS_Virtual_Env_Manager
 *
 * Container for managing virtual environments. Right now, only
 * one environment can be active per manager. Future version may
 * allow multiple environments to be active.
 */
class CUTS_NODE_DAEMON_COMMON_Export CUTS_Virtual_Env_Manager
{
public:
  /// Default constructor.
  CUTS_Virtual_Env_Manager (void);

  /// Destructor.
  ~CUTS_Virtual_Env_Manager (void);

  /**
   * Create a new virtual environment.
   *
   * @param[in]       name        Name of the new environment.
   */
  int create (const ACE_CString & name);

  /**
   * @overloaded
   *
   * @param[in]       name        Name of the new environment.
   * @param[in]       env         Newly created environment.
   */
  int create (const ACE_CString & name, CUTS_Virtual_Env * & env);

  /**
   * Find the environment with the specified name.
   */
  int find (const ACE_CString & name, CUTS_Virtual_Env * & env);

  /**
   * Destroy the specified virtual environment.
   *
   * @param[in]       name        Name of the environment to destroy.
   */
  int destroy (const ACE_CString & name);

  /// Close the virtual environment manager.
  void close (void);

  int set_active_environment (const ACE_CString & name);

  CUTS_Virtual_Env *  get_active_environment (void);

private:
  /// Type definition for collection of virtual environments.
  typedef
    ACE_Hash_Map_Manager <ACE_CString,
                          CUTS_Virtual_Env *,
                          ACE_RW_Thread_Mutex> VIRTUAL_ENV_TABLE;

  /// Collection of managed environments.
  VIRTUAL_ENV_TABLE env_table_;

  /// Pointer to the active environment.
  CUTS_Virtual_Env * active_;
};

#if defined (__CUTS_INLINE__)
#include "Virtual_Env_Manager.inl"
#endif

#endif  // !defined _CUTS_VIRTUAL_ENV_MANAGER_H_
