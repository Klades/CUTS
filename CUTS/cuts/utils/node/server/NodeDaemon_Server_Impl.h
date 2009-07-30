// -*- C++ -*-

//=============================================================================
/**
 * @file      NodeDaemon_Server_Impl.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODEDAEMON_SERVER_IMPL_H_
#define _CUTS_NODEDAEMON_SERVER_IMPL_H_

#include "cuts/ORB_Server_Task.h"
#include "NodeDaemon_i.h"

// Forward decl.
class CUTS_Virtual_Env_Manager;

/**
 * @class CUTS_NodeDaemon_Server_Impl
 *
 * Implementation of the node daemon's server.
 */
class CUTS_NodeDaemon_Server_Impl
{
public:
  CUTS_NodeDaemon_Server_Impl (CUTS_Virtual_Env_Manager & virtual_envs);

  virtual ~CUTS_NodeDaemon_Server_Impl (void);

  virtual int init (int argc, char * argv []);

  virtual int fini (void);

private:
  int parse_args (int argc, char * argv []);

  ::CORBA::ORB_var orb_;

  ::PortableServer::POA_var root_poa_;

  CUTS_ORB_Server_Task task_;

  CUTS_NodeDaemon_i daemon_;
};

#if defined (__CUTS_INLINE__)
#include "NodeDaemon_Server_Impl.inl"
#endif

#endif  // !defined _CUTS_NODEDAEMON_SERVER_H_
