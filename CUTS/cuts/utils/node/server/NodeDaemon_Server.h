// -*- C++ -*-

//=============================================================================
/**
 * @file      NodeDaemon_Server.h
 *
 * $Id$
 *
 * @author    James H. Hill
 */
//=============================================================================

#ifndef _CUTS_NODEDAEMON_SERVER_H_
#define _CUTS_NODEDAEMON_SERVER_H_

#include "NodeDaemon_Server_export.h"
#include "ace/Auto_Ptr.h"

// Forward decl.
class CUTS_NodeDaemon_Server_Impl;

// Forward decl.
class CUTS_Virtual_Env_Manager;

/**
 * @class CUTS_NodeDaemon_Server
 *
 * Basic implementation of the CUTS::NodeDaemon interface.
 */
class CUTS_NODEDAEMON_SERVER_Export CUTS_NodeDaemon_Server
{
public:
  CUTS_NodeDaemon_Server (CUTS_Virtual_Env_Manager & virtual_envs);

  virtual ~CUTS_NodeDaemon_Server (void);

  virtual int init (int argc, char * argv []);

  virtual int fini (void);

private:
  ACE_Auto_Ptr <CUTS_NodeDaemon_Server_Impl> impl_;
};

#if defined (__CUTS_INLINE__)
#include "NodeDaemon_Server.inl"
#endif

#endif  // !defined _CUTS_NODEDAEMON_SERVER_H_
