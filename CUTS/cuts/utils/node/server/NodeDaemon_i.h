// -*- C++ -*-

//=============================================================================
/**
 * @file      NodeDaemon_i.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODEDAEMON_I_H_
#define _CUTS_NODEDAEMON_I_H_

#include "NodeDaemonS.h"
#include "NodeDaemon_Server_export.h"

// Forward decl.
class CUTS_Virtual_Env_Manager;

/**
 * @class CUTS_NodeDaemon_i
 *
 * Implementation of the CUTS::NodeDaemon interface.
 */
class CUTS_NodeDaemon_i : public POA_CUTS::NodeDaemon
{
public:
  /// Default constructor.
  CUTS_NodeDaemon_i (CUTS_Virtual_Env_Manager & virtual_envs);

  /// Destructor.
  virtual ~CUTS_NodeDaemon_i (void);

  virtual char * active_environment (void);

  virtual void set_active_environment (const char * name);

  virtual void reset (void);

private:
  /// Reference to the virtual environments.
  CUTS_Virtual_Env_Manager & virtual_envs_;
};

#if defined (__CUTS_INLINE__)
#include "NodeDaemon_i.inl"
#endif

#endif  // !defined _CUTS_NODEDAEMON_I_H_
